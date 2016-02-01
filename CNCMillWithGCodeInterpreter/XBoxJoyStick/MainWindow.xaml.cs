using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Media3D;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using XGamepadDemo;
using stageclr;
using pathclr;
using millCmdCtrlclr;
using System.Runtime.InteropServices;
using System.Windows.Threading;
using System.Threading.Tasks;
using XBoxJoyStick;
using motionTestCLR;
using System.Threading;

namespace XBoxJoyStick
{


    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        static CStage _myStage;
        StageControl myStageControl = new StageControl();
        CmillCmdCtrl myMillCtrl = new CmillCmdCtrl();
        XGamepadDemo.XBoxJoyStick _JoyStick = new XGamepadDemo.XBoxJoyStick();
        CPath _myPath = new CPath();
        ProgramEditor _myEditor = new ProgramEditor();
        int _editorLine = 1;
        DispatcherTimer _timer;
        bool _firstPath = true;

        PathGeometry _pathGeometry1 = new PathGeometry();
        PathFigure _pathFigure1 = new PathFigure();
        System.Windows.Shapes.Path _path1 = new System.Windows.Shapes.Path();
        PathDisplay _myPathDisplay = new PathDisplay(); 

        CommandData _cmdData = new CommandData();

        public delegate void Updatedro();
        public event Updatedro Update1;
        protected void OnUpdate(string message)
        {
            if (Update1 != null)
            {
                Update1();
            }
        }

        // Timer and event
        public MainWindow()
        {
            InitializeComponent();
            this.Update1 += new Updatedro(UpdateDRO);

            myStageControl.Initialize();
            _myStage = myStageControl.Stage;
            _JoyStick.Initialize(0);
            _JoyStick.Stage = _myStage;
            InitializePath();
            _timer = new DispatcherTimer();
            _timer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            _timer.Tick += new EventHandler(OnTick);
            _timer.Start();
//            _timer.Stop();
        }
        public void InitializePath()
        {
            _myPath.SetPathParams(60,   //path frequency = 30 Hz
                       75,       //Store a minimum of 45 points in the path point buffer
                       15000.0,  //X scale - 20000.0 counts per inch
                       15000.0,  //Y scale - 20000.0 counts per inch
                       15000.0,      //Z scale - 1.0 counts per inch - not used
                       0.175);

            _myPath.SetOrigin(0.0, 0.0, 0.0);
            _myPath.SetFeedrate(0.200);
            _myPath.SetTangentTolerance((float)10.0);

            _path1 = new System.Windows.Shapes.Path();
            _path1.Stroke = new SolidColorBrush(Colors.Black);
            _path1.StrokeThickness = 2;
            _path1.Stroke = Brushes.Blue;
            _path1.Data = _pathGeometry1;
            stackPanel1.Children.Add(_path1);

        }

        private static void StartJoyStick()
        {
//            Console.WriteLine("Hello, world!");
        }
        // Add Update Method
        private void OnTick(object sender, EventArgs evt)
        {
            try
            {
                Update();
            }
            catch (Exception e)
            {
                _timer.Stop();
//                Text = "Error: " + e;
            }
        }

        public void Update()
        {
            UpdateDRO();
        }
        public void UpdateDRO()
        {
            double X = 0.0, Y = 0.0, Z = 0.0;
            _myStage.GetPos(out X, out Y, out Z);
            txtBoxXAxis.Text = X.ToString();
            txtBoxYAxis.Text = Y.ToString();
            txtBoxZAxis.Text = Z.ToString();

        }
        private void txtBoxXAxis_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void txtBoxXYZAxis_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void txtBoxXAxis_TextChanged_1(object sender, TextChangedEventArgs e)
        {

        }

        private void btnLoad_Click(object sender, RoutedEventArgs e)
        {
            _timer.Stop();
            _editorLine = 1;
            _myEditor.Set(txtProgram);
            string myFile=_myEditor.OpenFile();
            myMillCtrl.ProcessGCode(myFile);
            _timer.Start();
        }
        public void DoEvents()
        {
            DispatcherFrame frame = new DispatcherFrame();
            Dispatcher.CurrentDispatcher.BeginInvoke(DispatcherPriority.Background,
                new DispatcherOperationCallback(ExitFrames), frame);
            Dispatcher.PushFrame(frame);
        }

        public object ExitFrames(object f)
        {
            ((DispatcherFrame)f).Continue = false;

            return null;
        }

        private void btnRun_Click(object sender, RoutedEventArgs e)
        {
            int numberOfCommands = 0;
            numberOfCommands = myMillCtrl.Count();
            _timer.Stop();
            _JoyStick.Disable();
            double x1, y1, z1;
            double x2, y2, z2;
            double x3, y3, z3;
            string Command = "";
            myMillCtrl.InitRun();
            for (int i = 0; i < numberOfCommands; i++)
            {
                myMillCtrl.RunCommand(i);
                int itype = myMillCtrl.GetCommand();
                Command = "Nothing";
                if (itype == 6)
                {
                    Command = "G0";
                    Update1();
                    Thread.Sleep(500);

                }
                if (itype == 1)
                {
                    Command = "G1";
                    Update1();
                    Thread.Sleep(500);

                }

                if (itype == 0)
                {
                    Command = "G3";
                    myMillCtrl.GetStart(out x1, out  y1, out  z1);
                    myMillCtrl.GetEnd(out x2, out y2, out z2);
                    myMillCtrl.GetCenter(out x3, out y3, out z3);

                    _cmdData.SetData(CommandType.G3_MoveArcCCW, new Point3D(x1, y1, z1), new Point3D(x2, y2, z2), new Point3D(x3, y3, z3));
                    _cmdData.SetScale(20.0);
                    _cmdData.Translate(200.0, 200.0, 200.0);
                    if (_firstPath)
                    {
                        _myPathDisplay.StartPoint(_cmdData._start.X, _cmdData._start.Y);
                        _firstPath = false;
                    }

                    _myPathDisplay.SetCommand(_cmdData);
                    _myPathDisplay.GetFigure(ref _pathFigure1);
                    _pathGeometry1.Figures.Add(_pathFigure1);
                    Update1();
                    Thread.Sleep(500);

                }
                myMillCtrl.Iter();

                if (Command.Equals("G0") || Command.Equals("G1") || Command.Equals("G3"))
                {
                    _editorLine = _myEditor.SearchAndHighLightLine(_editorLine, Command);
                    DoEvents();
                }
            }
            _myStage.SetScale();
            _myStage.ResetPos();
            _JoyStick.Enable();
            _timer.Start();
        }
    }

    public static class ExtensionMethods
    {
        private static Action EmptyDelegate = delegate() { };

        public static void Refresh(this UIElement uiElement)
        {
            uiElement.Dispatcher.Invoke(DispatcherPriority.Render, EmptyDelegate);
        }
    }



}
