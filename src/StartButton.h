#pragma once
#ifndef __START_BUTTON__
#define __START_BUTTON__

#include "Button.h"

class StartButton : public Button
{
public:
	StartButton();
	~StartButton();

	bool ButtonClick() override;

private:
	bool m_isClicked;
};

#endif /* defined (__START_BUTTON__) */