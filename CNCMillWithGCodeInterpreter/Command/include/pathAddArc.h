#ifndef _PATHADDARC_H
#define _PATHADDARC_H

#include "Command.h"
#include "Path.h"

class pathAddArc: public Command
{
    Path & _path;  
	double _xStart,_yStart,_zStart;
	double _xEnd,_yEnd,_zEnd;
	double _xCenter,_yCenter,_zCenter;
	double _i,_j,_k;
public:
	void GetStart(double & x, double & y, double & z);
	void GetEnd(double & x, double & y, double & z);
	void GetCenter(double & x, double & y, double & z);

	void SetStart(double x, double y, double z);
	void SetEnd(double x, double y, double z);
	void SetCenter(double x, double y, double z);
	void SetNormal(double i, double j, double k);

    pathAddArc(Path & path);
    int execute();
 
};

#endif