using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Media3D;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows;

namespace XBoxJoyStick
{
    public class PathDisplay
    {
        StackPanel _stackPanel1 = new StackPanel();
        PathFigure _pathFigure1 = new PathFigure();
        CommandData _data = new CommandData();
        public void SetCommand(CommandData data)
        {
            _data = data;
        }

        public void Set(StackPanel stPanel)
        {
            _stackPanel1 = stPanel;
        }

        public void StartPoint(double X, double Y)
        {
            _pathFigure1.StartPoint = new Point(X, Y);
        }

        public void GetFigure(ref PathFigure myPathFigure)
        {
            _data.GetFigure(ref _pathFigure1);
            myPathFigure = _pathFigure1;
        }

    }
}
