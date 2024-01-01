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
    public partial class processingForm : Form
    {
        private cardManagerForm _cardParentForm;
        private mainDashboard _mainParentForm;
        public processingForm(cardManagerForm cardParentForm)
        {
            InitializeComponent();
            _cardParentForm = cardParentForm;
        }

        public processingForm(mainDashboard mainParentForm)
        {
            InitializeComponent();
            _mainParentForm = mainParentForm;
        }

        public void ShowCentered(Form _parentForm)
        {
            int x = _parentForm.Location.X + (_parentForm.Width - Width) / 2;
            int y = _parentForm.Location.Y + (_parentForm.Height - Height) / 2;
            Location = new Point(x, y);
            Show(_parentForm);
        }

    }
}
