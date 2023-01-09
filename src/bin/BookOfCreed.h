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
	
	void updatePcState();

private:
	std::jthread _raycastThread;
	bool _isHiddenBladeDrawn;
};
