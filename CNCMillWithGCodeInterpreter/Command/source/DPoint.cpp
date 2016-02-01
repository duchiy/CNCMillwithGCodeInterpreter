#include "stdafx.h"
#include "DPoint.h"
#include "FloatingPtHelper.h"
#include <cmath>
#include <limits>
using namespace std;


DPoint::DPoint()
{
	_x=0.0;
	_y=0.0;
	_z=0.0;
}
DPoint::DPoint(double x, double y, double z)
{
	_x=x;
	_y=y;
	_z=z;
}
void DPoint::Set(double x, double y, double z)
{
	_x=x;
	_y=y;
	_z=z;
}
void DPoint::Set(DPoint myPoint)
{
	_x=myPoint._x;
	_y=myPoint._y;
	_z=myPoint._z;
}
void DPoint::Get(double & x, double & y, double & z)
{
	x=_x;
	y=_y;
	z=_z;
}
void DPoint::Get(DPoint & myPoint)
{
	myPoint._x=_x;
	myPoint._y=_y;
	myPoint._z=_z;
}
DPoint DPoint::Translate(double x, double y, double z)
{
	DPoint myPoint;

	myPoint._x=_x+x;
	myPoint._y=_y+y;
	myPoint._z=_z+z;
	
	return myPoint;
};

DPoint DPoint::Change(double x, double y, double z)
{
	DPoint myPoint;
	if (!fequal(x, _x, 10))
	{
		if (fequal(x, 0.0, 10))
		{
			myPoint._x=_x;
		}
		else
		{
			myPoint._x=x;
		}
	}
	
	if (!fequal(y, _y, 10))
	{
		if (fequal(y, 0.0, 10))
		{
			myPoint._y=_y;
		}
		else
		{
			myPoint._y=y;
		}
	}
	
	if (!fequal(z, _z, 10))
	{
		if (fequal(z, 0.0, 10))
		{
			myPoint._z=_z;
		}
		else
		{
			myPoint._z=z;
		}
	}

	return myPoint;
};