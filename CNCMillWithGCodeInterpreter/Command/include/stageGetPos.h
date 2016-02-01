#ifndef _STAGEGETPOSITION_H
#define _STAGEGETPOSITION_H

#include "Command.h"
#include "Stage.h"

class stageGetPos: public Command
{
    Stage & _stage;  
	double _x,_y,_z;
public:
	void GetPos(double & x, double & y, double & z);

    stageGetPos(Stage & stage);

    int execute();
 
};

#endif