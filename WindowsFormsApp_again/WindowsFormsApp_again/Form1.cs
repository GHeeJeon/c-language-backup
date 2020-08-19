using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp_again
{

    public partial class Form1 : Form
    {
        Random r = new Random();
        GroupBox[] GB = new GroupBox[5]; // 그룹 박스 
        RadioButton[,] Bogi = new RadioButton[5, 5];  // 5문제, 보기 5개: 0, 1, 2, 3, 4(정답)
        Label[] Quiz = new Label[5];            //문제
        Label lbScore = new Label();     // 점수 표시 Label  
        Button button = new Button();  // Button 
        int Score = 0;
        string[,] rand = new string[5, 6] { { "0", "0", "0", "0", "0", "0" }, { "0", "0", "0", "0", "0", "0" },
            { "0", "0", "0", "0", "0","0" }, { "0", "0", "0", "0", "0", "0" }, { "0", "0", "0", "0", "0", "0" } };
        string[,] rand_A = new string[3, 4] { { "0", "0", "0", "0" }, { "0", "0", "0", "0" }, { "0", "0", "0", "0" } };
        public Form1()
        {
            InitializeComponent();

            string aa = "[문제 ";   // 1]  은 소스에서 추가 해야 함
            string[,] Question = new string[5, 6] {
            {"우리나라의 수도는?" ,"서울", "인천", "부산" , "광주", "서울"},
            {"인천대학교의 위치는?", "이천", "송도", "서울", "청주", "송도"},
            {"인천에 있는 산은 ?", "논산", "낙하산", "계양산", "묽은염산", "계양산"},
            {"다음 중 1 + 1은?", "4", "1", "3" , "2", "2" },
            {"숫자 정수의 타입은?", "float", "string", "int", "bool", "int"}
            };

            for (int i = 0; i < 3; i++) //문제 섞기, 3문제
            {
                int ran_Q = r.Next(0, 5);   //총 5문제
                for (int j = 0; j < 6; j++) //문제, 보기 답 넣기
                {
                    rand[i, j] = Question[ran_Q, j];
                }
                for (int k = 0; k < i; k++) //중복검토
                {
                    if (rand[i, 0] == rand[k, 0])
                        i--;
                }
            }   //전체랜덤 세팅 완료, 보기랜덤 필요

            for (int i = 0; i < 3; i++) //문제 섞기, 3문제
            {
                int j;
                int ran_A = r.Next(0, 4);    //보기 순서는 랜덤, 보기는 4개
                for (j = 0; j < 4; j++)  //총 4개의 보기
                {
                    rand_A[i, j] = Question[i, ran_A ];
                    
                }
                for (int k = 0; k < j; k++)   //중복검토
                {
                    if (rand[i, j] == rand[i, k])
                        j--;
                }
            }

            #region
            this.button.Name = "btnSubmit";
            this.button.Text = "채점하기";
            this.button.Size = new Size(90, 30);
            this.button.AutoSize = true;
            this.button.Location = new System.Drawing.Point(180, 550);
            this.button.Click += new EventHandler(button_Click);
            this.Controls.Add(button);
            #endregion

            #region
            lbScore = new Label();
            this.lbScore.Name = "lbScore";
            this.lbScore.Text = "Score: ";
            this.lbScore.Size = new Size(90, 30);
            this.lbScore.AutoSize = true;
            this.lbScore.Location = new System.Drawing.Point(30, 550);
            this.Controls.Add(lbScore);
            #endregion

            #region
            for (int n = 0; n < 3; n++)
            {
                GB[n] = new GroupBox();
                this.GB[n].AutoSize = true;
                this.GB[n].Location = new System.Drawing.Point(10, 10 + (n * 150));
                this.GB[n].Size = new System.Drawing.Size(350, 120);
                this.GB[n].TabIndex = 0;
                this.GB[n].TabStop = false;
                this.GB[n].Text = aa + (n + 1) + "]  " + rand[n, 0];
                this.Controls.Add(GB[n]);

                for (int i = 0; i < 5; i++)
                {
                    Bogi[n, i] = new RadioButton();
                    this.Bogi[n, i].Location = new System.Drawing.Point(30, 30 + (i * 20)); //문제 위치 설정하기
                    this.Bogi[n, i].Size = new System.Drawing.Size(100, 20);
                    this.Bogi[n, i].Text = rand[n, i + 1];

                    if (i == 4)
                        Bogi[n, 4].Visible = false; //정답 숨기기
                    this.Controls.Add(Bogi[n, i]);
                    this.GB[n].Controls.Add(this.Bogi[n, i]);
                }
            }
            #endregion
            void button_Click(object sender, EventArgs e)
            {
                Button button = sender as Button;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if ((Bogi[i, j].Checked == true)
                            && (Bogi[i, j].Text == rand[i, 5]))
                            Score += 1;
                    }
                }
                lbScore.Text = "Score: " + Convert.ToString(Score);
                Score = 0;
            }
        }
    }
}
