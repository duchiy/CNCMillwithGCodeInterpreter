#include "stdafx.h"
#include "PathAddStart.h"

void pathAddStart::SetPos(double x, double y, double z)
{
	_x=x;_y=y;_z=z;
};
pathAddStart::pathAddStart(Path & path):_path(path)
{
		
};
int pathAddStart::execute()
{
	_path.AddStartA(_x, _y, _z);
	return 0;
};
