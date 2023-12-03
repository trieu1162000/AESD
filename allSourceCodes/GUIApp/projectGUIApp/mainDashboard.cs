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
using System.Threading;

namespace projectGUIApp
{
    public partial class mainDashboard : Form
    {
        private byte[] sRequestFrame = { 0xFF, 0xAA, (byte)'R', 0xAA, 0xFF };
        private byte[] waitACKFrame = { 0xFF, 0xAA, (byte)'O', 0xAA, 0xFF };
        private bool ackReceived = false;
        private byte[] mainFormRecievedFrame;
        private ManualResetEvent dataReceivedEvent = new ManualResetEvent(false);

        public settingCOMForm comSettingsForm;

        public cardManagerForm manageCardForm;

        public SerialPort serialPORT { get; }
        public mainDashboard()
        {
            InitializeComponent();
            serialPORT = new SerialPort();
        }

        private void OpenCardManagerForm()
        {
            if (manageCardForm == null || manageCardForm.IsDisposed)
            {
                manageCardForm = new cardManagerForm(this);
            }

            manageCardForm.ShowDialog();

            if (manageCardForm.IsDisposed)
            {
                manageCardForm = null;
            }
            // Additional actions after the form is closed
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
                int bytesToRead = serialPORT.BytesToRead;
                mainFormRecievedFrame = new byte[bytesToRead];
                int bytesRead = serialPORT.Read(mainFormRecievedFrame, 0, bytesToRead);

                for (int i = 0; i < bytesRead; i++)
                {
                    Console.Write($"{mainFormRecievedFrame[i]:X2} "); // Print each byte as a two-digit hexadecimal number
                }

                Console.WriteLine();
                dataReceivedEvent.Set();
                // You can process the received data as needed
                // For example, update UI elements or perform some action
                //mainForm.HandleReceivedData(data);
            }
            catch (Exception ex)
            {
                // Handle any exceptions that may occur while processing the data
                this.LogMessage("Error handling received data: " + ex.Message, Color.Red);
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
            if (serialPORT.IsOpen)
            {
                // Send Request Frame
                this.serialPORT.Write(sRequestFrame, 0, sRequestFrame.Length);

                // Wait for the dataReceivedHandler to signal that it has completed
                dataReceivedEvent.WaitOne();

                ackReceived = CheckPattern(mainFormRecievedFrame, waitACKFrame);

                // Reset the event for the next round
                dataReceivedEvent.Reset();

                // Check if ACK frame was received successfully
                if (ackReceived)
                {
                    // ACK received, open the cardManagerForm
                    OpenCardManagerForm();
                }
                else
                {
                    // Timeout or error handling
                    MessageBox.Show(this, "Error: ACK not received.", "Unknow Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
                MessageBox.Show(this, "Error: Serial port is not open.", "Connection", MessageBoxButtons.OK, MessageBoxIcon.Error);

        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string message = "This software is designed for a Final Project:" +
                 "\nMonitoring & Controlling of Access Control System (ACS) using RFID." +
                 "\nAt Ho Chi Minh City University of Technology (HCMUT)." +
                 "\n\nDesigned by Group 6.";
            MessageBox.Show(message, "About this software", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        // Function to check if the pattern exists in the buffer
        private bool CheckPattern(byte[] buffer, byte[] pattern)
        {
            if (buffer.Length < pattern.Length)
            {
                return false;
            }

            for (int i = 0; i <= buffer.Length - pattern.Length; i++)
            {
                bool isMatch = true;

                for (int j = 0; j < pattern.Length; j++)
                {
                    if (buffer[i + j] != pattern[j])
                    {
                        isMatch = false;
                        break;
                    }
                }

                if (isMatch)
                {
                    return true;
                }
            }

            return false;
        }
    }
}
