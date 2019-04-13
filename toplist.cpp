/*
	Name:7-4-3-1-topologicalSort.cpp 
	Date: 07/06/17 08:14
	Description:复习几个名词：
	1.有向无环图dag: directed acyclic graph
	2.邻接矩阵：adjacency matrix
	3.邻接表：adjacency list
	4.逆邻接表: inverse adjacency list
9
a b c d e f g h i
0 0 1 1 0 0 0 0 0
0 0 0 1 1 1 0 0 0
0 0 0 0 0 0 0 1 0
0 0 0 0 0 1 0 0 0
0 0 0 0 0 1 1 0 0
0 0 0 0 0 0 1 0 1
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

vector<vector<int> > gam;//gam:graph by adjacency matirx 利用邻接矩阵表示图 
vector<vector<int> > gal;//graph by adjacency list 利用邻接表表示图,本质就是从这个点能到达那几个点，方便求出度 ，原理和树的数组表示法一样 
vector<vector<int> > gial;// graph by inverse adjacency list 利用逆邻接表表示图，本质是记住这个点能从那几个点到达。求入度方便 
vector<char> name;//用于存放节点的名字 
vector<int> indegree;//用于存放顶点的入度 
int n; //节点的个数 
int temp;//临时变量 temporary 

void CrtG(){
	cin>>n;
	gam.resize(n+1,vector<int>(n+1,0));
	gal.resize(n+1);
	gial.resize(n+1);
	indegree.resize(n+1,0);
	name.resize(n+1);
	for(int i = 1; i <= n; i++){
		cin>> name[i];
	}
	for(int i =1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cin>>temp;
			if(temp > 0){
				gam[i][j] = temp;//更新邻接矩阵，表示从i顶点可以到达j顶点
				gal[i].push_back(j);//邻接表表示法，j作为i的孩子存起来 
				gial[j].push_back(i);//逆邻接表表示法，i作为j的"爹"存起来 
			}
		}
	}
}

void FindIndegreeByAM(){//通过邻接矩阵求入度 find indegree by adjacency matrix
	bool dagFlag = false;
	for(int c = 1; c <= n; c++){
		temp = 0;
		for(int r = 1; r <=n; r++){
			if(gam[r][c] > 0){
				temp++;
			}
		}
		indegree[c] = temp;
		if(temp == 0){
			dagFlag = true;
		}
	}
	if(!dagFlag){
		cout<<"this is a direct cyclic graph"<<endl;
	}
}

void FindIndegreeByAL(){//通过邻接表求入度 find indegree by adjacency list
	bool dagFlag = false;
	for(int k = 1; k <= n; k++){
		temp = 0;
		for(int i = 1; i <= n; i++){//遍历每个节点的孩子 
			for(int c = 0; c < gal[i].size(); c++){//children
				if(gal[i][c] == k){
					temp++;
				}
			}
		}
	 	indegree[k] = temp;
		if(temp == 0){
			dagFlag = true;
		}
	}
	if(!dagFlag){
		cout<<"this is a direct cyclic graph"<<endl;
	}
}

void FindIndegreeByIAL(){//通过逆邻接表求入度 find indegree by inverse adjacency list
	bool dagFlag = false;
	for(int k = 1; k <= n; k++){
		temp = 0;
		temp = gial[k].size();
	 	indegree[k] = temp;
		if(temp == 0){
			dagFlag = true;
		}
	}
	if(!dagFlag){
		cout<<"this is a direct cyclic graph"<<endl;
	}
}

void OutG(){
	for(int i =1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cout<<gam[i][j]<<" ";
		}
		cout<<endl;
	}
}
void OutIndegree(){
	for(int i = 1; i <= n; i++){
		printf("%c:%d\n",name[i],indegree[i]);
	}
}

void TopologicalSort1(){
	int ans,cnt;//answer
	vector<int> vis(n+1,0);
	cnt = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(indegree[j] == 0){//找到一个入度为0的点
			    ans = j;
			    cnt++;
			    vis[cnt] = j;
			    indegree[j]--;//让他为负数，标记为不再使用 
			    break;
			}
		}
		for(int j = 1; j<= n; j++) {
			if(gam[ans][j] > 0){
				//gam[ans][j] = 0;//删除边，其实没什么用 
				indegree[j]--;//与相邻的边的入度减1 
			} 
		}
	}
	for(int i = 1; i <= cnt; i++){
		printf("c%d\t",vis[i]);
	} 
}

void TopologicalSort2(){//利用队列技术 
	queue<int> q;//用与存放入度为0的节点序号
	int vi;//vertex index
	for(int i = 1; i <= n; i++){
		if(indegree[i] == 0){
			q.push(i);//将入度为零的节点压入队列 
		}
	}
	while(!q.empty()){
		vi = q.front();
		q.pop();
		printf("c%d\t",vi);//输出入度为零的节点 
		for(int i = 0; i < gal[vi].size(); i++){
			indegree[gal[vi][i]]--;//将vi的邻接点的入度减1
			if(indegree[gal[vi][i]] == 0){
				q.push(gal[vi][i]);//将入度为零的节点压入队列 
			} 
		}
	}
 }

void TopologicalSort3(){//利用栈技术 
	stack<int> s;//用与存放入度为0的节点序号
	int vi;//vertex index
	for(int i = 1; i <= n; i++){
		if(indegree[i] == 0){
			s.push(i);//将入度为零的节点压入队列 
		}
	}
	while(!s.empty()){
		vi = s.top();
		s.pop();
		printf("c%d\t",vi);//输出入度为零的节点 
		for(int i = 0; i < gal[vi].size(); i++){
			indegree[gal[vi][i]]--;//将vi的邻接点的入度减1
			if(indegree[gal[vi][i]] == 0){
				s.push(gal[vi][i]);//将入度为零的节点压入队列 
			} 
		}
	}
 }



int main(){
	if(!freopen("7-4-3-1-topologicalSort.in","r",stdin)){
		cerr<<"Open file error";
		return 0;
	}
	CrtG();
	//OutG();
	//FindIndegreeByAM();
	//FindIndegreeByAL();
	FindIndegreeByIAL();
	OutIndegree();
	cout<<endl<<"============================"<<endl;
	TopologicalSort1();
	cout<<endl<<"============================"<<endl;
	FindIndegreeByIAL();
	cout<<endl<<"============================"<<endl;
	OutIndegree();
	cout<<endl<<"============================"<<endl;
	TopologicalSort2();
	cout<<endl<<"============================"<<endl;
	FindIndegreeByIAL();
	cout<<endl<<"============================"<<endl;
	OutIndegree();
	cout<<endl<<"============================"<<endl;
	TopologicalSort3();

	return 0;
}

