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
using System.Drawing;

namespace projectGUIApp
{
    public partial class mainDashboard : Form
    {
        public settingCOMForm comSettingsForm;
        public SerialPort serialPORT { get; }
        public mainDashboard()
        {
            InitializeComponent();
            serialPORT = new SerialPort();
        }

        // Method for receiving log messages from SettingCOMForm
        public void LogMessage(string message, Color color)
        {
            rtxtbComStatus.SelectionColor = color;
            rtxtbComStatus.AppendText(message + Environment.NewLine);
        }
        private void listViewTask_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void editCardToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void communicationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (comSettingsForm == null || comSettingsForm.IsDisposed)
            {
                // Create a new instance if the form is not yet created or has been disposed
                comSettingsForm = new settingCOMForm(this);
            }

            // Show the form as a dialog
            comSettingsForm.ShowDialog();

            // Check if the form is disposed (closed by the user)
            if (comSettingsForm.IsDisposed)
            {
                // Optionally set the form variable to null if you want to recreate it next time
                comSettingsForm = null;

                // Perform any other actions after the form is closed
            }
            else
            {
                // The form is still open, and you can continue using it
            }

        }

        public void serialDataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            // Handle the received data here
            try
            {
                string data = serialPORT.ReadExisting();
                // You can process the received data as needed
                // For example, update UI elements or perform some action
                //mainForm.HandleReceivedData(data);
            }
            catch (Exception ex)
            {
                // Handle any exceptions that may occur while processing the data
                //mainForm.LogMessage("Error handling received data: " + ex.Message, Color.Red);
            }
        }

        private void newCardToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void deleteCardToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void reportToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void dataManagerToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void cardManagerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // TODO: Change this accordingly
            if (comSettingsForm == null || comSettingsForm.IsDisposed)
            {
                // Create a new instance if the form is not yet created or has been disposed
                comSettingsForm = new settingCOMForm(this);
            }

            // Show the form as a dialog
            comSettingsForm.ShowDialog();

            // Check if the form is disposed (closed by the user)
            if (comSettingsForm.IsDisposed)
            {
                // Optionally set the form variable to null if you want to recreate it next time
                comSettingsForm = null;

                // Perform any other actions after the form is closed
            }
            else
            {
                // The form is still open, and you can continue using it
            }
        }
    }
}
