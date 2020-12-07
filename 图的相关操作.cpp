#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

#define MVNum 100							//��󶥵���
typedef char VerTexType;					//���趥�����������Ϊ�ַ���

//-------------ͼ���ڽӱ�---------------------
typedef struct ArcNode{                		//�߽��
    int adjvex;                          	//�ñ���ָ��Ķ����λ��q
    struct ArcNode *nextarc;          		//ָ����һ���ߵ�ָ��
}ArcNode;

typedef struct VNode{
    VerTexType data;                    	//������Ϣ
    ArcNode *firstarc;                		//ָ���һ�������ö���ıߵ�ָ��
}VNode, AdjList[MVNum];               		//AdjList��ʾ�ڽӱ�����

typedef struct{
    AdjList vertices;
    //�ڽӱ�
    int vexnum, arcnum;              		//ͼ�ĵ�ǰ�������ͱ���
}ALGraph;

bool visited[MVNum] = {false};           				//���ʱ�־���飬���ֵΪ"false"

//ȷ����v��G�е�λ��
int LocateVex(ALGraph G , VerTexType v){
    for(int i = 0; i < G.vexnum; ++i)
        if(G.vertices[i].data == v)
            return i;
    return -1;
}

//�����ڽӱ��ʾ������������ͼG
void CreateUDG(ALGraph &G){
    int i , k;

    cout <<"�������ܶ��������ܱ������Կո����:";
    cin >> G.vexnum >> G.arcnum;				//�����ܶ��������ܱ���
    cout << endl;

    cout << "���������ƣ���a" << endl;
    for(i = 0; i < G.vexnum; ++i){          	//������㣬�����ͷ����
        cout << "�������" << (i+1) << "���������:";
        cin >> G.vertices[i].data;           	//���붥��ֵ
        G.vertices[i].firstarc=NULL;			//��ʼ����ͷ����ָ����ΪNULL
    }
    cout << endl;

    cout << "����������Ķ��㣬��a b" << endl;
    for(k = 0; k < G.arcnum;++k){        		//������ߣ������ڽӱ�
        VerTexType v1 , v2;
        int i , j;
        cout << "�������" << (k + 1) << "���������Ķ���:";
        cin >> v1 >> v2;                 		//����һ������������������
        i = LocateVex(G, v1);  j = LocateVex(G, v2);
        //ȷ��v1��v2��G��λ�ã���������G.vertices�е����

        ArcNode *p1=new ArcNode;               	//����һ���µı߽��*p1
        p1->adjvex=j;                   		//�ڽӵ����Ϊj
        p1->nextarc= G.vertices[i].firstarc;  G.vertices[i].firstarc=p1;
        //���½��*p1���붥��vi�ı߱�ͷ��

        ArcNode *p2=new ArcNode;                //������һ���ԳƵ��µı߽��*p2
        p2->adjvex=i;                   		//�ڽӵ����Ϊi
        p2->nextarc= G.vertices[j].firstarc;  G.vertices[j].firstarc=p2;
        //���½��*p2���붥��vj�ı߱�ͷ��

    }
}

//�����������
void DFS(ALGraph G, int v){        				//ͼGΪ�ڽӱ�����
    cout << G.vertices[v].data << "   ";
    visited[v] = true;    						//���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue
    ArcNode *p = G.vertices[v].firstarc;		//pָ��v�ı�����ĵ�һ���߽��
    while(p != NULL){              				//�߽��ǿ�
        int w = p->adjvex;               		//��ʾw��v���ڽӵ�
        if(!visited[w])  DFS(G, w);   			//���wδ���ʣ���ݹ����DFS
        p = p->nextarc;                			//pָ����һ���߽��
    }
}

//�����������
void BFS(ALGraph &G,int v){          			//ͼGΪ�ڽӱ�����
   queue<VNode> Q;                              //��������
   Q.push(G.vertices[v]);                       //��Ҫ��ʼ�����Ľ��vѹ�����
   visited[v] = true;       					//���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue
   while (!Q.empty()){                          //Q�н��ǿ�
       VNode temp = Q.front();                  //��������
       cout << temp.data << "   ";
       Q.pop();                                 //���ʹ����ڽӵ㵯������
       ArcNode *p = temp.firstarc;              //pָ��temp�ĵ�һ���߽��
       while(p!=NULL){                          //�߽��ǿ�
           if(visited[p->adjvex]==false){             //����ñ߽����ָ���ڽӵ�δ������
               Q.push(G.vertices[p->adjvex]);   //��δ���ʹ����ڽӵ�ѹ�����
               visited[p->adjvex] = true;       //���ʹ��Ľ�������
           }
           p = p->nextarc;                      //pָ����һ���߽��
       }
   }
}

void DFSTraverse(ALGraph &G){
    int i;
    memset(visited,false,sizeof(visited));           				//���ʱ�־���飬���ֵΪ"false"
    for(i = 0;i<G.vexnum;i++){
        if(visited[i] == false)
            DFS(G,i);
    }
}

void BFSTraverse(ALGraph &G){
    int i;
    memset(visited,false,sizeof(visited));           				//���ʱ�־���飬���ֵΪ"false"
    for(i = 0;i<G.vexnum;i++){
        if(visited[i] == false)
            BFS(G,i);
    }
}



int main(){
    ALGraph G;
    CreateUDG(G);


    cout << endl;
    cout << "����ͼG������ɣ�" << endl << endl;

    cout << "�������������ʼ�㣺";
    VerTexType c;
    cin >> c;

    int i;
    for(i = 0 ; i < G.vexnum ; ++i){
        if(c == G.vertices[i].data)
            break;
    }
    cout << endl;
    while(i >= G.vexnum){
        cout << "�õ㲻���ڣ����������룡" << endl;
        cout << "�������������ʼ�㣺";
        cin >> c;
        for(i = 0 ; i < G.vexnum ; ++i){
            if(c == G.vertices[i].data)
                break;
        }
    }

    cout << "���������������ͼ�����" << endl;
    DFSTraverse(G);
    cout << endl;

    cout << "���������������ͼ�����" << endl;
    BFSTraverse(G);
    cout << endl;

    return 0;
}
