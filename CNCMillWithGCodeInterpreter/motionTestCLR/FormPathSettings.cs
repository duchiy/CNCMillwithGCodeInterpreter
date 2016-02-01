using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace motionTestCLR
{

    public partial class FormPathSettings : Form
    {
        private PathSettings _PathSet = new PathSettings();
        public PathSettings PathSet
        {
            get { return _PathSet; }
            set { _PathSet = value; }
        }
        public FormPathSettings()
        {
            InitializeComponent();
            textBox1.Text = _PathSet.Frequency.ToString();
            textBox2.Text = _PathSet.NumberOfPts.ToString();
            textBox3.Text = _PathSet.Xscale.ToString();
            textBox4.Text = _PathSet.Yscale.ToString();
            textBox5.Text = _PathSet.Zscale.ToString();
            textBox6.Text = _PathSet.Acceleration.ToString();
            textBox7.Text = _PathSet.Tolerance.ToString();
            textBox8.Text = _PathSet.Xorigin.ToString();
            textBox9.Text = _PathSet.Yorigin.ToString();
            textBox10.Text = _PathSet.Zorigin.ToString();
            textBox11.Text = _PathSet.Feedrate.ToString();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            _PathSet.Frequency = Convert.ToInt32(textBox1.Text);
            _PathSet.NumberOfPts = Convert.ToInt32(textBox2.Text);
            _PathSet.Xscale = Convert.ToDouble(textBox3.Text);
            _PathSet.Yscale = Convert.ToDouble(textBox4.Text);
            _PathSet.Zscale = Convert.ToDouble(textBox5.Text);
            _PathSet.Acceleration = Convert.ToDouble(textBox6.Text);
            _PathSet.Tolerance = Convert.ToDouble(textBox7.Text);
            _PathSet.Xorigin = Convert.ToDouble(textBox8.Text);
            _PathSet.Yorigin = Convert.ToDouble(textBox9.Text);
            _PathSet.Zorigin = Convert.ToDouble(textBox10.Text);
            _PathSet.Feedrate = Convert.ToDouble(textBox11.Text);

            this.Close();
        }
    }
}
