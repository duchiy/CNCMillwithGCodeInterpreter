#include "stdafx.h"

#include "MillCmd.h"

millCmd::millCmd()
{

};
void millCmd::SetCommand(Command *  Command )
{
    commandList.push_back(Command);
}

void millCmd::execute( int i)
{
    commandList[i]->execute();
}
int millCmd::GetNumberOfCommands()
{
	return commandList.size();	
};
void millCmd::InitIter()
{
	
	_iter = commandList.begin();	
};	

void millCmd::Iter()
{
	_iter++;
};	

Command * millCmd::GetCommand()
{

	Command * cmd = *_iter;
	return cmd;
};