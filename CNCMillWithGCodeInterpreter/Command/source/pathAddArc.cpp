#include "stdafx.h"
#include "PathAddArc.h"

void pathAddArc::GetStart(double & x, double & y, double & z)
{
	x=_xStart;y=_yStart;z=_zStart;
};
void pathAddArc::GetEnd(double & x, double & y, double & z)
{
	x=_xEnd;y=_yEnd;z=_zEnd;
};
void pathAddArc::GetCenter(double & x, double & y, double & z)
{
	x=_xCenter;y=_yCenter;z=_zCenter;

};

void pathAddArc::SetStart(double x, double y, double z)
{
	_xStart=x;_yStart=y;_zStart=z;
};
void pathAddArc::SetEnd(double x, double y, double z)
{
	_xEnd=x;_yEnd=y;_zEnd=z;
};
void pathAddArc::SetCenter(double x, double y, double z)
{
	_xCenter=x;_yCenter=y;_zCenter=z;

};
void pathAddArc::SetNormal(double i, double j, double k)
{
	_i=i;_j=j;_k=k;
};

pathAddArc::pathAddArc(Path & path):_path(path)
{
		
};
int pathAddArc::execute()
{
	_path.AddArcSegA(_xEnd, _yEnd, _zEnd, _xCenter, _yCenter, _zCenter, _i, _j, _k);
	return 0;
};
