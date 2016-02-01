#include "Path.h"
#include "Stage.h"
//#include "stageResetPos.h"
#include "pathAddArc.h"
#include "MillCmd.h"
#include "ParseCNC.h"
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
using namespace std;


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	fstream filestr;

	filestr.open ("C:\\Test Code\\Mill1A\\input\\CircleAtOrigin.nc", fstream::in | fstream::out | fstream::app);
  // >> i/o operations here <<
	std::string line;
	int parenIndex=0;
	int spaceIndex=0;
	int cmdLine=0;
	string cmd;
	vector<string> cmdlist;
	millCmd millCmdC;
	ParseCNC ParseCNC;

	while(filestr){
		std::getline(filestr, line);
		parenIndex=line.find("(",0);
		if (parenIndex == string::npos)
		{
			ParseCNC.ParseLine(line, cmdlist);
			vector<string>::iterator it = cmdlist.begin();

			while (it != cmdlist.end())
			{
				ParseCNC.SetCommand1 (it, cmdlist);
			}
			cmdlist.clear();
		}
	}

	filestr.close();
	ParseCNC.GetCmd(millCmdC);
	millCmdC.InitIter();
	Command *cmd1=millCmdC.GetCommand();
	millCmdC.Iter();
	Command *cmd2=millCmdC.GetCommand();
	millCmdC.Iter();
	Command *cmd3=millCmdC.GetCommand();
	millCmdC.Iter();
	Command *cmd4=millCmdC.GetCommand();
	millCmdC.Iter();
	Command *cmd5=millCmdC.GetCommand();
	millCmdC.Iter();
	Command *cmd6=millCmdC.GetCommand();
	millCmdC.Iter();
	Command *cmd7=millCmdC.GetCommand();
	pathAddArc *d = dynamic_cast<pathAddArc *>(cmd7);
//	Stage	stage;
//	Path	path;
//	MillCtrl millctrl;
//	BOOL bMotion;

//	stageMove *stagemove1 = new stageMove(stage); 
//	stagemove1->SetPos(0.0, 0.0, 0.0);
//	millctrl.SetCommand(stagemove1);

	return 0;
};