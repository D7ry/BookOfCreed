#include "BookOfCreed.h"
#include "include/Utils.h"
/// <summary>
/// Attempt an assassination of a potential target in front of the player.
/// If the target doesn't exist or the player fails any of the condition checks, return false,
/// otherwise return true.
/// </summary>
/// <returns>Whether the assassination is successfully initiated.</returns>
bool BookOfCreed::TryAssassinate()
{
	INFO("trying to assassinate");
	UpdatePcState();
	if (!_isHiddenBladeDrawn) {
		INFO("Hidden blade not drawn!");
		return false;
	}
	RE::PlayerCharacter* pc = RE::PlayerCharacter::GetSingleton();
	if (pc && pc->Is3DLoaded() && _target.ref && _target.ref->Is3DLoaded() && !_target.ref->IsDead()) {
		INFO("Playing assassination idle!");
		RE::Offset::playPairedIdle(pc->GetActorRuntimeData().currentProcess, pc, RE::DEFAULT_OBJECT::kActionIdle, _assassinateIdle_front, true, false, _target.ref);
		return true;
	}
	INFO("Target condition no pass");
	return false;
}
/// <summary>
/// Update the player's state, such as whether the hidden blade is drawn.
/// This function is called on each save load and on each animation event relevant to the hidden blade's drawing.
/// 
/// In Addition, when pc's state transitions from undrawn to drawn, start the raycast the thread to check for potential targets.
/// </summary>
void BookOfCreed::UpdatePcState()
{
	RE::PlayerCharacter* pc = RE::PlayerCharacter::GetSingleton();
	if (!pc) {
		return;
	}
	INFO("Updating pc state");
	bool isHiddenBladeDrawn;
	if (pc->GetGraphVariableBool("bWristbladeArmed", isHiddenBladeDrawn)) {
		//isHiddenBladeDrawn = true;
		if (isHiddenBladeDrawn) {
			INFO("blade drawn");
			if (!_raycastThread_isRunning) {
				INFO("starting raycast func");
				std::jthread t([&] { raycastThread_func();});
				t.detach();
				_raycastThread_isRunning = true;
			}
		}
		this->_isHiddenBladeDrawn = isHiddenBladeDrawn; //update cached state
	} else {
		INFO("failed to get ishiddenbladedrawn var");
	}
}

void BookOfCreed::LoadData()
{
	DtryUtils::formLoader loader("BOS_PairedTest.esp");
	loader.load(_assassinateIdle_front, 0xD61);
}

#define ASSASSINATION_DIST 300.f
/// <summary>
/// Check for nearby target to find the most suitable target for assassination.
/// </summary>
void BookOfCreed::updateTarget()
{
	RE::PlayerCharacter* pc = RE::PlayerCharacter::GetSingleton();
	if (!pc->Is3DLoaded()) {
		return;
	}
	RE::NiPoint3 relativeRayDest(0, 300, pc->GetHeight() * 0.5);  //a forward ray
	
	float rayHitDist;
	RE::TESObjectREFR* rayHit = DtryUtils::rayCast::cast_ray(pc, Utils::get_abs_pos(pc, relativeRayDest), 0.5f, &rayHitDist);
	if (rayHit 
		&& rayHitDist <= ASSASSINATION_DIST
		&& rayHit->GetFormType() == RE::FormType::ActorCharacter && Utils::Actor::isHumanoid(rayHit->As<RE::Actor>())
		&& !rayHit->IsDead()) {
		INFO("Found valid target: {}", rayHit->GetName());
		this->_target.distance = rayHitDist;
		this->_target.ref = rayHit->As<RE::Actor>();
		this->_target.angle = pc->GetHeadingAngle(rayHit);
	} else {
		INFO("failed to find target");
	}

}

#define RAYCAST_INTERVAL 0.3f
void BookOfCreed::raycastThread_func()
{
	while (true) {
		if (!_isHiddenBladeDrawn) {
			INFO("raycastThread_func:hidden blade not drawn anymore, ending raycast");
			break;
		}
		SKSE_ADDTASK([&] 
		{ 
			if(!RE::UI::GetSingleton()->GameIsPaused()) {
				updateTarget();
			}
		})
		//TODO:implement target highlight/widget
		//sleep for 0.3 sec
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(RAYCAST_INTERVAL * 1000)));
	}

	_raycastThread_isRunning = false;
}
