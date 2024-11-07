using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ServoApp
{
    public partial class Form1 : Form
    {
        SerialPort serialPort1 = new SerialPort();
        public Form1()
        {
            InitializeComponent();

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //groupBox1.Enabled = false;
        }

        private void combobox_DropDown(object sender, EventArgs e)
        {
            string[] portLists = SerialPort.GetPortNames();
            comboBox.Items.Clear();
            comboBox.Items.AddRange(portLists);
        }

        private void button_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName 
                    = comboBox.Text;
                serialPort1.BaudRate = 9600;
                serialPort1.Open();
                groupBox1.Enabled = true;
                MessageBox.Show("Conectado");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void trackBar_Scroll(object sender, EventArgs e)
        {
            int angle = trackBar.Value;
            label3.Text = angle.ToString(); 
            
            if (serialPort1.IsOpen)
            {
                serialPort1.WriteLine(angle.ToString());
            }
        
        }

        private void comboBox_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
