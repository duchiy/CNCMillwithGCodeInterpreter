#include "stdafx.h"
#include <string>
#include <map>
using namespace std;
class ParseCNC
{
private:
	MillCtrl  _millctrl;
	map <string, int> _gCodeCmd;
	map <int, string> _gCodeParam;
	DPoint _lastPoint;
public:
	ParseCNC()
	{

		InitializeMap();
	}
	void InitializeMap()
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
	
	void SetCmd(MillCtrl millctrl)
	{

		_millctrl=millctrl;
	}
	void GetCmd(MillCtrl & millctrl)
	{

		millctrl=_millctrl;
	}
	
	template <typename Iter, typename Cont>
	bool is_last(Iter iter, const Cont& cont)
	{
		return (iter != cont.end()) && (next(iter) == cont.end());
	}
	bool IsG_Command(string cmd)
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
	void GetXYZ(double & x, double & y, double &  z, vector<string> params)
	{
		x=std::stod(params[0]);
		y=std::stod(params[1]);
		z=std::stod(params[2]);
	}
	void GetIJK(double & i, double & j, double & k, vector<string> params)
	{
		i=std::stod(params[4]);
		j=std::stod(params[5]);
		k=std::stod(params[6]);

	}
	void GetFeed(double & feed, vector<string> params)
	{
		feed=std::stod(params[3]);

	}
	void SetG0(double xpos, double ypos, double zpos)
	{
		double x=0.0, y=0.0, z=0.0;
		stageMoveXYZ *stagemoveXYZ = new stageMoveXYZ(g_stage, x+xpos, y+ypos,z+zpos);
		_millctrl.SetCommand(stagemoveXYZ);
		_lastPoint.Set(x+xpos, y+ypos, z+zpos);

	}
	void SetG1(double xpos, double ypos, double zpos)
	{
		double xstart, ystart,zstart;
		_lastPoint.Get(xstart, ystart,zstart);
		pathClearList *clearList = new pathClearList(g_path, xstart, ystart,zstart);
		_millctrl.SetCommand(clearList);

		pathAddLine *addLine = new pathAddLine(g_path, xpos, ypos, zpos);
		_millctrl.SetCommand(addLine);

		stageExecutePath *executePath = new stageExecutePath(g_stage, g_path);
		_lastPoint.Set(xpos, ypos, zpos);

	}
	void SetG2(double xpos, double ypos, double zpos, double i, double j, double k)
	{		
		double xstart, ystart,zstart;
		_lastPoint.Get(xstart, ystart,zstart);
		pathClearList *clearList = new pathClearList(g_path, xstart, ystart,zstart);
		_millctrl.SetCommand(clearList);

		pathAddArc *addArc = new pathAddArc(g_path);
		_lastPoint.Get(xstart, ystart, zstart);
		addArc->SetEnd(xpos, ypos, zpos);
		addArc->SetCenter(xstart+i, ystart+j, zstart+k);
		vector<double> normal=cross( xstart+i, ystart+j, zstart+k, xpos, ypos, zpos );
		addArc->SetNormal(normal[0], normal[1], normal[2]);
		_millctrl.SetCommand(addArc);
		stageExecutePath *executePath = new stageExecutePath(g_stage, g_path);
		_lastPoint.Set(xpos, ypos, zpos);

	}
	template <typename cmdlist>
	int GetParam(string cmd1, vector<string>::iterator & it, const cmdlist& cmdlst, vector<string> & params)
	{

		it++;
		string param;
		vector<string> vparams(_gCodeParam.size(),"0.0");
		while (it != cmdlst.end())
		{
			for (map <int, string>::const_iterator itGparam=_gCodeParam.begin(); itGparam != _gCodeParam.end(); itGparam++)
			{
				if (ParseData(it, itGparam->second, 0, cmdlst, param))
				{
					vparams[itGparam->first]=param;
					it++;
					break;
				}
			}
		}
		params=vparams;
		return 0;
	}


	template <typename cmdlist>
	int SetCommand1 (vector<string>::iterator & it, const cmdlist& cmdlst)
	//int SetCommand (MillCtrl & millctrl, string cmd, vector<string> param)
	{
		string cmd = *it;
		double x=0.0,y=0.0,z=0.0;
		double feed=0.0;
		double i=0.0,j=0.0,k=0.0;
		// cmd can have 1 to many commands 
		if (!IsG_Command(cmd))
		{
			it++;
			return 0;
		}

	   vector<string> params;
       map <string, int>::const_iterator gCodeIt= _gCodeCmd.find(cmd);
	   switch(gCodeIt->second)
	   {
		   case 0:  //G0 - Rapid Move
			   {
				   GetParam(cmd, it, cmdlst,  params);
				   GetXYZ(x,y,z,params);
				   SetG0(x,y,z);
			   }
			   break;
		   case 1:  //G1 - Linear interpolated move
			   {
				   GetParam(cmd, it, cmdlst,  params);
				   GetXYZ(x,y,z,params);
				   GetFeed(feed,params);
				   SetG1(x,y,z);

			   }
			   break;

		   case 2:  //G2 - Circular interpolated move CW
			   {
				   GetParam(cmd, it, cmdlst,  params);
				   GetXYZ(x,y,z,params);
				   GetFeed(feed,params);
				   GetIJK(i,j,k,params);
				   SetG2(x, y, z, i, j, k);
			   }
			   break;
		   case 3:  //G3 - Circular interpolated move CCW
			   {
				   GetParam(cmd, it, cmdlst,  params);
				   GetXYZ(x,y,z,params);
				   GetFeed(feed,params);
				   GetIJK(i,j,k,params);
				   SetG2(x, y, z, i, j, k);

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

	   if (it != cmdlst.end())
	   {
		   it++;
	   }
	};
	int ParseLine(string cmdline, vector<string> & cmdlst)
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
	int ParseCmd(const string cmdline, const string search, int start, string & cmd)
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
	bool ParseData(const vector<string>::iterator & s_itr, const string search, int start, const Cont & cont, string & cmd)
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
	
};