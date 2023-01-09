#pragma once
#include "PCH.h"
namespace Hooks
{
	class AttackBlockHandler_OnProcessButton
	{
	public:
		static void Install()
		{
			REL::Relocation<std::uintptr_t> atkbckVtbl{ RE::VTABLE_AttackBlockHandler[0] };

			_ProcessButton = atkbckVtbl.write_vfunc(0x4, ProcessButton);
			logger::info("hook:AttackBlockHandler_OnProcessButton");
		}

	private:
		static void ProcessButton(RE::AttackBlockHandler* a_this, RE::ButtonEvent* a_event, RE::PlayerControlsData* a_data);
		static inline REL::Relocation<decltype(ProcessButton)> _ProcessButton;
	};
	

	/*Only hooking player events for now*/
	using EventResult = RE::BSEventNotifyControl;
	class AnimationEvent_OnProcessEvent
	{
	public:
		static void Install()
		{
			//REL::Relocation<uintptr_t> AnimEventVtbl_NPC{ RE::VTABLE_Character[2] };
			//_ProcessEvent_NPC = AnimEventVtbl_NPC.write_vfunc(0x1, ProcessEvent_NPC);
		
			REL::Relocation<uintptr_t> AnimEventVtbl_PC{ RE::VTABLE_PlayerCharacter[2] };
			_ProcessEvent_PC = AnimEventVtbl_PC.write_vfunc(0x1, ProcessEvent_PC);
			
		}
		
	private:
		static inline void ProcessEvent(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink, RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource);

		//static EventResult ProcessEvent_NPC(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink, RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource);
		//static inline REL::Relocation<decltype(ProcessEvent_NPC)> _ProcessEvent_NPC;

		static EventResult ProcessEvent_PC(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink, RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource);
		static inline REL::Relocation<decltype(ProcessEvent_PC)> _ProcessEvent_PC;
	};
	
	void Install();
}
