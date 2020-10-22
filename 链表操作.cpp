#include <iostream>
using namespace std;

typedef struct Node{
    int data;   //结点的数据域
    struct Node *next;  //结点的指针域
}Node,*NodeList;

void Create_NodeList(NodeList &L,int n) //创建链表
{

    Node *p,*r;    //临时结点，用于存放数据
    L = new Node;   //生成新结点作为头结点，用头指针L指向头结点
    L->next = NULL; //头结点的指针域置空
    r=L;
    cout << "请输入元素:\n";
    for(int i=0;i<n;i++)
    {
        p = new Node;   //申请新结点
        cin >> p->data; //输入数据
        p->next=NULL;   //后继指针域置空
        r->next = p;    //将结点加到链表后面
        r = p;
    }
}

void Reverse_NodeList(NodeList &A,NodeList&B)   //反转链表
{
    Node *pa,*pb;
    pa = A->next;
    pb = B;
    while (pa)  //将链表反转存到新表
    {
        pb = pa;
        pa = pa ->next;
        pb->next = B->next;
        B->next = pb;
    }
    delete A;
}
void Out_NodeList(NodeList &L)  //输出数据
{
    Node *p;
    p=L->next;
    while(p){
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int main(){
    int n;
    Node *head;
    NodeList newhead;

    newhead = new Node;
    newhead->next = NULL;


    cout << "请输入链表的元素个数：";
    cin >> n;
    Create_NodeList(head,n);    //创建链表
    Out_NodeList(head); //输出链表
    Reverse_NodeList(head,newhead); //反转链表
    cout << "反转后的链表为：" << endl;
    Out_NodeList(newhead);  //输出反转后的链表
    return 0;
}
