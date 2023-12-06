using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace projectGUIApp
{
    public partial class settingCOMForm : Form
    {
        public static bool btnConnClicked = false;

        private mainDashboard mainForm;

        public SerialPort serialPORT;

        public settingCOMForm(mainDashboard mainForm)
        {
            InitializeComponent();
            this.mainForm = mainForm;
            this.serialPORT = mainForm.serialPORT;

        }

        private void settingCOMFormLoad(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            cbbCOMPort.Items.AddRange(ports);
            if (serialPORT.IsOpen)
            {
                btnConnect.Text = "Disconnect";
                btnConnect.ImageIndex = 1;
                btnConnect.ForeColor = Color.Brown;
                btnConnect.Image = new Bitmap(projectGUIApp.Properties.Resources.icon_disconnect);
                btnReScan.Enabled = false;
            }
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (btnConnect.Text == "Connect")
            {
                btnConnect.Text = "Disconnect";
                btnConnect.ImageIndex = 1;
                btnConnect.ForeColor = Color.Brown;
                btnConnect.Image = new Bitmap(projectGUIApp.Properties.Resources.icon_disconnect);
                btnReScan.Enabled = false;

                // TODO: Disable other fields
                try
                {
                    serialPORT.PortName = cbbCOMPort.Text;
                    serialPORT.BaudRate = Convert.ToInt32(cbbBaudRate.Text);
                    serialPORT.DataBits = Convert.ToInt32(cbbDataBits.Text);
                    serialPORT.StopBits = (StopBits)Enum.Parse(typeof(StopBits), cbbStopBits.Text);
                    serialPORT.Parity = (Parity)Enum.Parse(typeof(Parity), cbbParity.Text);

                    serialPORT.Open();
                    btnConnClicked = true;
                    mainForm.LogMessage(serialPORT.PortName.ToString() + " is connected", Color.MediumBlue);
                    serialPORT.DataReceived += new SerialDataReceivedEventHandler(mainForm.serialDataReceivedHandler); // Subscribe to the event

                }
                catch (Exception error)
                {
                    MessageBox.Show(error.Message, "Connection Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    btnConnect.Text = "Connect";
                    btnConnect.ImageIndex = 0;
                    btnConnect.ForeColor = Color.MediumBlue;
                    btnReScan.Enabled = true;

                    btnConnClicked = false;
                    mainForm.LogMessage( "Connection Error!", Color.Red);
                    //Display.UpdateComStatus("status", 0, "Access to the port " + serialPORT.PortName + " is denied",
                    //System.Drawing.Color.Red);
                }
            }
            else
            {
                string mess = "This action will stop connecting to the system\nMake sure the system is working normally.\nDo you really want to Disconnect ?";
                DialogResult result = MessageBox.Show(mess, "Warning", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning);
                if (result == System.Windows.Forms.DialogResult.OK)
                {
                    btnConnect.Text = "Connect";
                    btnConnect.ImageIndex = 0;
                    btnConnect.ForeColor = Color.MediumBlue;
                    btnConnect.Image = new Bitmap(projectGUIApp.Properties.Resources.icon_connect);
                    btnReScan.Enabled = true;

                    serialPORT.Close();
                    btnConnClicked = false;
                    mainForm.LogMessage(serialPORT.PortName.ToString() + " is disconnected", Color.Red);

                    //Display.UpdateComStatus("status", 0, serialPORT.PortName + " is closed", System.Drawing.Color.Red);
                    // TODO: Enable other fields
                }
            }


        }

        private void btnReScan_Click(object sender, EventArgs e)
        {
            // fix multiple adding
            cbbCOMPort.Items.Clear();

            string[] ports = SerialPort.GetPortNames();
            cbbCOMPort.Items.AddRange(ports);
        }

        private void cbbCOMPort_DropDown(object sender, EventArgs e)
        {
            // fix multiple adding
            cbbCOMPort.Items.Clear();

            string[] ports = SerialPort.GetPortNames();
            cbbCOMPort.Items.AddRange(ports);
        }
    }
}
