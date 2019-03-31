/*
	Name:7-4-4-1-ShortestPathByDijkstraWithAdjacencyMatrix.cpp
	Date: 
	Description:
	ʱ�临�Ӷ�O(n2) 
*/
#include <iostream>
#include <cstdio>
#include <vector>
#define INFINITY 32767

using namespace std;
vector<vector<int> > arcs;
int arcNum = 0;
int vexNum = 0;

void CrtMatrixGraph(){
	cin>>vexNum;
	arcs.resize(vexNum+1,vector<int>(vexNum+1,32767) );

    for(int i = 0; i < vexNum; i++){
		for(int j = 0; j < vexNum; j++){
			cin>>arcs[i][j];
			if(arcs[i][j] < INFINITY){
				arcNum++;
			}
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
	int dist[vexNum];//dist[i]�д�Ŷ���v������i�ĵ�ǰ���·������distance
	int path[vexNum];//path[i]�д�Ŷ���i����һ����������һ�� 
	int s[vexNum];//sΪ���ҵ����·�����յ㼯��

	int mindis,i,j,u,pre;

	for(i = 0; i < vexNum; i++){
		dist[i]= arcs[v][i];        /*��ʼ������*/
    	s[i]=0;                    /*��������s[]�ó�ֵΪ0*/
     	if(arcs[v][i]<INFINITY){ 
        	path[i]=v;//��ʼ��ÿһ��������ʼ�� 
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
	          if(s[j]==0)
	            if(arcs[u][j]<INFINITY && dist[u]+arcs[u][j]<dist[j]){
					dist[j]=dist[u]+arcs[u][j];
					path[j]=u;
            }
		}
   }
   
   printf("\nDijkstra�㷨������£�\n");
   for(i=0;i<vexNum;i++){
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

int main(){
	const char *fileName = "7-4-4-1-ShortestPathByDijkstraWithAdjacencyMatrix.in";
	if(!freopen(fileName,"r",stdin)){
		cout<<"Open file error!";
		return 0 ;
	}

	CrtMatrixGraph();
	
	OutMatrixGraph();

	ShortestPahtDijkstra(0);
	return 0;
}


