#include "stdafx.h"
#include "PathClearList.h"

void pathClearList::SetPos(double x, double y, double z)
{
	_x=x;_y=y;_z=z;
};
pathClearList::pathClearList(Path & path, double x, double y, double z):_path(path)
{
	_x=x;_y=y;_z=z;		
};
int pathClearList::execute()
{
	_path.ClearSegListA(_x, _y, _z);
	return 0;
};
