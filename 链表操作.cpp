#include <iostream>
using namespace std;

typedef struct Node{
    int data;   //����������
    struct Node *next;  //����ָ����
}Node,*NodeList;

void Create_NodeList(NodeList &L,int n) //��������
{

    Node *p,*r;    //��ʱ��㣬���ڴ������
    L = new Node;   //�����½����Ϊͷ��㣬��ͷָ��Lָ��ͷ���
    L->next = NULL; //ͷ����ָ�����ÿ�
    r=L;
    cout << "������Ԫ��:\n";
    for(int i=0;i<n;i++)
    {
        p = new Node;   //�����½��
        cin >> p->data; //��������
        p->next=NULL;   //���ָ�����ÿ�
        r->next = p;    //�����ӵ��������
        r = p;
    }
}

void Reverse_NodeList(NodeList &A,NodeList&B)   //��ת����
{
    Node *pa,*pb;
    pa = A->next;
    pb = B;
    while (pa)  //������ת�浽�±�
    {
        pb = pa;
        pa = pa ->next;
        pb->next = B->next;
        B->next = pb;
    }
    delete A;
}
void Out_NodeList(NodeList &L)  //�������
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


    cout << "�����������Ԫ�ظ�����";
    cin >> n;
    Create_NodeList(head,n);    //��������
    Out_NodeList(head); //�������
    Reverse_NodeList(head,newhead); //��ת����
    cout << "��ת�������Ϊ��" << endl;
    Out_NodeList(newhead);  //�����ת�������
    return 0;
}
