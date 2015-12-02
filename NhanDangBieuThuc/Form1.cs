using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ClassLibrary1;

namespace NhanDangBieuThuc
{
    public partial class Form1 : Form
    {
        Class1 temp=new Class1();
        string FileName;

        public Form1()
        {
            InitializeComponent();
        }

        private void bbt_browser_Click(object sender, EventArgs e)
        {
            OpenFileDialog dl = new OpenFileDialog();
            dl.Filter = "File png|*.png";
            if (dl.ShowDialog() == DialogResult.OK)
            {
                FileName= dl.FileNames[0];
                ptb_image.Image = new Bitmap(dl.FileNames[0]);
            }
        }

        private void bbt_recognize_Click(object sender, EventArgs e)
        {
          rtb_output.Text = temp.TimChuoiDauRa(FileName);
        }

        private void bbt_calculate_Click(object sender, EventArgs e)
        {
            lbl_ketqua.Text = temp.tinh(rtb_output.Text).ToString();
        }
    }
}
