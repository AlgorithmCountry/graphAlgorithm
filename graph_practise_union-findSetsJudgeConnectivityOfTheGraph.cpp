/*
	Name: graph_practise_union-findSetsJudgeConnectivityOfTheGraph.cpp
	Date: 
	Description:
*/
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
int n,m,ne;//number of edges
vector<int> pre;

int find(int x){
	int r = x;
	while(pre[r] != r){//这一句比较难理解，其实就是没有上级的时候，也就是上级是自己的时候，就找到头了。 
		r = pre[r];
	}
	int i  = x,j; 
	while(pre[i]!=r) //路径压缩，其实是把刚才经过的所有节点的的父节点都调为r 
    {
        j = pre[i];
        pre[i] = r;
        i = j;
    }
    return r;
}

void join(int x,int y)    //让x和y有共同的
{

    int fx=find(x);//分别找到x和y的父节点 
	int fy=find(y);   
    if(fx!=fy){//如果x，y的父节点不想等，那么让其中一个作为父节点，也就是让x和y直接连通 
    	 /*可判断一下，让谁当父节点
		 int f = min(fx,fy);
		 pre[fx] = root;
		 pre[fy] = root; 
		 */ 
		 pre[fx ]=fy; 
		 ne--;
	}
}

int main(){
	if(!freopen("graph_practise_union-findSetsJudgeConnectivityOfTheGraph.in","r",stdin)){
		cerr<<"Open file error";
		return 0;
	}
	
	cin>>n>>m;//读入顶点数和边数 
	ne = n - 1;//连通图最小的边数应该是n-1 
	pre.resize(n+1);
	
	for(int i = 1; i <= n; i++){
		pre[i] = i;//初始化，一开始每个点都是独立的，自成一个集合，从1编号到n，每个点的上级都是自己 
	}
	
	int v1,v2,f1,f2;
	for(int i = 1; i <= m; i++){
		cin>>v1>>v2;
		join(v1,v2);
	}
	
	cout<<ne<<endl;

	return 0;
}


