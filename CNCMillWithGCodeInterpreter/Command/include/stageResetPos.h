#ifndef _STAGERESETPOS_H
#define _STAGERESETPOS_H

#include "Command.h"
#include "Stage.h"

class stageResetPos: public Command 
{
    Stage & _stage;  

public:

    stageResetPos(Stage & stage);
    int execute();
};

#endif