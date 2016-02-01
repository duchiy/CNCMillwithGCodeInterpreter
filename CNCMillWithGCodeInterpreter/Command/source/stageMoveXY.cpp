#include "stdafx.h"
#include "stageMoveXY.h"

stageMoveXY::stageMoveXY(Stage & stage, double x, double y):_stage(stage)
{
	_x=x;
	_y=y;

};
int stageMoveXY::execute()
{
	_stage.MoveTo(_x,_y, true);
	return 0;
};