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
        public byte[] mainFormRecievedFrame;
        public byte[] entireMainFormRecievedFrame;
        private const int TimeoutACKMilliseconds = 10000; // 10 seconds
        public ManualResetEvent dataReceivedEvent = new ManualResetEvent(false);

        public settingCOMForm comSettingsForm;
        public reportForm reportDataForm;
        public cardManagerForm manageCardForm;

        public SerialPort serialPORT { get; }
        public mainDashboard()
        {
            InitializeComponent();
            serialPORT = new SerialPort();
            entireMainFormRecievedFrame = new byte[0];

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
                entireMainFormRecievedFrame = entireMainFormRecievedFrame.Concat(mainFormRecievedFrame).ToArray();
                //for (int i = 0; i < entireMainFormRecievedFrame.Length; i++)
                //{
                //    Console.Write($"{entireMainFormRecievedFrame[i]:X2} "); // Print each byte as a two-digit hexadecimal number
                //}

                //Console.WriteLine();
                //Console.WriteLine("====================");

                dataReceivedEvent.Set();

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
            if (reportDataForm == null || reportDataForm.IsDisposed)
            {
                // Create a new instance if the form is not yet created or has been disposed
                reportDataForm = new reportForm();
            }

            // Show the form as a dialog
            reportDataForm.ShowDialog();

            // Check if the form is disposed (closed by the user)
            if (reportDataForm.IsDisposed)
            {
                // Optionally set the form variable to null if you want to recreate it next time
                reportDataForm = null;

                // Perform any other actions after the form is closed
            }
            else
            {
                // The form is still open, and you can continue using it
            }
        }

        private void dataManagerToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private async void cardManagerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (serialPORT.IsOpen)
            {
                dataReceivedEvent.Reset();
                // Send Request Frame
                this.serialPORT.Write(sRequestFrame, 0, sRequestFrame.Length);

                // Use Task.Run to run the dataReceivedEvent.WaitOne asynchronously
                Task<int> waitResult = Task.Run(() =>
                {
                    // Wait for the dataReceivedHandler to signal that it has completed or until the timeout (8000 milliseconds)
                    int result = WaitHandle.WaitAny(new WaitHandle[] { dataReceivedEvent }, 8000);
                    return result;
                });

                // Create and show a processing form
                processingForm processingDialog = new processingForm(this);
                processingDialog.ShowCentered(this);

                // Wait for either the dataReceivedEvent or the timeout
                int waitResultIndex = await waitResult;

                // Close the processing form
                processingDialog.Close();

                Console.WriteLine("====================");

                for (int i = 0; i < entireMainFormRecievedFrame.Length; i++)
                {
                    Console.Write($"{entireMainFormRecievedFrame[i]:X2} "); // Print each byte as a two-digit hexadecimal number
                }

                Console.WriteLine();
                Console.WriteLine("====================");
                Console.WriteLine("jump here");
                //// Check if ACK frame was received successfully
                //if (waitResultIndex == WaitHandle.WaitTimeout)
                //{
                //    MessageBox.Show(this, "Error: Timeout waiting for ACK.", "Timeout Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                //}
                //else
                //{
                ackReceived = CheckPattern(entireMainFormRecievedFrame, waitACKFrame);

                    // Reset the event for the next round
                    dataReceivedEvent.Reset();

                    // Check if ACK frame was received successfully
                    if (ackReceived)
                    {
                        entireMainFormRecievedFrame = new byte[0];
                        // ACK received, open the cardManagerForm
                        OpenCardManagerForm();
                    }
                    else
                    {
                        MessageBox.Show(this, "Error: ACK not received.", "Unknown Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }

                    // Reset the entire main frame
                    entireMainFormRecievedFrame = new byte[0];

            }
            else
            {
                MessageBox.Show(this, "Error: Serial port is not open.", "Connection", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
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

        public bool WaitForDataReceived(int timeoutMilliseconds)
        {
            // Wait for the event to be signaled or until the timeout expires
            return dataReceivedEvent.WaitOne(timeoutMilliseconds);
        }

    }
}
