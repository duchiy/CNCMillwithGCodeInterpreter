#ifndef _PARSECNC_H
#define _PARSECNC_H
#include "MillCmd.h"
#include "DPoint.h"
#include "Stage.h"
#include "Path.h"
//#include "StageAndPathSingleTon.h"
#include <vector>
#include <string>
#include <map>
#include <bitset>
//vector<double>	cross	( double x1, double y1, double z1, double x2, double y2, double z2 );

class ParseCNC
{
private:
	millCmd  _millCmd;
	map <string, int> _gCodeCmd;
	map <int, string> _gCodeParam;
	DPoint _lastPosition;

public:

	ParseCNC();	

	void InitializeMap();
	void SetCmd(millCmd millcmd);
	void GetCmd(millCmd & millcmd);

	
	template <typename Iter, typename Cont>
	bool is_last(Iter iter, const Cont& cont);
	bool IsG_Command(string cmd);
	void GetXYZ(double & x, double & y, double &  z, vector<string> params);
	void GetIJK(double & i, double & j, double & k, vector<string> params);
	void GetFeed(double & feed, vector<string> params);
	void SetG0(double xpos, double ypos, double zpos);
	void SetG1(double xpos, double ypos, double zpos);
	void SetG2(double xpos, double ypos, double zpos, double i, double j, double k);
	
	template <typename cmdlist>
	int GetParam(string cmd1, vector<string>::iterator & it, const cmdlist& cmdlst, vector<string> & params, bitset<16> & changedParams);
	template <typename cmdlist>
	bool HasGCodeParams(const cmdlist& cmdlst);
	void ParseCNC::CalculateXYZ(double x0, double y0, double z0, bitset<16> changedBits, double & x1, double & y1, double & z1 );
//	template <typename cmdlist>
	int SetCommand1 (vector<string>::iterator & it, vector<string> & cmdlst);

	int ParseLine(string cmdline, vector<string> & cmdlst);
	int ParseCmd(const string cmdline, const string search, int start, string & cmd);

	template <typename Cont>
	bool ParseData(const vector<string>::iterator & s_itr, const string search, int start, const Cont & cont, string & cmd);
	
};


#endif