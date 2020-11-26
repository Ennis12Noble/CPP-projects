#include <iostream>

using namespace std;
#define MAXSIZE 100 //���е���󳤶�
typedef struct {
    string name;    //����
    int sex;    //�Ա�1��ʾ���ԣ�0��ʾŮ��
}Person;
typedef struct {
    Person *base;   //�����е�����Ԫ������ΪPerson
    int head;   //ͷָ��
    int end;    //βָ��
}Quene;

//��ʼ������
int Create(Quene &q)
{
    q.base = new Person[MAXSIZE];   //Ϊ��������ռ�
    if(!q.base){ return 1; }  //����ռ�ʧ�ܣ�����1
    q.head = q. end = 0;    //ͷָ���βָ����Ϊ0�����п�
    return 0;   //�����ɹ�
}
//��ȡ���г���
int Length(Quene &q)
{
    return (q.end-q.head+MAXSIZE)%MAXSIZE;
}
//���
int InQuene(Quene &q,Person p)
{
    if((q.end+1)%MAXSIZE==q.head){ return 1; }  //�ж϶����Ƿ�����
    q.base[q.end] = p ; //��Ԫ�ز����β
    q.end = (q.end+1)%MAXSIZE;  //βָ���һ
}
//����
int OutQuene(Quene &q)
{
    if(q.end==q.head){ return 1; }  //�ж϶����Ƿ�Ϊ��
    q.head = (q.head+1)%MAXSIZE;    //ͷָ���һ
}
//��ȡ��ͷԪ��
Person GetHead(Quene &q)
{
    if(q.end!=q.head)   //������зǿ�
    {
        return q.base[q.head];  //���ض�ͷԪ�ص�ֵ�����ı�ͷָ��
    }
}
//�ж϶����Ƿ�Ϊ��
bool isEmpty(Quene &q)
{
    if(q.end==q.head){
        return true;   //����Ϊ��
    }else{
        return false;    //���зǿ�
    }
}
//�����������庯��
void Dance(Person dancer[],int num)
{
    Person p;
    Quene man,woman;    //������Ů��������
    //dancerΪ������ṹ����ɵ�����,numΪ����
    Create(man);Create(woman);  //��ʼ��������
    for(int i=0;i<num;i++)  //�����߰����Ա����
    {
        p = dancer[i];
        if(p.sex == 0)  //���Ա�ΪŮ������Ů��
        {
            InQuene(woman,p);
        }
        else    //ͬ��
        {
            InQuene(man,p);
        }
    }
    cout <<"ƥ����Ϣ����" << endl;
    while(!isEmpty(man)&&!isEmpty(woman))   //�����Ů���зǿ�
    {
        cout << " " << GetHead(man).name << " ��ʿ�� " << GetHead(woman).name << " Ůʿ����" <<endl;     //��ȡ��ͷ��Ů��������ƥ��
        OutQuene(man);OutQuene(woman);  //��������
    }
    if(!isEmpty(woman))
    {
        cout << "��һ��������һλ�õ�����Ůʿ�ǣ�" << GetHead(woman).name;
    }
    else if(!isEmpty(man))
    {
        cout << "��һ��������һλ�õ�������ʿ�ǣ�" << GetHead(man).name;
    }
}
//����Person����
void ScanfPerson(Person dancer[],int num)
{
    for(int i=0;i<num;i++)
    {
        cout << endl;
        cout << "�������" << i+1 << "���˵��Ա�(��Ϊ1��ŮΪ0)��";
        cin >> dancer[i].sex;
        cout << "�������" << i+1 << "���˵�������";
        cin >> dancer[i].name;
    }
}
int main()
{
    int num;
    cout << "���������ߵ���������" ;
    cin >> num;

    Person dancer[num]; //����Person�ṹ��
    ScanfPerson(dancer,num);    //����������Ϣ
    Dance(dancer,num);  //������麯��
    return 0;
}


