using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using stageclr;
using pathclr;
using millCmdCtrlclr;
using System.Runtime.InteropServices;
using motionTestCLR;
using XBoxJoyStick;

namespace PathStageTest
{
    class Program
    {
        static void Main(string[] args)
        {

            CStage _myStage = new CStage();
            StageControl myStageControl = new StageControl();

            myStageControl.Initialize();
            _myStage = myStageControl.Stage;
            CmillCmdCtrl myMillCtrl = new CmillCmdCtrl();

 //           double x, y, z;
 //           _myStage.GetPos(out x, out y, out z);
            CPath _myPath = new CPath();
            _myPath.SetPathParams(60,   //path frequency = 30 Hz
                                  75,       //Store a minimum of 45 points in the path point buffer
                                  15000.0,  //X scale - 20000.0 counts per inch
                                  15000.0,  //Y scale - 20000.0 counts per inch
                                  15000.0,      //Z scale - 1.0 counts per inch - not used
                                  0.175);

            _myPath.SetOrigin(0.0, 0.0, 0.0);
            _myPath.SetFeedrate(0.175);
            _myPath.SetTangentTolerance((float)10.0);

            myMillCtrl.ProcessGCode("C:\\Program Files (x86)\\Mill1A\\input\\CircleAtOrigin.nc");
            myMillCtrl.RunGCode();
        }
    }
}
