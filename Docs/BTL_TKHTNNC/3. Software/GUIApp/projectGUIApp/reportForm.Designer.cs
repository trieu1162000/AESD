﻿
namespace projectGUIApp
{
    partial class reportForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(reportForm));
            this.label2 = new System.Windows.Forms.Label();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.rtxbTemplate = new System.Windows.Forms.RichTextBox();
            this.txbPhoneNumber = new System.Windows.Forms.TextBox();
            this.txbName = new System.Windows.Forms.TextBox();
            this.txbTemplatePath = new System.Windows.Forms.TextBox();
            this.btnPreview = new System.Windows.Forms.Button();
            this.btnLoadTemplate = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.loadTemplateDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveReportDialog = new System.Windows.Forms.SaveFileDialog();
            this.txbEmail = new System.Windows.Forms.TextBox();
            this.btnSaveAs = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.label2.ForeColor = System.Drawing.Color.Navy;
            this.label2.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.label2.ImageIndex = 4;
            this.label2.ImageList = this.imageList1;
            this.label2.Location = new System.Drawing.Point(31, 20);
            this.label2.Name = "label2";
            this.label2.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.label2.Size = new System.Drawing.Size(136, 19);
            this.label2.TabIndex = 37;
            this.label2.Text = "     Supervisor Name:";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "icon_preview.png");
            this.imageList1.Images.SetKeyName(1, "icon_save.png");
            this.imageList1.Images.SetKeyName(2, "icon_template.png");
            this.imageList1.Images.SetKeyName(3, "icon_email.png");
            this.imageList1.Images.SetKeyName(4, "icon_person.png");
            this.imageList1.Images.SetKeyName(5, "icon_phone.png");
            // 
            // rtxbTemplate
            // 
            this.rtxbTemplate.BackColor = System.Drawing.Color.White;
            this.rtxbTemplate.Font = new System.Drawing.Font("Cambria", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rtxbTemplate.Location = new System.Drawing.Point(21, 125);
            this.rtxbTemplate.Name = "rtxbTemplate";
            this.rtxbTemplate.ReadOnly = true;
            this.rtxbTemplate.Size = new System.Drawing.Size(633, 334);
            this.rtxbTemplate.TabIndex = 47;
            this.rtxbTemplate.Text = "";
            // 
            // txbPhoneNumber
            // 
            this.txbPhoneNumber.Font = new System.Drawing.Font("Segoe UI Semibold", 10F, System.Drawing.FontStyle.Bold);
            this.txbPhoneNumber.Location = new System.Drawing.Point(170, 49);
            this.txbPhoneNumber.Name = "txbPhoneNumber";
            this.txbPhoneNumber.Size = new System.Drawing.Size(149, 25);
            this.txbPhoneNumber.TabIndex = 44;
            // 
            // txbName
            // 
            this.txbName.Font = new System.Drawing.Font("Segoe UI Semibold", 10F, System.Drawing.FontStyle.Bold);
            this.txbName.Location = new System.Drawing.Point(170, 18);
            this.txbName.Name = "txbName";
            this.txbName.Size = new System.Drawing.Size(149, 25);
            this.txbName.TabIndex = 43;
            // 
            // txbTemplatePath
            // 
            this.txbTemplatePath.BackColor = System.Drawing.SystemColors.Info;
            this.txbTemplatePath.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txbTemplatePath.Location = new System.Drawing.Point(155, 88);
            this.txbTemplatePath.Name = "txbTemplatePath";
            this.txbTemplatePath.ReadOnly = true;
            this.txbTemplatePath.Size = new System.Drawing.Size(499, 25);
            this.txbTemplatePath.TabIndex = 45;
            // 
            // btnPreview
            // 
            this.btnPreview.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.btnPreview.ForeColor = System.Drawing.Color.DarkRed;
            this.btnPreview.ImageIndex = 0;
            this.btnPreview.ImageList = this.imageList1;
            this.btnPreview.Location = new System.Drawing.Point(452, 465);
            this.btnPreview.Name = "btnPreview";
            this.btnPreview.Size = new System.Drawing.Size(85, 32);
            this.btnPreview.TabIndex = 40;
            this.btnPreview.Text = "Preview";
            this.btnPreview.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnPreview.UseVisualStyleBackColor = true;
            this.btnPreview.Click += new System.EventHandler(this.btnPreview_Click);
            // 
            // btnLoadTemplate
            // 
            this.btnLoadTemplate.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.btnLoadTemplate.ForeColor = System.Drawing.Color.DarkRed;
            this.btnLoadTemplate.ImageIndex = 2;
            this.btnLoadTemplate.ImageList = this.imageList1;
            this.btnLoadTemplate.Location = new System.Drawing.Point(21, 83);
            this.btnLoadTemplate.Name = "btnLoadTemplate";
            this.btnLoadTemplate.Size = new System.Drawing.Size(128, 32);
            this.btnLoadTemplate.TabIndex = 41;
            this.btnLoadTemplate.Text = "Load Template";
            this.btnLoadTemplate.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnLoadTemplate.UseVisualStyleBackColor = true;
            this.btnLoadTemplate.Click += new System.EventHandler(this.btnLoadTemplate_Click);
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.label1.ForeColor = System.Drawing.Color.Navy;
            this.label1.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.label1.ImageIndex = 5;
            this.label1.ImageList = this.imageList1;
            this.label1.Location = new System.Drawing.Point(31, 51);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(125, 19);
            this.label1.TabIndex = 38;
            this.label1.Text = "     Phone Number:";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // loadTemplateDialog
            // 
            this.loadTemplateDialog.FileName = "loadTemplateDialog";
            // 
            // saveReportDialog
            // 
            this.saveReportDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.saveReportDialog_FileOk);
            // 
            // txbEmail
            // 
            this.txbEmail.Font = new System.Drawing.Font("Segoe UI Semibold", 10F, System.Drawing.FontStyle.Bold);
            this.txbEmail.Location = new System.Drawing.Point(408, 49);
            this.txbEmail.Name = "txbEmail";
            this.txbEmail.Size = new System.Drawing.Size(186, 25);
            this.txbEmail.TabIndex = 46;
            // 
            // btnSaveAs
            // 
            this.btnSaveAs.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.btnSaveAs.ForeColor = System.Drawing.Color.DarkRed;
            this.btnSaveAs.ImageIndex = 1;
            this.btnSaveAs.ImageList = this.imageList1;
            this.btnSaveAs.Location = new System.Drawing.Point(557, 465);
            this.btnSaveAs.Name = "btnSaveAs";
            this.btnSaveAs.Size = new System.Drawing.Size(90, 32);
            this.btnSaveAs.TabIndex = 42;
            this.btnSaveAs.Text = "Save as";
            this.btnSaveAs.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnSaveAs.UseVisualStyleBackColor = true;
            this.btnSaveAs.Click += new System.EventHandler(this.btnSaveAs_Click);
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.label3.ForeColor = System.Drawing.Color.Navy;
            this.label3.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.label3.ImageIndex = 3;
            this.label3.ImageList = this.imageList1;
            this.label3.Location = new System.Drawing.Point(340, 51);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 19);
            this.label3.TabIndex = 39;
            this.label3.Text = "     Email:";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // reportForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(678, 515);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.rtxbTemplate);
            this.Controls.Add(this.txbPhoneNumber);
            this.Controls.Add(this.txbName);
            this.Controls.Add(this.txbTemplatePath);
            this.Controls.Add(this.btnPreview);
            this.Controls.Add(this.btnLoadTemplate);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txbEmail);
            this.Controls.Add(this.btnSaveAs);
            this.Controls.Add(this.label3);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "reportForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Report Management";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.RichTextBox rtxbTemplate;
        private System.Windows.Forms.TextBox txbPhoneNumber;
        private System.Windows.Forms.TextBox txbName;
        private System.Windows.Forms.TextBox txbTemplatePath;
        private System.Windows.Forms.Button btnPreview;
        private System.Windows.Forms.Button btnLoadTemplate;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.OpenFileDialog loadTemplateDialog;
        private System.Windows.Forms.SaveFileDialog saveReportDialog;
        private System.Windows.Forms.TextBox txbEmail;
        private System.Windows.Forms.Button btnSaveAs;
        private System.Windows.Forms.Label label3;
    }
}