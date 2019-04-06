/*
	Name:7-4-4-2-ShortestPathByFloydWithAdjacencyMatrix.cpp
	Date: 
	Description:ʱ�临�Ӷ�O��n2�� 
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
	int dist[g.vexNum];//dist[i]�д�Ŷ���i�ĵ�ǰ���·������
	int path[g.vexNum];//path[i]�д�Ŷ���i�ĵ�ǰ���·��
	int s[g.vexNum];//sΪ���ҵ����·�����յ㼯��

	int mindis,i,j,u,pre;

	for(i = 0; i < g.vexNum; i++){
		dist[i]= g.arcs[v][i];        /*��ʼ������*/
    	s[i]=0;                    /*��������s[]�ó�ֵΪ0*/
     	if(g.arcs[v][i]<INFINITY){ 
        	path[i]=v;//��ʼ��ÿһ��������ʼ�� 
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
   
   printf("\nDijkstra�㷨������£�\n");
   for(i=0;i<g.vexNum;i++){
   		if(i!=v){
		   printf("\n%d->%d:",v,i);
		   if(s[i]==1){
			   	printf("·������Ϊ%2d,",dist[i]);
				pre=i;
				printf("·������Ϊ��");
				while(pre!=v){
					printf("%d,",pre);
					pre=path[pre];
				}
				printf("%d\n",pre);
	        }else{
				printf("������·��\n");	
			}
      	}
   }
}

/*
vs��ʾ��ʼ�㡢ve��ʾ������ 
����һ�����͵Ķ�̬�滮 
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
    
    printf("\nFloyed �㷨������£� ");
    for(i=0;i<g.vexNum;i++){
		for(j=0;j<g.vexNum;j++){
			if(i!=j&&A[i][j]!=INFINITY){
				printf("\n%d->%d:",i,j);
				printf("���·������Ϊ:%d ,",A[i][j]);
				printf("·��Ϊ:%d->",i);
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


