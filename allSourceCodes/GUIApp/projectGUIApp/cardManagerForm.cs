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

namespace projectGUIApp
{
    public partial class cardManagerForm : Form
    {
        private mainDashboard mainForm;
        public cardManagerForm(mainDashboard mainForm)
        {
            InitializeComponent();
            this.mainForm = mainForm;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

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
        private string constructSFrame(char action, string name, string id)
        {
            // Assuming the format is: 0xFFAA - Action - Name - ID - 0xAAFF
            string sFrame = $"0xFFAA{action}{name}{id}0xAAFF";
            return sFrame;
        }
    }
}
