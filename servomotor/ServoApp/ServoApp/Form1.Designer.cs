namespace ServoApp
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.trackBar = new System.Windows.Forms.TrackBar();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.comboBox = new System.Windows.Forms.ComboBox();
            this.button = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.trackBar);
            this.groupBox1.Location = new System.Drawing.Point(30, 26);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(534, 164);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Grados";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(484, 63);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(25, 16);
            this.label5.TabIndex = 3;
            this.label5.Text = "90°";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(25, 59);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 16);
            this.label4.TabIndex = 2;
            this.label4.Text = "-90°";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.SystemColors.Control;
            this.label3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label3.Location = new System.Drawing.Point(225, 122);
            this.label3.MinimumSize = new System.Drawing.Size(70, 20);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(70, 20);
            this.label3.TabIndex = 1;
            // 
            // trackBar
            // 
            this.trackBar.Location = new System.Drawing.Point(68, 56);
            this.trackBar.Maximum = 180;
            this.trackBar.Name = "trackBar";
            this.trackBar.Size = new System.Drawing.Size(409, 56);
            this.trackBar.SmallChange = 5;
            this.trackBar.TabIndex = 0;
            this.trackBar.Scroll += new System.EventHandler(this.trackBar_Scroll);
            this.trackBar.ValueChanged += new System.EventHandler(this.trackBar_Scroll);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.comboBox);
            this.groupBox2.Controls.Add(this.button);
            this.groupBox2.Location = new System.Drawing.Point(591, 26);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(200, 164);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "COM";
            // 
            // comboBox
            // 
            this.comboBox.FormattingEnabled = true;
            this.comboBox.Location = new System.Drawing.Point(39, 56);
            this.comboBox.Name = "comboBox";
            this.comboBox.Size = new System.Drawing.Size(121, 24);
            this.comboBox.TabIndex = 1;
            this.comboBox.DropDown += new System.EventHandler(this.combobox_DropDown);
            this.comboBox.SelectedIndexChanged += new System.EventHandler(this.comboBox_SelectedIndexChanged);
            // 
            // button
            // 
            this.button.Location = new System.Drawing.Point(39, 101);
            this.button.Name = "button";
            this.button.Size = new System.Drawing.Size(121, 41);
            this.button.TabIndex = 0;
            this.button.Text = "Conectar";
            this.button.UseVisualStyleBackColor = true;
            this.button.Click += new System.EventHandler(this.button_Click);
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(861, 248);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox_grados;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox_puertos;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TrackBar trackBar;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.ComboBox comboBox;
        private System.Windows.Forms.Button button;
        //private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
    }
}

