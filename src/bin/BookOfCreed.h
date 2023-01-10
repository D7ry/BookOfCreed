#pragma once
#include "PCH.h"
/*Handles assassination*/
class BookOfCreed
{
	BookOfCreed()
	{
		_isHiddenBladeDrawn = false;
	}
public:
	static BookOfCreed* GetSingleton()
	{
		static BookOfCreed singleton;
		return &singleton;
	}
	
	bool TryAssassinate();
	
	void UpdatePcState();

	void LoadData();

private:
	struct AssassinationTarget_t
	{
		RE::Actor* ref;
		float distance;
		float angle;
	};
	void updateTarget();
	
	void raycastThread_func();
	std::atomic<bool> _raycastThread_isRunning;
	
	bool _isHiddenBladeDrawn;
	AssassinationTarget_t _target;

	RE::TESIdleForm* _assassinateIdle_front;

};
