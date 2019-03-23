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
	while(pre[r] != r){//��һ��Ƚ�����⣬��ʵ����û���ϼ���ʱ��Ҳ�����ϼ����Լ���ʱ�򣬾��ҵ�ͷ�ˡ� 
		r = pre[r];
	}
	int i  = x,j; 
	while(pre[i]!=r) //·��ѹ������ʵ�ǰѸղž��������нڵ�ĵĸ��ڵ㶼��Ϊr 
    {
        j = pre[i];
        pre[i] = r;
        i = j;
    }
    return r;
}

void join(int x,int y)    //��x��y�й�ͬ��
{

    int fx=find(x);//�ֱ��ҵ�x��y�ĸ��ڵ� 
	int fy=find(y);   
    if(fx!=fy){//���x��y�ĸ��ڵ㲻��ȣ���ô������һ����Ϊ���ڵ㣬Ҳ������x��yֱ����ͨ 
    	 /*���ж�һ�£���˭�����ڵ�
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
	
	cin>>n>>m;//���붥�����ͱ��� 
	ne = n - 1;//��ͨͼ��С�ı���Ӧ����n-1 
	pre.resize(n+1);
	
	for(int i = 1; i <= n; i++){
		pre[i] = i;//��ʼ����һ��ʼÿ���㶼�Ƕ����ģ��Գ�һ�����ϣ���1��ŵ�n��ÿ������ϼ������Լ� 
	}
	
	int v1,v2,f1,f2;
	for(int i = 1; i <= m; i++){
		cin>>v1>>v2;
		join(v1,v2);
	}
	
	cout<<ne<<endl;

	return 0;
}


