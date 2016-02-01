#ifndef _COMMAND_H
#define _COMMAND_H

#include "stdafx.h"
//#include <ostream>
//#include <iostream>
#include "stagePosition.h"

using namespace std;
enum CmdType {cmdAddArc, cmdAddLine, cmdStart, cmdSetOrigin, cmdClearList, cmdStageExecutePath, cmdStageMoveXYZ} ;

class Command
{
	CmdType _cmdType;
 public:  
     virtual int execute() = 0;  
	 void SetType(CmdType cmdType)
     { _cmdType = cmdType; };	 
	 void GetType(CmdType & cmdType)
     { cmdType = _cmdType; };	 
};
#endif
