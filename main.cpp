#include<iostream>
#include <queue>
using namespace std;
typedef struct BiNode{				//二叉链表定义
    char data;
    struct BiNode *lchild,*rchild;
}BiTNode,*BiTree;

//1.先序遍历的顺序建立二叉链表
void CreateBiTree(BiTree &T){
    //按先序次序输入二叉树中结点的值（一个字符），创建二叉链表表示的二叉树T
    char ch;
    cin >> ch;
    if(ch=='#'){
        T=NULL;
        return;
    }			//递归结束，建空树
    else{
        T=new BiTNode;
        T->data=ch;					//生成根结点
        CreateBiTree(T->lchild);	//递归创建左子树
        CreateBiTree(T->rchild);	//递归创建右子树
    }								//else
}									//CreateBiTree
//2.先序遍历
void PreOrderTraverse(BiTree T){
    if(T){
        cout << T->data;
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
//3.中序遍历
void InOrderTraverse(BiTree T){
    if(T){
        InOrderTraverse(T->lchild);
        cout << T->data;
        InOrderTraverse(T->rchild);
    }
}
//4.后序遍历
void PostOrderTraverse(BiTree T){
    if(T){
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout << T->data;
    }
}
//5.统计度为0的结点个数（叶子结点）
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
//6.统计度为1的结点个数
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
//7.统计度为2的结点个数
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
//8.统计所有结点的个数
int NodeNumber_Total(BiTree T)
{
    return NodeNumber_0(T)+NodeNumber_1(T)+NodeNumber_2(T);
}
//9.统计二叉树的高度
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
    return (depth+1);//因为有根节点一层，所以加1
}
//10.按层次次序遍历序列
void LevelOrder(BiTree T)
{
    BiTree p;
    queue<BiTree> qu;  //声明一个队列
    if(T){  //若数不为空
        qu.push(T); //根节点入队列
    }
    while(!qu.empty()){ //若队列非空
        p = qu.front();
        qu.pop();
        cout << p->data;
        if(p->lchild!=NULL){ //左孩子存在
            qu.push(p->lchild);
        }
        if(p->rchild!=NULL){ //右孩子存在
            qu.push(p->rchild);
        }
    }
}



int main(){
    BiTree tree;

    cout<<"请输入建立二叉链表的序列：（按先序遍历）\n";
    CreateBiTree(tree);
    cout << endl;

    cout << "先序遍历的结果为:\n";
    PreOrderTraverse(tree);
    cout << endl;

    cout<<"中序遍历的结果为：\n";
    InOrderTraverse(tree);
    cout << endl;

    cout << "后序遍历的结果:\n";
    PostOrderTraverse(tree);
    cout << endl;

    cout << "按层次次序遍历的结果为：\n";
    LevelOrder(tree);
    cout << endl;

    cout << "树中度为0的结点个数为：" << NodeNumber_0(tree) << endl;
    cout << "树中度为1的结点个数为：" << NodeNumber_1(tree) << endl;
    cout << "树中度为2的结点个数为：" << NodeNumber_2(tree) << endl;

    cout << "树中所有结点的个数为： " << NodeNumber_Total(tree) << endl;

    cout << "树的高度为：" << GetHeight(tree) << endl;


}