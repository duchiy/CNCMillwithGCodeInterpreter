using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Media;
using System.Windows.Media.Media3D;
using System.Windows;


namespace XBoxJoyStick
{
    public enum CommandType
    {
        G0_GoTo,
        G1_MoveTo,
        G2_MoveArcCW,
        G3_MoveArcCCW,
    };

    public class CommandData
    {
        public CommandData()
        {
            CalculateStartAngle();
            CalculateEndAngle();
            CalculateRadius();
        }
        public CommandData(CommandType cmdType, Point3D start, Point3D end, Point3D center)
        {
            _cmdType = cmdType;
            _start = start;
            _end = end;
            _center = center;
            CalculateStartAngle();
            CalculateEndAngle();
            CalculateRadius();
        }
        public CommandData(CommandData cmdData)
        {
            _cmdType = cmdData._cmdType;
            _start = cmdData._start;
            _end = cmdData._end;
            _center = cmdData._center;
            CalculateStartAngle();
            CalculateEndAngle();
            CalculateRadius();
        }
        public void SetData(CommandType cmdType, Point3D start, Point3D end, Point3D center)
        {
            _cmdType = cmdType;
            _start = start;
            _end = end;
            _center = center;
            CalculateStartAngle();
            CalculateEndAngle();
            CalculateRadius();
        }
        public double CalculateStartAngle()
        {
            Point3D P3 = new Point3D();
            P3.X = _start.X - _center.X;
            P3.Y = _start.Y - _center.Y;
            _startAngle = Math.Atan2(P3.Y, P3.X) * 180.0 / Math.PI;

            if (_startAngle < 0.0)
            {
                _startAngle = _startAngle + 360.0;
            }
            return _startAngle;
        }
        public double CalculateEndAngle()
        {
            Point3D P3 = new Point3D();
            P3.X = _end.X - _center.X;
            P3.Y = _end.Y - _center.Y;
            _endAngle = Math.Atan2(P3.Y, P3.X) * 180.0 / Math.PI;
            if (_endAngle <= 0.0)
            {
                _endAngle = _endAngle + 360.0;
            }

            return _endAngle;
        }


        public double CalculateRadius()
        {

            _radius = Math.Sqrt((_center.X - _start.X) * (_center.X - _start.X) + (_center.Y - _start.Y) * (_center.Y - _start.Y));
            return _radius;

        }
        public void GetCenter(ref double X, ref double Y)
        {
            X = _center.X;
            Y = _center.Y;
        }
        public void SetScale(double scale)
        {
            if (scale != 0.0)
            {
                _scale = scale;
                _start.X = _start.X * _scale;
                _start.Y = _start.Y * _scale;
                _end.X = _end.X * _scale;
                _end.Y = _end.Y * _scale;
                _center.X = _center.X * _scale;
                _center.Y = _center.Y * _scale;
                _radius = _radius * _scale;

            }

        }

        public void SetDegreeIncrement(double increment)
        {
            _increment = increment;
        }

        public void Translate(double X, double Y, double Z)
        {
            _start.X = _start.X + X;
            _start.Y = _start.Y + Y;
            _start.Z = _start.Z + Z;

            _end.X = _end.X + X;
            _end.Y = _end.Y + Y;
            _end.Z = _end.Z + Z;

            _center.X = _center.X + X;
            _center.Y = _center.Y + Y;
            _center.Z = _center.Z + Z;

        }
        public void GetFigure(ref PathFigure figure)
        {

            for (double start = _startAngle; start < _endAngle; start++)
            {
                LineSegment line = new LineSegment();
                Point myPoint = new Point();
                myPoint.X = _radius * Math.Cos(start * Math.PI / 180.0) + _center.X;
                myPoint.Y = _radius * Math.Sin(start * Math.PI / 180.0) + _center.Y;
                line.Point = myPoint;
                figure.Segments.Add(line);
            }

        }
        public CommandType _cmdType;
        public Point3D _start;
        public Point3D _end;
        public Point3D _center;
        private double _startAngle = 0.0;
        private double _endAngle = 0.0;
        private double _radius;
        private double _scale = 1.0;
        private double _increment = 1.0;
    }
}
