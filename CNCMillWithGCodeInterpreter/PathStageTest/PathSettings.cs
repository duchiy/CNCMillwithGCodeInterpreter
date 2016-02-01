using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace motionTestCLR
{

    public class PathSettings
    {
        private int _Frequency;
        private int _NumberOfPts;
        private double _Xscale, _Yscale, _Zscale;
        private double _Acceleration;
        private double _Feedrate;
        private double _Tolerance;
        private double _Xorigin, _Yorigin, _Zorigin;
 
        public PathSettings()
        {
            _Frequency=60;
            _NumberOfPts=75;
            _Xscale=15000.0; _Yscale=15000.0; _Zscale=15000.0;
            _Acceleration = 0.175;
            _Feedrate = 0.175;
            _Tolerance = 10.0;
            _Xorigin = 0.0; _Yorigin = 0.0; _Zorigin = 0.0;

        }
 
        public void SetParams(int pathFrequency,   //path frequency = 30 Hz
					int numberOfPts,                      //Store a minimum of 45 points in the path point buffer
					double Xscale,                 //X scale - 20000.0 counts per inch
					double Yscale,                 //Y scale - 20000.0 counts per inch
					double Zscale,                 //Z scale - 1.0 counts per inch - not used
					double pathAcceleration)                  //acceleration = 1.0 inch/second/second
         {

             _Frequency = pathFrequency;
             _NumberOfPts = numberOfPts;
             _Xscale = Xscale; _Yscale = Yscale; _Zscale = Zscale;
             _Acceleration = pathAcceleration;
             _Feedrate = 0.175;

         }
        public void SetOrigin(double XOrigin, double YOrigin, double ZOrigin)
        {
            _Xorigin = XOrigin;
            _Yorigin = YOrigin;
            _Zorigin = ZOrigin;

        }
        public void SetFeedRate(double Feedrate)
        {
            _Feedrate = Feedrate;
        }
        public int Frequency
        {
            get { return _Frequency; }
            set { _Frequency = value; }
        }
        public int NumberOfPts
        {
            get { return _NumberOfPts; }
            set { _NumberOfPts = value; }
        }
        public double Acceleration
        {
            get { return _Acceleration; }
            set { _Acceleration = value; }
        }
        public double Feedrate
        {
            get { return _Feedrate; }
            set { _Feedrate = value; }
        }
        public double Tolerance
        {
            get { return _Tolerance; }
            set { _Tolerance = value; }
        }
        public double Xscale
        {
            get { return _Xscale; }
            set { _Xscale = value; }
        }
        public double Yscale
        {
            get { return _Yscale; }
            set { _Yscale = value; }
        }
        public double Zscale
        {
            get { return _Zscale; }
            set { _Zscale = value; }
        }
        public double Xorigin
        {
            get { return _Xorigin; }
            set { _Xorigin = value; }
        }
        public double Yorigin
        {
            get { return _Yorigin; }
            set { _Yorigin = value; }
        }
        public double Zorigin
        {
            get { return _Zorigin; }
            set { _Zorigin = value; }
        }
    }
}
