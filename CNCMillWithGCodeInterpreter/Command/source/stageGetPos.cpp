#include "stdafx.h"
#include "stageGetPos.h"

void stageGetPos::GetPos(double & x, double & y, double & z)
{
	x=_x;y=_y;z=_z;
};
stageGetPos::stageGetPos(Stage & stage):_stage(stage)
{
		
};
int stageGetPos::execute()
{
	_stage.GetPos(_x,_y,_z);
	return 0;
};

