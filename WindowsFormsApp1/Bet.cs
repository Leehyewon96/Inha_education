using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    class Bet
    {
        public int Amount;
        public int Dog;
        public Guy Bettor;

        public string GetDescription()
        {
            if (Amount == 0 || Bettor.MyBet.Amount > Bettor.Cash)
                return Bettor.Name + "가(이) 아직 배팅하지 않았어";
            else
                return Bettor.Name + "가(이)" + Bettor.MyBet.Amount + "달러를 " + (Bettor.MyBet.Dog) + "에게 배팅했어";
        }

        public int PayOut(int Winner) //선택한 개의 번호가 맞을 경우 Betting 금액을 넘기고, 반대 경우에는 - 금액을 넘긴다
        {
            if (Bettor.MyBet.Dog == Winner)
                return Amount;
            else
                return -Amount;
        }
    }
}
