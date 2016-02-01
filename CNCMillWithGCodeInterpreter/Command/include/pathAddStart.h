#ifndef _PATHADDSTART_H
#define _PATHADDSTART_H

#include "Command.h"
#include "Path.h"

class pathAddStart: public Command
{
    Path & _path;  
	double _x,_y,_z;
public:
	void SetPos(double x, double y, double z);

    pathAddStart(Path & path);

    int execute();

 
};

#endif