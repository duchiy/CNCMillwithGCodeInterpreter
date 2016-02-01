// Motion.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
//#include "path.h"
//#include "NMCCOMTYPES.h"
//#include "nmcServo.h"
//#include "Picservo.h"
//#include "nmccom.h"
//#include "ServoInf.h"
//#include "PathPoint.h"
#include <math.h>
#include "MillCmd.h"
#include "MillCmdCtrl.h"
#include "ParseCNC.h"
#include "Stage.h"
#include "Matrix4x4.h"
#include "Vector4.h"
#include "stageMoveXYZ.h"
#include "stageGetPos.h"
#include <algorithm>
int TestCoordMotion();
int TestCoordMotionShortPath();
int TestCoordMotionCircleAtOrigin();
int TestSplineMotion();
int TestGCode();
int TestGCodeClass();
int TestPtToPtMotionWithServo();
int TestPtToPtMotionShort();
int TestSingleDoublePCSWithStage();
int TestPtToPtMotionInPCSWithStage();
int TestPtToPtMotionInPCSCommand();

int TestPtToPtMotionWithStage();
int TestPtToPtAndCoordStageMotion();
int TestPtToPtAndCoordStageMotionPCS();

int TestPtToPtAndCoordOutPts();

int InitNMCModule3Axis		(int & iModules);
int InitNMCModule3Axis		(int & iModules, Path & path);
int InitNMCModule3AxisStatic		(int & iModules, Stage & stage, Path & path);

int InitPathParam(int pathFreq, int numberOfPts,
				  double xScale, double yScale, double zScale,
				  double pathAccel,
				  double feedrate);
int SetPIDGain_3Axis		();
int SetScaling_3Axis		();
int SetPIDGain_3AxisStatic		(Stage & stage);
int SetScaling_3AxisStatic		(Stage & stage);
int ServoOnNMCModule3Axis	();
int ServoOnNMCModule3AxisStatic	(Stage & stage);
int ServoOnNMCModule3AxisNoReset	();
int CreatePath1				();
int CreatePath1A			();
int CreatePath1A_XOffset( double dX, double dY, double dZ );
int CreatePath1A_XOffset(double dX, double dY, double dZ, Path & vPath);
int CreateSplinePath		();
int CreatePath1_2			();
void ExecutePath3Axis		();
void ResetModules			(int & iModules);
void ResetModulesStatic			(int & iModules);
void ExecutePath();
int SetControlPts(vector<double> & Points);

Stage	 g_stage;
Path	 g_path;


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	string cmdline = GetCommandLine();
	int index = cmdline.find_first_of("-");
	string arg = cmdline.substr(index+1);
	int (*pf)(int)=tolower; 
	transform(arg.begin(), arg.end(), arg.begin(), pf); 
// Command line Arg:  servo, 
	if (!arg.compare("servo"))
		TestPtToPtMotionWithServo();
	
	if (!arg.compare("short_ptp"))
		TestPtToPtMotionShort();

	if (!arg.compare("ptp"))
		TestPtToPtMotionWithStage();
	
	if (!arg.compare("singledouble_ptp_pcs"))
		TestSingleDoublePCSWithStage();
	
	if (!arg.compare("ptp_pcs"))
		TestPtToPtMotionInPCSWithStage();
	
	if (!arg.compare("ptp_command"))
		TestPtToPtMotionInPCSCommand();
	
	if (!arg.compare("coord_ptp"))
		TestPtToPtAndCoordStageMotion();
	
	if (!arg.compare("coord_ptp_pcs"))
		TestPtToPtAndCoordStageMotionPCS();
		
	if (!arg.compare("coord_outpts"))
		TestPtToPtAndCoordOutPts();
	
	if (!arg.compare("coord"))
		TestCoordMotion();
	
	if (!arg.compare("shortcoord"))
		TestCoordMotionShortPath();
	
	if (!arg.compare("spline"))
		TestSplineMotion();
	
	if (!arg.compare("gcode"))
	{
		TestGCode();
	}
	
	if (!arg.compare("gcodeclass"))
	{
		TestGCodeClass();
	}
	return 0;
}
int TestPtToPtMotionWithServo()
{

	NMCSERVO Servo;
	int iModules;
	int iError;
	long lPosition;
	long lXPosition,lYPosition,lZPosition;
	long lCmdXPosition,lCmdYPosition,lCmdZPosition;
	long lCmdXSpeed,lCmdYSpeed,lCmdZSpeed;
	long lCmdXAccel,lCmdYAccel,lCmdZAccel;
	long lVelocity;
	long lHome;
	byte byAD;

	iModules=Servo.Initialize("COM3:");
// Axis 1 = X Axis
// Axis 2 = Y Axis
// Axis 3 = Z Axis
	int iProportional;
	int iDifferential;
	int iIntegral;
	Servo.SetGainLimits(eXAxis, 
		            0,		//IL = 0
					255,	//OL = 255
					0,		//CL = 0
					4000,	//EL = 4000
					1,		//SR = 1
					0		//DC = 0
	                );

	Servo.SetGainLimits(eYAxis, 
		            0,		//IL = 0
					255,	//OL = 255
					0,		//CL = 0
					4000,	//EL = 4000
					1,		//SR = 1
					0		//DC = 0
	                );
	Servo.SetGainLimits(eZAxis, 
		            0,		//IL = 0
					255,	//OL = 255
					0,		//CL = 0
					4000,	//EL = 4000
					1,		//SR = 1
					0		//DC = 0
	                );

	Servo.SetGain(eXAxis, 2144, 7680, 512);
	Servo.GetGain(eXAxis, iProportional, iDifferential,iIntegral);

	Servo.SetGain(eYAxis, 1656, 4064, 128);
	Servo.GetGain(eYAxis, iProportional, iDifferential,iIntegral);

	Servo.SetGain(eZAxis, 1872, 12288, 512);
	Servo.GetGain(eZAxis, iProportional, iDifferential,iIntegral);

	Servo.SetSpeed(eXAxis, 200000);
	Servo.SetAccel(eXAxis, 40000);
	Servo.SetSpeed(eYAxis, 200000);
	Servo.SetAccel(eYAxis, 40000);
	Servo.SetSpeed(eZAxis, 200000);
	Servo.SetAccel(eZAxis, 40000);

	Servo.EnableAmp(eXAxis);
	Servo.EnableAmp(eYAxis);
	Servo.EnableAmp(eZAxis);
	Servo.ResetPosition(eXAxis);
	Servo.ResetPosition(eYAxis);
	Servo.ResetPosition(eZAxis);

	BOOL bMotion;
	iError=Servo.MoveTo(1400, eXAxis);
	iError=Servo.MoveTo(1500, eYAxis);
	iError=Servo.MoveTo(1600, eZAxis);
	lPosition=Servo.GetPosition(eXAxis);
	lPosition=Servo.GetPosition(eYAxis);
	lPosition=Servo.GetPosition(eZAxis);

	lCmdXPosition=Servo.GetCmdPosition(eXAxis);
	lCmdYPosition=Servo.GetCmdPosition(eYAxis);
	lCmdZPosition=Servo.GetCmdPosition(eZAxis);

	lCmdXSpeed=Servo.GetCmdSpeed(eXAxis);
	lCmdYSpeed=Servo.GetCmdSpeed(eYAxis);
	lCmdZSpeed=Servo.GetCmdSpeed(eZAxis);

	lCmdXAccel=Servo.GetCmdAccel(eXAxis);
	lCmdYAccel=Servo.GetCmdAccel(eYAxis);
	lCmdZAccel=Servo.GetCmdAccel(eZAxis);

	iError=Servo.MoveTo(7500,eXAxis);
	iError=Servo.MoveTo(-8000,eYAxis);
	do{
		bMotion=Servo.IsInMotion(eXAxis);
		bMotion=Servo.IsInMotion(eYAxis);
		bMotion=Servo.IsInMotion(eZAxis);
	}while(bMotion);

	lPosition=Servo.GetPosition(eXAxis);
	lPosition=Servo.GetPosition(eYAxis);
	lPosition=Servo.GetPosition(eZAxis);

	iError=Servo.MoveTo(2400, eXAxis);
	iError=Servo.MoveTo(2500, eYAxis);
	iError=Servo.MoveTo(2600, eZAxis);
	do{
		bMotion=Servo.IsInMotion(eXAxis);
		bMotion=Servo.IsInMotion(eYAxis);
		bMotion=Servo.IsInMotion(eZAxis);
	}while(bMotion);
	lPosition=Servo.GetPosition(eXAxis);
	lPosition=Servo.GetPosition(eYAxis);
	lPosition=Servo.GetPosition(eZAxis);

	iError=Servo.MoveTo(1400, eXAxis);
	iError=Servo.MoveTo(1500, eYAxis);
	iError=Servo.MoveTo(1600, eZAxis);
	do{
		bMotion=Servo.IsInMotion(eXAxis);
		bMotion=Servo.IsInMotion(eYAxis);
		bMotion=Servo.IsInMotion(eZAxis);
	}while(bMotion);
	lPosition=Servo.GetPosition(eXAxis);
	lPosition=Servo.GetPosition(eYAxis);
	lPosition=Servo.GetPosition(eZAxis);

	iError=Servo.MoveTo(-1400, eXAxis);
	iError=Servo.MoveTo(-1500, eYAxis);
	iError=Servo.MoveTo(-1600, eZAxis);
	do{
		bMotion=Servo.IsInMotion(eXAxis);
		bMotion=Servo.IsInMotion(eYAxis);
		bMotion=Servo.IsInMotion(eZAxis);
	}while(bMotion);
	lPosition=Servo.GetPosition(eXAxis);
	lPosition=Servo.GetPosition(eYAxis);
	lPosition=Servo.GetPosition(eZAxis);

//	iError=Servo.move(-8000,2);
//	do{
//		bMotion=Servo.IsInMotion();
//	}
//	while(bMotion);
	lHome=Servo.GetHome(eXAxis);
	lHome=Servo.GetHome(eYAxis);
	lVelocity=Servo.GetSpeed(eYAxis);
	byAD=Servo.GetAD(eXAxis);	
	byAD=Servo.GetAD(eYAxis);	

	return 0;
}
int TestPtToPtMotionWithStage()
{

//	NMCSERVO Servo;
	int iModules;
	int iError;
	long lPosition;
	double dXPosition,dYPosition,dZPosition;
	double dCmdXPosition,dCmdYPosition,dCmdZPosition;
	double dCmdXSpeed,dCmdYSpeed,dCmdZSpeed;
	double dCmdXAccel,dCmdYAccel,dCmdZAccel;
	double dVelocity;
	double dXHome, dYHome, dZHome;
	byte byAD;

	iModules=g_stage.Initialize("COM4:");

	SetScaling_3Axis();
	SetPIDGain_3Axis();


	g_stage.SetVel(3.0, 3.0, 3.0);
	g_stage.SetAccel(1.0, 1.0, 1.0);

	g_stage.EnableAmp();
	g_stage.ResetPos();
	
	g_stage.GetCmdVel(dCmdXSpeed, dCmdYSpeed, dCmdZSpeed);
	g_stage.GetSpeed(dCmdXSpeed, dCmdYSpeed, dCmdZSpeed);
	g_stage.GetCmdAccel(dCmdXAccel, dCmdYAccel, dCmdZAccel );

	BOOL bMotion;
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	iError=g_stage.MoveTo(1.00, 1.000, 1.000, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	g_stage.GetCmdVel(dCmdXSpeed, dCmdYSpeed, dCmdZSpeed);
	g_stage.GetCmdAccel(dCmdXAccel, dCmdYAccel, dCmdZAccel );

	iError=g_stage.MoveTo(1.201, 1.202, 1.203, true);

	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	iError=g_stage.MoveTo(0.000, 0.000, 0.000, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	iError=g_stage.MoveTo(-1.201, -1.202, -1.203, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	iError=g_stage.MoveTo(-0.500, -0.500, -0.500, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	iError=g_stage.MoveTo(0.000, 0.000, 0.000, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

//	iError=Servo.move(-8000,2);
//	do{
//		bMotion=Servo.IsInMotion();
//	}
//	while(bMotion);
	g_stage.GetHome( dXHome, dYHome, dZHome);

	return 0;
}
int TestSingleDoublePCSWithStage()
{

//	NMCSERVO Servo;
	int iModules;
	int iError;
	long lPosition;
	double dXPosition,dYPosition,dZPosition;
	double dCmdXPosition,dCmdYPosition,dCmdZPosition;
	double dCmdXSpeed,dCmdYSpeed,dCmdZSpeed;
	double dCmdXAccel,dCmdYAccel,dCmdZAccel;
	double dVelocity;
	double dXHome, dYHome, dZHome;
	byte byAD;
	
	iModules=g_stage.Initialize("COM3:");

	SetScaling_3Axis();
	SetPIDGain_3Axis();

	g_stage.Rotate(180.0);

	g_stage.SetVel(3.0, 3.0, 3.0);
	g_stage.SetAccel(1.0, 1.0, 1.0);

	g_stage.EnableAmp();
	g_stage.ResetPos();
	
	g_stage.GetCmdVel(dCmdXSpeed, dCmdYSpeed, dCmdZSpeed);
	g_stage.GetSpeed(dCmdXSpeed, dCmdYSpeed, dCmdZSpeed);
	g_stage.GetCmdAccel(dCmdXAccel, dCmdYAccel, dCmdZAccel );

	
	BOOL bMotion;
	iError=g_stage.MoveTo(0.0, 0.0, 0.0, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	double x,y,z;
	x=0.5;y= 0.0;z= 0.5;
	iError=g_stage.MoveTo(z,2, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	
	x=0.5;y= 0.0;z= 0.0;
	iError=g_stage.MoveTo(x,0, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	
	x=0.0;y= 0.5;z= 0.0;
	iError=g_stage.MoveTo(y,1, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	x=-0.5;y= 0.0;z= 0.0;
	iError=g_stage.MoveTo(x,0, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	x=0.0;y= -0.5;z= 0.0;
	iError=g_stage.MoveTo(y,1, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	x=0.5;y= 0.5;z= 0.0;
	iError=g_stage.MoveTo(x,y,true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	x=-0.5;y= -0.5;z= 0.0;
	iError=g_stage.MoveTo(x,y,true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	
	x=0.5;y= -0.5;z= 0.0;
	iError=g_stage.MoveTo(x,y,true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	
	x=-0.5;y= 0.5;z= 0.0;
	iError=g_stage.MoveTo(x,y,true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

//	iError=Servo.move(-8000,2);
//	do{
//		bMotion=Servo.IsInMotion();
//	}
//	while(bMotion);
//	g_stage.GetHome( dXHome, dYHome, dZHome);

	return 0;
}
int TestPtToPtMotionInPCSWithStage()
{

//	NMCSERVO Servo;
	int iModules;
	int iError;
	long lPosition;
	double dXPosition,dYPosition,dZPosition;
	double dCmdXPosition,dCmdYPosition,dCmdZPosition;
	double dCmdXSpeed,dCmdYSpeed,dCmdZSpeed;
	double dCmdXAccel,dCmdYAccel,dCmdZAccel;
	double dVelocity;
	double dXHome, dYHome, dZHome;
	byte byAD;
	
	iModules=g_stage.Initialize("COM3:");

	SetScaling_3Axis();
	SetPIDGain_3Axis();

	g_stage.Rotate(180.0);

	g_stage.SetVel(3.0, 3.0, 3.0);
	g_stage.SetAccel(1.0, 1.0, 1.0);

	g_stage.EnableAmp();
	g_stage.ResetPos();
	
	g_stage.GetCmdVel(dCmdXSpeed, dCmdYSpeed, dCmdZSpeed);
	g_stage.GetSpeed(dCmdXSpeed, dCmdYSpeed, dCmdZSpeed);
	g_stage.GetCmdAccel(dCmdXAccel, dCmdYAccel, dCmdZAccel );

	
	BOOL bMotion;
	iError=g_stage.MoveTo(0.0, 0.0, 0.0, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	double x,y,z;
	x=0.5;y= 0.0;z= 0.0;
	iError=g_stage.MoveTo(x,y,z, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	
	x=0.0;y= 0.5;z= 0.0;
	iError=g_stage.MoveTo(x,y,z, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	x=-0.5;y= 0.0;z= 0.0;
	iError=g_stage.MoveTo(x,y,z, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	x=0.0;y= -0.5;z= 0.0;
	iError=g_stage.MoveTo(x,y,z, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	x=0.5;y= 0.5;z= 0.0;
	iError=g_stage.MoveTo(x,y,z, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

	x=-0.5;y= -0.5;z= 0.0;
	iError=g_stage.MoveTo(x,y,z, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	
	x=0.5;y= -0.5;z= 0.0;
	iError=g_stage.MoveTo(x,y,z, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	
	x=-0.5;y= 0.5;z= 0.0;
	iError=g_stage.MoveTo(x,y,z, true);
	g_stage.GetPos(dXPosition, dYPosition, dZPosition );

//	iError=Servo.move(-8000,2);
//	do{
//		bMotion=Servo.IsInMotion();
//	}
//	while(bMotion);
//	g_stage.GetHome( dXHome, dYHome, dZHome);

	return 0;
}
int TestPtToPtMotionInPCSCommand()
{

//	NMCSERVO Servo;
	int iModules;
	int iError;
	long lPosition;
	double dXPosition,dYPosition,dZPosition;
	double dCmdXPosition,dCmdYPosition,dCmdZPosition;
	double dCmdXSpeed,dCmdYSpeed,dCmdZSpeed;
	double dCmdXAccel,dCmdYAccel,dCmdZAccel;
	double dVelocity;
	double dXHome, dYHome, dZHome;
	byte byAD;
	
	iModules=g_stage.Initialize("COM9:");

	SetScaling_3Axis();
	SetPIDGain_3Axis();

	g_stage.Rotate(180.0);

	g_stage.SetVel(3.0, 3.0, 3.0);
	g_stage.SetAccel(1.0, 1.0, 1.0);

	g_stage.EnableAmp();
	g_stage.ResetPos();
	
	g_stage.GetCmdVel(dCmdXSpeed, dCmdYSpeed, dCmdZSpeed);
	g_stage.GetSpeed(dCmdXSpeed, dCmdYSpeed, dCmdZSpeed);
	g_stage.GetCmdAccel(dCmdXAccel, dCmdYAccel, dCmdZAccel );

	millCmd millctrl;
	BOOL bMotion;

//	iError=g_stage.MoveTo(0.0, 0.0, 0.0, true);
//	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	stageMoveXYZ *stagemove1 = new stageMoveXYZ(g_stage, 0.0, 0.0, 0.0); 
	millctrl.SetCommand(stagemove1);

	stageGetPos *stagegetpos1 = new stageGetPos(g_stage);
	millctrl.SetCommand(stagegetpos1);

	double x,y,z;
//	x=0.5;y= 0.0;z= 0.0;
//	iError=g_stage.MoveTo(x,y,z, true);
//	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	stageMoveXYZ *stagemove2 = new stageMoveXYZ(g_stage,0.5, 0.0, 0.0); 
	millctrl.SetCommand(stagemove2);
	stageGetPos *stagegetpos2 = new stageGetPos(g_stage);
	millctrl.SetCommand(stagegetpos2);
	
//	x=0.0;y= 0.5;z= 0.0;
//	iError=g_stage.MoveTo(x,y,z, true);
//	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	stageMoveXYZ *stagemove3 = new stageMoveXYZ(g_stage,0.0, 0.5, 0.0); 
	millctrl.SetCommand(stagemove3);
	stageGetPos *stagegetpos3 = new stageGetPos(g_stage);
	millctrl.SetCommand(stagegetpos3);

//	x=-0.5;y= 0.0;z= 0.0;
//	iError=g_stage.MoveTo(x,y,z, true);
//	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	stageMoveXYZ *stagemove4 = new stageMoveXYZ(g_stage,-0.5, 0.0, 0.0); 
	millctrl.SetCommand(stagemove4);
	stageGetPos *stagegetpos4 = new stageGetPos(g_stage);
	millctrl.SetCommand(stagegetpos4);

//	x=0.0;y= -0.5;z= 0.0;
//	iError=g_stage.MoveTo(x,y,z, true);
//	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	stageMoveXYZ *stagemove5 = new stageMoveXYZ(g_stage,0.0, -0.5, 0.0); 
	millctrl.SetCommand(stagemove5);
	stageGetPos *stagegetpos5 = new stageGetPos(g_stage);
	millctrl.SetCommand(stagegetpos5);

//	x=0.5;y= 0.5;z= 0.0;
//	iError=g_stage.MoveTo(x,y,z, true);
//	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	stageMoveXYZ *stagemove6 = new stageMoveXYZ(g_stage,0.5, 0.5, 0.0); 
	millctrl.SetCommand(stagemove6);
	stageGetPos *stagegetpos6 = new stageGetPos(g_stage);
	millctrl.SetCommand(stagegetpos6);

//	x=-0.5;y= -0.5;z= 0.0;
//	iError=g_stage.MoveTo(x,y,z, true);
//	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	stageMoveXYZ *stagemove7 = new stageMoveXYZ(g_stage,-0.5, 0.5, 0.0); 
	millctrl.SetCommand(stagemove7);
	stageGetPos *stagegetpos7 = new stageGetPos(g_stage);
	millctrl.SetCommand(stagegetpos7);
	
//	x=0.5;y= -0.5;z= 0.0;
//	iError=g_stage.MoveTo(x,y,z, true);
//	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	stageMoveXYZ *stagemove8 = new stageMoveXYZ(g_stage,0.5, -0.5, 0.0); 
	millctrl.SetCommand(stagemove8);
	stageGetPos *stagegetpos8 = new stageGetPos(g_stage);
	millctrl.SetCommand(stagegetpos8);
	
//	x=-0.5;y= 0.5;z= 0.0;
//	iError=g_stage.MoveTo(x,y,z, true);
//	g_stage.GetPos(dXPosition, dYPosition, dZPosition );
	stageMoveXYZ *stagemove9 = new stageMoveXYZ(g_stage,-0.5, 0.5, 0.0); 
	millctrl.SetCommand(stagemove9);
	stageGetPos *stagegetpos9 = new stageGetPos(g_stage);
	millctrl.SetCommand(stagegetpos9);
	int numberOfCommands =millctrl.GetNumberOfCommands(); 
	for (int i=0; i <= numberOfCommands-1;i++)
	{
		millctrl.execute(i);

	}
//	iError=Servo.move(-8000,2);
//	do{
//		bMotion=Servo.IsInMotion();
//	}
//	while(bMotion);
//	g_stage.GetHome( dXHome, dYHome, dZHome);

	return 0;
}
int TestPtToPtMotionShort()
{

//	NMCSERVO Servo;
	int iModules;
	int iError;
	long lPosition;
	double XPos,YPos,ZPos;
	double CmXPos,CmdYPos,CmdZPos;
	double dCmdXSpeed,dCmdYSpeed,dCmdZSpeed;
	double dCmdXAccel,dCmdYAccel,dCmdZAccel;
	double dVelocity;
	double dXHome, dYHome, dZHome;
	byte byAD;

	iModules=g_stage.Initialize("COM4:");

	SetScaling_3Axis();
	SetPIDGain_3Axis();


	g_stage.SetVel(3.0, 3.0, 3.0);
	g_stage.SetAccel(6.0, 6.0, 6.0);

	g_stage.EnableAmp();
	g_stage.ResetPos();
	g_stage.GetHome( dXHome, dYHome, dZHome);

	BOOL bMotion;
	iError=g_stage.MoveRel(0.00, 0.00, 0.15, true);
	iError=g_stage.MoveRel(0.00, 0.00, 0.15, true);
	iError=g_stage.MoveRel(0.00, 0.00, 0.15, true);
	iError=g_stage.MoveRel(0.15, 0.00, 0.00, true);
	iError=g_stage.MoveRel(0.15, 0.00, 0.00, true);
	iError=g_stage.MoveRel(0.15, 0.00, 0.00, true);
	iError=g_stage.MoveRel(0.00, 0.15, 0.00, true);
	iError=g_stage.MoveRel(0.00, 0.15, 0.00, true);
	iError=g_stage.MoveRel(0.00, 0.15, 0.00, true);
	iError=g_stage.MoveTo(1.00, 1.000, 1.000, true);
	g_stage.GetPos(XPos, YPos, ZPos );
	if ( !((XPos < 1.02) && (XPos > 0.98)) && 
		 !((YPos < 1.02) && (YPos > 0.98)) &&
		 !((ZPos < 1.02) && (ZPos > 0.98))   )
		 MessageBox(NULL, "Error with Position","Error Dialog", 1);

	g_stage.GetHome( dXHome, dYHome, dZHome);

	g_stage.GetCmdAccel(dCmdXSpeed, dCmdYSpeed, dCmdZSpeed);
	g_stage.GetCmdAccel(dCmdXAccel, dCmdYAccel, dCmdZAccel );

	iError=g_stage.MoveTo(0.0, 0.0, 0.0, true);

	g_stage.GetPos(XPos, YPos, ZPos );
	if ( !((XPos < 0.02) && (XPos > -0.02)) && 
		 !((YPos < 0.02) && (YPos > -0.02)) &&
		 !((ZPos < 0.02) && (ZPos > -0.02))   )
		 MessageBox(NULL, "Error with Position","Error Dialog", 1);

	iError=g_stage.MoveTo(0.000, 0.000, 0.000, true);
	g_stage.GetPos(XPos, YPos, ZPos );

	g_stage.GetHome( dXHome, dYHome, dZHome);

	return 0;
}	
int TestPtToPtAndCoordStageMotion()
{
	
	int iModule;
	int iError;
	double dX, dY, dZ;

	Path vPath;

	iError=InitNMCModule3Axis (iModule, vPath);

	g_stage.Rotate(180.0);
	g_stage.SetVel(3.0, 3.0, 3.0);
	g_stage.SetAccel(1.0, 1.0, 1.0);

//	g_stage.EnableAmp();
//	g_stage.ResetPos();
//	g_stage.SetPathStatus();

//	g_stage.EnableAmp();
//	g_stage.ResetPos();
//	g_stage.SetPathStatus();
	vPath.SetPathParams(P_60HZ,   //path frequency = 30 Hz
					75,       //Store a minimum of 45 points in the path point buffer
					15000.0,  //X scale - 20000.0 counts per inch
					15000.0,  //Y scale - 20000.0 counts per inch
					15000.0,      //Z scale - 1.0 counts per inch - not used
					0.175);     //acceleration = 1.0 inch/second/second
//	InitServoPathParams(P_30HZ,1, 2, 3);

	vPath.SetOrigin(0.0, 0.0, 0.0); //set the origin to X = 0, Y = 0, Z = 0
	vPath.SetFeedrate(0.175);         //feedrate = 1.0 inches/second
	vPath.SetTangentTolerance(10.0);  //continuous path tangent tolerence = 10 degrees	
	g_stage.InitPathMode(vPath);
	

	BOOL bMotion;
	iError=g_stage.MoveTo(0.0, 0.000, -0.5, true);
	g_stage.GetPos( dX, dY, dZ );
	CreatePath1A_XOffset( dX, dY, dZ, vPath);
	ExecutePath3Axis();
	
	iError=g_stage.MoveTo(1.0, 0.000, 0.000, true);
	iError=g_stage.MoveTo(1.0, 0.000, -0.5, true);

	g_stage.GetPos( dX, dY, dZ );
	CreatePath1A_XOffset( dX, dY, dZ, vPath );
	ExecutePath3Axis();
	
	iError=g_stage.MoveTo(-1.0, 1.000, 0.0, true);
	iError=g_stage.MoveTo(-1.0, 1.000, -0.5, true);
	g_stage.GetPos( dX, dY, dZ );
	CreatePath1A_XOffset( dX, dY, dZ, vPath );
	ExecutePath3Axis();
	
	iError=g_stage.MoveTo(0.0, 0.000, 0.000, true);

	return 0;
};
int TestPtToPtAndCoordStageMotionPCS()
{
	
	int iModule;
	int iError;
	double dX=0.0, dY=0.0, dZ=0.0;
	Path vPath;

	iError=InitNMCModule3Axis (iModule, vPath);

	g_stage.Rotate(180.0);
	g_stage.SetVel(3.0, 3.0, 3.0);
	g_stage.SetAccel(1.0, 1.0, 1.0);

//	g_stage.EnableAmp();
//	g_stage.ResetPos();
//	g_stage.SetPathStatus();
	vPath.SetPathParams(P_60HZ,   //path frequency = 30 Hz
					75,       //Store a minimum of 45 points in the path point buffer
					15000.0,  //X scale - 20000.0 counts per inch
					15000.0,  //Y scale - 20000.0 counts per inch
					15000.0,      //Z scale - 1.0 counts per inch - not used
					0.175);     //acceleration = 1.0 inch/second/second
//	InitServoPathParams(P_30HZ,1, 2, 3);

	vPath.SetOrigin(0.0, 0.0, 0.0); //set the origin to X = 0, Y = 0, Z = 0
	vPath.SetFeedrate(0.175);         //feedrate = 1.0 inches/second
	vPath.SetTangentTolerance(10.0);  //continuous path tangent tolerence = 10 degrees	
	g_stage.InitPathMode(vPath);

//Initialize path control module parameters
//	g_stage.SetPathFreq(P_60HZ);
//	g_stage.SetNumberOfPoints(75);
//	g_stage.SetScale(15000.0, 15000.0, 15000.0);
//	g_stage.SetPathAcceleration(0.175);
//	g_stage.SetFeedrate(0.175);         //feedrate = 1.0 inches/second
//	g_stage.SetTangentTolerance(10.0);  //continuous path tangent tolerence = 10 degrees
//	g_stage.SetPathParams();     //acceleration = 1.0 inch/second/second
	

//	g_stage.SetOrigin( 0.0, 0.0, 0.0 ); //set the origin to X = 0, Y = 0, Z = 0
	
	BOOL bMotion;
	iError=g_stage.MoveTo(0.0, 0.0, 0.0, true);
	g_stage.GetPos( dX, dY, dZ );
	CreatePath1A_XOffset( dX, dY, dZ, vPath );
//	CreatePath1A_XOffset( dX, dY, dZ );
	g_stage.ExecuteCoordMotion(vPath);

	iError=g_stage.MoveTo(1.0, 0.000, 0.000, true);
//	iError=g_stage.MoveTo(1.0, 0.000, -0.5, true);

	g_stage.GetPos( dX, dY, dZ );
	CreatePath1A_XOffset( dX, dY, dZ, vPath );
	g_stage.ExecuteCoordMotion(vPath);

//	ExecutePath3Axis();
	
//	iError=g_stage.MoveTo(-1.0, 1.000, 0.0, true);
//	iError=g_stage.MoveTo(-1.0, 1.000, -0.5, true);
//	g_stage.GetPos( dX, dY, dZ );
//	CreatePath1A_XOffset( dX, dY, dZ );
//	ExecutePath3Axis();
	
	iError=g_stage.MoveTo(0.0, 0.000, 0.000, true);

	return 0;
};

int TestPtToPtAndCoordOutPts()
{
	
	int iModule;
	int iError;
	double dX, dY, dZ;

	iError=InitNMCModule3Axis (iModule);

	g_stage.SetVel(3.0, 3.0, 3.0);
	g_stage.SetAccel(1.0, 1.0, 1.0);

//	g_stage.EnableAmp();
//	g_stage.ResetPos();
//	g_stage.SetPathStatus();

//Initialize path control module parameters
	g_stage.SetPathFreq(P_60HZ);
	g_stage.SetNumberOfPoints(75);
	g_stage.SetScale(15000.0, 15000.0, 15000.0);
	g_stage.SetPathAcceleration(0.175);
	g_stage.SetFeedrate(0.175);         //feedrate = 1.0 inches/second
	g_stage.SetTangentTolerance(10.0);  //continuous path tangent tolerence = 10 degrees
	g_stage.SetPathParams();     //acceleration = 1.0 inch/second/second
	g_stage.SetOrigin( 0.0, 0.0, 0.0 ); //set the origin to X = 0, Y = 0, Z = 0
	
//	g_stage.ClosePointsOut();

	return 0;
};

int TestCoordMotion()
{
	
//	NMCSERVO Servo;
	int iError;
	int iModule;
	double dX, dY, dZ;
	iError=InitNMCModule3Axis (iModule);
	if (iModule < 3)
		return -1;
//	g_stage.ResetPos();
//	InitPathParam(P_30HZ, 75, 
//		          66845.7447, 66845.7447, 2*66845.7447,
//				  0.001,
//				  0.001);
	InitPathParam(P_60HZ, 75, 
		          6684.57447, 6684.57447, 6684.57447,
				  1.0,
				  1.0);

	iError=CreatePath1();
	ExecutePath3Axis();
	iError=CreatePath1_2();
	ExecutePath3Axis();
	
	iError=CreatePath1();
	ExecutePath3Axis();
	iError=CreatePath1_2();
	ExecutePath3Axis();
	ResetModules(iModule);
	return 0;
};

int TestCoordMotionShortPath()
{
	
	int iError;
	int res;
	int iModule;
	Path vPath;

	iError=InitNMCModule3Axis (iModule, vPath);
	if (iModule < 3)
		return -1;
	
	g_stage.Rotate(180.0);
	g_stage.SetVel(3.0, 3.0, 3.0);
	g_stage.SetAccel(1.0, 1.0, 1.0);

	vPath.SetPathParams(P_60HZ,   //path frequency = 30 Hz
					75,       //Store a minimum of 45 points in the path point buffer
					6684.57447,  //X scale - 20000.0 counts per inch
					6684.57447,  //Y scale - 20000.0 counts per inch
					2*6684.57447,      //Z scale - 1.0 counts per inch - not used
					1.0);     //acceleration = 1.0 inch/second/second

	vPath.SetOrigin(0.0, 0.0, 0.0); //set the origin to X = 0, Y = 0, Z = 0
	vPath.SetFeedrate(1.0);         //feedrate = 1.0 inches/second
	vPath.SetTangentTolerance(10.0);  //continuous path tangent tolerence = 10 degrees	
	g_stage.InitPathMode(vPath);
	
	double x,y,z;
//	g_stage.GetPos(x,y,z);
//	InitPathParam(P_60HZ, 60, 
//		          6684.57447, 6684.57447, 2*6684.57447,
//				  1.0,
//				  1.0);

	g_stage.GetPos(x,y,z);
	g_stage.ResetPos();
//Clear the segment list and set the starting point for the path
//  at X = 0, Y = 1, Z = 0
	vPath.ClearSegListA(0,0,0);    

//Add a segment to move to x=0, y=2, z=0
	res = vPath.AddLineSegA(0.0, 1.0, 0.0);    
	if (res<0) return -1;
	
	res = vPath.AddArcSegA( 1.0, 2.0, 0.0,     //end point of arc: x=1, y=2, z=0
							 1.0, 1.0, 0.0,     //center point of arc: x=1, y=1, z = 0
							 0.0, 0.0, -1.0 );   //normal vector to arc plane: x = 0, y = 0, z = -1
	if (res<0) return -1;
	g_stage.ExecuteCoordMotion(vPath);
	
	vPath.ClearSegListA(1.0, 2.0, 0.0);    
	g_stage.GetPos(x,y,z);
	
	res = vPath.AddLineSegA(2.0, 2.0, 0.0);    //line segment endpoint: x=4, y=3, z=0
	if (res<0) return -1;
	
	res = vPath.AddArcSegA( 3.0, 1.0, 0.0,     //end point of arc: x=5, y=2, z=0
							 2.0, 1.0, 0.0,     //center point of arc: x=4, y=2, z = 0
							 0.0, 0.0, -1.0 );   //normal vector to arc plane: x = 0, y = 0, z = -1
	if (res<0) return -1;
	
//line segment endpoint: x=5, y=0, z=0
	res = vPath.AddLineSegA(3.0, 0.0, 0.0);    
	if (res<0) return -1;

//line segment endpoint: x=5, y=0, z=0
	g_stage.ExecuteCoordMotion(vPath);

	vPath.ClearSegListA(3.0, 0.0, 0.0);    
	if (res<0) return -1;

//line segment endpoint: x=5, y=0, z=0
	res = vPath.AddLineSegA(0.0, 0.0, 0.0);    
	if (res<0) return -1;
	g_stage.ExecuteCoordMotion(vPath);
	
	ResetModules(iModule);
	return 0;
};

int TestCoordMotionCircleAtOrigin()
{
	
	int iModule;
	int iError;
	double dX=0.0, dY=0.0, dZ=0.0;
	Path vPath;

	iError=InitNMCModule3Axis (iModule, vPath);

	g_stage.Rotate(180.0);
	g_stage.SetVel(3.0, 3.0, 3.0);
	g_stage.SetAccel(1.0, 1.0, 1.0);

	vPath.SetPathParams(P_60HZ,   //path frequency = 30 Hz
					75,       //Store a minimum of 45 points in the path point buffer
					15000.0,  //X scale - 20000.0 counts per inch
					15000.0,  //Y scale - 20000.0 counts per inch
					15000.0,      //Z scale - 1.0 counts per inch - not used
					0.175);     //acceleration = 1.0 inch/second/second

	vPath.SetOrigin(0.0, 0.0, 0.0); //set the origin to X = 0, Y = 0, Z = 0
	vPath.SetFeedrate(0.175);         //feedrate = 1.0 inches/second
	vPath.SetTangentTolerance(10.0);  //continuous path tangent tolerence = 10 degrees	
	g_stage.InitPathMode(vPath);

	

	
	BOOL bMotion;
	iError=g_stage.MoveTo(2.5, 0.0, 0.0, true);
	g_stage.GetPos( dX, dY, dZ );

	vPath.ClearSegListA(2.5, 0.0, 0.0);    //Clear the segment list and set the
									//  starting point for the path
									//  at X = 0, Y = 1, Z = 0

//
//Add line and arc segments to the path module's segment list for first move
//
	int res;
	res = vPath.AddArcSegA( 0.0, 2.5, 0.0,     //end point of arc: x=1, y=3, z=0
							 0.0, 0.0, 0.0,     //center point of arc: x=1, y=2, z = 0
							 0.0, 0.0, 1.0 );   //normal vector to arc plane: x = 0, y = 0, z = -1
	if (res<0) return -1;
	g_stage.ExecuteCoordMotion(vPath);

	vPath.ClearSegListA(0.0, 2.5, 0.0);    //Clear the segment list and set the
									//  starting point for the path
									//  at X = 0, Y = 1, Z = 0

//
//Add line and arc segments to the path module's segment list for first move
//

	res = vPath.AddArcSegA( -2.5, 0.0, 0.0,     //end point of arc: x=1, y=3, z=0
							 0.0, 0.0, 0.0,     //center point of arc: x=1, y=2, z = 0
							 0.0, 0.0, 1.0 );   //normal vector to arc plane: x = 0, y = 0, z = -1
	if (res<0) return -1;
	g_stage.ExecuteCoordMotion(vPath);


//	ExecutePath3Axis();
	
//	iError=g_stage.MoveTo(-1.0, 1.000, 0.0, true);
//	iError=g_stage.MoveTo(-1.0, 1.000, -0.5, true);
//	g_stage.GetPos( dX, dY, dZ );
//	CreatePath1A_XOffset( dX, dY, dZ );
//	ExecutePath3Axis();
	
	iError=g_stage.MoveTo(0.0, 0.000, 0.000, true);
	return 0;
};
int TestSplineMotion()
{
	
//	NMCSERVO Servo;
	int iError;
	int iModule;
	iError=InitNMCModule3Axis (iModule);
	if (iModule < 3)
		return -1;
	InitPathParam(P_60HZ, 80, 
		          6684.57447, 6684.57447, 6684.57447,
				  .5,
				  .5);
	iError=CreateSplinePath();
	ExecutePath3Axis();
	return 0;
};

int TestGCode()
{
	int iError;
	int res;
	int iModule;

	Stage & _stage = Singleton<Stage>::Instance();
	Path  & _path = Singleton<Path>::Instance();

	iError=InitNMCModule3AxisStatic (iModule, _stage, _path);
	if (iModule < 3)
		return -1;
	double x,y,z;
	_stage.GetPos(x,y,z);

	_stage.Rotate(180.0);
	_stage.SetVel(3.0, 3.0, 3.0);
	_stage.SetAccel(1.0, 1.0, 1.0);

	_stage.EnableAmp();
	_stage.ResetPos();
	_stage.GetPos(x,y,z);

//	g_stage.SetPathStatus();
	_path.SetPathParams(P_60HZ,   //path frequency = 30 Hz
					75,       //Store a minimum of 45 points in the path point buffer
					15000.0,  //X scale - 20000.0 counts per inch
					15000.0,  //Y scale - 20000.0 counts per inch
					15000.0,      //Z scale - 1.0 counts per inch - not used
					0.175);     //acceleration = 1.0 inch/second/second
//	InitServoPathParams(P_30HZ,1, 2, 3);

	_path.SetOrigin(0.0, 0.0, 0.0); //set the origin to X = 0, Y = 0, Z = 0
	_path.SetFeedrate(0.175);         //feedrate = 1.0 inches/second
	_path.SetTangentTolerance(10.0);  //continuous path tangent tolerence = 10 degrees	
	_stage.InitPathMode(_path);

	fstream filestr;

	filestr.open ("C:\\Program Files (x86)\\Mill1A\\input\\CircleAtOrigin.nc", fstream::in | fstream::out | fstream::app);

  // >> i/o operations here <<
	std::string line;
	int parenIndex=0;
	int spaceIndex=0;
	int cmdLine=0;
	string cmd;
	vector<string> cmdlist;
	millCmd millCmdC;
	ParseCNC ParseCNC;
//	ParseCNC.SetStage(_stage);
//	ParseCNC.SetPath(_path);
//	ParseCNC.SetStage(static_cast<Stage *>(&vStage));
//	ParseCNC.SetPath(static_cast<Path *>(&vPath));

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
	int numberOfCommands =millCmdC.GetNumberOfCommands(); 
	for (int i=0; i <= numberOfCommands-1;i++)
	{
		millCmdC.execute(i);

	}


	ResetModules(iModule);
	return 0;
}
int TestGCodeClass()
{
	int iError;
	int res;
	int iModule;
	millCmdCtrl millcmdCtrl;
	Stage & _stage = Singleton<Stage>::Instance();
	Path  & _path = Singleton<Path>::Instance();

	_path.SetPathParams(P_60HZ,   //path frequency = 30 Hz
					75,       //Store a minimum of 45 points in the path point buffer
					15000.0,  //X scale - 20000.0 counts per inch
					15000.0,  //Y scale - 20000.0 counts per inch
					15000.0,      //Z scale - 1.0 counts per inch - not used
					0.200);     //acceleration = 1.0 inch/second/second
//	InitServoPathParams(P_30HZ,1, 2, 3);

	_path.SetOrigin(0.0, 0.0, 0.0); //set the origin to X = 0, Y = 0, Z = 0
	_path.SetFeedrate(0.200);         //feedrate = 1.0 inches/second
	_path.SetTangentTolerance(10.0);  //continuous path tangent tolerence = 10 degrees	
	iError=InitNMCModule3AxisStatic (iModule, _stage, _path);
	if (iModule < 3)
		return -1;

//	millcmdCtrl.SetStage(&_stage);
//	millcmdCtrl.SetPath(&_path);
	millcmdCtrl.ProcessGCode("C:\\Program Files (x86)\\Mill1A\\input\\CircleAtOrigin.nc");
//	millcmdCtrl.RunGCode();

	int numberCmds=millcmdCtrl.Count();
	int itype=0;
	millcmdCtrl.InitRun();
	double x1,y1,z1;
	double x2,y2,z2;
	double x3,y3,z3;
	for(int i=0; i < numberCmds; i++)
	{
		millcmdCtrl.RunCommand(i);
		itype=millcmdCtrl.GetCommand();
		if (itype == 0)
		{
			millcmdCtrl.GetStart(x1,y1,z1);
			millcmdCtrl.GetEnd(x2,y2,z2);
			millcmdCtrl.GetCenter(x3,y3,z3);
		}
		millcmdCtrl.Iter();

		
	}

	ResetModules(iModule);
	return 0;
}
int InitNMCModule3Axis		(int & iModules)
{
 
	iModules=g_stage.Initialize("COM9:");

	if (iModules < 3)
	{
		MessageBox(NULL,"3 servos not found","",MB_TASKMODAL | MB_SETFOREGROUND);
		return -1;
	}

//Set the group address for both controllers to 128
	g_stage.SetGroupAddress(128, eXAxis);
	SetScaling_3Axis();
	SetPIDGain_3Axis();
	ServoOnNMCModule3Axis();

//Set the required status items for the path control module
	g_stage.SetPathStatus();

//  ServoSetIoCtrl(1, IO1_IN | IO2_IN);
//	ServoSetIoCtrl(2, IO1_IN | IO2_IN);
//	ServoSetIoCtrl(3, IO1_IN | IO2_IN);

	return 0;
};
int InitNMCModule3Axis		(int & iModules, Path & path)
{
 
	iModules=g_stage.Initialize("COM9:", path);

	if (iModules < 3)
	{
		MessageBox(NULL,"3 servos not found","",MB_TASKMODAL | MB_SETFOREGROUND);
		return -1;
	}

//Set the group address for both controllers to 128
	g_stage.SetGroupAddress(128, eXAxis);
	SetScaling_3Axis();
	SetPIDGain_3Axis();
	ServoOnNMCModule3Axis();

//Set the required status items for the path control module
	g_stage.SetPathStatus();

//  ServoSetIoCtrl(1, IO1_IN | IO2_IN);
//	ServoSetIoCtrl(2, IO1_IN | IO2_IN);
//	ServoSetIoCtrl(3, IO1_IN | IO2_IN);

	return 0;
};
int InitNMCModule3AxisStatic		(int & iModules, Stage & stage, Path & path)
{
 
	iModules=stage.Initialize("COM4:");

	if (iModules < 3)
	{
		MessageBox(NULL,"3 servos not found","",MB_TASKMODAL | MB_SETFOREGROUND);
		return -1;
	}
	stage.Rotate(180.0);

//Set the group address for both controllers to 128
	stage.SetGroupAddress(128, eXAxis);
	SetScaling_3AxisStatic(stage);
	SetPIDGain_3AxisStatic(stage);
	ServoOnNMCModule3AxisStatic(stage);

//Set the required status items for the path control module
	stage.SetPathStatus();

//  ServoSetIoCtrl(1, IO1_IN | IO2_IN);
//	ServoSetIoCtrl(2, IO1_IN | IO2_IN);
//	ServoSetIoCtrl(3, IO1_IN | IO2_IN);

	return 0;
};
int InitPathParam(int pathFreq, int numberOfPts,
				  double xScale, double yScale, double zScale,
				  double pathAccel,
				  double feedrate)
{

//Initialize path control module parameters
	g_stage.SetPathFreq(pathFreq);
	g_stage.SetNumberOfPoints(numberOfPts);
	g_stage.SetScale(xScale, yScale, zScale);
	g_stage.SetPathAcceleration(pathAccel);
	g_stage.SetFeedrate(feedrate);
	g_stage.SetPathParams();     //acceleration = 1.0 inch/second/second


	g_stage.SetOrigin(0.0, 0.0, 0.0); //set the origin to X = 0, Y = 0, Z = 0
	g_stage.SetFeedrate(1.0);         //feedrate = 1.0 inches/second
	g_stage.SetTangentTolerance(10.0);  //continuous path tangent tolerence = 10 degrees

	return 0;
}
int SetPIDGain_3Axis()
{
	int iProportional;
	int iDifferential;
	int iIntegral;

	BOOL bXAxisGain=FALSE;
	BOOL bYAxisGain=FALSE;
	BOOL bZAxisGain=FALSE;
	GainLimit GainLimits;
	GainLimits.dIntegralLimit	=0.0; 
	GainLimits.dOutputLimit		=255.0; 
	GainLimits.dCurrentLimit	=0.0; 
	GainLimits.dErrorLimit		=2000.0; 
	GainLimits.dServoRate		=1.0;
	GainLimits.dDeadBand		=0.0;

	g_stage.SetGainLimits(eXAxis, GainLimits);
	g_stage.SetGainLimits(eYAxis, GainLimits);
	g_stage.SetGainLimits(eZAxis, GainLimits);
	bXAxisGain= g_stage.SetGain(	eXAxis, 2144, 7680, 512);	   //DC = 0
	if (bXAxisGain)
		return -1;

	bYAxisGain= g_stage.SetGain(	eYAxis, 1656, 4064, 128);     //DC = 0;
	if (bYAxisGain)
		return -2;

	bZAxisGain= g_stage.SetGain(	eZAxis, 1872, 12288, 512);      //DC = 0
		if (bZAxisGain)
		return -3;

	g_stage.GetGain(eXAxis, iProportional, iDifferential,iIntegral);
	g_stage.GetGain(eYAxis, iProportional, iDifferential,iIntegral);
	g_stage.GetGain(eZAxis, iProportional, iDifferential,iIntegral);

	return 0;

}
int SetScaling_3Axis		()
{
	g_stage.SetEncoderCounts(eXAxis, 200.00);
	g_stage.SetEncoderCounts(eYAxis, 200.00);
	g_stage.SetEncoderCounts(eZAxis, 200.00);

	g_stage.SetLeadScrewPitch(eXAxis, 10.00);
	g_stage.SetLeadScrewPitch(eYAxis, 10.00);
	g_stage.SetLeadScrewPitch(eZAxis, 20.00);
	
	g_stage.SetMotorGearRatio(eXAxis, 5.9);
	g_stage.SetMotorGearRatio(eYAxis, 5.9);
	g_stage.SetMotorGearRatio(eZAxis, 5.9);

	g_stage.SetPulleyRatio(eXAxis, 2.13/1.504);
	g_stage.SetPulleyRatio(eYAxis, 2.13/1.504);
	g_stage.SetPulleyRatio(eZAxis, 2.13/1.504);

	return 0;
};
int SetPIDGain_3AxisStatic(Stage & stage)
{
	int iProportional;
	int iDifferential;
	int iIntegral;

	BOOL bXAxisGain=FALSE;
	BOOL bYAxisGain=FALSE;
	BOOL bZAxisGain=FALSE;
	GainLimit GainLimits;
	GainLimits.dIntegralLimit	=0.0; 
	GainLimits.dOutputLimit		=255.0; 
	GainLimits.dCurrentLimit	=0.0; 
	GainLimits.dErrorLimit		=2000.0; 
	GainLimits.dServoRate		=1.0;
	GainLimits.dDeadBand		=0.0;

	stage.SetGainLimits(eXAxis, GainLimits);
	stage.SetGainLimits(eYAxis, GainLimits);
	stage.SetGainLimits(eZAxis, GainLimits);
	bXAxisGain= stage.SetGain(	eXAxis, 2144, 7680, 512);	   //DC = 0
	if (bXAxisGain)
		return -1;

	bYAxisGain= stage.SetGain(	eYAxis, 1656, 4064, 128);     //DC = 0;
	if (bYAxisGain)
		return -2;

	bZAxisGain= stage.SetGain(	eZAxis, 1872, 12288, 512);      //DC = 0
		if (bZAxisGain)
		return -3;

	stage.GetGain(eXAxis, iProportional, iDifferential,iIntegral);
	stage.GetGain(eYAxis, iProportional, iDifferential,iIntegral);
	stage.GetGain(eZAxis, iProportional, iDifferential,iIntegral);

	return 0;

}
int SetScaling_3AxisStatic		(Stage & stage)
{
	stage.SetEncoderCounts(eXAxis, 200.00);
	stage.SetEncoderCounts(eYAxis, 200.00);
	stage.SetEncoderCounts(eZAxis, 200.00);

	stage.SetLeadScrewPitch(eXAxis, 10.00);
	stage.SetLeadScrewPitch(eYAxis, 10.00);
	stage.SetLeadScrewPitch(eZAxis, 20.00);
	
	stage.SetMotorGearRatio(eXAxis, 5.9);
	stage.SetMotorGearRatio(eYAxis, 5.9);
	stage.SetMotorGearRatio(eZAxis, 5.9);

	stage.SetPulleyRatio(eXAxis, 2.13/1.504);
	stage.SetPulleyRatio(eYAxis, 2.13/1.504);
	stage.SetPulleyRatio(eZAxis, 2.13/1.504);

	return 0;
};
int ServoOnNMCModule3Axis()
{
	g_stage.StopMotor(eXAxis, AMP_ENABLE | STOP_ABRUPT | ADV_FEATURE);
	g_stage.StopMotor(eYAxis, AMP_ENABLE | STOP_ABRUPT | ADV_FEATURE);
	g_stage.StopMotor(eZAxis, AMP_ENABLE | STOP_ABRUPT | ADV_FEATURE);

//Reset position counters to zero:
//	g_stage.ResetPos();

//Clear any error bits
//	ServoClearBits(1);
//	ServoClearBits(2);
//	ServoClearBits(3);
	
	return 0;
};
int ServoOnNMCModule3AxisStatic(Stage & stage)
{
	stage.StopMotor(eXAxis, AMP_ENABLE | STOP_ABRUPT | ADV_FEATURE);
	stage.StopMotor(eYAxis, AMP_ENABLE | STOP_ABRUPT | ADV_FEATURE);
	stage.StopMotor(eZAxis, AMP_ENABLE | STOP_ABRUPT | ADV_FEATURE);

//Reset position counters to zero:
//	g_stage.ResetPos();

//Clear any error bits
//	ServoClearBits(1);
//	ServoClearBits(2);
//	ServoClearBits(3);
	
	return 0;
};
int ServoOnNMCModule3AxisNoReset()
{
	g_stage.StopMotor(eXAxis, AMP_ENABLE | STOP_SMOOTH );
	g_stage.StopMotor(eYAxis, AMP_ENABLE | STOP_SMOOTH );
	g_stage.StopMotor(eZAxis, AMP_ENABLE | STOP_SMOOTH );

//	ServoResetPos(1);
//	ServoResetPos(2);
//	ServoResetPos(3);

//Clear any error bits
//	ServoClearBits(1);
//	ServoClearBits(2);
//	ServoClearBits(3);
	
	return 0;
};

int CreatePath1()
{
	int res;

//
//Clear the segment list and initialize the starting point for the path
//
	g_stage.ClearSegList(0.0, 0.0, 0.0);    //Clear the segment list and set the
											//  starting point for the path
											//  at X = 0, Y = 1, Z = 0

//
//Add line and arc segments to the path module's segment list for first move
//


	res = g_stage.AddLineSeg(0.0, 1.0, 0.0);    //Add a segment to move to x=0, y=2, z=0
	if (res<0) return -1;

	res = g_stage.AddArcSeg( 1.0, 2.0, 0.0,     //end point of arc: x=1, y=3, z=0
							 1.0, 1.0, 0.0,     //center point of arc: x=1, y=2, z = 0
							 0.0, 0.0, -1.0 );   //normal vector to arc plane: x = 0, y = 0, z = -1
	if (res<0) return -1;

	res = g_stage.AddLineSeg(2.0, 2.0, 0.0);    //line segment endpoint: x=4, y=3, z=0
	if (res<0) return -1;

	res = g_stage.AddArcSeg( 3.0, 1.0, 0.0,     //end point of arc: x=5, y=2, z=0
											2.0, 1.0, 0.0,     //center point of arc: x=4, y=2, z = 0
											0.0, 0.0, -1.0 );   //normal vector to arc plane: x = 0, y = 0, z = -1
	if (res<0) return -1;

	res = g_stage.AddLineSeg(3.0, 0.0, 0.0);    //line segment endpoint: x=5, y=0, z=0
	if (res<0) return -1;

}
int CreatePath1A()
{
	int res;

//
//Clear the segment list and initialize the starting point for the path
//
	g_stage.ClearSegList(0.0, 0.0, 0.0);    //Clear the segment list and set the
									//  starting point for the path
									//  at X = 0, Y = 1, Z = 0

//
//Add line and arc segments to the path module's segment list for first move
//


	res = g_stage.AddLineSeg(0.0, 1.0, 0.0);    //Add a segment to move to x=0, y=2, z=0
	if (res<0) return -1;

	res = g_stage.AddArcSeg( 1.0, 2.0, 0.0,     //end point of arc: x=1, y=3, z=0
											1.0, 1.0, 0.0,     //center point of arc: x=1, y=2, z = 0
											0.0, 0.0, -1.0 );   //normal vector to arc plane: x = 0, y = 0, z = -1
	if (res<0) return -1;

	res = g_stage.AddLineSeg(2.0, 2.0, 0.0);    //line segment endpoint: x=4, y=3, z=0
	if (res<0) return -1;

//	ServoInf::m_pNMCServo->ClearSegList(4.0, 3.0, 0.0);    //Clear the segment list and set the
//	ExecutePath3Axis();

	res = g_stage.AddArcSeg( 3.0, 1.0, 0.0,     //end point of arc: x=5, y=2, z=0
							 2.0, 1.0, 0.0,     //center point of arc: x=4, y=2, z = 0
							 0.0, 0.0, -1.0 );   //normal vector to arc plane: x = 0, y = 0, z = -1
	if (res<0) return -1;

	res = g_stage.AddLineSeg(3.0, 0.0, 0.0);    //line segment endpoint: x=5, y=0, z=0
	if (res<0) return -1;

	res = g_stage.AddStart(3.0, 0.0, 0.0);    //line segment endpoint: x=5, y=0, z=0
	if (res<0) return -1;

	res = g_stage.AddLineSeg(0.0, 0.0, 0.0);    //line segment endpoint: x=5, y=0, z=0
	if (res<0) return -1;

}
int CreatePath1A_XOffset(double dX, double dY, double dZ)
{
	int res;

//
//Clear the segment list and initialize the starting point for the path
//
	g_stage.ClearSegList(dX, dY, dZ);    //Clear the segment list and set the
									//  starting point for the path
									//  at X = 0, Y = 1, Z = 0

//
//Add line and arc segments to the path module's segment list for first move
//


	res = g_stage.AddLineSeg(dX, dY+1.0, dZ+0.0);    //Add a segment to move to x=0, y=2, z=0
	if (res<0) return -1;

	res = g_stage.AddArcSeg( dX+1.0, dY+2.0, dZ+0.0,     //end point of arc: x=1, y=3, z=0
							 dX+1.0, dY+1.0, dZ+0.0,     //center point of arc: x=1, y=2, z = 0
							 0.0, 0.0, -1.0 );   //normal vector to arc plane: x = 0, y = 0, z = -1
	if (res<0) return -1;

	res = g_stage.AddLineSeg(dX+2.0, dY+2.0, dZ+0.0);    //line segment endpoint: x=4, y=3, z=0
	if (res<0) return -1;

//	ServoInf::m_pNMCServo->ClearSegList(4.0, 3.0, 0.0);    //Clear the segment list and set the
//	ExecutePath3Axis();

	res = g_stage.AddArcSeg( dX+3.0, dY+1.0, dZ+0.0,     //end point of arc: x=5, y=2, z=0
							 dX+2.0, dY+1.0, dZ+0.0,     //center point of arc: x=4, y=2, z = 0
							 0.0, 0.0, -1.0 );   //normal vector to arc plane: x = 0, y = 0, z = -1
	if (res<0) return -1;

	res = g_stage.AddLineSeg(dX+3.0, dY+0.0, dZ+0.0);    //line segment endpoint: x=5, y=0, z=0
	if (res<0) return -1;

	res = g_stage.AddStart(dX+3.0, dY+0.0, dZ+0.0);    //line segment endpoint: x=5, y=0, z=0
	if (res<0) return -1;

	res = g_stage.AddLineSeg(dX+0.0, dY+0.0, dZ+0.0);    //line segment endpoint: x=5, y=0, z=0
	if (res<0) return -1;

}
int CreatePath1A_XOffset(double dX, double dY, double dZ, Path & vPath)
{
	int res;

//
//Clear the segment list and initialize the starting point for the path
//
	vPath.ClearSegListA(dX, dY, dZ);    //Clear the segment list and set the
									//  starting point for the path
									//  at X = 0, Y = 1, Z = 0

//
//Add line and arc segments to the path module's segment list for first move
//


	res = vPath.AddLineSegA(dX, dY+1.0, dZ+0.0);    //Add a segment to move to x=0, y=2, z=0
	if (res<0) return -1;

	res = vPath.AddArcSegA( dX+1.0, dY+2.0, dZ+0.0,     //end point of arc: x=1, y=3, z=0
							 dX+1.0, dY+1.0, dZ+0.0,     //center point of arc: x=1, y=2, z = 0
							 0.0, 0.0, -1.0 );   //normal vector to arc plane: x = 0, y = 0, z = -1
	if (res<0) return -1;

	res = vPath.AddLineSegA(dX+2.0, dY+2.0, dZ+0.0);    //line segment endpoint: x=4, y=3, z=0
	if (res<0) return -1;

//	ServoInf::m_pNMCServo->ClearSegList(4.0, 3.0, 0.0);    //Clear the segment list and set the
//	ExecutePath3Axis();

	res = vPath.AddArcSegA( dX+3.0, dY+1.0, dZ+0.0,     //end point of arc: x=5, y=2, z=0
							 dX+2.0, dY+1.0, dZ+0.0,     //center point of arc: x=4, y=2, z = 0
							 0.0, 0.0, -1.0 );   //normal vector to arc plane: x = 0, y = 0, z = -1
	if (res<0) return -1;

	res = vPath.AddLineSegA(dX+3.0, dY+0.0, dZ+0.0);    //line segment endpoint: x=5, y=0, z=0
	if (res<0) return -1;

	res = vPath.AddStartA(dX+3.0, dY+0.0, dZ+0.0);    //line segment endpoint: x=5, y=0, z=0
	if (res<0) return -1;

	res = vPath.AddLineSegA(dX+0.0, dY+0.0, dZ+0.0);    //line segment endpoint: x=5, y=0, z=0
	if (res<0) return -1;

}
int CreateSplinePath		()
{
	int res;
//
//Clear the segment list and initialize the starting point for the path
//
	g_stage.ClearSegList(0.0, 0.0, 0.0);    //Clear the segment list and set the
									//  starting point for the path
									//  at X = 0, Y = 1, Z = 0

//
//Add line and arc segments to the path module's segment list for first move
//

	vector<double> CtrlPts;
	SetControlPts(CtrlPts);
	res = g_stage.AddSplineSeg(CtrlPts, 60, enCatmullRom);    //Add a segment to move to x=0, y=2, z=0
	if (res<0) return -1;

	
};

int CreatePath1_2()
{
	int res;

//
//Clear the segment list and initialize the starting point for the path
//
	g_stage.ClearSegList(3.0, 0.0, 0.0);    //Clear the segment list and set the
									//  starting point for the path
									//  at X = 5, Y = 0, Z = 0
//
//Add line and arc segments to the path module's segment list for first move
//
	res = g_stage.AddLineSeg(0.0, 0.0, 0.0);    //Add a segment to move to x=0, y=2, z=0
	if (res<0) return -1;

}
void ExecutePath3Axis()
{
//	g_stage.SetPathStatus();
	g_stage.ExecuteCoordMotion();
}


void ResetModules(int & iModules)
{
	if (iModules == 0) 
		return;

	NmcShutdown();
};
void ExecutePath()
{
//
//Initialize the path just before execution
//
//InitPath();

//
//Download path points to the PIC-SERVO CMC modules until all points are
//  downloaded.  Motion will begin automatically when the minimum number
//  of path points have been loaded.
//
//while ( AddPathPoints() != -1 ) ;

//
//Poll the X axis module to detect when the path is complete
//
do
  {
  NmcNoOp(1);   //retrieve current status data
  }
while ( ServoGetAux(1) & PATH_MODE );   //poll while still in path mode	
};

int SetControlPts(vector<double> & Points)
{
    Points.push_back(0.0);  // x0
    Points.push_back(0.0);  // y0
    Points.push_back(0.0);  // z0      
    
    Points.push_back(0.0);  // x1
    Points.push_back(2.0);  // y1
    Points.push_back(0.0);  // z1      

    Points.push_back(2.0);  // x2
    Points.push_back(1.0); // y2
    Points.push_back(0.0);  // z2      
 
    Points.push_back(2.0);  // x3
    Points.push_back(0.0); // y3
    Points.push_back(0.0);  // z3      


	Points.push_back(2.0);  // x4
    Points.push_back(0.0); // y4
    Points.push_back(0.0);  // z4      
    
    Points.push_back(2.0); // x5
    Points.push_back(-1.0); // y5
    Points.push_back(0.0);  // z5      

    Points.push_back(0.0); // x6
    Points.push_back(-2.0);  // y6
    Points.push_back(0.0);  // z6      
 
    Points.push_back(0.0);  // x7
    Points.push_back(0.0);  // y7
    Points.push_back(0.0);  // z7      

	return 0;
};
