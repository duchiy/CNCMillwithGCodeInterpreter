#include "millCmdCtrl.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace motionTestCLR;
using namespace stageclr;
using namespace pathclr;

namespace millCmdCtrlclr
{


	public ref class CmillCmdCtrl
	{
	public:
		CmillCmdCtrl( );
		void ProcessGCode (String ^ name);   
		void RunGCode ( );
	    void RunCommand ( int i );
	    void InitRun ( );
	    void Iter ( );
	    int GetCommand ( );
	    int Count ( );
	    void GetStart ( [Out]double % X, [Out]double % Y, [Out]double % Z );
	    void GetEnd ( [Out]double % X, [Out]double % Y, [Out]double % Z );
	    void GetCenter ( [Out]double % X, [Out]double % Y, [Out]double % Z );
		
	private:
		millCmdCtrl *_millCmdCtrl;

	};
}