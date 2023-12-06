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
using System.Threading;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace projectGUIApp
{
    public partial class cardManagerForm : Form
    {
        private byte[] rSyncFrame;
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

        private byte[] constructSendAddFrame(char functionalCode, string name, string id)
        {
            // Assuming functionalCode is a single character

            // Convert functionalCode to byte
            byte functionalCodeByte = (byte)functionalCode;

            // Convert name, uuid, and id to byte arrays with fixed lengths
            byte[] nameBytes = Encoding.ASCII.GetBytes(name.PadRight(32, '\0')).Take(32).ToArray();

            // Convert id string to an integer
            int idInt = int.Parse(id);

            // Convert the integer id to 4 bytes
            byte[] idBytes = BitConverter.GetBytes(idInt);

            // Create a List<byte> to store the frame bytes
            List<byte> frameBytes = new List<byte>();

            // Add fixed header
            frameBytes.AddRange(new byte[] {0xFF, 0xAA});

            // Add functional code, uuid, name, and id
            frameBytes.AddRange(new byte[] { functionalCodeByte });
            frameBytes.AddRange(nameBytes);
            frameBytes.AddRange(idBytes);

            // Add fixed footer
            frameBytes.AddRange(new byte[] {0xAA, 0xFF});

            return frameBytes.ToArray();

        }

        private byte[] constructSendUpdateFrame(char functionalCode, string name, string uuid, string id)
        {
            // Assuming functionalCode is a single character

            // Convert functionalCode to byte
            byte functionalCodeByte = (byte) functionalCode;

            // Convert name, uuid, and id to byte arrays with fixed lengths
            byte[] nameBytes = Encoding.ASCII.GetBytes(name.PadRight(32, '\0')).Take(32).ToArray();

            // Convert uuid hex string to bytes
            byte[] uuidBytes = Enumerable.Range(0, uuid.Length / 2)
                                         .Select(i => Convert.ToByte(uuid.Substring(i * 2, 2), 16))
                                         .ToArray();

            // Convert id string to an integer
            int idInt = int.Parse(id);

            // Convert the integer id to 4 bytes
            byte[] idBytes = BitConverter.GetBytes(idInt);

            // Create a List<byte> to store the frame bytes
            List<byte> frameBytes = new List<byte>();

            // Add fixed header
            frameBytes.AddRange(new byte[] {0xFF, 0xAA});

            // Add functional code, uuid, name, and id
            frameBytes.AddRange(new byte[] {functionalCodeByte});
            frameBytes.AddRange(uuidBytes);
            frameBytes.AddRange(nameBytes);
            frameBytes.AddRange(idBytes);

            // Add fixed footer
            frameBytes.AddRange(new byte[] {0xAA, 0xFF});

            return frameBytes.ToArray();

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
                byte[] sAddFrame = constructSendAddFrame('A', name, id);
                mainForm.serialPORT.Write(sAddFrame, 0, sAddFrame.Length);

                if (listViewCard.Items.Count == 10)
                {
                    MessageBox.Show("Cannot add more than 10 rows.");
                    return;
                }


                // Use Task.Run to run the dataReceivedEvent.WaitOne asynchronously
                Task<int> waitResult = Task.Run(() =>
                {
                    // Wait for the dataReceivedHandler to signal that it has completed or until the timeout (8000 milliseconds)
                    int result = WaitHandle.WaitAny(new WaitHandle[] { mainForm.dataReceivedEvent }, 5000);
                    return result;
                });

                // Create and show a processing form
                processingForm processingDialog = new processingForm(this);
                processingDialog.ShowCentered(this);

                // Wait for either the dataReceivedEvent or the timeout
                await waitResult;

                // Close the processing form
                processingDialog.Close();
                for (int i = 0; i < mainForm.entireMainFormRecievedFrame.Length; i++)
                {
                    Console.Write($"{mainForm.entireMainFormRecievedFrame[i]:X2} "); // Print each byte as a two-digit hexadecimal number
                }

                Console.WriteLine();
                Console.WriteLine("====================");

                mainForm.dataReceivedEvent.Reset();
                AddAddDataToListView("23456", name, id);
                //AddAddDataToListView(AddParseRawStream(mainForm.entireMainFormRecievedFrame), name, id);
                MessageBox.Show("Add successfully.");
                mainForm.entireMainFormRecievedFrame = new byte[0];

            }
            catch (Exception ex)
            {
                mainForm.LogMessage("Error communicating with MCU: " + ex.Message, Color.Red);
            }
        }

        private void btnRemove_Click(object sender, EventArgs e)
        {

            // Retrieve user input directly from the TextBoxes
            string selectedID = cbbRemoveID.SelectedItem?.ToString();

            if (string.IsNullOrEmpty(selectedID))
            {
                MessageBox.Show("Invalid ID to remove.", "Input Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            ListViewItem itemToRemove = null;

            foreach (ListViewItem item in listViewCard.Items)
            {
                if (item.SubItems[2].Text == selectedID)
                {
                    itemToRemove = item;
                    break;
                }
            }

            if (itemToRemove != null)
            {
                listViewCard.Items.Remove(itemToRemove);

                // Convert the string to an unsigned integer
                uint idValue = uint.Parse(selectedID);

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
                    0xFF, 0xAA, // Start of frame
                    (byte)'D',   // 'D' stands for delete
                    idBytes[0],   // First byte of ID
                    idBytes[1],   // Second byte of ID
                    idBytes[2],   // First byte of ID
                    idBytes[3],   // Second byte of ID
                    0xAA, 0xFF     // End of frame
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
                byte[] sUpdateFrame = constructSendUpdateFrame('U', newName, selectedUUID, newID);
                mainForm.serialPORT.Write(sUpdateFrame, 0, sUpdateFrame.Length);
                MessageBox.Show("Item updated successfully.");
            }
            else
            {
                MessageBox.Show("Item not found.");
            }
        }

        private async void btnSyncCard_Click(object sender, EventArgs e)
        {
            // Construct the sRemoveFrame byte array
            byte[] sSyncFrame = new byte[]
            {
                    0xFF, 0xAA, // Start of frame
                    (byte)'S',   // 'S' stands for synchronize
                    0xAA, 0xFF     // End of frame
            };
            mainForm.dataReceivedEvent.Reset();
            this.serialPORT.Write(sSyncFrame, 0, sSyncFrame.Length);
            //mainForm.dataReceivedEvent.WaitOne();
            //Console.WriteLine("Jump here");

            // Use Task.Run to run the dataReceivedEvent.WaitOne asynchronously
            Task<int> waitResult = Task.Run(() =>
            {
                // Wait for the dataReceivedHandler to signal that it has completed or until the timeout (8000 milliseconds)
                int result = WaitHandle.WaitAny(new WaitHandle[] { mainForm.dataReceivedEvent }, 5000);
                return result;
            });

            // Create and show a processing form
            processingForm processingDialog = new processingForm(this);
            processingDialog.ShowCentered(this);

            // Wait for either the dataReceivedEvent or the timeout
            await waitResult;

            // Close the processing form
            processingDialog.Close();
            //{
            //    //Console.WriteLine("Jump here");
            //    mainForm.dataReceivedEvent.Reset();
            //}
            //System.Threading.Thread.Sleep(5000);
            mainForm.dataReceivedEvent.Reset();

            SyncAddDataToListView(SyncParseRawStream(mainForm.entireMainFormRecievedFrame));
            MessageBox.Show("Synchronize successfully.");
            mainForm.entireMainFormRecievedFrame = new byte[0];
            //mainForm.dataReceivedEvent.Reset();


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
            mainForm.serialPORT.Write(sFinishFrame, 0, sFinishFrame.Length);

        }

        public List<frameClass> SyncParseRawStream(byte[] rawStream)
        {
            List<frameClass> frames = new List<frameClass>();
            int frameSize = 46; // Size of each frame in bytes
            byte[] headerMarker = { 0xFF, 0xAA };
            byte functionalCode = (byte)'S';
            byte[] eofMarker = { 0xAA, 0xFF };

            for (int i = 0; i < rawStream.Length - frameSize + 1; i++)
            {
                if (rawStream[i] == headerMarker[0] && rawStream[i + 1] == headerMarker[1] &&
                    rawStream[i + 2] == functionalCode)
                {
                    int frameEndIndex = i + frameSize; // Add 4 for the length of the EOF marker
                    if (frameEndIndex <= rawStream.Length &&
                        rawStream[frameEndIndex - 2] == eofMarker[0] && rawStream[frameEndIndex - 1] == eofMarker[1])
                    {
                        byte[] frameBytes = new byte[frameSize];
                        Array.Copy(rawStream, i, frameBytes, 0, frameSize);
                        frameClass frame = ParseFrame(frameBytes);
                        frames.Add(frame);
                        i = frameEndIndex - 1; // Move to the next potential frame
                    }
                }
            }

            return frames;
        }

        public string AddParseRawStream(byte[] rawStream)
        {
            int frameSize = 10; // Size of each frame in bytes
            byte[] headerMarker = { 0xFF, 0xAA };
            byte functionalCode = (byte)'A';
            byte[] eofMarker = { 0xAA, 0xFF };
            byte[] uuidBytes = new byte[5];
            string uuidString = string.Empty;

            for (int i = 0; i < rawStream.Length; i++)
            { 
                if (rawStream[i] == headerMarker[0] && rawStream[i + 1] == headerMarker[1] &&
                    rawStream[i + 2] == functionalCode)
                {
                    int frameEndIndex = i + frameSize - 1;
                    if (frameEndIndex < rawStream.Length &&
                        rawStream[frameEndIndex - 1] == eofMarker[0] && rawStream[frameEndIndex] == eofMarker[1])
                    {
                        Array.Copy(rawStream, i+3, uuidBytes, 0, 5);
                        uuidString = BitConverter.ToString(uuidBytes).Replace("-", ""); // Extract UUID
                    }
                }
            }

            return uuidString;
        }

        private frameClass ParseFrame(byte[] frameBytes)
        {
            frameClass frame = new frameClass();

            byte[] uuidBytes = new byte[5];
            Array.Copy(frameBytes, 39, uuidBytes, 0, 5);
            frame.UUID = BitConverter.ToString(uuidBytes).Replace("-", ""); // Extract UUID

            byte[] nameBytes = new byte[32];
            Array.Copy(frameBytes, 7, nameBytes, 0, 32); // Adjust the starting index for the name
            frame.Name = Encoding.ASCII.GetString(nameBytes).TrimEnd('\0'); // Extract and convert Name from ASCII bytes

            byte[] idBytes = new byte[4];
            Array.Copy(frameBytes, 3, idBytes, 0, 4); // Adjust the starting index for the ID
            frame.ID = BitConverter.ToInt32(idBytes, 0); // Convert ID from bytes to int

            return frame;
        }

        private void SyncAddDataToListView(List<frameClass> frames)
        {
            listViewCard.Items.Clear();

            foreach (var frame in frames)
            {
                ListViewItem item = new ListViewItem(frame.UUID);
                item.SubItems.Add(frame.Name);
                item.SubItems.Add(frame.ID.ToString());
                listViewCard.Items.Add(item);
            }
        }

        private void AddAddDataToListView(string uuid, string name, string id)
        {
            ListViewItem item = new ListViewItem(uuid);
            item.SubItems.Add(name);
            item.SubItems.Add(id);
            listViewCard.Items.Add(item);
        }

    }
}
