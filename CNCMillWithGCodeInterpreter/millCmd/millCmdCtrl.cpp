// millCmd.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "millCmdCtrl.h"
#include "pathAddArc.h"
#include "ParseCNC.h"
	
millCmdCtrl::millCmdCtrl(): _millCmdC()
{
	_retCmd=NULL;
}

//void millCmdCtrl::SetPath(Path * path)
//{
//	_path = path;
//};
//void millCmdCtrl::SetStage(Stage * stage)
//{
//	_stage = stage;
//};

void millCmdCtrl::Message (string message )
{
	MessageBox(0, (LPCTSTR)message.c_str(), (LPCTSTR)"", MB_OK );
};
void millCmdCtrl::ProcessGCode (string GCodeFile )
{
	
	Stage & myStage = Singleton<Stage>::Instance();
	Path & myPath = Singleton<Path>::Instance();
	Message("1");
	double x,y,z;
	myStage.GetPos(x,y,z);
	Message("2");
	myStage.SetVel(3.0, 3.0, 3.0);
	myStage.SetAccel(1.0, 1.0, 1.0);

	myStage.EnableAmp();
	myStage.ResetPos();
	myStage.GetPos(x,y,z);
	Message("3");

//	g_stage.SetPathStatus();
//	myPath.SetPathParams(P_60HZ,   //path frequency = 30 Hz
//					75,       //Store a minimum of 45 points in the path point buffer
//					15000.0,  //X scale - 20000.0 counts per inch
//					15000.0,  //Y scale - 20000.0 counts per inch
//					15000.0,      //Z scale - 1.0 counts per inch - not used
//					0.175);     //acceleration = 1.0 inch/second/second
//	InitServoPathParams(P_30HZ,1, 2, 3);

//	myPath.SetOrigin(0.0, 0.0, 0.0); //set the origin to X = 0, Y = 0, Z = 0
//	myPath.SetFeedrate(0.175);         //feedrate = 1.0 inches/second
//	myPath.SetTangentTolerance(10.0);  //continuous path tangent tolerence = 10 degrees	
	Message("4");

	myStage.InitPathMode(myPath);

	fstream filestr;
	Message("5");
	filestr.open (GCodeFile, fstream::in | fstream::out | fstream::app);

  // >> i/o operations here <<
	std::string line;
	int parenIndex=0;
	int spaceIndex=0;
	int cmdLine=0;
	string cmd;
	vector<string> cmdlist;
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
	ParseCNC.GetCmd(_millCmdC);


};
void millCmdCtrl::RunGCode ( )
{
		
	int numberOfCommands =_millCmdC.GetNumberOfCommands(); 
	for (int i=0; i <= numberOfCommands-1;i++)
	{
		_millCmdC.execute(i);

	}		
};

void millCmdCtrl::RunCommand (int i )
{
	_millCmdC.execute(i);	
};
void millCmdCtrl::InitRun ( )
{
	_millCmdC.InitIter();
};
void millCmdCtrl::Iter ( )
{
	_millCmdC.Iter();
};
int millCmdCtrl::Count ( )
{
	return _millCmdC.GetNumberOfCommands();
};

int millCmdCtrl::GetCommand ( )
{
	Command *retCmd = _millCmdC.GetCommand();
	CmdType cmdType;
	retCmd->GetType(cmdType);
	_retCmd=retCmd;
	return (int)cmdType;
};
void millCmdCtrl::GetStart ( double & X, double & Y, double & Z )
{
	 
//   pathAddArc * myCmd =_retCmd;
	pathAddArc *d = dynamic_cast<pathAddArc *>(_retCmd);
	d->GetStart(X,Y,Z);
};
void millCmdCtrl::GetEnd ( double & X, double & Y, double & Z )
{
	pathAddArc *d = dynamic_cast<pathAddArc *>(_retCmd);
	d->GetEnd(X,Y,Z);
};
void millCmdCtrl::GetCenter ( double & X, double & Y, double & Z )
{
	pathAddArc *d = dynamic_cast<pathAddArc *>(_retCmd);
	d->GetCenter(X,Y,Z);
};
