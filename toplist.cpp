/*
	Name:7-4-3-1-topologicalSort.cpp 
	Date: 07/06/17 08:14
	Description:��ϰ�������ʣ�
	1.�����޻�ͼdag: directed acyclic graph
	2.�ڽӾ���adjacency matrix
	3.�ڽӱ�adjacency list
	4.���ڽӱ�: inverse adjacency list
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

vector<vector<int> > gam;//gam:graph by adjacency matirx �����ڽӾ����ʾͼ 
vector<vector<int> > gal;//graph by adjacency list �����ڽӱ��ʾͼ,���ʾ��Ǵ�������ܵ����Ǽ����㣬��������� ��ԭ������������ʾ��һ�� 
vector<vector<int> > gial;// graph by inverse adjacency list �������ڽӱ��ʾͼ�������Ǽ�ס������ܴ��Ǽ����㵽�����ȷ��� 
vector<char> name;//���ڴ�Žڵ������ 
vector<int> indegree;//���ڴ�Ŷ������� 
int n; //�ڵ�ĸ��� 
int temp;//��ʱ���� temporary 

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
				gam[i][j] = temp;//�����ڽӾ��󣬱�ʾ��i������Ե���j����
				gal[i].push_back(j);//�ڽӱ��ʾ����j��Ϊi�ĺ��Ӵ����� 
				gial[j].push_back(i);//���ڽӱ��ʾ����i��Ϊj��"��"������ 
			}
		}
	}
}

void FindIndegreeByAM(){//ͨ���ڽӾ�������� find indegree by adjacency matrix
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

void FindIndegreeByAL(){//ͨ���ڽӱ������ find indegree by adjacency list
	bool dagFlag = false;
	for(int k = 1; k <= n; k++){
		temp = 0;
		for(int i = 1; i <= n; i++){//����ÿ���ڵ�ĺ��� 
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

void FindIndegreeByIAL(){//ͨ�����ڽӱ������ find indegree by inverse adjacency list
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
			if(indegree[j] == 0){//�ҵ�һ�����Ϊ0�ĵ�
			    ans = j;
			    cnt++;
			    vis[cnt] = j;
			    indegree[j]--;//����Ϊ���������Ϊ����ʹ�� 
			    break;
			}
		}
		for(int j = 1; j<= n; j++) {
			if(gam[ans][j] > 0){
				//gam[ans][j] = 0;//ɾ���ߣ���ʵûʲô�� 
				indegree[j]--;//�����ڵıߵ���ȼ�1 
			} 
		}
	}
	for(int i = 1; i <= cnt; i++){
		printf("c%d\t",vis[i]);
	} 
}

void TopologicalSort2(){//���ö��м��� 
	queue<int> q;//���������Ϊ0�Ľڵ����
	int vi;//vertex index
	for(int i = 1; i <= n; i++){
		if(indegree[i] == 0){
			q.push(i);//�����Ϊ��Ľڵ�ѹ����� 
		}
	}
	while(!q.empty()){
		vi = q.front();
		q.pop();
		printf("c%d\t",vi);//������Ϊ��Ľڵ� 
		for(int i = 0; i < gal[vi].size(); i++){
			indegree[gal[vi][i]]--;//��vi���ڽӵ����ȼ�1
			if(indegree[gal[vi][i]] == 0){
				q.push(gal[vi][i]);//�����Ϊ��Ľڵ�ѹ����� 
			} 
		}
	}
 }

void TopologicalSort3(){//����ջ���� 
	stack<int> s;//���������Ϊ0�Ľڵ����
	int vi;//vertex index
	for(int i = 1; i <= n; i++){
		if(indegree[i] == 0){
			s.push(i);//�����Ϊ��Ľڵ�ѹ����� 
		}
	}
	while(!s.empty()){
		vi = s.top();
		s.pop();
		printf("c%d\t",vi);//������Ϊ��Ľڵ� 
		for(int i = 0; i < gal[vi].size(); i++){
			indegree[gal[vi][i]]--;//��vi���ڽӵ����ȼ�1
			if(indegree[gal[vi][i]] == 0){
				s.push(gal[vi][i]);//�����Ϊ��Ľڵ�ѹ����� 
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

