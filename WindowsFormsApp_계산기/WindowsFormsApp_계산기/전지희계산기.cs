using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp_계산기
{
    public partial class 전지희계산기 : Form
    {
        Stack<string> left = new Stack<string>();
        Stack<string> right = new Stack<string>();  
        string buffer = ""; // 버퍼
        double result; 

        public 전지희계산기()
        {
            InitializeComponent();
        }

        private void bt_num_click(object sender, MouseEventArgs e)
        {
            Button myButton = (Button)sender; // 숫자 키 저장
            buffer += myButton.Text; // 버퍼에 저장
            textBox1.Text += myButton.Text; // 텍스트창 출력
        }

        private int GetRank(char operation) // 연산자 우선순위 리턴
        {
            if (operation == '!' || operation == '√' || operation == '^') // 우선순위 높음
                return 3;
            else if (operation == '*' || operation == '/' || operation == '%')
                return 2;
            else // 우선순위 낮음
                return 1;
        }

        private void bt_oper_click(object sender, MouseEventArgs e)
        {
            Button myButton = (Button)sender;  // 숫자 키 저장
            left.Push(buffer); // 입력 피연산자 - 왼쪽 스택에 저장
            buffer = "";
            textBox1.Text += myButton.Text; // 입력값 추가출력
            if (right.Count == 0) { right.Push(myButton.Text); } // 입력이 연산자 일 때 오른쪽 스택이 비어있다면 연산자를 오른쪽에 저장
            else // 스택이 비어있지 않다면
            {
                if (GetRank(myButton.Text[0]) > GetRank(right.Peek()[0])) // 오른쪽에 마지막으로 저장된 연산자보다 우선순위가 높은 경우
                {
                    right.Push(myButton.Text); // 오른쪽에 스택 저장
                }
                else // 오른쪽에 마지막으로 저장된 연산자보다 우선순위가 낮은 경우
                {
                    left.Push(right.Pop()); // 오른쪽 스택 -> 왼쪽 스택 이동
                    right.Push(myButton.Text); // 오른쪽에 연산자 저장
                }
            }
        }

        private void bt_clear_click(object sender, MouseEventArgs e)    //텍스트출력도 버퍼도 결과도 싹 지워주기
        {
            textBox1.Text = "";
            buffer = "";
            result = 0.0;
        }

        private void 전지희계산기_Load(object sender, EventArgs e)
        {
        }

        private void bt_calc_click(object sender, MouseEventArgs e)
        {
            Button myButton = (Button)sender;
            if (buffer.Length != 0) // 마지막 숫자를 왼쪽에 저장
            {
                left.Push(buffer);
            }
            while (right.Count != 0) // 오른쪽 연산자들을 왼쪽으로
            {
                left.Push(right.Pop());
            }
            while (left.Count != 0) // 연산식 반전
            {
                right.Push(left.Pop());
            }
            while (right.Count != 0) // 최종연산
            {
                if (!operOrNot(right.Peek()[0])) // 스택 가장 위 - 피연산자라면
                {
                    left.Push(right.Pop()); // 왼쪽으로
                }
                else // 스택 가장 위 - 연산자라면
                {
                    int n = Convert.ToInt32(left.Pop());
                    switch (right.Pop()[0]) 
                    {
                        case '+': result = Convert.ToInt32(left.Pop()) + n; break;
                        case '-': result = Convert.ToInt32(left.Pop()) - n; break;
                        case '*': result = Convert.ToInt32(left.Pop()) * n; break;
                        case '/': result = Convert.ToInt32(left.Pop()) / n; break;
                        case '%': result = Convert.ToInt32(left.Pop()) % n; break;
                        case '!':
                            {
                                int a = 1;
                                for (int i = n; i > 1; i--)
                                {
                                    a *= i;
                                }
                                result = a;
                                break;
                            }
                        case '√':
                            {
                                result = Math.Sqrt(n); break;
                            }
                        case '^':
                            {
                                int a = Convert.ToInt32(left.Pop());
                                int b = 1;
                                for (int i = n; i > 0; i--)
                                {
                                    b *= a;
                                }
                                result = b;
                                break;
                            }
                    }
                    left.Push(Convert.ToString(result)); // 한번의 연산이 끝나고 나온 결과는 왼쪽의 가장 위에 저장된다.
                }
            }
            textBox1.Text += myButton.Text + result.ToString(); // 텍스트박스에 결과 추가출력
            buffer = Convert.ToString(result);
        }
        private bool operOrNot(char oper) // 연산자이면 true
        {
            if (oper == '*' || oper == '/' || oper == '!'|| oper == '√'
                || oper == '^' || oper == '%' || oper == '+' || oper == '-')
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
