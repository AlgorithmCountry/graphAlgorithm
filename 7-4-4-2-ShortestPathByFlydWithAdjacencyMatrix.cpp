/*
	Name:7-4-4-2-ShortestPathByFloydWithAdjacencyMatrix.cpp
	Date: 
	Description:时间复杂度O（n2） 
*/
#include <iostream>
#include <cstdio>
#include <vector>
#define INFINITY 32767

using namespace std;
struct MatrixGraph{
	vector<int> vertexes;
	vector<vector<int> > arcs;
	int arcNum = 0;
	int vexNum = 0;
};

void CrtMatrixGraph(MatrixGraph &g){
	cin>>g.vexNum;
	g.vertexes.resize(g.vexNum);
	g.arcs.resize(g.vexNum);
	for(int i = 0; i < g.vexNum; i++){
		cin>>g.vertexes[i];
		g.arcs[i].resize(g.vexNum);
	}
	
    for(int i = 0; i < g.vexNum; i++){
		for(int j = 0; j < g.vexNum; j++){
			cin>>g.arcs[i][j];
			if(g.arcs[i][j] < INFINITY){
				g.arcNum++;
			}
		}
	}
}

void OutMatrixGraph(MatrixGraph &g){
	cout<<g.vexNum<<"\t"<<g.arcNum<<endl;
    for(int i = 0; i < g.vexNum; i++){
		for(int j = 0; j < g.vexNum; j++){
			cout<<g.arcs[i][j]<<"\t";
			if(g.arcs[i][j] < INFINITY){
				g.arcNum++;
			}
		}
		cout<<endl;
	}
}

void ShortestPahtDijkstra(MatrixGraph &g,int v){
	int dist[g.vexNum];//dist[i]中存放顶点i的当前最短路径长度
	int path[g.vexNum];//path[i]中存放顶点i的当前最短路径
	int s[g.vexNum];//s为已找到最短路径的终点集合

	int mindis,i,j,u,pre;

	for(i = 0; i < g.vexNum; i++){
		dist[i]= g.arcs[v][i];        /*初始化距离*/
    	s[i]=0;                    /*辅助数组s[]置初值为0*/
     	if(g.arcs[v][i]<INFINITY){ 
        	path[i]=v;//初始化每一条弧的起始点 
		}else{
			path[i]=-1;
		}
	}

	s[v]=1;
	path[v]=0;
	for(i=0;i<g.vexNum;i++){
    	mindis=INFINITY;
    	u=-1;
    	for(j=0;j<g.vexNum;j++){
	    	if(s[j]==0 && dist[j]<mindis){
				u=j;
	            mindis=dist[j];
        	}	
		}
         
		if(u!=-1){
			s[u]=1;
	        for(j=0;j<g.vexNum;j++)
	          if(s[j]==0)
	            if(g.arcs[u][j]<INFINITY && dist[u]+g.arcs[u][j]<dist[j]){
					dist[j]=dist[u]+g.arcs[u][j];
					path[j]=u;
            }
		}
   }
   
   printf("\nDijkstra算法求解如下：\n");
   for(i=0;i<g.vexNum;i++){
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

/*
vs表示开始点、ve表示结束点 
这是一个典型的动态规划 
*/
void ShortestPahtFloyd(MatrixGraph &g,int vs,int ve){
	int A[g.vexNum][g.vexNum],path[g.vexNum][g.vexNum];
   	int i,j,k,pre;
  	for(i=0;i<g.vexNum;i++){
	    for(j=0;j<g.vexNum;j++){
			A[i][j]=g.arcs[i][j];
	        path[i][j]=-1;
	    }
	}

    for(k=0;k<g.vexNum;k++){
		for(i=0;i<g.vexNum;i++){
			for(j=0;j<g.vexNum;j++){
				if(A[i][j]>A[i][k]+A[k][j]){
					A[i][j]=A[i][k]+A[k][j];
			        path[i][j]=k;
			    }
			}
		}
    }
    
    printf("\nFloyed 算法求解如下： ");
    for(i=0;i<g.vexNum;i++){
		for(j=0;j<g.vexNum;j++){
			if(i!=j&&A[i][j]!=INFINITY){
				printf("\n%d->%d:",i,j);
				printf("最短路径长度为:%d ,",A[i][j]);
				printf("路径为:%d->",i);
				pre=path[i][j];
				while(pre!=-1){
				 	printf("%d,",pre);
				    pre=path[pre][j];
				}
				printf("%d",j);
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

	MatrixGraph mg;
	CrtMatrixGraph(mg);
	
	//OutMatrixGraph(mg);

	//ShortestPahtDijkstra(mg,0);
	ShortestPahtFloyd(mg,0,1);
	return 0;
}


