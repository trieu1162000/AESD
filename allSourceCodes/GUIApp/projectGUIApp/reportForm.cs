using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
//using MSWord = Microsoft.

namespace projectGUIApp
{
    public partial class reportForm : Form
    {
        public reportForm()
        {
            InitializeComponent();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void rtxbTemplate_TextChanged(object sender, EventArgs e)
        {

        }

        private void txbPhoneNumber_TextChanged(object sender, EventArgs e)
        {

        }

        private void txbName_TextChanged(object sender, EventArgs e)
        {

        }

        private void txbTemplatePath_TextChanged(object sender, EventArgs e)
        {

        }

        private void btnPreview_Click(object sender, EventArgs e)
        {

        }

        private void btnLoadTemplate_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void loadTemplateDialog_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void saveReportDialog_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void txbEmail_TextChanged(object sender, EventArgs e)
        {

        }

        private void btnSaveAs_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(txbName.Text) ||
                String.IsNullOrEmpty(txbPhoneNumber.Text) ||
                String.IsNullOrEmpty(txbTemplatePath.Text))
            {
                MessageBox.Show("Do not enough information to save the report", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            saveReportDialog.Filter = "DOCX files (*.docx, *.dotx, *.docm, *.dotm)|*.docx;*.dotx;*.docm;*.dotm" +
                                        "|DOC files (*.doc, *.dot)|*.doc;*.dot";
            if (saveReportDialog.ShowDialog() == DialogResult.OK)
            {
                ///CreateWordDocument(txbTemplatePath.Text, saveReportDialog.FileName);
            }
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
    }
}
