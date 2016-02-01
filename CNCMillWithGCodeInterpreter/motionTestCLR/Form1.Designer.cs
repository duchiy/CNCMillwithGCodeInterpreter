namespace stageclr
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.button1 = new System.Windows.Forms.Button();
            this.stbMouseStick = new System.Windows.Forms.StatusBar();
            this.userControl12 = new MoyStick.UserControl1();
            this.shipTimer = new System.Timers.Timer();
            this.txtPositionX = new System.Windows.Forms.TextBox();
            this.txtPositionY = new System.Windows.Forms.TextBox();
            this.txtPositionZ = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.directorySearcher1 = new System.DirectoryServices.DirectorySearcher();
            this.btnUp = new System.Windows.Forms.Button();
            this.btnDown = new System.Windows.Forms.Button();
            this.tbEvent = new System.Windows.Forms.TextBox();
            this.ZAxisTimer = new System.Windows.Forms.Timer(this.components);
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.vScrollBar1 = new System.Windows.Forms.VScrollBar();
            this.hScrollBar1 = new System.Windows.Forms.HScrollBar();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.button4 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.shipTimer)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(766, 190);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "TestPtToPt";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // stbMouseStick
            // 
            this.stbMouseStick.Location = new System.Drawing.Point(0, 548);
            this.stbMouseStick.Name = "stbMouseStick";
            this.stbMouseStick.Size = new System.Drawing.Size(713, 22);
            this.stbMouseStick.TabIndex = 1;
            // 
            // userControl12
            // 
            this.userControl12.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.userControl12.CircleDiameter = 120;
            this.userControl12.Direction = MoyStick.cPoint.north;
            this.userControl12.LineColor = System.Drawing.Color.Red;
            this.userControl12.LineShapeEnd = System.Drawing.Drawing2D.LineCap.Flat;
            this.userControl12.LineWidth = 0F;
            this.userControl12.Location = new System.Drawing.Point(766, 377);
            this.userControl12.Magnitude = 0;
            this.userControl12.Name = "userControl12";
            this.userControl12.Size = new System.Drawing.Size(171, 172);
            this.userControl12.TabIndex = 1;
            this.userControl12.Text = "userControl12";
            this.userControl12.MouseLeave += new System.EventHandler(this.userControl12_MouseLeave);
            this.userControl12.MouseStickMoved += new MoyStick.MouseStickMovedEventHandler(this.userControl12_MouseStickMoved);
            this.userControl12.MouseDirectionChanged += new MoyStick.MouseStickMovedEventHandler(this.userControl12_MouseDirectionChanged);
            this.userControl12.MouseEnter += new System.EventHandler(this.userControl12_MouseEnter);
            // 
            // shipTimer
            // 
            this.shipTimer.Enabled = true;
            this.shipTimer.SynchronizingObject = this;
            this.shipTimer.Elapsed += new System.Timers.ElapsedEventHandler(this.shipTimer_Elapsed);
            // 
            // txtPositionX
            // 
            this.txtPositionX.AcceptsReturn = true;
            this.txtPositionX.BackColor = System.Drawing.Color.Black;
            this.txtPositionX.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtPositionX.ForeColor = System.Drawing.Color.Red;
            this.txtPositionX.Location = new System.Drawing.Point(766, 58);
            this.txtPositionX.Name = "txtPositionX";
            this.txtPositionX.Size = new System.Drawing.Size(245, 38);
            this.txtPositionX.TabIndex = 2;
            this.txtPositionX.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // txtPositionY
            // 
            this.txtPositionY.BackColor = System.Drawing.Color.Black;
            this.txtPositionY.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtPositionY.ForeColor = System.Drawing.Color.Red;
            this.txtPositionY.Location = new System.Drawing.Point(766, 102);
            this.txtPositionY.Name = "txtPositionY";
            this.txtPositionY.Size = new System.Drawing.Size(245, 38);
            this.txtPositionY.TabIndex = 3;
            this.txtPositionY.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // txtPositionZ
            // 
            this.txtPositionZ.BackColor = System.Drawing.Color.Black;
            this.txtPositionZ.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtPositionZ.ForeColor = System.Drawing.Color.Red;
            this.txtPositionZ.Location = new System.Drawing.Point(766, 146);
            this.txtPositionZ.Name = "txtPositionZ";
            this.txtPositionZ.Size = new System.Drawing.Size(245, 38);
            this.txtPositionZ.TabIndex = 1;
            this.txtPositionZ.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(961, 340);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(50, 16);
            this.label1.TabIndex = 4;
            this.label1.Text = "Z Axis";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(822, 340);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(64, 16);
            this.label2.TabIndex = 5;
            this.label2.Text = "X Y Axis";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(872, 24);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(48, 20);
            this.label3.TabIndex = 6;
            this.label3.Text = "DRO";
            // 
            // directorySearcher1
            // 
            this.directorySearcher1.ClientTimeout = System.TimeSpan.Parse("-00:00:01");
            this.directorySearcher1.ServerPageTimeLimit = System.TimeSpan.Parse("-00:00:01");
            this.directorySearcher1.ServerTimeLimit = System.TimeSpan.Parse("-00:00:01");
            // 
            // btnUp
            // 
            this.btnUp.Image = ((System.Drawing.Image)(resources.GetObject("btnUp.Image")));
            this.btnUp.Location = new System.Drawing.Point(956, 377);
            this.btnUp.Name = "btnUp";
            this.btnUp.Size = new System.Drawing.Size(55, 77);
            this.btnUp.TabIndex = 7;
            this.btnUp.UseVisualStyleBackColor = true;
            this.btnUp.MouseLeave += new System.EventHandler(this.btnUp_MouseLeave);
            this.btnUp.Click += new System.EventHandler(this.btnUp_Click);
            this.btnUp.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btnUp_MouseDown);
            // 
            // btnDown
            // 
            this.btnDown.Image = ((System.Drawing.Image)(resources.GetObject("btnDown.Image")));
            this.btnDown.Location = new System.Drawing.Point(956, 470);
            this.btnDown.Name = "btnDown";
            this.btnDown.Size = new System.Drawing.Size(55, 79);
            this.btnDown.TabIndex = 8;
            this.btnDown.UseVisualStyleBackColor = true;
            this.btnDown.MouseLeave += new System.EventHandler(this.btnDown_MouseLeave);
            this.btnDown.Click += new System.EventHandler(this.btnDown_Click);
            this.btnDown.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btnDown_MouseDown);
            // 
            // tbEvent
            // 
            this.tbEvent.Location = new System.Drawing.Point(766, 219);
            this.tbEvent.Name = "tbEvent";
            this.tbEvent.Size = new System.Drawing.Size(245, 20);
            this.tbEvent.TabIndex = 9;
            this.tbEvent.Visible = false;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(855, 190);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 10;
            this.button2.Text = "TestCoordMotion";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(936, 190);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 11;
            this.button3.Text = "TestIOCoordMotion";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Location = new System.Drawing.Point(141, 116);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(494, 400);
            this.pictureBox1.TabIndex = 12;
            this.pictureBox1.TabStop = false;
            // 
            // vScrollBar1
            // 
            this.vScrollBar1.Location = new System.Drawing.Point(647, 116);
            this.vScrollBar1.Maximum = 30000;
            this.vScrollBar1.Name = "vScrollBar1";
            this.vScrollBar1.Size = new System.Drawing.Size(17, 400);
            this.vScrollBar1.TabIndex = 2;
            this.vScrollBar1.Scroll += new System.Windows.Forms.ScrollEventHandler(this.vScrollBar1_Scroll);
            // 
            // hScrollBar1
            // 
            this.hScrollBar1.Location = new System.Drawing.Point(141, 532);
            this.hScrollBar1.Maximum = 50000;
            this.hScrollBar1.Name = "hScrollBar1";
            this.hScrollBar1.Size = new System.Drawing.Size(494, 17);
            this.hScrollBar1.TabIndex = 1;
            this.hScrollBar1.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar1_Scroll);
            // 
            // trackBar1
            // 
            this.trackBar1.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.trackBar1.Location = new System.Drawing.Point(141, 58);
            this.trackBar1.Maximum = 20;
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(494, 45);
            this.trackBar1.TabIndex = 1;
            this.trackBar1.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(766, 254);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(245, 23);
            this.button4.TabIndex = 13;
            this.button4.Text = "Path Settings";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.ClientSize = new System.Drawing.Size(1127, 612);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.trackBar1);
            this.Controls.Add(this.hScrollBar1);
            this.Controls.Add(this.vScrollBar1);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.tbEvent);
            this.Controls.Add(this.btnDown);
            this.Controls.Add(this.btnUp);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtPositionZ);
            this.Controls.Add(this.txtPositionY);
            this.Controls.Add(this.txtPositionX);
            this.Controls.Add(this.userControl12);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
            ((System.ComponentModel.ISupportInitialize)(this.shipTimer)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private MoyStick.UserControl1 userControl12;
        private System.Windows.Forms.TextBox txtPositionZ;
        private System.Windows.Forms.TextBox txtPositionY;
        private System.Windows.Forms.TextBox txtPositionX;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.DirectoryServices.DirectorySearcher directorySearcher1;
        private System.Windows.Forms.Button btnUp;
        private System.Windows.Forms.Button btnDown;
        private System.Windows.Forms.TextBox tbEvent;
        private System.Windows.Forms.Timer ZAxisTimer;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.VScrollBar vScrollBar1;
        private System.Windows.Forms.HScrollBar hScrollBar1;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.Button button4;
    }
}

