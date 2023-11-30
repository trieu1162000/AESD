using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;
using System.IO.Ports;

namespace projectGUIApp
{
    public partial class cardManagerForm : Form
    {
        private const int TimeoutMilliseconds = 5000; // Adjust the timeout as needed
        private SerialPort serialPORT;
        private mainDashboard mainForm;
        public cardManagerForm(mainDashboard mainForm)
        {
            InitializeComponent();
            this.mainForm = mainForm;
            this.serialPORT = mainForm.serialPORT;
        }

        private void btnAddCard_Click(object sender, EventArgs e)
        {
            try
            {
                // Assuming you have TextBoxes for Name, ID, etc.
                //string name = txtName.Text;
                //string id = txtID.Text;

                // Construct sFrame (assuming you have a method for this)
                //string sFrame = constructSFrame('A', name, id);

                // Send sFrame to MCU through serial port
                //mainForm.serialPORT.Write(sFrame);

                // Handle the response from MCU
                //string response = mainForm.serialPORT.ReadLine();

                // Process the response (assuming you have a method for this)
                //ProcessResponse(response);

                // Update UI or perform other actions based on the response
            }
            catch (Exception ex)
            {
                // Handle exceptions that may occur during the communication
                //mainForm.LogMessage("Error communicating with MCU: " + ex.Message, Color.Red);
            }
        }
        private string constructSendAddFrame(char action, string name, string id)
        {
            // Assuming the format is: 0xFFAA - Action - Name - ID - 0xAAFF
            string sFrame = $"0xFFAA{action}{name}{id}0xAAFF";
            return sFrame;
        }

        private void btnRemoveCard_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void btnOK_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private async void btnAdd_Click(object sender, EventArgs e)
        {
            try
            {
                // Retrieve user input directly from the TextBoxes
                string name = txtBoxAddName.Text;
                string id = txtBoxAddID.Text;

                // Construct sFrame and communicate with MCU (similar to previous code)
                string sFrame = constructSendAddFrame('A', name, id);
                //mainForm.serialPORT.Write(sFrame);

                // Show a waiting dialog
                using (var progressDialog = new processingForm(this))
                {
                    progressDialog.StartPosition = FormStartPosition.CenterParent; // Set the dialog to be centered on the parent form
                    var waitTask = WaitForAckWithUUIDAsync();
                    progressDialog.Show(this);

                    // Show the dialog and wait for the task to complete
                    if (await Task.WhenAny(waitTask, Task.Delay(TimeoutMilliseconds)) == waitTask)
                    {
                        // Task completed within the timeout
                        string response = waitTask.Result;

                        // Close the waiting dialog
                        progressDialog.Close();

                        // Process the response and update the UI
                        ProcessResponseAndUpdateUI(response);
                    }
                    else
                    {
                        // Timeout occurred
                        progressDialog.Close();
                        MessageBox.Show("Action timed out. Please try again.", "Timeout", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
            catch (Exception ex)
            {
                mainForm.LogMessage("Error communicating with MCU: " + ex.Message, Color.Red);
            }
        }

        private Task<string> WaitForAckWithUUIDAsync()
        {
            var tcs = new TaskCompletionSource<string>();

            // Subscribe to DataReceived event to listen for incoming data
            SerialDataReceivedEventHandler dataReceivedHandler = null;
            dataReceivedHandler = (sender, e) =>
            {
                try
                {
                    string response = mainForm.serialPORT.ReadLine();

                    // Check if the received data is the expected ACK with UUID
                    if (response.StartsWith("0xFFAA") && response.EndsWith("0xAAFF"))
                    {
                        // Extract UUID from the response
                        string uuid = response.Substring(7, response.Length - 13);

                        // Set the result of the task
                        tcs.SetResult(uuid);
                    }
                    else
                    {
                        // Handle unexpected responses or errors
                        tcs.SetException(new Exception("Unexpected response from MCU."));
                    }

                    // Unsubscribe from the event to avoid further processing
                    mainForm.serialPORT.DataReceived -= dataReceivedHandler;
                }
                catch (Exception ex)
                {
                    // Set the exception if an error occurs
                    tcs.SetException(ex);
                }
            };

            // Subscribe to DataReceived event
            mainForm.serialPORT.DataReceived += dataReceivedHandler;

            // Return the task that will be completed when the ACK with UUID is received
            return tcs.Task;
        }
        private void ProcessResponseAndUpdateUI(string uuid)
        {
            // Update the UI or perform other actions based on the received UUID
            // For example, update the ListView with the Order, UUID, Name, and ID columns
            ListViewItem item = new ListViewItem(new[] { "1", uuid, txtBoxAddName.Text, txtBoxAddID.Text });
            listViewCard.Items.Add(item);
        }

    }
}
