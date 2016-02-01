// millCmdclr.cpp : main project file.

#include "stdafx.h"
#include "millCmdCtrlclr.h"
#include <vcclr.h>
#include <msclr\marshal_cppstd.h>
using namespace millCmdCtrlclr;

CmillCmdCtrl::CmillCmdCtrl( )
{
	_millCmdCtrl = new millCmdCtrl();
};
//void CmillCmdCtrl::SetPath (CPath ^ path )
//{
//	Path *pathptr=path->GetNativePtr();
//	_millCmdCtrl->SetPath(pathptr);
//};
//void CmillCmdCtrl::SetStage (CStage  ^ stage)
//{
//   Stage *stageptr=stage->GetNativePtr();
//	_millCmdCtrl->SetStage(stageptr);
//};
void CmillCmdCtrl::ProcessGCode (String ^ fileName)
{
    std::string message = msclr::interop::marshal_as<std::string>(fileName);
	string str (message.begin(), message.end());

	_millCmdCtrl->ProcessGCode (str);	
};   
void CmillCmdCtrl::RunGCode ( )
{
	_millCmdCtrl->RunGCode ( );
	
};

void CmillCmdCtrl::RunCommand ( int i )
{
	_millCmdCtrl->RunCommand ( i );
};
void CmillCmdCtrl::InitRun ( )
{
	_millCmdCtrl->InitRun ( );
};
void CmillCmdCtrl::Iter ( )
{
	_millCmdCtrl->Iter ( );
};
int CmillCmdCtrl::GetCommand ( )
{
	return _millCmdCtrl->GetCommand ( );
};
int CmillCmdCtrl::Count ( )
{
	return _millCmdCtrl->Count ( );
};
void CmillCmdCtrl::GetStart ( [Out]double % X, [Out]double % Y, [Out]double % Z )
{
	double X1, Y1, Z1;
	_millCmdCtrl->GetStart ( X1, Y1, Z1 );
	X=X1;
	Y=Y1;
	Z=Z1;
};
void CmillCmdCtrl::GetEnd ( [Out]double % X, [Out]double % Y, [Out]double % Z )
{
	double X1, Y1, Z1;
	_millCmdCtrl->GetEnd ( X1, Y1, Z1 );
	X=X1;
	Y=Y1;
	Z=Z1;
};
void CmillCmdCtrl::GetCenter ( [Out]double % X, [Out]double % Y, [Out]double % Z )
{
	double X1, Y1, Z1;
	_millCmdCtrl->GetCenter ( X1, Y1, Z1 );
	X=X1;
	Y=Y1;
	Z=Z1;
};
