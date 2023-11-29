
namespace projectGUIApp
{
    partial class mainDashboard
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(mainDashboard));
            this.monitorListGrpBx = new System.Windows.Forms.GroupBox();
            this.monitorListView = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader6 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.comStatusGrpBx = new System.Windows.Forms.GroupBox();
            this.rtxtbComStatus = new System.Windows.Forms.RichTextBox();
            this.mnstrHomeScr = new System.Windows.Forms.MenuStrip();
            this.communicationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cardManagerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.reportToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.operationManualToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.monitorListGrpBx.SuspendLayout();
            this.comStatusGrpBx.SuspendLayout();
            this.mnstrHomeScr.SuspendLayout();
            this.SuspendLayout();
            // 
            // monitorListGrpBx
            // 
            this.monitorListGrpBx.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.monitorListGrpBx.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.monitorListGrpBx.BackColor = System.Drawing.Color.Lavender;
            this.monitorListGrpBx.Controls.Add(this.monitorListView);
            this.monitorListGrpBx.Font = new System.Drawing.Font("Segoe UI Semibold", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.monitorListGrpBx.ForeColor = System.Drawing.Color.DarkRed;
            this.monitorListGrpBx.Location = new System.Drawing.Point(12, 42);
            this.monitorListGrpBx.Name = "monitorListGrpBx";
            this.monitorListGrpBx.Size = new System.Drawing.Size(780, 403);
            this.monitorListGrpBx.TabIndex = 16;
            this.monitorListGrpBx.TabStop = false;
            this.monitorListGrpBx.Text = "Monitor List";
            // 
            // monitorListView
            // 
            this.monitorListView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.monitorListView.BackColor = System.Drawing.Color.White;
            this.monitorListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader4,
            this.columnHeader5,
            this.columnHeader6});
            this.monitorListView.Font = new System.Drawing.Font("Segoe UI", 9.25F);
            this.monitorListView.HideSelection = false;
            this.monitorListView.Location = new System.Drawing.Point(11, 26);
            this.monitorListView.Name = "monitorListView";
            this.monitorListView.Size = new System.Drawing.Size(760, 367);
            this.monitorListView.TabIndex = 1;
            this.monitorListView.UseCompatibleStateImageBehavior = false;
            this.monitorListView.View = System.Windows.Forms.View.Details;
            this.monitorListView.SelectedIndexChanged += new System.EventHandler(this.listViewTask_SelectedIndexChanged);
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "No.";
            this.columnHeader1.Width = 80;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Name";
            this.columnHeader2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeader2.Width = 250;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "ID";
            this.columnHeader3.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeader3.Width = 109;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "I/O";
            this.columnHeader4.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeader4.Width = 100;
            // 
            // columnHeader5
            // 
            this.columnHeader5.Text = "Time";
            this.columnHeader5.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeader5.Width = 90;
            // 
            // columnHeader6
            // 
            this.columnHeader6.Text = "Date";
            this.columnHeader6.Width = 130;
            // 
            // comStatusGrpBx
            // 
            this.comStatusGrpBx.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comStatusGrpBx.BackColor = System.Drawing.Color.Lavender;
            this.comStatusGrpBx.Controls.Add(this.rtxtbComStatus);
            this.comStatusGrpBx.Font = new System.Drawing.Font("Segoe UI Semibold", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comStatusGrpBx.ForeColor = System.Drawing.Color.DarkRed;
            this.comStatusGrpBx.Location = new System.Drawing.Point(12, 461);
            this.comStatusGrpBx.Name = "comStatusGrpBx";
            this.comStatusGrpBx.Size = new System.Drawing.Size(780, 183);
            this.comStatusGrpBx.TabIndex = 17;
            this.comStatusGrpBx.TabStop = false;
            this.comStatusGrpBx.Text = "Communication Status";
            // 
            // rtxtbComStatus
            // 
            this.rtxtbComStatus.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.rtxtbComStatus.BackColor = System.Drawing.Color.WhiteSmoke;
            this.rtxtbComStatus.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.rtxtbComStatus.Font = new System.Drawing.Font("Segoe UI", 11.25F);
            this.rtxtbComStatus.Location = new System.Drawing.Point(11, 26);
            this.rtxtbComStatus.Name = "rtxtbComStatus";
            this.rtxtbComStatus.Size = new System.Drawing.Size(760, 144);
            this.rtxtbComStatus.TabIndex = 6;
            this.rtxtbComStatus.Text = "";
            // 
            // mnstrHomeScr
            // 
            this.mnstrHomeScr.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.mnstrHomeScr.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.mnstrHomeScr.GripStyle = System.Windows.Forms.ToolStripGripStyle.Visible;
            this.mnstrHomeScr.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.communicationToolStripMenuItem,
            this.cardManagerToolStripMenuItem,
            this.reportToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.mnstrHomeScr.Location = new System.Drawing.Point(0, 0);
            this.mnstrHomeScr.Name = "mnstrHomeScr";
            this.mnstrHomeScr.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
            this.mnstrHomeScr.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.mnstrHomeScr.Size = new System.Drawing.Size(804, 27);
            this.mnstrHomeScr.TabIndex = 18;
            this.mnstrHomeScr.Text = "mnstrHomeScr";
            // 
            // communicationToolStripMenuItem
            // 
            this.communicationToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("communicationToolStripMenuItem.Image")));
            this.communicationToolStripMenuItem.Name = "communicationToolStripMenuItem";
            this.communicationToolStripMenuItem.Size = new System.Drawing.Size(134, 23);
            this.communicationToolStripMenuItem.Text = "&Communication";
            this.communicationToolStripMenuItem.Click += new System.EventHandler(this.communicationToolStripMenuItem_Click);
            // 
            // cardManagerToolStripMenuItem
            // 
            this.cardManagerToolStripMenuItem.Image = global::projectGUIApp.Properties.Resources.icon_card;
            this.cardManagerToolStripMenuItem.Name = "cardManagerToolStripMenuItem";
            this.cardManagerToolStripMenuItem.Size = new System.Drawing.Size(125, 23);
            this.cardManagerToolStripMenuItem.Text = "&Card Manager";
            this.cardManagerToolStripMenuItem.Click += new System.EventHandler(this.cardManagerToolStripMenuItem_Click);
            // 
            // reportToolStripMenuItem
            // 
            this.reportToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("reportToolStripMenuItem.Image")));
            this.reportToolStripMenuItem.Name = "reportToolStripMenuItem";
            this.reportToolStripMenuItem.Size = new System.Drawing.Size(78, 23);
            this.reportToolStripMenuItem.Text = "&Report";
            this.reportToolStripMenuItem.Click += new System.EventHandler(this.reportToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.operationManualToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("helpToolStripMenuItem.Image")));
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(65, 23);
            this.helpToolStripMenuItem.Text = "&Help";
            // 
            // operationManualToolStripMenuItem
            // 
            this.operationManualToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("operationManualToolStripMenuItem.Image")));
            this.operationManualToolStripMenuItem.Name = "operationManualToolStripMenuItem";
            this.operationManualToolStripMenuItem.Size = new System.Drawing.Size(193, 24);
            this.operationManualToolStripMenuItem.Text = "&Project Description";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("aboutToolStripMenuItem.Image")));
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(193, 24);
            this.aboutToolStripMenuItem.Text = "&About...";
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(61, 4);
            // 
            // mainDashboard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(804, 656);
            this.Controls.Add(this.mnstrHomeScr);
            this.Controls.Add(this.comStatusGrpBx);
            this.Controls.Add(this.monitorListGrpBx);
            this.Name = "mainDashboard";
            this.Text = "mainDashBoardForm";
            this.monitorListGrpBx.ResumeLayout(false);
            this.comStatusGrpBx.ResumeLayout(false);
            this.mnstrHomeScr.ResumeLayout(false);
            this.mnstrHomeScr.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox monitorListGrpBx;
        private System.Windows.Forms.ListView monitorListView;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ColumnHeader columnHeader5;
        private System.Windows.Forms.GroupBox comStatusGrpBx;
        private System.Windows.Forms.MenuStrip mnstrHomeScr;
        private System.Windows.Forms.ToolStripMenuItem communicationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cardManagerToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem reportToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem operationManualToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.RichTextBox rtxtbComStatus;
        private System.Windows.Forms.ColumnHeader columnHeader6;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
    }
}

