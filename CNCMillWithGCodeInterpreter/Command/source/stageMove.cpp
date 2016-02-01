#include "stdafx.h"
#include "stageMove.h"

stageMove::stageMove(Stage & stage, double pos, int axis):_stage(stage)
{
	_pos=pos;
	_axis =axis;
};
int stageMove::execute()
{
	_stage.MoveTo(_pos, _axis, true);
	return 0;
};