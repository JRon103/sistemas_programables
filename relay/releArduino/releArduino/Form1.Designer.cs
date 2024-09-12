namespace releArduino
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            btnRele = new Button();
            comboBoxList = new ComboBox();
            SuspendLayout();
            // 
            // btnRele
            // 
            btnRele.BackColor = Color.IndianRed;
            btnRele.Font = new Font("Segoe UI", 25F);
            btnRele.Location = new Point(215, 82);
            btnRele.Name = "btnRele";
            btnRele.Size = new Size(242, 129);
            btnRele.TabIndex = 0;
            btnRele.Text = "Relevador";
            btnRele.UseVisualStyleBackColor = false;
            btnRele.Click += button1_Click;
            // 
            // comboBoxList
            // 
            comboBoxList.FormattingEnabled = true;
            comboBoxList.Location = new Point(601, 129);
            comboBoxList.Name = "comboBoxList";
            comboBoxList.Size = new Size(151, 28);
            comboBoxList.TabIndex = 1;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(comboBoxList);
            Controls.Add(btnRele);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ResumeLayout(false);
        }

        #endregion

        private Button btnRele;
        private ComboBox comboBoxList;
    }
}
