using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace csAssignment_Random
{
    public partial class Form1 : Form
    {
        Random r = new Random();
        GroupBox[] GB = new GroupBox[5]; // 그룹 박스 
        RadioButton[,] Bogi = new RadioButton[5, 5];  // 5문제, 보기 5개
        Label[] Quiz = new Label[5];            //문제
        Label lbScore = new Label();     // 점수 표시 Label  
        Button button = new Button();  // Button 
        int Score = 0;                          // 점수 변수

        string[,] rand = new string[5, 6] { { "0", "0", "0", "0", "0", "0" }, { "0", "0", "0", "0", "0", "0" },
            { "0", "0", "0", "0", "0","0" }, { "0", "0", "0", "0", "0", "0" }, { "0", "0", "0", "0", "0", "0" } };


        public Form1()
        {
            InitializeComponent();

            string aa = "[문제 ";   // 1]  은 소스에서 추가 해야 함
            string[,] Question = new string[5, 6] {
            {"우리나라의 수도는?" ,"서울", "인천", "부산" , "광주", "서울"},
            {"인천대학교의 위치는?", "이천", "송도", "서울", "청주", "송도"},
            {"인천에 있는 산은 ?", "논산", "낙하산", "계양산", "묽은염산", "계양산"},
            {"다음 중 1 + 1은?", "1", "2", "3" , "4", "1" },
            {"숫자 정수의 타입은?", "int", "string", "float", "bool", "int"}
            };

            for (int i = 0; i < 5; i++)
            {
                int ran = r.Next(0, 5);
                for (int j = 0; j < 6; j++)
                {
                    rand[i, j] = Question[ran, j];
                }
                for (int k = 0; k < i; k++)
                {
                    if (rand[i, 0] == rand[k, 0])
                        i--;
                }
            }

            #region
            lbScore = new Label();
            this.lbScore.Name = "lbScore";
            this.lbScore.Text = "Score : ";
            this.lbScore.Size = new Size(90, 30);
            this.lbScore.AutoSize = true;
            this.lbScore.Location = new System.Drawing.Point(30, 750);
            this.Controls.Add(lbScore);
            #endregion

            #region
            this.button.Name = "btnSubmit";
            this.button.Text = "채점하기";
            this.button.Size = new Size(90, 30);
            this.button.AutoSize = true;
            this.button.Location = new System.Drawing.Point(180, 50);
            this.button.Click += new EventHandler(button_Click);
            this.Controls.Add(button);
            #endregion

            #region
            for (int n = 0; n < 3; n++)
            {
                GB[n] = new GroupBox();
                this.GB[n].AutoSize = true;
                this.GB[n].Location = new System.Drawing.Point(10, 10 + (n * 150));
                this.GB[n].Size = new Size(350, 120);
                this.GB[n].TabIndex = 0;
                this.GB[n].TabStop = false;
                this.GB[n].Text = aa + (n + 1) + "] " + rand[n, 0];
                this.Controls.Add(GB[n]);   //문제생성 끝

                for (int i = 0; i < 5; i++)
                {
                    Bogi[n, i] = new RadioButton();
                    this.Bogi[n, i].Location = new System.Drawing.Point(30, 30 + (i * 20));
                    this.Bogi[n, i].Size = new System.Drawing.Size(100, 20);
                    this.Bogi[n, i].Text = rand[n, i + 1];
                    if (i == 4)
                        Bogi[n, 4].Visible = false;
                    this.Controls.Add(Bogi[n, i]);
                }
            }
            #endregion

            void button_Click(object sender, EventArgs e)
            {
                Button button = sender as Button;
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 4; j++) //[4]는 정답!
                    {
                        if (Bogi[i, j].Checked == true
                                            && ((Bogi[i, j].Text == "서울")
                                            || Bogi[i, j].Text == "송도"
                                            || Bogi[i, j].Text == "계양산"
                                            || Bogi[i, j].Text == "1"
                                            || Bogi[i, j].Text == "int"))
                            Score += 1;
                    }
                }
                lbScore.Text = "Score : " + Convert.ToString(Score);
                Score = 0;
            }
        }
    }
}
