#include "stdafx.h"
class DPoint
{
private:
	double _x, _y, _z;

public:
	DPoint()
	{
		_x=0.0;
		_y=0.0;
		_z=0.0;
	}
	DPoint(double x, double y, double z)
	{
		_x=x;
		_y=y;
		_z=z;
	}
	void Set(double x, double y, double z)
	{
		_x=x;
		_y=y;
		_z=z;
	}
	void Get(double & x, double & y, double & z)
	{
		x=_x;
		y=_y;
		z=_z;
	}
};