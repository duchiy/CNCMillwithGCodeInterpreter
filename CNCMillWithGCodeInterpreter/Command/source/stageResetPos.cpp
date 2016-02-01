#include "stdafx.h"
#include "stageResetPos.h"

stageResetPos::stageResetPos(Stage & stage):_stage(stage)
{
	g_currentPosition.SetPosition(0.0, 0.0, 0.0);
};
int stageResetPos::execute()
{
	_stage.ResetPos();
	return 0;
};