using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Collections;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Timers;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using stageclr;
using MoyStick;
using System.Threading;
using System.IO;


namespace stageclr
{

    public partial class Form1 : Form
    {
        CStage myStage;
        private System.Windows.Forms.StatusBar stbMouseStick;
        int shipX, shipY, dX, dY;
        private System.Timers.Timer shipTimer;
        private System.Timers.Timer _stageTimer;
        private bool _StageTimerDone;
        private bool _ZAxisMoveUp;
        private int _iter;
        private motionTestCLR.PathSettings PathSet;

        private MainMenu mainMenu;
        ArrayList myPathList = new ArrayList();
        GraphicsPath myPathB = new GraphicsPath();
        Graphics pictureboxGraphics;
        private float xOffset = 0;
        private float yOffset = 0;
        private float zZoom = 0.001f;
        private string _pathfile = null;
        public Form1()
        {
            InitializeComponent();
            PathSet = new motionTestCLR.PathSettings();

            myPathB = new GraphicsPath();
            pictureboxGraphics = this.pictureBox1.CreateGraphics();
            pictureBox1.Paint += new PaintEventHandler(pictureBox1_Paint);
            CenterToScreen();
            SetStyle(ControlStyles.ResizeRedraw, true);	// Alternative to handling Resize().

            CreateMenu();

            // Attach main menu to the Form object.         
            this.Menu = mainMenu;
            this.shipX = this.Width / 2;
            this.shipY = this.Height / 2;
            this.dX = 0;
            this.dY = 0;
            this.SetStyle(System.Windows.Forms.ControlStyles.DoubleBuffer, true);

            this._stageTimer = new System.Timers.Timer();
            this._stageTimer.Enabled = true;
            this._stageTimer.SynchronizingObject = this;
            this._StageTimerDone = true;
            this._stageTimer.Elapsed += new System.Timers.ElapsedEventHandler(this.On_ElapsedTimer);

            this.ZAxisTimer.Enabled = false;
            this.ZAxisTimer.Tick += new System.EventHandler(this.On_ZAxisTimerTick);
            _iter = 0;
        }
        private void CreateMenu()
        {
            mainMenu = new MainMenu();
            //Create the 'File | Exit' Menu.
            MenuItem miFile = mainMenu.MenuItems.Add("&File");
            miFile.MenuItems.Add(new MenuItem("O&pen",
                new EventHandler(this.FileOpen_Clicked),
                Shortcut.CtrlP));
            miFile.MenuItems.Add(new MenuItem("E&xit",
                new EventHandler(this.FileExit_Clicked),
                Shortcut.CtrlX));

            // Now create a 'Help | About' menu.
            MenuItem miHelp = mainMenu.MenuItems.Add("Help");
            miHelp.MenuItems.Add(new MenuItem("&About",
                new EventHandler(this.HelpAbout_Clicked),
                Shortcut.CtrlA));

        }
        public int SetScaling_3Axis		()
        {
            myStage.SetEncoderCounts(0, 200.00);
            myStage.SetEncoderCounts(1, 200.00);
            myStage.SetEncoderCounts(2, 200.00);

            myStage.SetLeadScrewPitch(0, 10.00);
            myStage.SetLeadScrewPitch(1, 10.00);
            myStage.SetLeadScrewPitch(2, 20.00);

            myStage.SetMotorGearRatio(0, 5.9);
            myStage.SetMotorGearRatio(1, 5.9);
            myStage.SetMotorGearRatio(2, 5.9);

            myStage.SetPulleyRatio(0, 2.13 / 1.504);
            myStage.SetPulleyRatio(1, 2.13 / 1.504);
            myStage.SetPulleyRatio(2, 2.13 / 1.504);

	        return 0;
        }
        public int SetPIDGain_3Axis()
        {
            int iProportional;
            int iDifferential;
            int iIntegral;

            int bXAxisGain = 0;
            int bYAxisGain = 0;
            int bZAxisGain = 0;

            myStage.SetGainLimits(0, 0.0, 255.0, 0.0, 2000.0, 1.0, 0.0);
            myStage.SetGainLimits(1, 0.0, 255.0, 0.0, 2000.0, 1.0, 0.0);
            myStage.SetGainLimits(2, 0.0, 255.0, 0.0, 2000.0, 1.0, 0.0);
      
            bXAxisGain = myStage.SetGain(0, 2144, 7680, 512);	   //DC = 0
            if (bXAxisGain==1)
                return -1;

            bYAxisGain = myStage.SetGain(1, 1656, 4064, 128);     //DC = 0;
            if (bYAxisGain==1)
                return -2;

            bZAxisGain = myStage.SetGain(2, 1872, 12288, 512);      //DC = 0
            if (bZAxisGain==1)
                return -3;

 //           myStage.GetGain(0, iProportional, iDifferential, iIntegral);
 //           myStage.GetGain(1, iProportional, iDifferential, iIntegral);
 //           myStage.GetGain(2, iProportional, iDifferential, iIntegral);

            return 0;

        }
        private void InitializeCoordMotion()
        {
            myStage.SetGroupAddress(128, 0);
            myStage.StopResetMotors();
            myStage.SetPathStatus();

        }
        private void SetMotionGains()
        {
            SetScaling_3Axis();
            SetPIDGain_3Axis();
        }

        private void SetSpeedAndAcceleration()
        {
            myStage.SetVel(3.0, 3.0, 3.0);
            myStage.SetAccel(6.00, 6.00, 6.00);
            myStage.EnableAmp();
 //           myStage.ResetPos();
            ShowPosition();

        }
        private void Form1_Load(object sender, EventArgs e)
        {
            myStage = new CStage("COM4:");
            InitializeCoordMotion();
            SetMotionGains();
            SetSpeedAndAcceleration();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            double XPos = new double();
            double YPos = new double();
            double ZPos = new double();
            
            double XAcc = new double();
            double YAcc = new double();
            double ZAcc = new double();

            SetMotionGains(); 
            SetSpeedAndAcceleration();
            myStage.GetCmdAccel(out XAcc, out YAcc, out ZAcc);

            myStage.EnableAmp();
            myStage.ResetPos();
            int iError;
            iError = myStage.MoveTo(0.25, 0.25, 0.25, true);

            myStage.GetPos(out XPos, out YPos, out ZPos);
            iError = myStage.MoveTo(0.0, 0.0, 0.0, true);

            myStage.GetPos(out XPos, out YPos, out ZPos);

        }
        private void userControl12_MouseEnter(object sender, System.EventArgs e)
        {
 //           tbEvent.Text = "MouseEnter " + "Interation=" + _iter.ToString();
 //           _iter += 1;

        }
        private void userControl12_MouseLeave(object sender, System.EventArgs e)
        {
            this.stbMouseStick.Text = "Mouse Left";
            dX = 0;
            dY = 0;
                
            myStage.Stop();
            Thread.Sleep(100);

        }
        private int ShowPosition()
        {
            double X = 0.0, Y = 0.0, Z = 0.0;
 
            myStage.GetPos(out X, out Y, out Z);
            txtPositionX.Text = String.Format("{0,2:0.0000000}", X);
            txtPositionY.Text = String.Format("{0,2:0.0000000}", Y);   
            txtPositionZ.Text = String.Format("{0,2:0.0000000}", Z);

            txtPositionX.Update();
            txtPositionY.Update();
            txtPositionZ.Update();
            return 0;
        }
        private void userControl12_MouseStickMoved(object sender, MoyStick.MouseStickEventArgs e)
        {
            stbMouseStick.Text = "direction: " + e.Direction.ToString() + " magnitude: " + e.Magnitude.ToString();

            double XPos = new double();
            double YPos = new double();
            double ZPos = new double();
            double DeltaX = new double();
            double DeltaY = new double();

            if (_StageTimerDone == false)
                return;

            switch (e.Direction)
            {
                case MoyStick.cPoint.north:
                    dY = e.Magnitude * (-1);
                    dX = 0;
                    break;
                case MoyStick.cPoint.northEast:
                    dY = e.Magnitude * (-1);
                    dX = e.Magnitude;
                    break;
                case MoyStick.cPoint.east:
                    dY = 0;
                    dX = e.Magnitude;
                    break;
                case MoyStick.cPoint.southEast:
                    dY = e.Magnitude;
                    dX = e.Magnitude;
                    break;
                case MoyStick.cPoint.south:
                    dY = e.Magnitude;
                    dX = 0;
                    break;
                case MoyStick.cPoint.southWest:
                    dY = e.Magnitude;
                    dX = e.Magnitude * (-1);
                    break;
                case MoyStick.cPoint.west:
                    dY = 0;
                    dX = e.Magnitude * (-1);
                    break;
                case MoyStick.cPoint.northWest:
                    dY = e.Magnitude * (-1);
                    dX = e.Magnitude * (-1);
                    break;
                default:
                    dY = 0;
                    dX = 0;
                    myStage.Stop();
                    return;
                    break;
            }

            double mag = Math.Sqrt(dX * dX + dY * dY);
            if (mag == 0.0)
                return;


            _stageTimer.Interval = 250;
            _stageTimer.Start();
            _StageTimerDone = false;

            myStage.GetPos(out XPos, out YPos, out ZPos);
            DeltaX = dX / 100.00; DeltaY = dY / 100.00;
            myStage.MoveTo(XPos + DeltaX, YPos + DeltaY, ZPos);
//            tbEvent.Text = "MouseStickMoved " + "Interation=" + _iter.ToString();
//            _iter += 1;
            ShowPosition();
        }
        private void userControl12_MouseDirectionChanged(object sender, MoyStick.MouseStickEventArgs e)
        {
            myStage.Stop();
            ShowPosition();
        }

        private void shipTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            shipX += dX;
            shipY += dY;
            this.Invalidate();
        }
        private void On_ElapsedTimer(object sender, System.Timers.ElapsedEventArgs e)
        {
            _StageTimerDone = true;
            _stageTimer.Stop();
        }
        private void Form1_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.DrawEllipse(Pens.Black, shipX, shipY, 20, 20);
            g.FillEllipse(Brushes.Aqua, shipX, shipY, 20, 20);
        }
        private void MoveZ(double ZDelta)
        {
            double XPos, YPos, ZPos;
            myStage.GetPos(out XPos, out YPos, out ZPos);
            myStage.MoveTo(XPos, YPos, ZPos + ZDelta);
            ShowPosition();

        }
        private void btnUp_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            this.ZAxisTimer.Enabled = true;
            this.ZAxisTimer.Interval=150;
            _ZAxisMoveUp = true;
        }
        private void On_ZAxisTimerTick(object sender, System.EventArgs e)
        {
            if (_ZAxisMoveUp)
                MoveZ(0.10);
            else
                MoveZ(-0.10);

        }
        private void btnUp_MouseLeave(object sender, EventArgs e)
        {
            this.ZAxisTimer.Enabled = false;
            myStage.Stop();
            Thread.Sleep(100);
        }

        private void btnUp_Click(object sender, EventArgs e)
        {
            this.ZAxisTimer.Enabled = false;
            MoveZ(0.02);
        }
        private void btnDown_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            this.ZAxisTimer.Enabled = true;
            this.ZAxisTimer.Interval = 150;
            _ZAxisMoveUp = false;
        }
        private void btnDown_MouseLeave(object sender, EventArgs e)
        {
            this.ZAxisTimer.Enabled = false;
            myStage.Stop();
            Thread.Sleep(100);
        }
 
        private void btnDown_Click(object sender, EventArgs e)
        {
            this.ZAxisTimer.Enabled = false;
            MoveZ(-0.02);

        }

        private void button2_Click(object sender, EventArgs e)
        {
            int ret;
            double x, y, z;
            InitializeCoordMotion();
            myStage.SetPathFreq(60);
            myStage.SetNumberOfPoints(60);
            myStage.SetScale(6684.57447, 6684.57447, 6684.57447);
            myStage.SetPathAcceleration(1.0);
            myStage.SetFeedrate(1.0);
            myStage.SetPathParams();     //acceleration = 1.0 inch/second/second


            myStage.SetOrigin(0.0, 0.0, 0.0); //set the origin to X = 0, Y = 0, Z = 0
            myStage.SetFeedrate(1.0);         //feedrate = 1.0 inches/second
            myStage.SetTangentTolerance(10.0);  //continuous path tangent tolerence = 10 degrees


            myStage.GetPos(out x, out y, out z);
            myStage.ResetPos();
            ShowPosition();
            //Clear the segment list and set the starting point for the path
            //  at X = 0, Y = 1, Z = 0
            myStage.ClearSegList(0, 0, 0);

            //Add a segment to move to x=0, y=2, z=0
            ret = myStage.AddLineSeg(0.0, 1.0, 0.0);
            if (ret < 0) return;

            ret = myStage.AddArcSeg(1.0, 2.0, 0.0,     //end point of arc: x=1, y=2, z=0
                                    1.0, 1.0, 0.0,     //center point of arc: x=1, y=1, z = 0
                                    0.0, 0.0, -1.0);   //normal vector to arc plane: x = 0, y = 0, z = -1
            if (ret < 0) return;
            myStage.ExecuteCoordMotion();

            myStage.ClearSegList(1.0, 2.0, 0.0);
            myStage.GetPos(out x, out y, out z);

            ret = myStage.AddLineSeg(2.0, 2.0, 0.0);    //line segment endpoint: x=4, y=3, z=0
            if (ret < 0) return;

            ret = myStage.AddArcSeg(3.0, 1.0, 0.0,     //end point of arc: x=5, y=2, z=0
                                    2.0, 1.0, 0.0,     //center point of arc: x=4, y=2, z = 0
                                    0.0, 0.0, -1.0);   //normal vector to arc plane: x = 0, y = 0, z = -1
            if (ret < 0) return;

            //line segment endpoint: x=5, y=0, z=0
            ret = myStage.AddLineSeg(3.0, 0.0, 0.0);
            if (ret < 0) return;

            //line segment endpoint: x=5, y=0, z=0
            ShowPosition();
            myStage.ExecuteCoordMotion();
            ShowPosition();

            ret = myStage.ClearSegList(3.0, 0.0, 0.0);
            if (ret < 0) return;

            //line segment endpoint: x=5, y=0, z=0
            ret = myStage.AddLineSeg(0.0, 0.0, 0.0);
            ShowPosition();
            if (ret < 0) return;
            myStage.ExecuteCoordMotion();
            ShowPosition();
            SetMotionGains();
            SetSpeedAndAcceleration();
            myStage.ResetPos();
            myStage.EnableAmp();

        }

        private void button3_Click(object sender, EventArgs e)
        {
            InitializeCoordMotion();
            SetPathSettings();

            if (_pathfile == null)
                return;

            myStage.OpenInFile(_pathfile);
            myStage.ReadInFile();
            myStage.CloseInFile();
            SetMotionGains();
            SetSpeedAndAcceleration();
            myStage.EnableAmp();
//            myStage.ResetPos();
        }
        private void pictureBox1_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
        {
            DrawShapesA(e.Graphics);
            Invalidate();

        }
		private void MainForm_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
		{
            DrawShapesA(pictureboxGraphics);


        }
        private void FileExit_Clicked(object sender, EventArgs e)
        {
            this.Close();
        }
        private void FileOpen_Clicked(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            openFileDialog1.InitialDirectory = "C:\\Program Files\\Mill1\\_Output";
            openFileDialog1.Filter = "path files (*.path)|*.path|All files (*.*)|*.*";
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.RestoreDirectory = true;

            SetPathSettings();

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    _pathfile = openFileDialog1.FileName;
                    myStage.OpenInFile(_pathfile);
                    myStage.ReadInFileSimulation();
                    myStage.CloseInFile();

                    AddCurves("OutputPoints.pts");
                    DrawShapesA(pictureboxGraphics);
                    this.pictureBox1.Invalidate();
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
                }
            }

        }
        private void SetPathSettings()
        {
            myStage.SetPathFreq(PathSet.Frequency);
            myStage.SetNumberOfPoints(PathSet.NumberOfPts);
            myStage.SetScale(PathSet.Xscale, PathSet.Yscale, PathSet.Zscale);
            myStage.SetPathAcceleration(PathSet.Acceleration);
            myStage.SetFeedrate(PathSet.Feedrate);         //feedrate = 1.0 inches/second
            myStage.SetTangentTolerance(PathSet.Tolerance);  //continuous path tangent tolerence = 10 degrees
            myStage.SetPathParams();     //acceleration = 1.0 inch/second/second
            myStage.SetOrigin(PathSet.Xorigin, PathSet.Yorigin, PathSet.Zorigin); //set the origin to X = 0, Y = 0, Z = 0


        }
        private void AddCurves(string file)
        {

            StreamReader FileStr = new StreamReader(file);
            string indata;
            char[] delimiterChars = { ' ', ',', '\t' };
            Point ptsStore = new Point();
            ArrayList ptsList = new ArrayList();

            string[] pts;
            double x, y;
            myPathB.Reset();

            while (!FileStr.EndOfStream)
            {
                indata = FileStr.ReadLine();
                ptsList.Clear();
                while (true)
                {
                    indata = FileStr.ReadLine();
                    if (indata.Equals("END") == true)
                        break;

                    pts = indata.Split(delimiterChars);
                    x = Convert.ToDouble(pts[0]);
                    y = Convert.ToDouble(pts[1]);
                    ptsStore.X = (int)(x );
                    ptsStore.Y = (int)(y );
                    ptsList.Add(ptsStore);
                }
                Point[] points = new Point[ptsList.Count];
                for (int i = 0; i <= ptsList.Count - 1; i++)
                {
                    points[i] = (Point)ptsList[i];
                }
                myPathB.StartFigure();
                myPathB.AddCurve(points);
                myPathB.CloseFigure();

            }

            FileStr.Close();

        }

         private void DrawShapesA(Graphics g)
        {

            pictureBox1.SizeMode = PictureBoxSizeMode.CenterImage;
            float Zoom = new float();
            Matrix x = new Matrix();
            Zoom = 0.005f;
            x.Scale(zZoom, zZoom);

            g.Transform = x;
            g.TranslateTransform(xOffset, yOffset);

            Pen outline = new Pen(Color.Purple, 5);
            g.DrawPath(outline, myPathB);

        }
        // Help | About Menu item handler
        private void HelpAbout_Clicked(object sender, EventArgs e)
        {
            MessageBox.Show("The amazing menu app...");
        }

		private void Form1_Resize(object sender, System.EventArgs e)
		{
			// Invalidate();  See ctor!
		}

        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            yOffset = this.vScrollBar1.Value;
            DrawShapesA(pictureboxGraphics);
            this.pictureBox1.Invalidate();
        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            xOffset = this.hScrollBar1.Value;
            DrawShapesA(pictureboxGraphics);
            this.pictureBox1.Invalidate();

        }


        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            if (this.trackBar1.Value == 0)
                zZoom = 0.001f;
            
            if (this.trackBar1.Value == 10)
                zZoom = this.trackBar1.Value*0.1f;

            zZoom = this.trackBar1.Value * 0.001f;
            
            DrawShapesA(pictureboxGraphics);
            this.pictureBox1.Invalidate();

        }

        private void button4_Click(object sender, EventArgs e)
        {
            motionTestCLR.FormPathSettings PathSettings = new motionTestCLR.FormPathSettings();
            PathSettings.ShowDialog();
            PathSet = PathSettings.PathSet;

        }

    }
}
