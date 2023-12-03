namespace projectGUIApp
{
    partial class cardManagerForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(cardManagerForm));
            this.myToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.ID = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.userName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.UUID = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.listViewCard = new System.Windows.Forms.ListView();
            this.btnSyncCard = new System.Windows.Forms.Button();
            this.btnCardManagementOK = new System.Windows.Forms.Button();
            this.groupBoxUpdateCard = new System.Windows.Forms.GroupBox();
            this.lbUpdateName = new System.Windows.Forms.Label();
            this.txtBoxUpdateID = new System.Windows.Forms.TextBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.txtBoxUpdateName = new System.Windows.Forms.TextBox();
            this.btnUpdateCard = new System.Windows.Forms.Button();
            this.lbBoxUpdateID = new System.Windows.Forms.Label();
            this.lbUpdateUUID = new System.Windows.Forms.Label();
            this.cbbUpdateUUID = new System.Windows.Forms.ComboBox();
            this.groupBoxAddCard = new System.Windows.Forms.GroupBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.lbNameAdd = new System.Windows.Forms.Label();
            this.btnAddCard = new System.Windows.Forms.Button();
            this.txtBoxAddID = new System.Windows.Forms.TextBox();
            this.txtBoxAddName = new System.Windows.Forms.TextBox();
            this.lbAddID = new System.Windows.Forms.Label();
            this.groupBoxListCards = new System.Windows.Forms.GroupBox();
            this.groupBoxRemoveCard = new System.Windows.Forms.GroupBox();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.btnRemoveCard = new System.Windows.Forms.Button();
            this.lbRemoveID = new System.Windows.Forms.Label();
            this.cbbRemoveID = new System.Windows.Forms.ComboBox();
            this.groupBoxUpdateCard.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.groupBoxAddCard.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBoxListCards.SuspendLayout();
            this.groupBoxRemoveCard.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.SuspendLayout();
            // 
            // myToolTip
            // 
            this.myToolTip.AutoPopDelay = 5000;
            this.myToolTip.InitialDelay = 100;
            this.myToolTip.ReshowDelay = 100;
            // 
            // ID
            // 
            this.ID.Text = "ID";
            this.ID.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.ID.Width = 113;
            // 
            // userName
            // 
            this.userName.Text = "Name";
            this.userName.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.userName.Width = 293;
            // 
            // UUID
            // 
            this.UUID.Text = "UUID";
            this.UUID.Width = 134;
            // 
            // listViewCard
            // 
            this.listViewCard.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.UUID,
            this.userName,
            this.ID});
            this.listViewCard.Font = new System.Drawing.Font("Segoe UI", 9.25F);
            this.listViewCard.ForeColor = System.Drawing.SystemColors.WindowText;
            this.listViewCard.FullRowSelect = true;
            this.listViewCard.GridLines = true;
            this.listViewCard.HideSelection = false;
            this.listViewCard.Location = new System.Drawing.Point(8, 26);
            this.listViewCard.Name = "listViewCard";
            this.listViewCard.Size = new System.Drawing.Size(539, 361);
            this.listViewCard.TabIndex = 32;
            this.listViewCard.UseCompatibleStateImageBehavior = false;
            this.listViewCard.View = System.Windows.Forms.View.Details;
            // 
            // btnSyncCard
            // 
            this.btnSyncCard.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.btnSyncCard.ForeColor = System.Drawing.Color.MediumBlue;
            this.btnSyncCard.Image = ((System.Drawing.Image)(resources.GetObject("btnSyncCard.Image")));
            this.btnSyncCard.Location = new System.Drawing.Point(325, 393);
            this.btnSyncCard.Name = "btnSyncCard";
            this.btnSyncCard.Size = new System.Drawing.Size(108, 27);
            this.btnSyncCard.TabIndex = 47;
            this.btnSyncCard.Text = "Sync";
            this.btnSyncCard.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnSyncCard.UseVisualStyleBackColor = true;
            this.btnSyncCard.Click += new System.EventHandler(this.btnSyncCard_Click);
            // 
            // btnCardManagementOK
            // 
            this.btnCardManagementOK.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.btnCardManagementOK.ForeColor = System.Drawing.Color.MediumBlue;
            this.btnCardManagementOK.Image = ((System.Drawing.Image)(resources.GetObject("btnCardManagementOK.Image")));
            this.btnCardManagementOK.Location = new System.Drawing.Point(439, 393);
            this.btnCardManagementOK.Name = "btnCardManagementOK";
            this.btnCardManagementOK.Size = new System.Drawing.Size(108, 27);
            this.btnCardManagementOK.TabIndex = 48;
            this.btnCardManagementOK.Text = "OK";
            this.btnCardManagementOK.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnCardManagementOK.UseVisualStyleBackColor = true;
            this.btnCardManagementOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // groupBoxUpdateCard
            // 
            this.groupBoxUpdateCard.BackColor = System.Drawing.Color.Lavender;
            this.groupBoxUpdateCard.Controls.Add(this.lbUpdateName);
            this.groupBoxUpdateCard.Controls.Add(this.txtBoxUpdateID);
            this.groupBoxUpdateCard.Controls.Add(this.pictureBox2);
            this.groupBoxUpdateCard.Controls.Add(this.txtBoxUpdateName);
            this.groupBoxUpdateCard.Controls.Add(this.btnUpdateCard);
            this.groupBoxUpdateCard.Controls.Add(this.lbBoxUpdateID);
            this.groupBoxUpdateCard.Controls.Add(this.lbUpdateUUID);
            this.groupBoxUpdateCard.Controls.Add(this.cbbUpdateUUID);
            this.groupBoxUpdateCard.Font = new System.Drawing.Font("Segoe UI Semibold", 11F, System.Drawing.FontStyle.Bold);
            this.groupBoxUpdateCard.ForeColor = System.Drawing.Color.DarkRed;
            this.groupBoxUpdateCard.Location = new System.Drawing.Point(574, 165);
            this.groupBoxUpdateCard.Name = "groupBoxUpdateCard";
            this.groupBoxUpdateCard.Size = new System.Drawing.Size(245, 179);
            this.groupBoxUpdateCard.TabIndex = 51;
            this.groupBoxUpdateCard.TabStop = false;
            this.groupBoxUpdateCard.Text = "     Update";
            // 
            // lbUpdateName
            // 
            this.lbUpdateName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.lbUpdateName.AutoSize = true;
            this.lbUpdateName.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.lbUpdateName.ForeColor = System.Drawing.Color.Navy;
            this.lbUpdateName.Location = new System.Drawing.Point(17, 89);
            this.lbUpdateName.Name = "lbUpdateName";
            this.lbUpdateName.Size = new System.Drawing.Size(48, 19);
            this.lbUpdateName.TabIndex = 19;
            this.lbUpdateName.Text = "Name:";
            this.lbUpdateName.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // txtBoxUpdateID
            // 
            this.txtBoxUpdateID.Font = new System.Drawing.Font("Segoe UI Semibold", 10F, System.Drawing.FontStyle.Bold);
            this.txtBoxUpdateID.Location = new System.Drawing.Point(71, 114);
            this.txtBoxUpdateID.Name = "txtBoxUpdateID";
            this.txtBoxUpdateID.Size = new System.Drawing.Size(155, 25);
            this.txtBoxUpdateID.TabIndex = 22;
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(9, 2);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(17, 17);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox2.TabIndex = 19;
            this.pictureBox2.TabStop = false;
            // 
            // txtBoxUpdateName
            // 
            this.txtBoxUpdateName.Font = new System.Drawing.Font("Segoe UI Semibold", 10F, System.Drawing.FontStyle.Bold);
            this.txtBoxUpdateName.Location = new System.Drawing.Point(71, 56);
            this.txtBoxUpdateName.Multiline = true;
            this.txtBoxUpdateName.Name = "txtBoxUpdateName";
            this.txtBoxUpdateName.Size = new System.Drawing.Size(155, 52);
            this.txtBoxUpdateName.TabIndex = 20;
            // 
            // btnUpdateCard
            // 
            this.btnUpdateCard.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.btnUpdateCard.ForeColor = System.Drawing.Color.DarkRed;
            this.btnUpdateCard.Location = new System.Drawing.Point(155, 145);
            this.btnUpdateCard.Name = "btnUpdateCard";
            this.btnUpdateCard.Size = new System.Drawing.Size(71, 27);
            this.btnUpdateCard.TabIndex = 17;
            this.btnUpdateCard.Text = "Update";
            this.btnUpdateCard.UseVisualStyleBackColor = true;
            this.btnUpdateCard.Click += new System.EventHandler(this.btnUpdate_Click);
            // 
            // lbBoxUpdateID
            // 
            this.lbBoxUpdateID.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.lbBoxUpdateID.AutoSize = true;
            this.lbBoxUpdateID.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.lbBoxUpdateID.ForeColor = System.Drawing.Color.Navy;
            this.lbBoxUpdateID.Location = new System.Drawing.Point(17, 120);
            this.lbBoxUpdateID.Name = "lbBoxUpdateID";
            this.lbBoxUpdateID.Size = new System.Drawing.Size(26, 19);
            this.lbBoxUpdateID.TabIndex = 21;
            this.lbBoxUpdateID.Text = "ID:";
            this.lbBoxUpdateID.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lbUpdateUUID
            // 
            this.lbUpdateUUID.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.lbUpdateUUID.AutoSize = true;
            this.lbUpdateUUID.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.lbUpdateUUID.ForeColor = System.Drawing.Color.Navy;
            this.lbUpdateUUID.Location = new System.Drawing.Point(17, 31);
            this.lbUpdateUUID.Name = "lbUpdateUUID";
            this.lbUpdateUUID.Size = new System.Drawing.Size(46, 19);
            this.lbUpdateUUID.TabIndex = 17;
            this.lbUpdateUUID.Text = "UUID:";
            this.lbUpdateUUID.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // cbbUpdateUUID
            // 
            this.cbbUpdateUUID.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbbUpdateUUID.Font = new System.Drawing.Font("Segoe UI Semibold", 10F, System.Drawing.FontStyle.Bold);
            this.cbbUpdateUUID.FormattingEnabled = true;
            this.cbbUpdateUUID.Location = new System.Drawing.Point(71, 25);
            this.cbbUpdateUUID.MaxDropDownItems = 4;
            this.cbbUpdateUUID.Name = "cbbUpdateUUID";
            this.cbbUpdateUUID.Size = new System.Drawing.Size(155, 25);
            this.cbbUpdateUUID.TabIndex = 17;
            this.cbbUpdateUUID.DropDown += new System.EventHandler(this.cbbUpdateUUID_DropDown);
            // 
            // groupBoxAddCard
            // 
            this.groupBoxAddCard.BackColor = System.Drawing.Color.Lavender;
            this.groupBoxAddCard.Controls.Add(this.pictureBox1);
            this.groupBoxAddCard.Controls.Add(this.lbNameAdd);
            this.groupBoxAddCard.Controls.Add(this.btnAddCard);
            this.groupBoxAddCard.Controls.Add(this.txtBoxAddID);
            this.groupBoxAddCard.Controls.Add(this.txtBoxAddName);
            this.groupBoxAddCard.Controls.Add(this.lbAddID);
            this.groupBoxAddCard.Font = new System.Drawing.Font("Segoe UI Semibold", 11F, System.Drawing.FontStyle.Bold);
            this.groupBoxAddCard.ForeColor = System.Drawing.Color.DarkRed;
            this.groupBoxAddCard.Location = new System.Drawing.Point(574, 12);
            this.groupBoxAddCard.Name = "groupBoxAddCard";
            this.groupBoxAddCard.Size = new System.Drawing.Size(245, 145);
            this.groupBoxAddCard.TabIndex = 50;
            this.groupBoxAddCard.TabStop = false;
            this.groupBoxAddCard.Text = "     Add";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(9, 1);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(18, 18);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 18;
            this.pictureBox1.TabStop = false;
            // 
            // lbNameAdd
            // 
            this.lbNameAdd.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.lbNameAdd.AutoSize = true;
            this.lbNameAdd.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.lbNameAdd.ForeColor = System.Drawing.Color.Navy;
            this.lbNameAdd.Location = new System.Drawing.Point(17, 54);
            this.lbNameAdd.Name = "lbNameAdd";
            this.lbNameAdd.Size = new System.Drawing.Size(48, 19);
            this.lbNameAdd.TabIndex = 8;
            this.lbNameAdd.Text = "Name:";
            this.lbNameAdd.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // btnAddCard
            // 
            this.btnAddCard.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.btnAddCard.ForeColor = System.Drawing.Color.DarkRed;
            this.btnAddCard.Location = new System.Drawing.Point(155, 110);
            this.btnAddCard.Name = "btnAddCard";
            this.btnAddCard.Size = new System.Drawing.Size(71, 27);
            this.btnAddCard.TabIndex = 6;
            this.btnAddCard.Text = "Add";
            this.btnAddCard.UseVisualStyleBackColor = true;
            this.btnAddCard.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // txtBoxAddID
            // 
            this.txtBoxAddID.Font = new System.Drawing.Font("Segoe UI Semibold", 10F, System.Drawing.FontStyle.Bold);
            this.txtBoxAddID.Location = new System.Drawing.Point(71, 79);
            this.txtBoxAddID.Name = "txtBoxAddID";
            this.txtBoxAddID.Size = new System.Drawing.Size(155, 25);
            this.txtBoxAddID.TabIndex = 16;
            // 
            // txtBoxAddName
            // 
            this.txtBoxAddName.Font = new System.Drawing.Font("Segoe UI Semibold", 10F, System.Drawing.FontStyle.Bold);
            this.txtBoxAddName.Location = new System.Drawing.Point(71, 21);
            this.txtBoxAddName.Multiline = true;
            this.txtBoxAddName.Name = "txtBoxAddName";
            this.txtBoxAddName.Size = new System.Drawing.Size(155, 52);
            this.txtBoxAddName.TabIndex = 10;
            // 
            // lbAddID
            // 
            this.lbAddID.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.lbAddID.AutoSize = true;
            this.lbAddID.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.lbAddID.ForeColor = System.Drawing.Color.Navy;
            this.lbAddID.Location = new System.Drawing.Point(17, 85);
            this.lbAddID.Name = "lbAddID";
            this.lbAddID.Size = new System.Drawing.Size(26, 19);
            this.lbAddID.TabIndex = 11;
            this.lbAddID.Text = "ID:";
            this.lbAddID.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // groupBoxListCards
            // 
            this.groupBoxListCards.BackColor = System.Drawing.Color.Lavender;
            this.groupBoxListCards.Controls.Add(this.listViewCard);
            this.groupBoxListCards.Controls.Add(this.btnSyncCard);
            this.groupBoxListCards.Controls.Add(this.btnCardManagementOK);
            this.groupBoxListCards.Font = new System.Drawing.Font("Segoe UI Semibold", 11F, System.Drawing.FontStyle.Bold);
            this.groupBoxListCards.ForeColor = System.Drawing.Color.DarkRed;
            this.groupBoxListCards.Location = new System.Drawing.Point(12, 12);
            this.groupBoxListCards.Name = "groupBoxListCards";
            this.groupBoxListCards.Size = new System.Drawing.Size(556, 426);
            this.groupBoxListCards.TabIndex = 52;
            this.groupBoxListCards.TabStop = false;
            this.groupBoxListCards.Text = "List of Cards";
            // 
            // groupBoxRemoveCard
            // 
            this.groupBoxRemoveCard.BackColor = System.Drawing.Color.Lavender;
            this.groupBoxRemoveCard.Controls.Add(this.pictureBox3);
            this.groupBoxRemoveCard.Controls.Add(this.btnRemoveCard);
            this.groupBoxRemoveCard.Controls.Add(this.lbRemoveID);
            this.groupBoxRemoveCard.Controls.Add(this.cbbRemoveID);
            this.groupBoxRemoveCard.Font = new System.Drawing.Font("Segoe UI Semibold", 11F, System.Drawing.FontStyle.Bold);
            this.groupBoxRemoveCard.ForeColor = System.Drawing.Color.DarkRed;
            this.groupBoxRemoveCard.Location = new System.Drawing.Point(574, 350);
            this.groupBoxRemoveCard.Name = "groupBoxRemoveCard";
            this.groupBoxRemoveCard.Size = new System.Drawing.Size(245, 88);
            this.groupBoxRemoveCard.TabIndex = 52;
            this.groupBoxRemoveCard.TabStop = false;
            this.groupBoxRemoveCard.Text = "     Remove";
            // 
            // pictureBox3
            // 
            this.pictureBox3.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox3.Image")));
            this.pictureBox3.Location = new System.Drawing.Point(9, 2);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(17, 17);
            this.pictureBox3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox3.TabIndex = 19;
            this.pictureBox3.TabStop = false;
            // 
            // btnRemoveCard
            // 
            this.btnRemoveCard.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.btnRemoveCard.ForeColor = System.Drawing.Color.DarkRed;
            this.btnRemoveCard.Location = new System.Drawing.Point(155, 55);
            this.btnRemoveCard.Name = "btnRemoveCard";
            this.btnRemoveCard.Size = new System.Drawing.Size(71, 27);
            this.btnRemoveCard.TabIndex = 17;
            this.btnRemoveCard.Text = "Remove";
            this.btnRemoveCard.UseVisualStyleBackColor = true;
            this.btnRemoveCard.Click += new System.EventHandler(this.btnRemove_Click);
            // 
            // lbRemoveID
            // 
            this.lbRemoveID.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.lbRemoveID.AutoSize = true;
            this.lbRemoveID.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.lbRemoveID.ForeColor = System.Drawing.Color.Navy;
            this.lbRemoveID.Location = new System.Drawing.Point(17, 31);
            this.lbRemoveID.Name = "lbRemoveID";
            this.lbRemoveID.Size = new System.Drawing.Size(26, 19);
            this.lbRemoveID.TabIndex = 17;
            this.lbRemoveID.Text = "ID:";
            this.lbRemoveID.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // cbbRemoveID
            // 
            this.cbbRemoveID.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbbRemoveID.Font = new System.Drawing.Font("Segoe UI Semibold", 10F, System.Drawing.FontStyle.Bold);
            this.cbbRemoveID.FormattingEnabled = true;
            this.cbbRemoveID.Location = new System.Drawing.Point(71, 25);
            this.cbbRemoveID.MaxDropDownItems = 4;
            this.cbbRemoveID.Name = "cbbRemoveID";
            this.cbbRemoveID.Size = new System.Drawing.Size(155, 25);
            this.cbbRemoveID.TabIndex = 17;
            this.cbbRemoveID.DropDown += new System.EventHandler(this.cbbRemoveID_DropDown);
            // 
            // cardManagerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(830, 448);
            this.Controls.Add(this.groupBoxRemoveCard);
            this.Controls.Add(this.groupBoxListCards);
            this.Controls.Add(this.groupBoxUpdateCard);
            this.Controls.Add(this.groupBoxAddCard);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "cardManagerForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Card Management";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.cardManagerForm_FormClosing);
            this.groupBoxUpdateCard.ResumeLayout(false);
            this.groupBoxUpdateCard.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.groupBoxAddCard.ResumeLayout(false);
            this.groupBoxAddCard.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBoxListCards.ResumeLayout(false);
            this.groupBoxRemoveCard.ResumeLayout(false);
            this.groupBoxRemoveCard.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.ToolTip myToolTip;
        private System.Windows.Forms.ColumnHeader ID;
        private System.Windows.Forms.ColumnHeader userName;
        private System.Windows.Forms.ColumnHeader UUID;
        private System.Windows.Forms.ListView listViewCard;
        private System.Windows.Forms.Button btnSyncCard;
        private System.Windows.Forms.Button btnCardManagementOK;
        private System.Windows.Forms.GroupBox groupBoxUpdateCard;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.Button btnUpdateCard;
        private System.Windows.Forms.Label lbUpdateUUID;
        private System.Windows.Forms.ComboBox cbbUpdateUUID;
        private System.Windows.Forms.GroupBox groupBoxAddCard;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label lbNameAdd;
        private System.Windows.Forms.Button btnAddCard;
        private System.Windows.Forms.TextBox txtBoxAddID;
        private System.Windows.Forms.TextBox txtBoxAddName;
        private System.Windows.Forms.Label lbAddID;
        private System.Windows.Forms.GroupBox groupBoxListCards;
        private System.Windows.Forms.GroupBox groupBoxRemoveCard;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.Button btnRemoveCard;
        private System.Windows.Forms.Label lbRemoveID;
        private System.Windows.Forms.ComboBox cbbRemoveID;
        private System.Windows.Forms.Label lbUpdateName;
        private System.Windows.Forms.TextBox txtBoxUpdateID;
        private System.Windows.Forms.TextBox txtBoxUpdateName;
        private System.Windows.Forms.Label lbBoxUpdateID;
    }
}