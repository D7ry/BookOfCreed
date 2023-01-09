#include "BookOfCreed.h"
/// <summary>
/// Attempt an assassination of a potential target in front of the player.
/// If the target doesn't exist or the player fails any of the condition checks, return false,
/// otherwise return true.
/// </summary>
/// <returns>Whether the assassination is successfully initiated.</returns>
bool BookOfCreed::TryAssassinate()
{
	if (!_isHiddenBladeDrawn) {
		return false;
	}
	
	return false;
}
/// <summary>
/// Update the player's state, such as whether the hidden blade is drawn.
/// This function is called on each save load and on each animation event relevant to the hidden blade's drawing.
/// </summary>
void BookOfCreed::UpdatePcState()
{
	RE::PlayerCharacter* pc = RE::PlayerCharacter::GetSingleton();
	if (!pc) {
		return;
	}
	bool isHiddenBladeDrawn;
	if (pc->GetGraphVariableBool("bWristbladeArmed", isHiddenBladeDrawn)) {
		this->_isHiddenBladeDrawn = isHiddenBladeDrawn;
	}
}
