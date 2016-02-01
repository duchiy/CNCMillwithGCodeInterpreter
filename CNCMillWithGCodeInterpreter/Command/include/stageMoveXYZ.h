#ifndef _STAGEMOVEXYZ_H
#define _STAGEMOVEXYZ_H

#include "Command.h"
#include "Stage.h"

class stageMoveXYZ: public Command 
{
    Stage & _stage;  
	double _x,_y,_z;
public:

    stageMoveXYZ(Stage & stage, double x, double y, double z);
    int execute();
};

#endif