#ifndef _PATHADDLINE_H
#define _PATHADDLINE_H

#include "Command.h"
#include "Path.h"

class pathAddLine: public Command
{
    Path & _path;  
	double _x,_y,_z;
public:
	pathAddLine (Path & path, double x, double y, double z);
	void AddPos(double x, double y, double z);
    pathAddLine(Path & path);

    int execute();

 
};

#endif