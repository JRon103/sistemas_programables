
using System.IO.Ports;

namespace releArduino
{
    public partial class Form1 : Form
    {

        bool bandera = false;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //SerialPort port = new SerialPort("COM1", 9600, Parity.None, 8, StopBits.One);
            SerialPort port = new SerialPort();
            
            port.PortName = comboBoxList.Text;
            port.BaudRate = 9600;
            try
            {
                port.Open();
                if (!bandera)
                {
                    bandera = true;
                    port.WriteLine("e");
                    btnRele.BackColor = Color.Lime;
                }
                else
                {
                    bandera = false;
                    port.WriteLine("a");
                    btnRele.BackColor = Color.Red;
                }
                port.Close();

            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: " + ex.ToString());
            }

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
                string[] portNames = SerialPort.GetPortNames();     
                foreach (var portName in portNames)
                {
                    comboBoxList.Items.Add(portName);               
                }
                comboBoxList.SelectedIndex = 0;                     
            
        }
    }
}
