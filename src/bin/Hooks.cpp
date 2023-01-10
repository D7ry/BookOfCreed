#include "Hooks.h"
#include "BookOfCreed.h"

void Hooks::Install()
{
	AttackBlockHandler_OnProcessButton::Install();
	AnimationEvent_OnProcessEvent::Install();
}

void Hooks::AttackBlockHandler_OnProcessButton::ProcessButton(RE::AttackBlockHandler* a_this, RE::ButtonEvent* a_event, RE::PlayerControlsData* a_data)
{
	if (a_event->QUserEvent() == "Right Attack/Block" 
		&& BookOfCreed::GetSingleton()->TryAssassinate()) { //assassination success, block input
		return;
	}
	_ProcessButton(a_this, a_event, a_data);
}


inline void Hooks::AnimationEvent_OnProcessEvent::ProcessEvent(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink, RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource)
{
	if (!a_event->holder) {
		return;
	}
	if (a_event->tag == "WristExtendTail" || a_event->tag == "WristRetractTail") {
		BookOfCreed::GetSingleton()->UpdatePcState();
	}
}

Hooks::EventResult Hooks::AnimationEvent_OnProcessEvent::ProcessEvent_PC(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink, RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource)
{
	ProcessEvent(a_sink, a_event, a_eventSource);
	return _ProcessEvent_PC(a_sink, a_event, a_eventSource);
}
