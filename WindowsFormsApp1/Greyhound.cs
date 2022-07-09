using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace WindowsFormsApp1
{
    class Greyhound
    {
        public int StartingPosition;
        public int RacetrackLength;
        public PictureBox MyPictureBox;
        public int Location = 0;
        public Random MyRandom;
        public int distance;

        public bool Run()
        {
            Point currentLocation = MyPictureBox.Location;
            
            if(currentLocation.X + MyPictureBox.Width >= RacetrackLength)
            {
                return true;
            }
            else
            {
                currentLocation.X += distance;
                MyPictureBox.Location = currentLocation;

                return false;
            }
        
        }

        public void TakeStartingPosition()
        {
            Location = MyPictureBox.Location.Y;
            MyPictureBox.Location = new Point(StartingPosition, Location);
        }
    }
}
