using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;
using System.Diagnostics;

namespace projectGUIApp
{
    public partial class mainDashboard : Form
    {
        private byte[] sRequestFrame = { 0xFF, 0xAA, (byte)'R', 0xAA, 0xFF };
        private byte[] waitACKFrame = { 0xFF, 0xAA, (byte)'O', 0xAA, 0xFF };
        private bool ackReceived = false;
        private bool cardManagerIsClicked = false;
        private const int waitTimeoutMilliseconds = 5000;
        public byte[] mainFormRecievedFrame;
        public byte[] entireMainFormRecievedFrame;
        public bool cardFormIsOpen = false;
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
                if(!cardFormIsOpen && !cardManagerIsClicked)
                    this.Invoke(new EventHandler(HandleVerifiedDataReceived));
                else 
                    dataReceivedEvent.Set();

            }
            catch (Exception ex)
            {
                // Handle any exceptions that may occur while processing the data
                this.LogMessage("Error handling received data: " + ex.Message, Color.Red);
            }
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

        private async void cardManagerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            cardManagerIsClicked = true;
            bool requestFlagTimeout = false;
            if (serialPORT.IsOpen)
            {
                dataReceivedEvent.Reset();
                // Send Request Frame
                this.serialPORT.Write(sRequestFrame, 0, sRequestFrame.Length);

                // Create and show a processing form
                processingForm processingDialog = new processingForm(this);
                processingDialog.ShowCentered(this);

                // Record the start time
                DateTime startTime = DateTime.Now;
                do
                {
                    // Use Task.Run to run the dataReceivedEvent.WaitOne asynchronously
                    Task<int> waitResult = Task.Run(() =>
                    {
                        // Wait for the dataReceivedHandler to signal that it has completed or until the timeout (8000 milliseconds)
                        int result = WaitHandle.WaitAny(new WaitHandle[] { this.dataReceivedEvent }, 3000);
                        return result;
                    });

                    // Wait for either the dataReceivedEvent or the timeout
                    await waitResult;

                    this.dataReceivedEvent.Reset();

                    // Calculate elapsed time
                    TimeSpan elapsedTime = DateTime.Now - startTime;

                    // Check if elapsed time exceeds the timeout
                    if (elapsedTime.TotalMilliseconds > waitTimeoutMilliseconds)
                    {
                        requestFlagTimeout = true;
                        // Break out of the loop if the timeout is exceeded
                        break;
                    }

                } while (this.entireMainFormRecievedFrame.Length < 5);
                // Close the processing form
                processingDialog.Close();

                // Close the processing form
                processingDialog.Close();

                Console.WriteLine("====================");

                for (int i = 0; i < entireMainFormRecievedFrame.Length; i++)
                {
                    Console.Write($"{entireMainFormRecievedFrame[i]:X2} "); // Print each byte as a two-digit hexadecimal number
                }

                // Reset the event for the next round
                dataReceivedEvent.Reset();

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
                if (requestFlagTimeout)
                    MessageBox.Show(this, "Error: Timeout, failed to send the GUI request. Please try again.", "Unknown Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                else
                {

                    // Check if ACK frame was received successfully
                    if (ackReceived)
                    {
                        cardManagerIsClicked = false;
                        cardFormIsOpen = true;
                        entireMainFormRecievedFrame = new byte[0];
                        // ACK received, open the cardManagerForm
                        OpenCardManagerForm();
                    }
                    else
                    {
                        cardFormIsOpen = false;
                        cardManagerIsClicked = false;
                        MessageBox.Show(this, "Error: ACK not received.", "Unknown Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }

                    // Reset the entire main frame
                    entireMainFormRecievedFrame = new byte[0];
                }

            }
            else
            {
                cardFormIsOpen = false;
                cardManagerIsClicked = false;
                MessageBox.Show(this, "Error: Serial port is not open.", "Connection", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string message = "This software is designed for a Final Project of AESD" +
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

        private void HandleVerifiedDataReceived(object sender, EventArgs e)
        {
            // Your code to handle the received data goes here
            // This method will be called when data is received without opening card manager form
            ParseVerifiedData(entireMainFormRecievedFrame);
        }

        public void ParseVerifiedData(byte[] rawStream)
        {
            int frameSize = 41; // TODO
            byte[] headerMarker = { 0xFF, 0xAA };
            byte functionalCode = (byte)'V';
            byte[] eofMarker = { 0xAA, 0xFF };
            string id = string.Empty;
            string name = string.Empty;
            List<authorizedDataClass> listData = authorizedDataClass.ListAuthorizedData;

            for (int i = 0; i < rawStream.Length - 2; i++)
            {
                if (rawStream[i] == headerMarker[0] && rawStream[i + 1] == headerMarker[1] &&
                    rawStream[i + 2] == functionalCode)
                {
                    int frameEndIndex = i + frameSize - 1;
                    if (frameEndIndex < rawStream.Length &&
                        rawStream[frameEndIndex - 1] == eofMarker[0] && rawStream[frameEndIndex] == eofMarker[1])
                    {
                        byte[] nameBytes = new byte[32];
                        Array.Copy(rawStream, 7, nameBytes, 0, 32); // Adjust the starting index for the name
                        name = Encoding.ASCII.GetString(nameBytes).TrimEnd('\0'); // Extract and convert Name from ASCII bytes
                        if (string.IsNullOrEmpty(name))
                            return;

                        byte[] idBytes = new byte[4];
                        Array.Copy(rawStream, 3, idBytes, 0, 4); // Adjust the starting index for the ID
                        id = BitConverter.ToUInt32(idBytes, 0).ToString(); // Convert ID from bytes to int
                        if (id == "0")
                            return;

                        entireMainFormRecievedFrame = new byte[0];

                        string inOrOut = CheckInOrOut(name);
                        // Add to List View first
                        ListViewItem newItem = new ListViewItem(new[]
                        {
                            (monitorListView.Items.Count + 1).ToString(),   // No.
                            name,                                           // Name (replace with actual Name)
                            id,                                             // ID (replace with actual ID)
                            inOrOut,                                           // In/Out (replace with actual In/Out status)
                            DateTime.Now.ToString("HH:mm:ss")               // Time (replace with actual time)
                        });

                        // Add the new item to the ListView
                        monitorListView.Items.Add(newItem);

                        // Then, add to authorized data 
                        authorizedDataClass authorizedData = new authorizedDataClass(name, id, inOrOut, DateTime.Now.ToString("HH:mm:ss"));
                        authorizedDataClass.ListAuthorizedData.Add(authorizedData);
                    }
                }
            }
        }

        private string CheckInOrOut(string targetName)
        {
            int count = 0;

            foreach (ListViewItem item in monitorListView.Items)
            {
                // Assuming that "Name" is the second column (index 1)
                string itemName = item.SubItems[1].Text;

                // Compare the name and increment count if it matches the target name
                if (itemName.Equals(targetName, StringComparison.OrdinalIgnoreCase))
                {
                    count++;
                }
            }

            // Check count
            if ((count % 2) == 0)
            {
                return "In";
            }
            else
                return "Out";

        }

        private void operationManualToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string url = "https://github.com/trieu1162000/AESD";

            // Open the link in the default web browser
            Process.Start(url);
        }
    }
}
