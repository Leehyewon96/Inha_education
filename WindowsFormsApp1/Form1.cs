using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        Random MyRandom = new Random(); //뭔지 모름
        Greyhound[] dogs = new Greyhound[4]; //그레이하운드 4개짜리 배열
        Guy[] guys = new Guy[3];//가이 3개짜리 배열


        public Form1()
        {
            InitializeComponent();      
            
            guys[0] = new Guy() { Cash = 50, Name = "Joe", MyBet = new Bet(), MyLabel = Joe_Label, MyRadioButton = rdb_Joe };
            guys[1] = new Guy() { Cash = 75, Name = "Bob", MyBet = new Bet(), MyLabel = Bob_Label, MyRadioButton = rdb_Bob };
            guys[2] = new Guy() { Cash = 45, Name = "Al", MyBet = new Bet(), MyLabel = Al_Label, MyRadioButton = rdb_Al };
        
            for(int i = 0; i < guys.Length; i++)
            {
                guys[i].MyBet.Amount = 0;
                guys[i].MyBet.Dog = 0;
                guys[i].MyBet.Bettor = guys[i];
                guys[i].UpdateLabels();
            }

            int x = 0;
            int locy = 0;

            while (x < 4)
            {
                dogs[x] = new Greyhound();

                dogs[x].RacetrackLength = pictureBox1.Width;
                dogs[x].StartingPosition = pictureBox1.Location.X;
                dogs[x].MyRandom = new Random();
                dogs[x].Location = 25 + locy;

                dogs[x].distance = MyRandom.Next(5,15);

                x = x + 1;
                locy += 60;
            }

            /*
            PicDog1.Parent = pictureBox1;
            PicDog1.BackColor = Color.Transparent;
            PicDog2.Parent = pictureBox1;
            PicDog2.BackColor = Color.Transparent;
            PicDog3.Parent = pictureBox1;
            PicDog3.BackColor = Color.Transparent;
            PicDog4.Parent = pictureBox1;
            PicDog4.BackColor = Color.Transparent;
            */

            dogs[0].MyPictureBox = PicDog1;
            dogs[1].MyPictureBox = PicDog2;
            dogs[2].MyPictureBox = PicDog3;
            dogs[3].MyPictureBox = PicDog4;

            // 하나 이상의 배팅이 되기 전까지는 레이스 버튼을 비활성화 시킨다
            btn_Race.Enabled = false;

            
            Label1.Text = "최소배팅 금액은 : " + (int)numericUpDown1.Value + "달러";



        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }


        private void btn_Race_Click(object sender, EventArgs e)
        {
            btn_Race.Enabled = false;
            btn_Bets.Enabled = false;

            bool winner = false;
            int winningDog = 0;

            while(!winner)
            {
                for(int i = 0; i < 4; i++)
                {
                    if(dogs[i].Run())
                    {
                        winner = true;
                        winningDog = i;
                    }
                    pictureBox1.Update();
                    System.Threading.Thread.Sleep(10);
                }                
            }


            MessageBox.Show("승리한 개는 " + (winningDog) + "!", "Race Over");

            for(int y = 0; y < guys.Length; y++)
            {
                if(guys[y].MyBet.Amount >= 5 && guys[y].Cash > 0)
                {
                    guys[y].Collect((winningDog));
                }
                guys[y].ClearBet();
            }

            for(int i = 0; i < 4; i++)
            {
                dogs[i].TakeStartingPosition();
                dogs[i].distance = MyRandom.Next(5,15);
            }

            numericUpDown1.Value = 5;
            numericUpDown2.Value = 1;
            rdb_Joe.Checked = true;

            btn_Bets.Enabled = true;
            btn_Race.Enabled = false;

            if(guys[0].Cash < numericUpDown1.Value && guys[1].Cash < numericUpDown1.Value && guys[2].Cash < numericUpDown1.Value)
            {
                MessageBox.Show("모든 사용자의 돈이 다 떨어졌어", "Game Over");
                btn_Bets.Enabled = false;
            }

        }

        

        private void btn_Bets_Click(object sender, EventArgs e)
        {
            bool betSucceded = false;
            if(rdb_Joe.Checked)
            {
                betSucceded = guys[0].PlaceBet((int)numericUpDown1.Value,(int)numericUpDown2.Value);
            }
            if (rdb_Bob.Checked)
            {
                betSucceded = guys[1].PlaceBet((int)numericUpDown1.Value, (int)numericUpDown2.Value);
            }
            if (rdb_Al.Checked)
            {
                betSucceded = guys[2].PlaceBet((int)numericUpDown1.Value, (int)numericUpDown2.Value);
            }

            if(betSucceded)
            {
                MessageBox.Show("배팅이 성공했다", "Bet Information");
                btn_Race.Enabled = true;
                numericUpDown1.Value = 5;
                numericUpDown2.Value = 1;
            }
            else
            {
                MessageBox.Show("배팅 실패", "Bet Information");

                numericUpDown1.Value = 5;
                numericUpDown2.Value = 1;
            }
        }

        

        private void rdb_Joe_CheckedChanged(object sender, EventArgs e)
        {
            lbl_who.Text = "Joe";
        }
        private void rdb_Bob_CheckedChanged(object sender, EventArgs e)
        {
            lbl_who.Text = "Bob";
        }
        private void rdb_Al_CheckedChanged(object sender, EventArgs e)
        {
            lbl_who.Text = "Al";
        }
    }
}
