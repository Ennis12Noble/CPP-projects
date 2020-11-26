#include <iostream>

using namespace std;
#define MAXSIZE 100 //队列的最大长度
typedef struct {
    string name;    //姓名
    int sex;    //性别，1表示男性，0表示女性
}Person;
typedef struct {
    Person *base;   //队列中的数据元素类型为Person
    int head;   //头指针
    int end;    //尾指针
}Quene;

//初始化队列
int Create(Quene &q)
{
    q.base = new Person[MAXSIZE];   //为队列申请空间
    if(!q.base){ return 1; }  //申请空间失败，返回1
    q.head = q. end = 0;    //头指针和尾指针置为0，队列空
    return 0;   //创建成功
}
//获取队列长度
int Length(Quene &q)
{
    return (q.end-q.head+MAXSIZE)%MAXSIZE;
}
//入队
int InQuene(Quene &q,Person p)
{
    if((q.end+1)%MAXSIZE==q.head){ return 1; }  //判断队列是否已满
    q.base[q.end] = p ; //新元素插入队尾
    q.end = (q.end+1)%MAXSIZE;  //尾指针加一
}
//出队
int OutQuene(Quene &q)
{
    if(q.end==q.head){ return 1; }  //判断队列是否为空
    q.head = (q.head+1)%MAXSIZE;    //头指针加一
}
//获取队头元素
Person GetHead(Quene &q)
{
    if(q.end!=q.head)   //如果队列非空
    {
        return q.base[q.head];  //返回队头元素的值，不改变头指针
    }
}
//判断队列是否为空
bool isEmpty(Quene &q)
{
    if(q.end==q.head){
        return true;   //队列为空
    }else{
        return false;    //队列非空
    }
}
//舞伴问题的主体函数
void Dance(Person dancer[],int num)
{
    Person p;
    Quene man,woman;    //创建男女两个队列
    //dancer为人这个结构体组成的数组,num为人数
    Create(man);Create(woman);  //初始化两队列
    for(int i=0;i<num;i++)  //将舞者按照性别入队
    {
        p = dancer[i];
        if(p.sex == 0)  //若性别为女，则入女队
        {
            InQuene(woman,p);
        }
        else    //同理
        {
            InQuene(man,p);
        }
    }
    cout <<"匹配信息如下" << endl;
    while(!isEmpty(man)&&!isEmpty(woman))   //如果男女队列非空
    {
        cout << " " << GetHead(man).name << " 男士与 " << GetHead(woman).name << " 女士共舞" <<endl;     //获取队头男女姓名进行匹配
        OutQuene(man);OutQuene(woman);  //共舞后出队
    }
    if(!isEmpty(woman))
    {
        cout << "下一首舞曲第一位得到舞伴的女士是：" << GetHead(woman).name;
    }
    else if(!isEmpty(man))
    {
        cout << "下一首舞曲第一位得到舞伴的男士是：" << GetHead(man).name;
    }
}
//输入Person数组
void ScanfPerson(Person dancer[],int num)
{
    for(int i=0;i<num;i++)
    {
        cout << endl;
        cout << "请输入第" << i+1 << "个人的性别(男为1，女为0)：";
        cin >> dancer[i].sex;
        cout << "请输入第" << i+1 << "个人的姓名：";
        cin >> dancer[i].name;
    }
}
int main()
{
    int num;
    cout << "请输入舞者的总人数：" ;
    cin >> num;

    Person dancer[num]; //定义Person结构体
    ScanfPerson(dancer,num);    //输入舞者信息
    Dance(dancer,num);  //运行舞伴函数
    return 0;
}


