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
            this.Close();
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

                if (listViewCard.Items.Count == 10)
                {
                    MessageBox.Show("Cannot add more than 10 rows.");
                    return;
                }

                ListViewItem newItem = new ListViewItem(new[] { "23333", name, id });
                listViewCard .Items.Add(newItem);

                MessageBox.Show("Item added successfully.");

                // Show a waiting dialog
                // using (var progressDialog = new processingForm(this))
                // {
                // progressDialog.ShowCentered();
                // //progressDialog.StartPosition = FormStartPosition.CenterParent; // Set the dialog to be centered on the parent form
                // var waitTask = WaitForAckWithUUIDAsync();
                // //progressDialog.StartPosition = FormStartPosition.CenterParent; // Set the dialog to be centered on the parent form


                // // Show the dialog and wait for the task to complete
                // if (await Task.WhenAny(waitTask, Task.Delay(TimeoutMilliseconds)) == waitTask)
                // {
                // // Task completed within the timeout
                // string response = waitTask.Result;

                // // Close the waiting dialog
                // progressDialog.Close();

                // // Process the response and update the UI
                // ProcessResponseAndUpdateUI(response);

                // MessageBox.Show(this, "Add Card Successfully. Please try again.", "Add Card", MessageBoxButtons.OK, MessageBoxIcon.Information);

                // }
                // else
                // {
                // // Timeout occurred
                // progressDialog.Close();
                // MessageBox.Show(this, "Action timed out. Please try again.", "Timeout", MessageBoxButtons.OK, MessageBoxIcon.Error);
                // }
                // }
            }
            catch (Exception ex)
            {
                mainForm.LogMessage("Error communicating with MCU: " + ex.Message, Color.Red);
            }
        }

        private void ProcessResponseAndUpdateUI(string uuid)
        {
            // Update the UI or perform other actions based on the received UUID
            // For example, update the ListView with the Order, UUID, Name, and ID columns
            ListViewItem item = new ListViewItem(new[] { "1", uuid, txtBoxAddName.Text, txtBoxAddID.Text });
            listViewCard.Items.Add(item);
        }

        private void btnUpdateCard_Click(object sender, EventArgs e)
        {
            // Assuming comboBoxUpdateUUID, textBoxNewName, textBoxNewID are the names of your ComboBox and TextBox controls for Update operation
            string selectedUUID = cbbUpdateUUID.SelectedItem?.ToString();
            string newName = txtBoxUpdateName.Text;
            string newID = txtBoxUpdateID.Text;

            if (string.IsNullOrEmpty(selectedUUID))
            {
                MessageBox.Show("Please select a UUID to update.");
                return;
            }

            ListViewItem itemToUpdate = null;

            foreach (ListViewItem item in listViewCard.Items)
            {
                if (item.SubItems["UUID"].Text == selectedUUID)
                {
                    itemToUpdate = item;
                    break;
                }
            }

            if (itemToUpdate != null)
            {
                itemToUpdate.SubItems["Name"].Text = newName;
                itemToUpdate.SubItems["ID"].Text = newID;

                MessageBox.Show("Item updated successfully.");
            }
            else
            {
                MessageBox.Show("Item not found.");
            }
        }

        private void cbbUpdateUUID_DropDown(object sender, EventArgs e)
        {
            RefreshUUIDComboBoxes();
        }

        private void cbbRemoveID_DropDown(object sender, EventArgs e)
        {
            RefreshIDComboBoxes();
        }


        private void btnRemove_Click(object sender, EventArgs e)
        {            // Assuming comboBoxRemoveID is the name of your ComboBox control for Remove operation
            string selectedID = cbbRemoveID.SelectedItem?.ToString();

            if (string.IsNullOrEmpty(selectedID))
            {
                MessageBox.Show("Please select an ID to remove.");
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

            if (string.IsNullOrEmpty(selectedUUID))
            {
                MessageBox.Show("Please select a UUID to update.");
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

                MessageBox.Show("Item updated successfully.");
            }
            else
            {
                MessageBox.Show("Item not found.");
            }
        }
    }
}
