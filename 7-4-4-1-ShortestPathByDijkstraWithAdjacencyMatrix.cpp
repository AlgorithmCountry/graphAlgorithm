/*
	Name:7-4-4-1-ShortestPathByDijkstraWithAdjacencyMatrix.cpp
	Date: 
	Description:
	时间复杂度O(n2) 
*/
#include <iostream>
#include <cstdio>
#include <vector>
#define INFINITY 32767

using namespace std;
vector<int> vertexes;

vector<vector<int> > arcs;
int arcNum = 0;
int vexNum = 0;

void CrtMatrixGraph(){
	cin>>vexNum;
	vertexes.resize(vexNum);
	arcs.resize(vexNum,vector<int>(vexNum,INFINITY));
//	for(int i = 0; i < g.vexNum; i++){
//		cin>>g.vertexes[i];
//		g.arcs[i].resize(g.vexNum);
//	}
	
    for(int i = 0; i < vexNum; i++){
		for(int j = 0; j < vexNum; j++){
			cin>>arcs[i][j];
		}
	}
}

void OutMatrixGraph(){
	cout<<vexNum<<"\t"<<arcNum<<endl;
    for(int i = 0; i < vexNum; i++){
		for(int j = 0; j < vexNum; j++){
			cout<<arcs[i][j]<<"\t";
		}
		cout<<endl;
	}
}

void ShortestPahtDijkstra(int v){
	int dist[vexNum];//dist[i]中存放顶点v到顶点i的当前最短路径长度 distance
	int path[vexNum];//path[i]中存放顶点i的上一个顶点是那一个 
	int s[vexNum];//s为已找到最短路径的终点集合

	int mindis,i,j,u,pre;

	for(i = 0; i < vexNum; i++){
		dist[i]= arcs[v][i];        /*初始化距离*/
    	s[i]=0;                    /*辅助数组s[]置初值为0*/
     	if(arcs[v][i]<INFINITY){ 
        	path[i]=v;//初始化每一条弧的起始点 
		}else{
			path[i]=-1;
		}
	}

	s[v]=1;
	//path[v]=0;
	for(i=0;i<vexNum;i++){
    	mindis=INFINITY;
    	u=-1;
    	for(j=0;j<vexNum;j++){
	    	if(s[j]==0 && dist[j]<mindis){
				u=j;
	            mindis=dist[j];
        	}	
		}
         
		if(u!=-1){
			s[u]=1;
	        for(j=0;j<vexNum;j++)
	            if(s[j]==0 && arcs[u][j]<INFINITY && dist[u]+arcs[u][j]<dist[j]){
					dist[j]=dist[u]+arcs[u][j];
					path[j]=u;
            }
		}
   }
   
   printf("\nDijkstra算法求解如下：\n");
   for(i=0;i<vexNum;i++){
   		if(i!=v){
		   printf("\n%d->%d:",v,i);
		   if(s[i]==1){
			   	printf("路径长度为%2d,",dist[i]);
				pre=i;
				printf("路径逆序为：");
				while(pre!=v){
					printf("%d,",pre);
					pre=path[pre];
				}
				printf("%d\n",pre);
        	}else{
				printf("不存在路径\n");	
			}
      }
   }
}

int main(){
	const char *fileName = "7-4-4-1-ShortestPathByDijkstraWithAdjacencyMatrix.in";
	if(!freopen(fileName,"r",stdin)){
		cout<<"Open file error!";
		return 0 ;
	}

	CrtMatrixGraph();
	
	//OutMatrixGraph();

	ShortestPahtDijkstra(0);
	return 0;
}


