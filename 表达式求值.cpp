#include <iostream>
#include <stdio.h>
#include <stack>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;
#define MAXSIZE 100 //栈空间的初始分配量

typedef struct{
    char *base;	//栈底指针
    char *top;	//栈顶指针
    int stacksize;	//栈可用的最大容量
}Stack_char;

typedef struct{
    double *base;	//栈底指针
    double *top;	//栈顶指针
    int stacksize;	//栈可用的最大容量
}Stack_double;

template <typename Stack ,typename any>
//构建栈
int Create_Stack(Stack &s,any type)
{
    any c = type;
    s.base = new any[MAXSIZE];  //给栈分配空间
    if(!s.base) return 1;   //分配失败
    s.top = s.base; //top和base指向同一位置
    s.stacksize = MAXSIZE;  //stack标记为栈的最大长度
    return 0;
}

template <typename Stack ,typename any>
//向栈里压入元素
double Push_Stack(Stack &s,any c)
{
    if(s.top-s.base==s.stacksize){  //栈满
        return 1;
    }
    *s.top++ = c;   //压入栈顶，栈顶指针加1
    return 0;
}
template <typename Stack>
//元素出栈（删除）
int Pop_Stack(Stack &s)
{
    if(s.top==s.base){  //栈空
        return 1;
    }
    --s.top;   //栈顶元素赋给c
}
template <typename Stack>
//获取栈顶元素（不删除）
double Get_Stack(Stack &s)
{
    if(s.top!=s.base)   //栈非空
    {
        return *(s.top-1);
    }
}

//运算符比较函数
char Compare(char a,char b){
    char priority[7][7]={
            {'>','>','<','<','<','>','>'},
            {'>','>','<','<','<','>','>'},
            {'>','>','>','>','<','>','>'},
            {'>','>','>','>','<','>','>'},
            {'<','<','<','<','<','=','0'},  //这一行的0表示左右括号相遇
            {'>','>','>','>','0','>','>'},  //其余的0表示语法错误
            {'<','<','<','<','<','0','='}   //这一行的=表示整个表达式求值已完成
    };
    int i,j;    //行，列
    switch(a){  //跳转到行对应的符号
        case'+':i=0;break;
        case'-':i=1;break;
        case'*':i=2;break;
        case'/':i=3;break;
        case'(':i=4;break;
        case')':i=5;break;
        case'#':i=6;break;   // # 是表达式的结束符
    }
    switch(b){  //跳转到列对应的符号
        case'+':j=0;break;
        case'-':j=1;break;
        case'*':j=2;break;
        case'/':j=3;break;
        case'(':j=4;break;
        case')':j=5;break;
        case'#':j=6;break;
    }
    return priority[i][j];
}

//运算函数
double Operate(double m,double n,char x){
    if(x=='+')
        return m+n;
    if(x=='-')
        return n-m;
    if(x=='*')
        return m*n;
    if(x=='/')
        return n/m;
}

int main(){

    Stack_char op;  //创建运算符栈
    Stack_double num;   //创建数字栈

    double a = 0;
    char b = 'a';
    Create_Stack(num,a);    //初始化栈
    Create_Stack(op,b);

    Push_Stack(op,'#'); //在运算符栈压入#
    char end[2]="#";    //尾部有\0
    char s[MAXSIZE];
    cout << "请输入运算式：";
    cin>>s;
    strcat(s,end);// 运算式尾部加#
    char c=s[0];
    int k=1;
    while(c!='#'||Get_Stack(op)!='#'){  //表达式未读完或者运算未完
        double y=0.0;
        double z=0.0;
        int count=0;
        if(c>='0'&&c<='9'){
            while(c>='0'&&c<='9'){  // 读入连续的数字
                y=y*10+(c-'0');
                c=s[k++];
                if(c=='.'){ //读入小数点
                    c=s[k++];
                    while (c>='0'&&c<='9'){
                        ++count;
                        z=z+pow(0.1,count)*(c-'0');
                        c=s[k++];
                    }
                }
            }
            Push_Stack(num,y+z);  // 把读进的数字入数字栈
        }
        else{
            switch(Compare(Get_Stack(op),c))
            {
                case'<':  //栈顶元素优先权低
                    Push_Stack(op,c);
                    c=s[k++];
                    break;
                case'=':
                    Pop_Stack(op);  //括号匹配成功，左右括号出栈
                    c=s[k++];  // 读入下一个字符
                    break;
                case'>':  //退栈并将运算结果入栈
                    char x=Get_Stack(op);Pop_Stack(op);
                    double m=Get_Stack(num);Pop_Stack(num);
                    double n=Get_Stack(num);Pop_Stack(num);
                    Push_Stack(num,Operate(m,n,x));
                    break;
            }
        }
    }
    cout << endl << "运算结果为："<<setiosflags(ios::fixed) << setprecision(4) <<Get_Stack(num);
    return 0;
}
