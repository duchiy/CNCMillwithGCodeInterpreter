#include "stdafx.h"
#include "Path.h"
#include "pathClearList.h"
#include "pathAddLine.h"
#include "pathAddArc.h"
#include "Stage.h"
#include "stageResetPos.h"
#include "stagePosition.h"
#include "stageMoveXY.h"
#include "stageExecutePath.h"
#include "stageMoveXYZ.h"
#include "stageGetPos.h"
#include "MillCmd.h"
#include "DPoint.h"
#include "ParseCNC.h"
#include "Vector3.h"
#include "FloatingPtHelper.h"
#include <string>
#include <map>
using namespace std;

bitset<16> gXAxisChange (string("0000000001"));
bitset<16> gYAxisChange (string("0000000010"));
bitset<16> gZAxisChange (string("0000000100"));
//
bitset<16> gFeedChange  (string("0001000000"));
bitset<16> gIAxisChange (string("0000001000"));
bitset<16> gJAxisChange (string("0000010000"));
bitset<16> gKAxisChange (string("0000100000"));
size_t  gXAxisbit  = 0 ;
size_t  gYAxisbit  = 1 ;
size_t  gZAxisbit  = 2 ;

size_t  gFeedbit   = 3 ;
size_t  gIAxisbit  = 4 ;
size_t  gJAxisbit  = 5 ;
size_t  gKAxisbit  = 6 ;

ParseCNC::ParseCNC()
{

	InitializeMap();
}
//ParseCNC::ParseCNC(Stage & stage, Path  & path)
//{
//
//};

//void ParseCNC::SetStage (Stage & stage)
//{
//	_stage = stage;
//}
//void ParseCNC::SetPath (Path & path)
//{
//	_path = path;
//}

void ParseCNC::InitializeMap()
{
	_gCodeCmd["G0"]=0;
	_gCodeCmd["G1"]=1;
	_gCodeCmd["G2"]=2;
	_gCodeCmd["G3"]=3;
	_gCodeCmd["G21"]=21;
	_gCodeCmd["G90"]=90;
	_gCodeCmd["G64"]=64;
	_gCodeCmd["G40"]=40;

	_gCodeParam[0]="X";
	_gCodeParam[1]="Y";
	_gCodeParam[2]="Z";
	_gCodeParam[3]="F";
	_gCodeParam[4]="I";
	_gCodeParam[5]="J";
	_gCodeParam[6]="K";

}
	
void ParseCNC::SetCmd(millCmd millcmd)
{

	_millCmd=millcmd;
}
void ParseCNC::GetCmd(millCmd & millcmd)
{

	millcmd=_millCmd;
}
	
template <typename Iter, typename Cont>
bool ParseCNC::is_last(Iter iter, const Cont& cont)
{
	return (iter != cont.end()) && (next(iter) == cont.end());
}
bool ParseCNC::IsG_Command(string cmd)
{
	// cmd is 1 command

	if (cmd.find("G") == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void ParseCNC::GetXYZ(double & x, double & y, double &  z, vector<string> params)
{
	x=std::stod(params[0]);
	y=std::stod(params[1]);
	z=std::stod(params[2]);
}
void ParseCNC::GetIJK(double & i, double & j, double & k, vector<string> params)
{
	i=std::stod(params[4]);
	j=std::stod(params[5]);
	k=std::stod(params[6]);

}
void ParseCNC::GetFeed(double & feed, vector<string> params)
{
	feed=std::stod(params[3]);

}
void ParseCNC::SetG0(double xpos, double ypos, double zpos)
{
	stageMoveXYZ *stagemoveXYZ = new stageMoveXYZ(Singleton<Stage>::Instance(), xpos, ypos, zpos);
	stagemoveXYZ->SetType(cmdStageMoveXYZ);
	_millCmd.SetCommand(stagemoveXYZ);
	_lastPosition.Set(xpos, ypos, zpos);

}
void ParseCNC::SetG1(double xpos, double ypos, double zpos)
{
	DPoint prevPos;
	_lastPosition.Get(prevPos);

	pathClearList *clearList = new pathClearList(Singleton<Path>::Instance(), prevPos._x, prevPos._y, prevPos._z);
	_millCmd.SetCommand(clearList);

	pathAddLine *addLine = new pathAddLine(Singleton<Path>::Instance(), xpos, ypos, zpos);
	addLine->SetType(cmdAddLine);
	_millCmd.SetCommand(addLine);

	stageExecutePath *executePath = new stageExecutePath(Singleton<Stage>::Instance(), Singleton<Path>::Instance());
	_millCmd.SetCommand(executePath);
	_lastPosition.Set(xpos, ypos, zpos);

}
void ParseCNC::SetG2(double xpos, double ypos, double zpos, double i, double j, double k)
{		
	DPoint prevPos;
	DPoint centerPos;

	_lastPosition.Get(prevPos);

	pathClearList *clearList = new pathClearList(Singleton<Path>::Instance(), prevPos._x, prevPos._y, prevPos._z);
	_millCmd.SetCommand(clearList);

	pathAddArc *addArc = new pathAddArc(Singleton<Path>::Instance());
	addArc->SetStart(prevPos._x, prevPos._y, prevPos._z);

	addArc->SetType(cmdAddArc);
	addArc->SetEnd(xpos, ypos, zpos);

	centerPos._x=prevPos._x+i;centerPos._y=prevPos._y+j;centerPos._z=prevPos._z+k;
	addArc->SetCenter(centerPos._x, centerPos._y, centerPos._z);

	Vector3 start(prevPos._x, prevPos._y, prevPos._z);
	Vector3 center(centerPos._x, centerPos._y, centerPos._z);
	Vector3 end(xpos, ypos, zpos);
  
	start = start - center;
	end = end - center;
	Vector3 normal=start.CrossProductWith(end);
	normal=normal.Normalize();

	addArc->SetNormal(normal.X, normal.Y, normal.Z);
	
	_millCmd.SetCommand(addArc);
	stageExecutePath *executePath = new stageExecutePath(Singleton<Stage>::Instance(), Singleton<Path>::Instance());
	_millCmd.SetCommand(executePath);
	_lastPosition.Set(xpos, ypos, zpos);

}
template <typename cmdlist>
int ParseCNC::GetParam(string cmd1, vector<string>::iterator & it, const cmdlist& cmdlst, vector<string> & params, bitset<16> & paramsChanged)
{

	it++;
	string param;
	paramsChanged = 0;
	vector<string> vparams(_gCodeParam.size(),"0.0");
	while (it != cmdlst.end())
	{
		for (map <int, string>::const_iterator itGparam=_gCodeParam.begin(); itGparam != _gCodeParam.end(); itGparam++)
		{
			if (ParseData(it, itGparam->second, 0, cmdlst, param))
			{
				it++;
				vparams[itGparam->first]=param;
			    switch (itGparam->first)
				{
					case 0:  
						{
							paramsChanged.set(gXAxisbit, true);
						}
						break;
					case 1:  
						{
							paramsChanged.set(gYAxisbit, true);
						}
						break;
					case 2:  
						{
							paramsChanged.set(gZAxisbit, true);
						}
						break;
					case 3:  
						{
							paramsChanged.set(gFeedbit, true);
						}
						break;
					case 4:  
						{
							paramsChanged.set(gIAxisbit, true);
						}
						break;
					case 5:  
						{
							paramsChanged.set(gJAxisbit, true);
						}
						break;
					case 6:  
						{
							paramsChanged.set(gKAxisbit, true);
						}
						break;
					default:
						{
						}

				};

			}
		}
	}
	params=vparams;
	return 0;
}
template <typename cmdlist>
bool ParseCNC::HasGCodeParams(const cmdlist& cmdlst)
{
	int i=1;
	while (i <= cmdlst.size()-1)
	{
		for (map <int, string>::const_iterator itGparam=_gCodeParam.begin(); itGparam != _gCodeParam.end(); itGparam++)
		{
			size_t found =cmdlst[i].find(itGparam->second, 0);
			if ( found != string::npos)
			{
				return true;
			}

		}
		i++;
	}
	return false;
}

void ParseCNC::CalculateXYZ(double x0, double y0, double z0, bitset<16> changedxyz, double & x1, double & y1, double & z1 )
{
	double x,y,z;
	_lastPosition.Get(x, y, z);

	if (changedxyz.test(0))
	{
		x1=x0;
	}
	else
	{
		x1=x;
	}

	if (changedxyz.test(1))
	{
		y1=y0;
	}
	else
	{
		y1=y;
	}

	if (changedxyz.test(2))
	{
		z1=z0;
	}
	else
	{
		z1=z;
	}
		
}
//template <typename cmdlist>
int ParseCNC::SetCommand1 (vector<string>::iterator & it, vector<string> & cmdlst)
{
	string cmd = *it;
	double x=0.0,y=0.0,z=0.0;
	double x1=0.0,y1=0.0,z1=0.0;
	double feed=0.0;
	double i=0.0,j=0.0,k=0.0;
	// cmd can have 1 to many commands 
	if (!IsG_Command(cmd))
	{
		it++;
		return 0;
	}
	bitset<16> changedParams;
	vector<string> params;
    map <string, int>::const_iterator gCodeIt= _gCodeCmd.find(cmd);
	if (HasGCodeParams(cmdlst))
	{
		GetParam(cmd, it, cmdlst,  params, changedParams);
		GetXYZ(x,y,z, params);		
		CalculateXYZ(x,y,z, changedParams, x1,y1,z1 );

	}

	switch(gCodeIt->second)
	{
		
	    case 0:  //G0 - Rapid Move
			{
				SetG0(x1,y1,z1);
			}
			break;
		case 1:  //G1 - Linear interpolated move
			{
				GetFeed(feed,params);
				SetG1(x1,y1,z1);

			}
			break;

		case 2:  //G2 - Circular interpolated move CW
			{
				GetFeed(feed,params);
				GetIJK(i,j,k,params);
				SetG2(x1,y1,z1, i, j, k);
			}
			break;
		case 3:  //G3 - Circular interpolated move CCW
			{
				GetFeed(feed,params);
				GetIJK(i,j,k,params);
				SetG2(x1,y1,z1, i, j, k);

			}
			break;

		case 17:  //G17 XY Reference Plane
			{


			}
			break;
		case 20:  //G20 INCH Data
			{


			}
			break;
		case 21:  //G21 Metric Data
			{


			}
			break;
		case 90:  //G90 Absolute Positioning
			{


			}
			break;
		case 64:  //G64 
			{


			}
			break;
		case 40:  //G40
			{


			}
			break;

		default:
			{
				it++;
				return -1;
			}

	};

	_lastPosition.Set(x1,y1,z1);
	if (it != cmdlst.end())
	{
		it++;
	}
};
int ParseCNC::ParseLine(string cmdline, vector<string> & cmdlst)
{
	string cmd;
	int start =0;
	cmdline = cmdline + "\r\n";
	while ( (start=ParseCmd(cmdline, " ", start, cmd)) != -1)
	{
		cmdlst.push_back(cmd);
		start++;
	} 
	return 0;
}
int ParseCNC::ParseCmd(const string cmdline, const string search, int start, string & cmd)
{
	int offset=0;
	offset=cmdline.find(search,start);
	if (offset == -1)
	{
		//Search for the end of line
		offset=cmdline.find("\r\n",start);
		if (offset == -1)
		{
			return -1;
		}
	}

	cmd=cmdline.substr(start, offset-start);
	return offset;
}
template <typename Cont>
bool ParseCNC::ParseData(const vector<string>::iterator & s_itr, const string search, int start, const Cont & cont, string & cmd)
{
	int offset=0;
		
	if (s_itr == cont.end())
	{
		return false;
	}

	cmd.clear();
	string cmdline = *s_itr;
	offset=cmdline.find(search,start);
	if (offset == -1)
	{
		//Search for the end of line
		offset=cmdline.find("\r\n",start);
		if (offset == -1)
		{
			return false;
		}
	}
	cmd=cmdline.substr(start+1, cmdline.size()-start+1);
	return true;
}
	
