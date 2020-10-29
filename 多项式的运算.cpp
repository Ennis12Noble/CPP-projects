#include <iostream>
#include <iomanip>
using namespace std;

typedef struct Node{
    double coef;    //系数
    int expn;   //指数
    struct Node *next;  //结点的指针域
}Node,*NodeList;
void Out_NodeList(NodeList L);

int Merge_NodeList(NodeList p,NodeList s,NodeList &q){   //合并同类项
    NodeList p1 = p->next;  //p1指向首元结点
    NodeList p2 = p;    //p2指向头结点   目的是让p2指的元素永远在p1之前一个
    while (p1){
        if(s->expn>p1->expn){   //如果输入的数据的指数比p1指向的大
            p1 = p1->next;  //p1继续遍历
            p2 = p2->next;  //p2继续遍历
        }
        else if(s->expn == p1->expn){   //如果输入的数据的指数跟p1指向的一样大
            q = p1; //q指向p1
            return 1;    //返回真
        }
        else{
            q = p2;
            return 0;   //返回假
        }
    }
    if(!p1){    //如果遍历结束，则q指向p2
        q = p2;
        return 0;
    }
}

void Create_NodeList(NodeList &p,int n) //创建多项式链表
{
    NodeList s,q;   //s为输入用的临时结点，q为临时存放数据的结点
    p = new Node;   //new一个新结点
    p->next = NULL; //置空，一个头结点
    for(int i = 0;i<n;i++){
        s = new Node;
        cout << "请输入系数和指数（用空格分隔开）" << endl;
        cin >> s->coef >> s->expn;
        if(!Merge_NodeList(p,s,q)){ //若没有相同指数项，则链入
            s->next = q->next;  //将s接入p后
            q->next = s;
        }
        else{   //若有相同的指数向，则系数相加
            q->coef += s->coef;
        }
    }
}

void Add_NodeList(NodeList &p,NodeList p1){  //多项式相加

    NodeList prior,r;
    NodeList qa,qb;
    qa = p->next;   //qa，qb分别遍历p和p1

    qb = p1->next;


    while (qa&&qb){
        if(qa->expn<qb->expn){   //如果qa的指数小
            prior = qa;
            qa = qa->next;  //qa继续遍历
        }
        else if(qa->expn>qb->expn){ //如果qa的指数大
            r = qb;
            qb = qb->next;  //qb遍历
            r->next = qa;
            prior->next = r;    //将qb接到和多项式后
            prior = r;  //prior指向r
        }
        else{   //其他情况
            if(qa->coef+qb->coef!=0){   //如果系数相加不等于0
                qa->coef += qb->coef;   //系数相加
                r = qb; //r指向qb
                qb = qb->next;  //qb继续遍历
                delete r;   //释放qb所指的结点
            }
            else{   //如果系数相加等于0
                r = qa;     //释放qa和qb所指的结点
                qa = qa->next;
                prior->next = qa;   //qa接到和多项式后
                delete r;
                r = qb;
                qb = qb->next;
                delete r;
            }
        }
    }
    if(qb){ //将剩余节点接入
        prior->next = qb;
    }
    delete p1;
}

void Reverse(NodeList p)    //将多项式改为它的相反数，方便相减
{
    NodeList q = p->next;
    while(q){
        q->coef = -(q->coef);
        q = q->next;
    }
}

void Clone_NodeList(NodeList &q,NodeList r) //将r复制给q
{
    q = new Node;
    NodeList q1=q,r1=r->next; //将q1指向q的头结点，r1指向r的首元结点

    while(r1)
    {
        q1->next = new Node;
        q1 = q1->next;

        q1->coef = r1->coef;    //复制系数和指数
        q1->expn = r1->expn;


        r1 = r1->next;  //r1遍历

    }
    q1->next = NULL;    //q1遍历结束

}

void Del_NodeList(NodeList r)   //删除结点
{
    NodeList q;
    do{
        q = r;  //q指向r的头结点
        r = r->next;    //r遍历
        delete q;   //释放q
    }while (r);
}

void Sub_NodeList(NodeList p,NodeList p1)   //多项式相减
{
    Reverse(p1);    //将第二个链表的系数置反
    Add_NodeList(p,p1);
}
void Single_NodeList(NodeList p,double coef,int expn)   //多项式中的一个链表中的所有元素乘以另一个链表的一个元素
{
    NodeList q = p->next;   //q指向p的首元结点
    while (q)
    {
        q->coef *= coef;    //系数相乘
        q->expn += expn;    //指数相加
        q = q->next;    //q指向下一个
    }
}

void Multiply_NodeList(NodeList &p,NodeList p1) //多项式相乘的函数
{
    NodeList q;
    NodeList r=NULL,r1 = NULL; //r1为临时结点，用于
    q = p1;   //q指向p1的首元结点
    Out_NodeList(q);
    Clone_NodeList(r,p);    //用p克隆一个一样链表r
    Single_NodeList(r,q->coef,q->coef); //第一项先相乘
    q = q->next;    //q指向下一项
    Out_NodeList(q);
    while (q)
    {
        Clone_NodeList(r1,p);   //将p克隆给r1
        Single_NodeList(r1,q->coef,q->expn);    //q的一项乘以整个r1
        Add_NodeList(r,r1); //将r和r1相加，r1就完成了使命，存储在r中
        r1 = NULL;  //r1置空
        q = q->next;    //q遍历
    }
    Del_NodeList(p);    //删除p
    p = NULL;
    Clone_NodeList(p,r);    //把r克隆给p
    Del_NodeList(r);    //删除r
}

void Out_NodeList(NodeList L)  //输出数据
{
    Node *p;
    p=L->next;
    cout << "多项式为：" ;

    while(p){
        if(p->expn==0)
        {
            cout << p->coef;
        }
        else if(p->next)
        {
            cout << p->coef << "x^" << p->expn;
        }
        else{
            cout << p->coef << "x^" << p->expn;
            break;
        }
        if(p->next->coef>=0){
            cout << "+";
        }
        p = p->next;
    }
    cout << endl;
}
int Out()   //小目录
{
    cout << "*1.返回目录*\n";
    cout << "*2.退出程序*\n";
    char str0;
    cin >> str0;
    switch (str0) {
        case '1' :
            return true;
        case '2' :
            return false;
        default:
            cout << "非法输入，已返回主目录";
            return  true;
            break;
    }

}
void Menu(NodeList p,NodeList p1,NodeList p2,NodeList p3) //选择菜单
{
    system("cls");
    bool state =true;   //是否循环的一个标志
    while (state)
    {
        cout << endl;
        cout << setw(10) << "*0.创建多项式*" << endl;
        cout << setw(10) << "*1.多项式相加*"<< endl;
        cout << setw(10) << "*2.多项式相减*"<< endl;
        cout << setw(10) << "*3.多项式相乘*"<< endl;

        char str;
        cin >> str;
        switch (str)
        {
            case '0' :  //创建多项式
                int n,m;    //A,B的项数
                cout << "按升幂输入多项式A(x),B(x)的系数，指数\n";
                //A(x)的初始化
                cout << "请输入A(x)的项数：" ;
                cin >> n;
                Create_NodeList(p,n);
                cout << "A(x)" ;
                Out_NodeList(p);    //输出A(x)

                //B(x)的初始化
                cout << "请输入B(x)的项数：" ;
                cin >> m;
                Create_NodeList(p1,m);
                cout << "B(x)" ;
                Out_NodeList(p1);    //输出B(x)

                Clone_NodeList(p2,p);   //将A(x)复制给p2
                Clone_NodeList(p3,p1);  //将B(x)复制给p3

                state = Out();
                break;
            case '1' :  //相加
                Add_NodeList(p,p1);
                cout << "A(x)+B(x)= ";
                Out_NodeList(p);
                cout << "按回车返回目录" << endl;
                state = Out();
                break;
            case '2' :  //相减
                Sub_NodeList(p,p1);
                cout << "A(x)-B(x)= ";
                Out_NodeList(p);
                state = Out();
                break;
            case '3' :  //相乘
                Multiply_NodeList(p,p1);
                cout << "A(x)*B(x)= ";
                Out_NodeList(p);
                state = Out();
                break;
            default:
                cout << "非法输入，请重新选择\n";
                break;
        }
        Del_NodeList(p);
        p1 = p = NULL;
        Clone_NodeList(p,p2);   //把p2赋给p
        Clone_NodeList(p1,p3);  //把p3赋给p1
    }
    cout << "菜单已退出";
}

int main(){
    int n;  //输入的项数
    NodeList p,p1,p2=NULL,p3=NULL;
    Menu(p,p1,p2,p3);
    return 0;
}

