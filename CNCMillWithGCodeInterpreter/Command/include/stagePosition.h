#ifndef _STAGEPOSITION_H
#define _STAGEPOSITION_H

class stagePosition
{
public:
	stagePosition()
	{
		_x=0; _y=0; _z=0;
	}
	void GetPosition (double & x, double & y, double & z)
	{
		x=_x; y=_y; z=_z;
	}
	void SetPosition (double x, double y, double z)
	{
		_x=x; _y=y; _z=z;
	}
	double _x, _y, _z;

};
static stagePosition g_currentPosition;

#endif