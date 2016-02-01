#ifndef _STAGEMOVEXY_H
#define _STAGEMOVEXY_H

#include "Command.h"
#include "Stage.h"

class stageMoveXY: public Command 
{
    Stage & _stage;  
	double _x,_y;
public:

    stageMoveXY(Stage & stage, double x, double y);
    int execute();
};

#endif