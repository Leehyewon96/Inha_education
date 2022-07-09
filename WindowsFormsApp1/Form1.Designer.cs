
namespace WindowsFormsApp1
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.PicDog1 = new System.Windows.Forms.PictureBox();
            this.PicDog2 = new System.Windows.Forms.PictureBox();
            this.PicDog3 = new System.Windows.Forms.PictureBox();
            this.PicDog4 = new System.Windows.Forms.PictureBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btn_Race = new System.Windows.Forms.Button();
            this.lbl_who = new System.Windows.Forms.Label();
            this.numericUpDown2 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.Label1 = new System.Windows.Forms.Label();
            this.Al_Label = new System.Windows.Forms.Label();
            this.Bob_Label = new System.Windows.Forms.Label();
            this.Joe_Label = new System.Windows.Forms.Label();
            this.textBox8 = new System.Windows.Forms.TextBox();
            this.btn_Bets = new System.Windows.Forms.Button();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.rdb_Al = new System.Windows.Forms.RadioButton();
            this.rdb_Bob = new System.Windows.Forms.RadioButton();
            this.rdb_Joe = new System.Windows.Forms.RadioButton();
            ((System.ComponentModel.ISupportInitialize)(this.PicDog1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.PicDog2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.PicDog3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.PicDog4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.SuspendLayout();
            // 
            // PicDog1
            // 
            this.PicDog1.Image = ((System.Drawing.Image)(resources.GetObject("PicDog1.Image")));
            this.PicDog1.Location = new System.Drawing.Point(25, 21);
            this.PicDog1.Name = "PicDog1";
            this.PicDog1.Size = new System.Drawing.Size(76, 23);
            this.PicDog1.TabIndex = 0;
            this.PicDog1.TabStop = false;
            // 
            // PicDog2
            // 
            this.PicDog2.Image = ((System.Drawing.Image)(resources.GetObject("PicDog2.Image")));
            this.PicDog2.Location = new System.Drawing.Point(25, 67);
            this.PicDog2.Name = "PicDog2";
            this.PicDog2.Size = new System.Drawing.Size(76, 23);
            this.PicDog2.TabIndex = 1;
            this.PicDog2.TabStop = false;
            // 
            // PicDog3
            // 
            this.PicDog3.Image = ((System.Drawing.Image)(resources.GetObject("PicDog3.Image")));
            this.PicDog3.Location = new System.Drawing.Point(25, 119);
            this.PicDog3.Name = "PicDog3";
            this.PicDog3.Size = new System.Drawing.Size(76, 23);
            this.PicDog3.TabIndex = 2;
            this.PicDog3.TabStop = false;
            // 
            // PicDog4
            // 
            this.PicDog4.Image = ((System.Drawing.Image)(resources.GetObject("PicDog4.Image")));
            this.PicDog4.Location = new System.Drawing.Point(25, 169);
            this.PicDog4.Name = "PicDog4";
            this.PicDog4.Size = new System.Drawing.Size(76, 23);
            this.PicDog4.TabIndex = 3;
            this.PicDog4.TabStop = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(12, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(604, 203);
            this.pictureBox1.TabIndex = 4;
            this.pictureBox1.TabStop = false;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btn_Race);
            this.groupBox1.Controls.Add(this.lbl_who);
            this.groupBox1.Controls.Add(this.numericUpDown2);
            this.groupBox1.Controls.Add(this.numericUpDown1);
            this.groupBox1.Controls.Add(this.Label1);
            this.groupBox1.Controls.Add(this.Al_Label);
            this.groupBox1.Controls.Add(this.Bob_Label);
            this.groupBox1.Controls.Add(this.Joe_Label);
            this.groupBox1.Controls.Add(this.textBox8);
            this.groupBox1.Controls.Add(this.btn_Bets);
            this.groupBox1.Controls.Add(this.textBox2);
            this.groupBox1.Controls.Add(this.rdb_Al);
            this.groupBox1.Controls.Add(this.rdb_Bob);
            this.groupBox1.Controls.Add(this.rdb_Joe);
            this.groupBox1.Location = new System.Drawing.Point(12, 240);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(604, 210);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Betting Parlor";
            // 
            // btn_Race
            // 
            this.btn_Race.BackColor = System.Drawing.SystemColors.ControlLight;
            this.btn_Race.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.btn_Race.Location = new System.Drawing.Point(510, 171);
            this.btn_Race.Name = "btn_Race";
            this.btn_Race.Size = new System.Drawing.Size(58, 19);
            this.btn_Race.TabIndex = 23;
            this.btn_Race.Text = "Race !";
            this.btn_Race.UseVisualStyleBackColor = false;
            this.btn_Race.Click += new System.EventHandler(this.btn_Race_Click);
            // 
            // lbl_who
            // 
            this.lbl_who.AutoSize = true;
            this.lbl_who.Location = new System.Drawing.Point(18, 171);
            this.lbl_who.Name = "lbl_who";
            this.lbl_who.Size = new System.Drawing.Size(29, 12);
            this.lbl_who.TabIndex = 22;
            this.lbl_who.Text = "who";
            // 
            // numericUpDown2
            // 
            this.numericUpDown2.Location = new System.Drawing.Point(377, 169);
            this.numericUpDown2.Maximum = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.numericUpDown2.Name = "numericUpDown2";
            this.numericUpDown2.Size = new System.Drawing.Size(98, 21);
            this.numericUpDown2.TabIndex = 21;
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Location = new System.Drawing.Point(138, 169);
            this.numericUpDown1.Minimum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(98, 21);
            this.numericUpDown1.TabIndex = 20;
            this.numericUpDown1.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
            // 
            // Label1
            // 
            this.Label1.AutoSize = true;
            this.Label1.Location = new System.Drawing.Point(13, 21);
            this.Label1.Name = "Label1";
            this.Label1.Size = new System.Drawing.Size(38, 12);
            this.Label1.TabIndex = 19;
            this.Label1.Text = "label1";
            // 
            // Al_Label
            // 
            this.Al_Label.AutoSize = true;
            this.Al_Label.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Al_Label.Location = new System.Drawing.Point(314, 103);
            this.Al_Label.Name = "Al_Label";
            this.Al_Label.Size = new System.Drawing.Size(50, 14);
            this.Al_Label.TabIndex = 18;
            this.Al_Label.Text = "Al\'s bet";
            // 
            // Bob_Label
            // 
            this.Bob_Label.AutoSize = true;
            this.Bob_Label.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Bob_Label.Location = new System.Drawing.Point(314, 81);
            this.Bob_Label.Name = "Bob_Label";
            this.Bob_Label.Size = new System.Drawing.Size(61, 14);
            this.Bob_Label.TabIndex = 17;
            this.Bob_Label.Text = "Bob\'s bet";
            // 
            // Joe_Label
            // 
            this.Joe_Label.AutoSize = true;
            this.Joe_Label.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Joe_Label.Location = new System.Drawing.Point(314, 57);
            this.Joe_Label.Name = "Joe_Label";
            this.Joe_Label.Size = new System.Drawing.Size(59, 14);
            this.Joe_Label.TabIndex = 16;
            this.Joe_Label.Text = "Joe\'s bet";
            // 
            // textBox8
            // 
            this.textBox8.BackColor = System.Drawing.SystemColors.Control;
            this.textBox8.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox8.Font = new System.Drawing.Font("굴림", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.textBox8.ForeColor = System.Drawing.SystemColors.WindowText;
            this.textBox8.Location = new System.Drawing.Point(242, 176);
            this.textBox8.Name = "textBox8";
            this.textBox8.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.textBox8.Size = new System.Drawing.Size(129, 14);
            this.textBox8.TabIndex = 11;
            this.textBox8.Text = "bucks on dog number";
            // 
            // btn_Bets
            // 
            this.btn_Bets.BackColor = System.Drawing.SystemColors.ControlLight;
            this.btn_Bets.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.btn_Bets.Location = new System.Drawing.Point(62, 168);
            this.btn_Bets.Name = "btn_Bets";
            this.btn_Bets.Size = new System.Drawing.Size(58, 19);
            this.btn_Bets.TabIndex = 9;
            this.btn_Bets.Text = "Bets";
            this.btn_Bets.UseVisualStyleBackColor = false;
            this.btn_Bets.Click += new System.EventHandler(this.btn_Bets_Click);
            // 
            // textBox2
            // 
            this.textBox2.BackColor = System.Drawing.SystemColors.Control;
            this.textBox2.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox2.Font = new System.Drawing.Font("굴림", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.textBox2.ForeColor = System.Drawing.SystemColors.WindowText;
            this.textBox2.Location = new System.Drawing.Point(314, 20);
            this.textBox2.Name = "textBox2";
            this.textBox2.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.textBox2.Size = new System.Drawing.Size(39, 14);
            this.textBox2.TabIndex = 4;
            this.textBox2.Text = "Bets";
            // 
            // rdb_Al
            // 
            this.rdb_Al.AutoSize = true;
            this.rdb_Al.Location = new System.Drawing.Point(22, 101);
            this.rdb_Al.Name = "rdb_Al";
            this.rdb_Al.Size = new System.Drawing.Size(34, 16);
            this.rdb_Al.TabIndex = 3;
            this.rdb_Al.TabStop = true;
            this.rdb_Al.Text = "Al";
            this.rdb_Al.UseVisualStyleBackColor = true;
            this.rdb_Al.CheckedChanged += new System.EventHandler(this.rdb_Al_CheckedChanged);
            // 
            // rdb_Bob
            // 
            this.rdb_Bob.AutoSize = true;
            this.rdb_Bob.Location = new System.Drawing.Point(22, 79);
            this.rdb_Bob.Name = "rdb_Bob";
            this.rdb_Bob.Size = new System.Drawing.Size(45, 16);
            this.rdb_Bob.TabIndex = 2;
            this.rdb_Bob.TabStop = true;
            this.rdb_Bob.Text = "Bob";
            this.rdb_Bob.UseVisualStyleBackColor = true;
            this.rdb_Bob.CheckedChanged += new System.EventHandler(this.rdb_Bob_CheckedChanged);
            // 
            // rdb_Joe
            // 
            this.rdb_Joe.AutoSize = true;
            this.rdb_Joe.Location = new System.Drawing.Point(22, 57);
            this.rdb_Joe.Name = "rdb_Joe";
            this.rdb_Joe.Size = new System.Drawing.Size(43, 16);
            this.rdb_Joe.TabIndex = 1;
            this.rdb_Joe.TabStop = true;
            this.rdb_Joe.Text = "Joe";
            this.rdb_Joe.UseVisualStyleBackColor = true;
            this.rdb_Joe.CheckedChanged += new System.EventHandler(this.rdb_Joe_CheckedChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(638, 476);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.PicDog4);
            this.Controls.Add(this.PicDog3);
            this.Controls.Add(this.PicDog2);
            this.Controls.Add(this.PicDog1);
            this.Controls.Add(this.pictureBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.PicDog1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.PicDog2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.PicDog3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.PicDog4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox PicDog1;
        private System.Windows.Forms.PictureBox PicDog2;
        private System.Windows.Forms.PictureBox PicDog3;
        private System.Windows.Forms.PictureBox PicDog4;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rdb_Al;
        private System.Windows.Forms.RadioButton rdb_Bob;
        private System.Windows.Forms.RadioButton rdb_Joe;
        private System.Windows.Forms.TextBox textBox8;
        private System.Windows.Forms.Button btn_Bets;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label Joe_Label;
        private System.Windows.Forms.Label Al_Label;
        private System.Windows.Forms.Label Bob_Label;
        private System.Windows.Forms.Label Label1;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.NumericUpDown numericUpDown2;
        private System.Windows.Forms.Label lbl_who;
        private System.Windows.Forms.Button btn_Race;
    }
}

