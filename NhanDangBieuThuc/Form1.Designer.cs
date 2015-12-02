namespace NhanDangBieuThuc
{
    partial class Form1
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
            this.ptb_image = new System.Windows.Forms.PictureBox();
            this.bbt_recognize = new System.Windows.Forms.Button();
            this.bbt_calculate = new System.Windows.Forms.Button();
            this.bbt_browser = new System.Windows.Forms.Button();
            this.lbl_ketqua = new System.Windows.Forms.Label();
            this.rtb_output = new System.Windows.Forms.RichTextBox();
            ((System.ComponentModel.ISupportInitialize)(this.ptb_image)).BeginInit();
            this.SuspendLayout();
            // 
            // ptb_image
            // 
            this.ptb_image.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ptb_image.Location = new System.Drawing.Point(12, 12);
            this.ptb_image.Name = "ptb_image";
            this.ptb_image.Size = new System.Drawing.Size(356, 237);
            this.ptb_image.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.ptb_image.TabIndex = 0;
            this.ptb_image.TabStop = false;
            // 
            // bbt_recognize
            // 
            this.bbt_recognize.Location = new System.Drawing.Point(386, 286);
            this.bbt_recognize.Name = "bbt_recognize";
            this.bbt_recognize.Size = new System.Drawing.Size(75, 24);
            this.bbt_recognize.TabIndex = 2;
            this.bbt_recognize.Text = "Recognize";
            this.bbt_recognize.UseVisualStyleBackColor = true;
            this.bbt_recognize.Click += new System.EventHandler(this.bbt_recognize_Click);
            // 
            // bbt_calculate
            // 
            this.bbt_calculate.Location = new System.Drawing.Point(497, 286);
            this.bbt_calculate.Name = "bbt_calculate";
            this.bbt_calculate.Size = new System.Drawing.Size(75, 24);
            this.bbt_calculate.TabIndex = 3;
            this.bbt_calculate.Text = "Calculate";
            this.bbt_calculate.UseVisualStyleBackColor = true;
            this.bbt_calculate.Click += new System.EventHandler(this.bbt_calculate_Click);
            // 
            // bbt_browser
            // 
            this.bbt_browser.Location = new System.Drawing.Point(12, 255);
            this.bbt_browser.Name = "bbt_browser";
            this.bbt_browser.Size = new System.Drawing.Size(75, 24);
            this.bbt_browser.TabIndex = 4;
            this.bbt_browser.Text = "Browser";
            this.bbt_browser.UseVisualStyleBackColor = true;
            this.bbt_browser.Click += new System.EventHandler(this.bbt_browser_Click);
            // 
            // lbl_ketqua
            // 
            this.lbl_ketqua.AutoSize = true;
            this.lbl_ketqua.Location = new System.Drawing.Point(393, 204);
            this.lbl_ketqua.Name = "lbl_ketqua";
            this.lbl_ketqua.Size = new System.Drawing.Size(0, 13);
            this.lbl_ketqua.TabIndex = 6;
            // 
            // rtb_output
            // 
            this.rtb_output.Location = new System.Drawing.Point(386, 12);
            this.rtb_output.Name = "rtb_output";
            this.rtb_output.Size = new System.Drawing.Size(335, 174);
            this.rtb_output.TabIndex = 7;
            this.rtb_output.Text = "";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(733, 319);
            this.Controls.Add(this.rtb_output);
            this.Controls.Add(this.lbl_ketqua);
            this.Controls.Add(this.bbt_browser);
            this.Controls.Add(this.bbt_calculate);
            this.Controls.Add(this.bbt_recognize);
            this.Controls.Add(this.ptb_image);
            this.Name = "Form1";
            this.Text = "Nhận dạng biểu thức";
            ((System.ComponentModel.ISupportInitialize)(this.ptb_image)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox ptb_image;
        private System.Windows.Forms.Button bbt_recognize;
        private System.Windows.Forms.Button bbt_calculate;
        private System.Windows.Forms.Button bbt_browser;
        private System.Windows.Forms.Label lbl_ketqua;
        private System.Windows.Forms.RichTextBox rtb_output;
    }
}

