#ifndef _MILLCTRL_H
#define _MILLCTRL_H

#include "Command.h"
#include <vector>
//using namespace std;

class millCmd
{
public:
    millCmd();
    void SetCommand(Command *  Command );

	void execute( int i);
	int GetNumberOfCommands();	
	void InitIter();	
	void Iter();	
	Command * GetCommand( );
private:
    // Looking at this command list gives
    // this order history
    vector<Command *> commandList;
	vector<Command *>::iterator _iter;
};
#endif