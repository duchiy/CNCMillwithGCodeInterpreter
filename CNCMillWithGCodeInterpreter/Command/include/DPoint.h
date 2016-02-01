#ifndef _DPOINT_H
#define _DPOINT_H

class DPoint
{
private:

public:
	double _x, _y, _z;
	DPoint();
	DPoint(double x, double y, double z);
	void Set(double x, double y, double z);
	void Set(DPoint myPoint);
	void Get(double & x, double & y, double & z);
	void Get(DPoint & myPoint);
	DPoint Translate(double x, double y, double z);	
	DPoint Change(double x, double y, double z);
};
#endif