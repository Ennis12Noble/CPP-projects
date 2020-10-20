#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

#define MAXSIZE 500 //顺序表可能达到的长度

using namespace std;

struct Book{        //图书的结构体
   long isbn;    //书籍的ISBN
   string name;    //书名
   double price;   //书籍价格
};

typedef struct{
   Book *elem; //存储空间的基地址
   int length; //顺序表当前长度
}Sq_list;


int DelList(Sq_list &List,int i);
void Menu();

int Init_List(Sq_list &List) //顺序表的初始化
{
   //构造一个空的顺序表
   List.elem = new Book[MAXSIZE];  //为顺序表分配一个大小为MAXSIZE的数组空间
   if(!List.elem)
   {
       cout << "空间分配失败" << endl;
       return 1;   //存储分配失败退出
   }
   List.length=0;  //空表的长度为0
   return 0;
}

void InputList(Sq_list &List)   //顺序表的录入
{
   int count;
   cout << "请输入要录入的书籍数:"; cin >> count;
   cout << "请开始录入数据（ISBN，书名，价格）" << endl;

   for(int i =0;i<count;i++)
   {
       cin >> List.elem[i].isbn;
       cin >> List.elem[i].name;
       cin >> List.elem[i].price;
       List.length++;

   }
   cout << "录入结束!";
}


int GetElem(Sq_list &List,long &vary)   //顺序表的查找
{
       for(int i=0;i<List.length;i++)
       {
           if(List.elem[i].isbn==vary)
           {
               cout << "找到了！位置在：" << i+1 << "处" << endl;
               return i+1; //查找成功，返回位置i+1
           }
       }
       cout << "未找到！按回车返回目录" << endl;
       return 0;   //查找失败，返回错误
}

int InsertList(Sq_list &List,int i,Book &b)    //顺序表的插入
{
   if (i < 1 || i > List.length)  //判断i值是否合法
   {
       cout << "插入失败" << endl;
       return 1;

   }
   if (List.length == MAXSIZE)    //当前存储空间已满，返回错误
   {
       cout << "插入失败" << endl;
       return 1;
   }
   for (int j = List.length - 1; j >= i - 1; j--) {
       List.elem[j + 1] = List.elem[j];  //插入位置及之后的元素后移
   }
   List.elem[i - 1] = b; //将新元素放在第i个位置
   ++List.length;  //顺序表长加1
   cout << "插入成功" << endl;
   return 0;
}

int DelList(Sq_list &List,int i)    //顺序表的删除
{
   if((i<1)||(i>List.length))
   {
       cout << "删除失败" << endl;
       return 1;   //判断i值是否合理,不合理则返回错误
   }
   for(int j=i;j<=List.length-1;j++)
   {
       List.elem[j-1] = List.elem[j];  //被删除的元素之后的元素后移
   }
   cout << "删除成功" << endl;
   --List.length;  //顺序表长减1
   return 0;
}

void OutputList(Sq_list &List)  //顺序表的输出
{
   for(int k = 0;k<List.length;k++)
   {
       cout   << "第" << k+1 << "本书的ISBN为：" << List.elem[k].isbn << " 书名为：" << List.elem[k].name << " 价格为：" << List.elem[k].price << endl;
   }
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
void SortList(Sq_list &List)    //顺序表的排序(按ISBN的值）
{
   for(int i = 0; i <List.length - 1; i++)
   {
       for(int j = 0; j < List.length - i - 1; j++)
       {
           if(List.elem[j].isbn > List.elem[j+1].isbn)
               std::swap(List.elem[j],List.elem[j+1]);
       }
   }
   cout << "排序完成！" << endl;
}

void Menu(Sq_list &List) //选择菜单
{
   system("cls");
   bool state =true;   //是否循环的一个标志
   while (state)
   {
       cout << endl;
       cout << setw(10) << "*0.初始化*" << endl;
       cout << setw(10) << "*1.录入数据*"<< endl;
       cout << setw(10) << "*2.查找数据*"<< endl;
       cout << setw(10) << "*3.插入数据*"<< endl;
       cout << setw(10) << "*4.删除数据*"<< endl;
       cout << setw(10) << "*5.输出数据*"<< endl;
       cout << setw(10) << "*6.排序数据*"<< endl;

       char str;
       cin >> str;
       switch (str)
       {
           case '0' :  //初始化
               Init_List(List);
               cout << "初始化成功！按回车返回目录" << endl;
               state = Out();
               break;
           case '1' :
               InputList(List);
               cout << "录入完成！按回车返回目录" << endl;
               state = Out();
               break;
           case '2' :
               long isbn;
               cout << "*依据ISBN查询*" << endl;
               cin >> isbn;
               GetElem(List,isbn);\
               state = Out();
               break;
           case '3' :
           {
               Book b;
               int x;
               cout << "请依次输入要插入的元素的ISBN、书名和价格" << endl;
               cin >> b.isbn >> b.name >> b.price;
               cout <<"请输入要插入的位置:" ;
               cin >> x;
               InsertList(List,x,b);

           }
               state = Out();
               break;
           case '4' :
               int y;
               cout << "请输入要删除的元素的位置";
               cin >> y;
               DelList(List,y);
               state = Out();
               break;
           case '5' :
               OutputList(List);
               state = Out();
               break;
           case '6' :
               SortList(List);
               state = Out();
               break;
           default:
               cout << "非法输入，请重新选择\n";
               break;
       }

   }
   cout << "菜单已退出";
}

int main()
{
   Sq_list L0;
   Menu(L0);
   return 0;
}
