using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MSWord = Microsoft.Office.Interop.Word;

namespace projectGUIApp
{
    public partial class reportForm : Form
    {
        public reportForm()
        {
            InitializeComponent();
        }

        private void FindAndReplace(MSWord.Application wordApp, object findText, object replaceWithText)
        {
            object matchCase = true;
            object matchWholeWord = true;
            object matchWildCards = false;
            object matchSoundLike = false;
            object nmatchAllForms = false;
            object forward = true;
            object format = false;
            object matchKashida = false;
            object matchDiactitics = false;
            object matchAlefHamza = false;
            object matchControl = false;
            object read_only = false;
            object visible = true;
            object replace = 2;
            object wrap = 1;

            wordApp.Selection.Find.Execute(ref findText,
                                           ref matchCase, ref matchWholeWord,
                                           ref matchWildCards, ref matchSoundLike,
                                           ref nmatchAllForms, ref forward,
                                           ref wrap, ref format, ref replaceWithText,
                                           ref replace, ref matchKashida,
                                           ref matchDiactitics, ref matchAlefHamza,
                                           ref matchControl);
        }

        private void CreateWordDocument(object filename, object savaAs)
        {
            object missing = System.Reflection.Missing.Value;
            List<authorizedDataClass> listData = authorizedDataClass.ListAuthorizedData;


            MSWord.Application wordApp = new MSWord.Application();

            MSWord.Document myWordDoc = null;

            if (System.IO.File.Exists((string)filename))
            {
                DateTime today = DateTime.Now;

                object readOnly = false; //default
                object isVisible = false;

                wordApp.Visible = false;

                myWordDoc = wordApp.Documents.Open(ref filename, ref missing, ref readOnly,
                                                   ref missing, ref missing, ref missing,
                                                   ref missing, ref missing, ref missing,
                                                   ref missing, ref missing, ref missing,
                                                   ref missing, ref missing, ref missing, ref missing);

                myWordDoc.Activate();

                //Find and replace:
                this.FindAndReplace(wordApp, "<name>", txbName.Text);
                this.FindAndReplace(wordApp, "<phone number>", txbPhoneNumber.Text);
                this.FindAndReplace(wordApp, "<date>", DateTime.Now.ToString("dddd, MMMM dd, yyyy h:mm:ss tt"));
                this.FindAndReplace(wordApp, "<email>", txbEmail.Text);

                MSWord.Table table = myWordDoc.Tables[1];
                for (int i = 0; i < listData.Count; i++)
                {
                    table.Cell(i + 2, 1).Range.Text = (i + 1).ToString();
                    table.Cell(i + 2, 2).Range.Text = listData[i].ID;
                    table.Cell(i + 2, 3).Range.Text = listData[i].Name;
                    table.Cell(i + 2, 4).Range.Text = listData[i].InOrOut;
                    table.Cell(i + 2, 5).Range.Text = listData[i].AuthorizeAtTime;
                    if (i != listData.Count - 1) table.Rows.Add(missing);

                }
            }
            else
            {
                MessageBox.Show("File dose not exist.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            //Save as: filename
            myWordDoc.SaveAs2(ref savaAs, ref missing, ref missing, ref missing,
                    ref missing, ref missing, ref missing,
                    ref missing, ref missing, ref missing,
                    ref missing, ref missing, ref missing,
                    ref missing, ref missing, ref missing);

            myWordDoc.Close(ref missing, ref missing, ref missing);
            wordApp.Quit(ref missing, ref missing, ref missing);

            MessageBox.Show("File is created at:\n" + savaAs, "", MessageBoxButtons.OK, MessageBoxIcon.Information);

            txbTemplatePath.Clear();
            rtxbTemplate.Clear();
        }

        private void btnLoadTemplate_Click(object sender, EventArgs e)
        {
            loadTemplateDialog.Filter = "DOCX files (*.docx, *.dotx, *.docm, *.dotm)|*.docx;*.dotx;*.docm;*.dotm" +
                                        "|DOC files (*.doc, *.dot)|*.doc;*.dot";
            if (loadTemplateDialog.ShowDialog() == DialogResult.OK)
            {
                txbTemplatePath.Text = loadTemplateDialog.FileName;

                object missing = System.Reflection.Missing.Value;
                MSWord.Application wordApp = new MSWord.Application() { Visible = false };
                MSWord.Document myWordDoc = null;
                object readOnly = false; //default
                object isVisible = false;
                object filename = loadTemplateDialog.FileName;
                myWordDoc = wordApp.Documents.Open(ref filename, ref missing, ref readOnly,
                                                   ref missing, ref missing, ref missing,
                                                   ref missing, ref missing, ref missing,
                                                   ref missing, ref missing, ref missing,
                                                   ref missing, ref missing, ref missing, ref missing);
                myWordDoc.ActiveWindow.Selection.WholeStory();
                myWordDoc.ActiveWindow.Selection.Copy();
                IDataObject dataObject = Clipboard.GetDataObject();
                rtxbTemplate.Rtf = dataObject.GetData(DataFormats.Rtf).ToString();

                myWordDoc.Close(ref missing, ref missing, ref missing);
                wordApp.Quit(ref missing, ref missing, ref missing);
            }
        }

        private void btnPreview_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(txbName.Text) ||
                String.IsNullOrEmpty(txbPhoneNumber.Text) ||
                String.IsNullOrEmpty(txbTemplatePath.Text))
            {
                MessageBox.Show("Do not enough information to preview the report", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            List<authorizedDataClass> listData = authorizedDataClass.ListAuthorizedData;
            object missing = System.Reflection.Missing.Value;
            MSWord.Application wordApp = new MSWord.Application();
            MSWord.Document myWordDoc = null;
            object filename = txbTemplatePath.Text;
            if (System.IO.File.Exists((string)filename))
            {
                DateTime today = DateTime.Now;
                object readOnly = false; //default
                object isVisible = false;
                wordApp.Visible = false;
                myWordDoc = wordApp.Documents.Open(ref filename, ref missing, ref readOnly,
                                                    ref missing, ref missing, ref missing,
                                                    ref missing, ref missing, ref missing,
                                                    ref missing, ref missing, ref missing,
                                                    ref missing, ref missing, ref missing, ref missing);

                //Find and replace:
                this.FindAndReplace(wordApp, "<name>", txbName.Text);
                this.FindAndReplace(wordApp, "<phone number>", txbPhoneNumber.Text);
                this.FindAndReplace(wordApp, "<date>", DateTime.Now.ToString("dddd, MMMM dd, yyyy h:mm:ss tt"));
                this.FindAndReplace(wordApp, "<email>", txbEmail.Text);

                MSWord.Table table = myWordDoc.Tables[1];
                for (int i = 0; i < listData.Count; i++)
                {
                    table.Cell(i + 2, 1).Range.Text = (i + 1).ToString();
                    table.Cell(i + 2, 2).Range.Text = listData[i].ID;
                    table.Cell(i + 2, 3).Range.Text = listData[i].Name;
                    table.Cell(i + 2, 4).Range.Text = listData[i].InOrOut;
                    table.Cell(i + 2, 5).Range.Text = listData[i].AuthorizeAtTime;
                    if (i != listData.Count - 1) table.Rows.Add(missing);

                }
            }
            else
            {
                MessageBox.Show("File dose not exist.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            myWordDoc.ActiveWindow.Selection.WholeStory();
            myWordDoc.ActiveWindow.Selection.Copy();
            IDataObject dataObject = Clipboard.GetDataObject();
            rtxbTemplate.Rtf = dataObject.GetData(DataFormats.Rtf).ToString();

            object isSave = false;
            myWordDoc.Close(isSave, ref missing, ref missing);
            wordApp.Quit(isSave, ref missing, ref missing);
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
                CreateWordDocument(txbTemplatePath.Text, saveReportDialog.FileName);
            }
        }

        private void saveReportDialog_FileOk(object sender, CancelEventArgs e)
        {

        }
    }
}
