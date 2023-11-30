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
            this.Name = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.UUID = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.label10 = new System.Windows.Forms.Label();
            this.listViewCard = new System.Windows.Forms.ListView();
            this.btnAddCard = new System.Windows.Forms.Button();
            this.btnRemoveCard = new System.Windows.Forms.Button();
            this.btnUpdateCard = new System.Windows.Forms.Button();
            this.btnSync = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
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
            // Name
            // 
            this.Name.Text = "Name";
            this.Name.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.Name.Width = 293;
            // 
            // UUID
            // 
            this.UUID.Text = "UUID";
            this.UUID.Width = 134;
            // 
            // label10
            // 
            this.label10.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.label10.ForeColor = System.Drawing.Color.Navy;
            this.label10.Location = new System.Drawing.Point(12, 9);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(88, 19);
            this.label10.TabIndex = 36;
            this.label10.Text = "List of Cards:";
            this.label10.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // listViewCard
            // 
            this.listViewCard.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.UUID,
            this.Name,
            this.ID});
            this.listViewCard.Font = new System.Drawing.Font("Segoe UI", 9.25F);
            this.listViewCard.ForeColor = System.Drawing.SystemColors.WindowText;
            this.listViewCard.HideSelection = false;
            this.listViewCard.Location = new System.Drawing.Point(16, 31);
            this.listViewCard.Name = "listViewCard";
            this.listViewCard.Size = new System.Drawing.Size(543, 243);
            this.listViewCard.TabIndex = 32;
            this.listViewCard.UseCompatibleStateImageBehavior = false;
            this.listViewCard.View = System.Windows.Forms.View.Details;
            // 
            // btnAddCard
            // 
            this.btnAddCard.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.btnAddCard.ForeColor = System.Drawing.Color.MediumBlue;
            this.btnAddCard.Image = global::projectGUIApp.Properties.Resources.icon_add;
            this.btnAddCard.Location = new System.Drawing.Point(575, 31);
            this.btnAddCard.Name = "btnAddCard";
            this.btnAddCard.Size = new System.Drawing.Size(108, 27);
            this.btnAddCard.TabIndex = 44;
            this.btnAddCard.Text = "Add";
            this.btnAddCard.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnAddCard.UseVisualStyleBackColor = true;
            this.btnAddCard.Click += new System.EventHandler(this.btnAddCard_Click);
            // 
            // btnRemoveCard
            // 
            this.btnRemoveCard.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.btnRemoveCard.ForeColor = System.Drawing.Color.MediumBlue;
            this.btnRemoveCard.Image = global::projectGUIApp.Properties.Resources.icon_remove;
            this.btnRemoveCard.Location = new System.Drawing.Point(575, 64);
            this.btnRemoveCard.Name = "btnRemoveCard";
            this.btnRemoveCard.Size = new System.Drawing.Size(108, 27);
            this.btnRemoveCard.TabIndex = 45;
            this.btnRemoveCard.Text = "Remove";
            this.btnRemoveCard.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnRemoveCard.UseVisualStyleBackColor = true;
            // 
            // btnUpdateCard
            // 
            this.btnUpdateCard.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.btnUpdateCard.ForeColor = System.Drawing.Color.MediumBlue;
            this.btnUpdateCard.Image = ((System.Drawing.Image)(resources.GetObject("btnUpdateCard.Image")));
            this.btnUpdateCard.Location = new System.Drawing.Point(575, 97);
            this.btnUpdateCard.Name = "btnUpdateCard";
            this.btnUpdateCard.Size = new System.Drawing.Size(108, 27);
            this.btnUpdateCard.TabIndex = 46;
            this.btnUpdateCard.Text = "Update";
            this.btnUpdateCard.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnUpdateCard.UseVisualStyleBackColor = true;
            // 
            // btnSync
            // 
            this.btnSync.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.btnSync.ForeColor = System.Drawing.Color.MediumBlue;
            this.btnSync.Image = ((System.Drawing.Image)(resources.GetObject("btnSync.Image")));
            this.btnSync.Location = new System.Drawing.Point(337, 280);
            this.btnSync.Name = "btnSync";
            this.btnSync.Size = new System.Drawing.Size(108, 27);
            this.btnSync.TabIndex = 47;
            this.btnSync.Text = "Sync";
            this.btnSync.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnSync.UseVisualStyleBackColor = true;
            // 
            // btnOK
            // 
            this.btnOK.Font = new System.Drawing.Font("Segoe UI", 10.25F);
            this.btnOK.ForeColor = System.Drawing.Color.MediumBlue;
            this.btnOK.Image = ((System.Drawing.Image)(resources.GetObject("btnOK.Image")));
            this.btnOK.Location = new System.Drawing.Point(451, 280);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(108, 27);
            this.btnOK.TabIndex = 48;
            this.btnOK.Text = "OK";
            this.btnOK.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnOK.UseVisualStyleBackColor = true;
            // 
            // cardManagerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(695, 317);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.btnSync);
            this.Controls.Add(this.btnUpdateCard);
            this.Controls.Add(this.btnRemoveCard);
            this.Controls.Add(this.btnAddCard);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.listViewCard);
            this.Name.Name = "cardManagerForm";
            this.Text = "cardManagerForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ToolTip myToolTip;
        private System.Windows.Forms.ColumnHeader ID;
        private System.Windows.Forms.ColumnHeader Name;
        private System.Windows.Forms.ColumnHeader UUID;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.ListView listViewCard;
        private System.Windows.Forms.Button btnAddCard;
        private System.Windows.Forms.Button btnRemoveCard;
        private System.Windows.Forms.Button btnUpdateCard;
        private System.Windows.Forms.Button btnSync;
        private System.Windows.Forms.Button btnOK;
    }
}