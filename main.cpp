#include<iostream>
#include <queue>
using namespace std;
typedef struct BiNode{				//����������
    char data;
    struct BiNode *lchild,*rchild;
}BiTNode,*BiTree;

//1.���������˳������������
void CreateBiTree(BiTree &T){
    //�������������������н���ֵ��һ���ַ������������������ʾ�Ķ�����T
    char ch;
    cin >> ch;
    if(ch=='#'){
        T=NULL;
        return;
    }			//�ݹ������������
    else{
        T=new BiTNode;
        T->data=ch;					//���ɸ����
        CreateBiTree(T->lchild);	//�ݹ鴴��������
        CreateBiTree(T->rchild);	//�ݹ鴴��������
    }								//else
}									//CreateBiTree
//2.�������
void PreOrderTraverse(BiTree T){
    if(T){
        cout << T->data;
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
//3.�������
void InOrderTraverse(BiTree T){
    if(T){
        InOrderTraverse(T->lchild);
        cout << T->data;
        InOrderTraverse(T->rchild);
    }
}
//4.�������
void PostOrderTraverse(BiTree T){
    if(T){
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout << T->data;
    }
}
//5.ͳ�ƶ�Ϊ0�Ľ�������Ҷ�ӽ�㣩
int NodeNumber_0(BiTree T)
{
    int i=0;
    if(T)
    {
        if(T->lchild==NULL&&T->rchild==NULL)
        {
            i=1;
        }
        else
        {
            i=NodeNumber_0( T->lchild ) + NodeNumber_0( T->rchild );
        }
    }
    return i;
}
//6.ͳ�ƶ�Ϊ1�Ľ�����
int NodeNumber_1(BiTree T)
{
    int i=0;
    if(T)
    {
        if( (T->lchild==NULL&&T->rchild!=NULL) ||(T->lchild!=NULL&&T->rchild==NULL))
        {
            i=1+NodeNumber_1(T->lchild)+NodeNumber_1(T->rchild);
        }
        else
        {
            i=NodeNumber_1(T->lchild)+NodeNumber_1(T->rchild);
        }
    }
    return i;
}
//7.ͳ�ƶ�Ϊ2�Ľ�����
int NodeNumber_2(BiTree T)
{
    int i=0;
    if(T)
    {
        if((T->lchild!=NULL)&&(T->rchild!=NULL))
        {
            i=1+NodeNumber_2(T->lchild) + NodeNumber_2(T->rchild);
        }
        else
        {
            i= NodeNumber_2(T->lchild) + NodeNumber_2(T->rchild);
        }
    }
    return i;
}
//8.ͳ�����н��ĸ���
int NodeNumber_Total(BiTree T)
{
    return NodeNumber_0(T)+NodeNumber_1(T)+NodeNumber_2(T);
}
//9.ͳ�ƶ������ĸ߶�
int GetHeight(BiTree T)
{
    if(!T)
    {
        return 0;
    }
    int depth=0;
    int leftDepth=GetHeight(T->lchild );
    int rightDepth=GetHeight(T->rchild);
    depth = leftDepth>rightDepth?leftDepth:rightDepth;
    return (depth+1);//��Ϊ�и��ڵ�һ�㣬���Լ�1
}
//10.����δ����������
void LevelOrder(BiTree T)
{
    BiTree p;
    queue<BiTree> qu;  //����һ������
    if(T){  //������Ϊ��
        qu.push(T); //���ڵ������
    }
    while(!qu.empty()){ //�����зǿ�
        p = qu.front();
        qu.pop();
        cout << p->data;
        if(p->lchild!=NULL){ //���Ӵ���
            qu.push(p->lchild);
        }
        if(p->rchild!=NULL){ //�Һ��Ӵ���
            qu.push(p->rchild);
        }
    }
}



int main(){
    BiTree tree;

    cout<<"�����뽨��������������У��������������\n";
    CreateBiTree(tree);
    cout << endl;

    cout << "��������Ľ��Ϊ:\n";
    PreOrderTraverse(tree);
    cout << endl;

    cout<<"��������Ľ��Ϊ��\n";
    InOrderTraverse(tree);
    cout << endl;

    cout << "��������Ľ��:\n";
    PostOrderTraverse(tree);
    cout << endl;

    cout << "����δ�������Ľ��Ϊ��\n";
    LevelOrder(tree);
    cout << endl;

    cout << "���ж�Ϊ0�Ľ�����Ϊ��" << NodeNumber_0(tree) << endl;
    cout << "���ж�Ϊ1�Ľ�����Ϊ��" << NodeNumber_1(tree) << endl;
    cout << "���ж�Ϊ2�Ľ�����Ϊ��" << NodeNumber_2(tree) << endl;

    cout << "�������н��ĸ���Ϊ�� " << NodeNumber_Total(tree) << endl;

    cout << "���ĸ߶�Ϊ��" << GetHeight(tree) << endl;


}