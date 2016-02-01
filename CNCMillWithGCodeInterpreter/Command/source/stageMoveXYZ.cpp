#include "stdafx.h"
#include "stageMoveXYZ.h"

stageMoveXYZ::stageMoveXYZ(Stage & stage, double x, double y, double z):_stage(stage)
{
	_x=x;_y=y;_z=z;
};
int stageMoveXYZ::execute()
{
	_stage.MoveTo(_x,_y,_z, true);
	return 0;
};
//void stageMoveXYZ::SetType(CmdType cmdType)
//{
//	SetType(cmdType);
//};
//void stageMoveXYZ::GetType(CmdType & cmdType)
//{
//	GetType(cmdType);
//};
