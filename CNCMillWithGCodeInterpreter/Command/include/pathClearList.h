#ifndef _PATHCLEARLIST_H
#define _PATHCLEARLIST_H

#include "Command.h"
#include "Path.h"

class pathClearList: public Command
{
    Path & _path;  
	double _x,_y,_z;
public:
	void SetPos(double x, double y, double z);

    pathClearList(Path & path, double x, double y, double z);

    int execute();

 
};

#endif