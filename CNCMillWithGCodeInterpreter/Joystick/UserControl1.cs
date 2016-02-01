using System;
using System.Collections;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Data;
using System.Windows.Forms;

namespace MoyStick
{
	public delegate void MouseStickMovedEventHandler(object sender, MouseStickEventArgs e);
	public enum cPoint
	{
		north,
		northEast,
		east,
		southEast,
		south,
		southWest,
		west,
		northWest
	}
	/// <summary>
	/// Summary description for UserControl1.
	/// </summary>
	/// 

	public class UserControl1 : System.Windows.Forms.Control
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
        public event MouseStickMovedEventHandler MouseStickMoved;
        public event MouseStickMovedEventHandler MouseDirectionChanged;
		

		int magnitude;	//	proportional to distance from center
		int circle_diameter;	// diameter of circular location graphic
		Color line_color;
		float line_width;
		Point mousePoint, center;
		LineCap line_end_shape;
		bool isActive;
		private System.Timers.Timer drawTimer;
		cPoint direction;
        cPoint previousdirection;

		public UserControl1()
		{
			// This call is required by the Windows.Forms Form Designer.
			InitializeComponent();
            mousePoint = new Point(this.Width / 2, this.Height / 2);
            isActive = false;
            center = new Point(this.Width / 2, this.Height / 2);

			// TODO: Add any initialization after the InitComponent call
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if( components != null )
					components.Dispose();
			}
			base.Dispose( disposing );
		}

		#region Component Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.drawTimer = new System.Timers.Timer();
			((System.ComponentModel.ISupportInitialize)(this.drawTimer)).BeginInit();
			// 
			// drawTimer
			// 
			this.drawTimer.Enabled = true;
			this.drawTimer.Interval = 10;
			this.drawTimer.SynchronizingObject = this;
			this.drawTimer.Elapsed += new System.Timers.ElapsedEventHandler(this.drawTimer_Elapsed);
			// 
			// UserControl1
			// 
			this.Paint += new System.Windows.Forms.PaintEventHandler(this.UserControl1_Paint);
			this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.UserControl1_MouseMove);
			this.MouseLeave += new System.EventHandler(this.UserControl1_MouseLeave);
			this.MouseEnter += new System.EventHandler(this.UserControl1_MouseEnter);
			((System.ComponentModel.ISupportInitialize)(this.drawTimer)).EndInit();
            

		}
		#endregion

		protected void UserControl1_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
		{
			PointF center = new PointF(this.Width/2,this.Height/2);
			Graphics g = e.Graphics;
			Pen lPen = new Pen(line_color);
			lPen.EndCap = this.line_end_shape;

			//Assign the control's region
			GraphicsPath gP = new GraphicsPath();
			gP.AddEllipse(this.ClientRectangle);
			this.Region = new Region(gP);
			// Draw the Line
			g.DrawLine(lPen, center, mousePoint);
		}

		private void UserControl1_MouseEnter(object sender, System.EventArgs e)
		{
			isActive = true;
		}

		private void UserControl1_MouseLeave(object sender, System.EventArgs e)
		{
			mousePoint.X = this.Width/2;
			mousePoint.Y = this.Height/2;
			magnitude = 0;
			isActive = false;
		}

		private void UserControl1_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
		{
			if (isActive)
			{
				int x_Val,y_Val;
				//Translating mouse motion on the control
				//To a 30 x 30 cartesian grid.
				y_Val = (e.Y * 31 / this.Height) - 15;
				x_Val = (e.X * 31 / this.Width) - 15;
				y_Val = -y_Val;

				//Setting up to raise the MouseStickMoved Event
				direction = GetDirection(x_Val, y_Val);
                if (previousdirection != direction)
                {
                    previousdirection = direction;
                    MouseDirectionChanged(this, new MouseStickEventArgs(this.magnitude, this.direction));

                }

				magnitude = (int)Math.Sqrt(y_Val * y_Val + x_Val * x_Val);
//				if (magnitude > 15) magnitude = 15;
                magnitude = 15;
                mousePoint.X = e.X;
				mousePoint.Y = e.Y;
			}
			else
			{
				magnitude = 0;
				mousePoint.X = this.Width/2;
				mousePoint.Y = this.Height/2;
			}

			if(MouseStickMoved != null)
				MouseStickMoved(this, new MouseStickEventArgs(this.magnitude, this.direction));

		}

		private cPoint GetDirection(float x, float y)
		{
			//Changing cartesian coordinates from control surface to  
			//more usable polar coordinates
			double theta;
			if(x >= 0 && y > 0)
				theta = (Math.Atan(y/ x) * (180 /Math.PI));
			else if(x < 0)
				theta = ((Math.PI + Math.Atan(y / x)) * (180 /Math.PI));
			else theta = (((2*Math.PI) + Math.Atan(y / x)) * (180 /Math.PI));
			
			//Changing from degrees to direction.
			if(theta <= 26 || theta > 341)
				return cPoint.east;
			else if (theta > 26 && theta <=71)
				return cPoint.northEast;
			else if (theta > 71 && theta <= 116)
				return cPoint.north;
			else if (theta > 116 && theta <= 161)
				return cPoint.northWest;
			else if (theta > 161 && theta <= 206)
				return cPoint.west;
			else if (theta > 206 && theta <= 251)
				return cPoint.southWest;
			else if (theta > 251 && theta <= 296)
				return cPoint.south;
			else return cPoint.southEast;
		}

		private void drawTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
		{
			this.Invalidate();
		}


		public int Magnitude 
		{
			get{return magnitude;}
			set 
			{
				magnitude = value;
				this.Refresh();
			}
		}

		public Color LineColor 
		{
			get{return line_color;}
			set 
			{
				line_color = value;
				this.Refresh();
			}
		}

		public float LineWidth 
		{
			get{return line_width;}
			set 
			{
				line_width = value;
				this.Refresh();
			}
		}

		public LineCap LineShapeEnd 
		{
			get{return line_end_shape;}
			set 
			{
				line_end_shape = value;
				this.Refresh();
			}
		}

		public int CircleDiameter 
		{
			get{return circle_diameter;}
			set 
			{
				circle_diameter = value;
				this.Size = new Size(circle_diameter, circle_diameter);
				this.Refresh();
			}
		}

		public cPoint Direction 
		{
			get{return direction;}
			set 
			{
				direction = value;
				this.Refresh();
			}
		}
	}

	public class MouseStickEventArgs : System.EventArgs
	{
		public MouseStickEventArgs(int Magnitude, cPoint Direction)
		{
			dir = Direction;
			mag = Magnitude;
		}
        public MouseStickEventArgs(bool upZdirection)
        {
            upZdir = upZdirection;

        }

		public int Magnitude
		{
			get{return mag;}
		}
        public cPoint Direction
        {
            get { return dir; }
        }
        public bool ZDirectionUp
        {
            get { return upZdir; }
            set
            {
                upZdir = value;
            }

        }

		int mag;
		cPoint dir;
        bool upZdir;
	}


}
