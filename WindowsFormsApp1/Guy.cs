using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    class Guy
    {
        public string Name;
        public Bet MyBet;
        public int Cash;

        public RadioButton MyRadioButton;
        public Label MyLabel;

        public void UpdateLabels()
        {
            MyRadioButton.Text = this.Name + "가(이)" + this.Cash + "달러 가지고 있어";
            MyLabel.Text = this.MyBet.GetDescription();

            // Set my label to my bet’s description, and the label on my 
            // radio button to show my cash (“Joe has 43 bucks”) 
        }

        public void ClearBet()
        {
            MyBet.Amount = 0;
            MyRadioButton.Text = this.Name + "가(이)" + this.Cash + "가지고 있어";
            MyLabel.Text = this.Name + "가(이) 아직 배팅하지 않았어";
        }

        public bool PlaceBet(int Amount, int Dog)
        {
            MyBet = new Bet() { Amount = Amount, Dog = Dog, Bettor = this };

            if (this.Cash > MyBet.Amount)
            {
                this.UpdateLabels();
                return true;
            }
            else
            {
                return false;
            }
        }

        public void Collect(int Winner)
        {
            this.Cash += MyBet.PayOut(Winner);
        }
    }
}
