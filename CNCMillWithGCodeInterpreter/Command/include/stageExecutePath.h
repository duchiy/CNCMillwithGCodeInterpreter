#ifndef _STAGEEXECUTEPATH_H
#define _STAGEEXECUTEPATH_H

#include "Command.h"
#include "Stage.h"
#include "Path.h"

class stageExecutePath: public Command 
{
    Stage & _stage;  
    Path & _path;  
	double _x,_y,_z;
public:

    stageExecutePath(Stage & stage, Path & path);
    int execute();


};

#endif