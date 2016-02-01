#ifndef _STAGEMOVE_H
#define _STAGEMOVE_H

#include "Command.h"
#include "Stage.h"

class stageMove: public Command 
{
    Stage & _stage;  
	double _x,_y,_z;
	double _pos, _axis;
public:

    stageMove(Stage & stage, double pos, int axis);
    int execute();
};

#endif