using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace projectGUIApp
{
    public partial class testForm : Form
    {
        private cardManagerForm _parentForm;

        public testForm(cardManagerForm parentForm)
        {
            InitializeComponent();
            _parentForm = parentForm;

        }
        public void ShowCentered()
        {
            int x = _parentForm.Location.X + (_parentForm.Width - Width) / 2;
            int y = _parentForm.Location.Y + (_parentForm.Height - Height) / 2;
            Location = new Point(x, y);
            Show(_parentForm);
        }
    }
}
