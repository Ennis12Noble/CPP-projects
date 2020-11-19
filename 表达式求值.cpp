#include <iostream>
#include <stdio.h>
#include <stack>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;
#define MAXSIZE 100 //ջ�ռ�ĳ�ʼ������

typedef struct{
    char *base;	//ջ��ָ��
    char *top;	//ջ��ָ��
    int stacksize;	//ջ���õ��������
}Stack_char;

typedef struct{
    double *base;	//ջ��ָ��
    double *top;	//ջ��ָ��
    int stacksize;	//ջ���õ��������
}Stack_double;

template <typename Stack ,typename any>
//����ջ
int Create_Stack(Stack &s,any type)
{
    any c = type;
    s.base = new any[MAXSIZE];  //��ջ����ռ�
    if(!s.base) return 1;   //����ʧ��
    s.top = s.base; //top��baseָ��ͬһλ��
    s.stacksize = MAXSIZE;  //stack���Ϊջ����󳤶�
    return 0;
}

template <typename Stack ,typename any>
//��ջ��ѹ��Ԫ��
double Push_Stack(Stack &s,any c)
{
    if(s.top-s.base==s.stacksize){  //ջ��
        return 1;
    }
    *s.top++ = c;   //ѹ��ջ����ջ��ָ���1
    return 0;
}
template <typename Stack>
//Ԫ�س�ջ��ɾ����
int Pop_Stack(Stack &s)
{
    if(s.top==s.base){  //ջ��
        return 1;
    }
    --s.top;   //ջ��Ԫ�ظ���c
}
template <typename Stack>
//��ȡջ��Ԫ�أ���ɾ����
double Get_Stack(Stack &s)
{
    if(s.top!=s.base)   //ջ�ǿ�
    {
        return *(s.top-1);
    }
}

//������ȽϺ���
char Compare(char a,char b){
    char priority[7][7]={
            {'>','>','<','<','<','>','>'},
            {'>','>','<','<','<','>','>'},
            {'>','>','>','>','<','>','>'},
            {'>','>','>','>','<','>','>'},
            {'<','<','<','<','<','=','0'},  //��һ�е�0��ʾ������������
            {'>','>','>','>','0','>','>'},  //�����0��ʾ�﷨����
            {'<','<','<','<','<','0','='}   //��һ�е�=��ʾ�������ʽ��ֵ�����
    };
    int i,j;    //�У���
    switch(a){  //��ת���ж�Ӧ�ķ���
        case'+':i=0;break;
        case'-':i=1;break;
        case'*':i=2;break;
        case'/':i=3;break;
        case'(':i=4;break;
        case')':i=5;break;
        case'#':i=6;break;   // # �Ǳ��ʽ�Ľ�����
    }
    switch(b){  //��ת���ж�Ӧ�ķ���
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

//���㺯��
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

    Stack_char op;  //���������ջ
    Stack_double num;   //��������ջ

    double a = 0;
    char b = 'a';
    Create_Stack(num,a);    //��ʼ��ջ
    Create_Stack(op,b);

    Push_Stack(op,'#'); //�������ջѹ��#
    char end[2]="#";    //β����\0
    char s[MAXSIZE];
    cout << "����������ʽ��";
    cin>>s;
    strcat(s,end);// ����ʽβ����#
    char c=s[0];
    int k=1;
    while(c!='#'||Get_Stack(op)!='#'){  //���ʽδ�����������δ��
        double y=0.0;
        double z=0.0;
        int count=0;
        if(c>='0'&&c<='9'){
            while(c>='0'&&c<='9'){  // ��������������
                y=y*10+(c-'0');
                c=s[k++];
                if(c=='.'){ //����С����
                    c=s[k++];
                    while (c>='0'&&c<='9'){
                        ++count;
                        z=z+pow(0.1,count)*(c-'0');
                        c=s[k++];
                    }
                }
            }
            Push_Stack(num,y+z);  // �Ѷ���������������ջ
        }
        else{
            switch(Compare(Get_Stack(op),c))
            {
                case'<':  //ջ��Ԫ������Ȩ��
                    Push_Stack(op,c);
                    c=s[k++];
                    break;
                case'=':
                    Pop_Stack(op);  //����ƥ��ɹ����������ų�ջ
                    c=s[k++];  // ������һ���ַ�
                    break;
                case'>':  //��ջ������������ջ
                    char x=Get_Stack(op);Pop_Stack(op);
                    double m=Get_Stack(num);Pop_Stack(num);
                    double n=Get_Stack(num);Pop_Stack(num);
                    Push_Stack(num,Operate(m,n,x));
                    break;
            }
        }
    }
    cout << endl << "������Ϊ��"<<setiosflags(ios::fixed) << setprecision(4) <<Get_Stack(num);
    return 0;
}
