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
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace projectGUIApp
{
    public partial class cardManagerForm : Form
    {
        private byte[] sFinishFrame = { 0xFF, 0xAA, (byte)'F', 0xAA, 0xFF };
        private const int TimeoutMilliseconds = 5000; // Adjust the timeout as needed
        private SerialPort serialPORT;
        private mainDashboard mainForm;
        public cardManagerForm(mainDashboard mainForm)
        {
            InitializeComponent();
            this.mainForm = mainForm;
            this.serialPORT = mainForm.serialPORT;
            RefreshIDComboBoxes();
        }

        private void RefreshIDComboBoxes()
        {
            cbbRemoveID.Items.Clear();

            foreach (ListViewItem item in listViewCard.Items)
            {
                cbbRemoveID.Items.Add(item.SubItems[2].Text);
            }
        }

        private void RefreshUUIDComboBoxes()
        {
            cbbUpdateUUID.Items.Clear();

            foreach (ListViewItem item in listViewCard.Items)
            {
                cbbUpdateUUID.Items.Add(item.SubItems[0].Text);
            }
        }

        private string ConstructSendAddFrame(char functionalCode, string name, string id)
        {
            // Assuming the format is: 0xFFAA - Action - Name - ID - 0xAAFF
            string sAddFrame = $"0xFFAA{functionalCode}{name}{id}0xAAFF";
            return sAddFrame;
        }

        private string ConstructSendRemoveFrame(char functionalCode, string id)
        {
            // Assuming the format is: 0xFFAA - Action - ID - 0xAAFF
            string sRemoveFrame = $"0xFFAA{functionalCode}{id}0xAAFF";
            return sRemoveFrame;
        }

        private string constructSendUpdateFrame(char functionalCode, string name, string uuid, string id)
        {
            // Assuming the format is: 0xFFAA - Action - Name - ID - 0xAAFF
            string sUpdateFrame = $"0xFFAA{functionalCode}{uuid}{name}{id}0xAAFF";
            return sUpdateFrame;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private async void btnAdd_Click(object sender, EventArgs e)
        {
            try
            {
                // Retrieve user input directly from the TextBoxes
                string name = txtBoxAddName.Text;
                string id = txtBoxAddID.Text;

                // Check for null or empty input for name
                if (string.IsNullOrEmpty(name))
                {
                    // Handle null or empty input for name (e.g., show an error message or set a default value)
                    MessageBox.Show("Please enter a valid name.", "Input Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return; // or throw an exception or handle it according to your application's logic
                }

                // Check for null or empty input for id
                if (string.IsNullOrEmpty(id))
                {
                    // Handle null or empty input for id (e.g., show an error message or set a default value)
                    MessageBox.Show("Please enter a valid ID.", "Input Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return; // or throw an exception or handle it according to your application's logic
                }

                // Construct sFrame and communicate with MCU (similar to previous code)
                string sAddFrame = ConstructSendAddFrame('A', name, id);
                //mainForm.serialPORT.Write(sRequestFrame);

                if (listViewCard.Items.Count == 10)
                {
                    MessageBox.Show("Cannot add more than 10 rows.");
                    return;
                }
                //ListViewItem newItem2 = new ListViewItem(new[] { "23333", name, id });
                //listViewCard.Items.Add(newItem2);

                // Show a waiting dialog
                using (var progressDialog = new processingForm(this))
                {
                    progressDialog.ShowCentered();
                    //progressDialog.StartPosition = FormStartPosition.CenterParent; // Set the dialog to be centered on the parent form
                    var waitTask = WaitForAddACKWithUUIDAsync();
                    //progressDialog.StartPosition = FormStartPosition.CenterParent; // Set the dialog to be centered on the parent form


                    // Show the dialog and wait for the task to complete
                    if (await Task.WhenAny(waitTask, Task.Delay(TimeoutMilliseconds)) == waitTask)
                    {
                        // Task completed within the timeout
                        string uuid = waitTask.Result;

                        // Close the waiting dialog
                        progressDialog.Close();

                        // Process the response and update the UI
                        ListViewItem newItem = new ListViewItem(new[] {uuid, name, id });
                        listViewCard.Items.Add(newItem);
                        //mainForm.serialPORT.Write(sAddFrame);
                        MessageBox.Show(this, "Add Card Successfully.", "Add Card", MessageBoxButtons.OK, MessageBoxIcon.Information);

                    }
                    else
                    {
                        // Timeout occurred
                        progressDialog.Close();
                        MessageBox.Show(this, "Action timed out. Please try again.", "Timeout", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
            catch (Exception ex)
            {
                mainForm.LogMessage("Error communicating with MCU: " + ex.Message, Color.Red);
            }
        }

        private void btnRemove_Click(object sender, EventArgs e)
        {

            // Retrieve user input directly from the TextBoxes
            //string selectedID = cbbRemoveID.SelectedItem?.ToString();

            //if (string.IsNullOrEmpty(selectedID))
            //{
            //    MessageBox.Show("Invalid ID to remove.", "Input Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            //    return;
            //}

            ListViewItem itemToRemove = null;

            //foreach (ListViewItem item in listViewCard.Items)
            //{
            //    if (item.SubItems[2].Text == selectedID)
            //    {
            //        itemToRemove = item;
            //        break;
            //    }
            //}

            //if (itemToRemove != null)
            if (itemToRemove == null)
                {
                //listViewCard.Items.Remove(itemToRemove);
                // Construct sFrame and communicate with MCU (similar to previous code)
                string testID = "2370014";

                // Convert the string to an unsigned integer
                uint idValue = uint.Parse(testID);

                // Convert the unsigned integer to a byte array
                byte[] idBytes = BitConverter.GetBytes(idValue);

                // If your system is little-endian, you might need to reverse the byte order
                if (BitConverter.IsLittleEndian)
                {
                    Array.Reverse(idBytes);
                }

                // Construct the sRemoveFrame byte array
                byte[] sRemoveFrame = new byte[]
                {
                    0xCC, 0xDD, // Start of frame
                    (byte)'D',   // 'D' stands for delete
                    idBytes[0],   // First byte of ID
                    idBytes[1],   // Second byte of ID
                    idBytes[2],   // First byte of ID
                    idBytes[3],   // Second byte of ID
                    0xAA, 0xBB     // End of frame
                };

                for (int i = 0; i < sRemoveFrame.Length; i++)
                {
                    Console.Write($"{sRemoveFrame[i]:X2} "); // Print each byte as a two-digit hexadecimal number
                }
                Console.WriteLine();

                this.serialPORT.Write(sRemoveFrame, 0, sRemoveFrame.Length);
                MessageBox.Show("Item removed successfully.");
            }
            else
            {
                MessageBox.Show("Item not found.");
            }
        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            // Assuming comboBoxUpdateUUID, textBoxNewName, textBoxNewID are the names of your ComboBox and TextBox controls for Update operation
            string selectedUUID = cbbUpdateUUID.SelectedItem?.ToString();
            string newName = txtBoxUpdateName.Text;
            string newID = txtBoxUpdateID.Text;

            // Check for null or empty input for name
            if (string.IsNullOrEmpty(newName))
            {
                // Handle null or empty input for name (e.g., show an error message or set a default value)
                MessageBox.Show("Please enter a valid name.", "Input Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return; // or throw an exception or handle it according to your application's logic
            }

            // Check for null or empty input for id
            if (string.IsNullOrEmpty(newID))
            {
                // Handle null or empty input for id (e.g., show an error message or set a default value)
                MessageBox.Show("Please enter a valid ID.", "Input Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return; // or throw an exception or handle it according to your application's logic
            }

            if (string.IsNullOrEmpty(selectedUUID))
            {
                MessageBox.Show("Invalid UUID to update.", "Input Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                return;
            }

            ListViewItem itemToUpdate = null;

            foreach (ListViewItem item in listViewCard.Items)
            {
                if (item.SubItems[0].Text == selectedUUID)
                {
                    itemToUpdate = item;
                    break;
                }
            }

            if (itemToUpdate != null)
            {
                itemToUpdate.SubItems[1].Text = newName;
                itemToUpdate.SubItems[2].Text = newID;
                string sUpdateFrame = constructSendUpdateFrame('U', newName, selectedUUID, newID);
                //mainForm.serialPORT.Write(sUpdateFrame);
                MessageBox.Show("Item updated successfully.");
            }
            else
            {
                MessageBox.Show("Item not found.");
            }
        }

        private void btnSyncCard_Click(object sender, EventArgs e)
        {

        }

        private Task<string> WaitForAddACKWithUUIDAsync()
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

        private void cbbUpdateUUID_DropDown(object sender, EventArgs e)
        {
            RefreshUUIDComboBoxes();
        }

        private void cbbRemoveID_DropDown(object sender, EventArgs e)
        {
            RefreshIDComboBoxes();
        }

        private void cardManagerForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            // Send Finished Frame
            //mainForm.serialPORT.Write(sFinishFrame, 0, sFinishFrame.Length);

        }
    }
}
