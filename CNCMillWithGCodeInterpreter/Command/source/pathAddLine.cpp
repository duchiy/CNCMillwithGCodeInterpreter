#include "stdafx.h"
#include "PathAddLine.h"

void pathAddLine::AddPos(double x, double y, double z)
{
	_x=x;_y=y;_z=z;
};
pathAddLine::pathAddLine(Path & path, double x, double y, double z):_path(path)
{
	AddPos( x, y, z);	
};
int pathAddLine::execute()
{
	_path.AddLineSegA(_x, _y, _z);
	return 0;
};
