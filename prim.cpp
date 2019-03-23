#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define ll long long

using namespace std;

struct node
{
	ll pr = 0;				//权值 
	ll sv;					//结束 
	ll ev;					//开始 

	
};

vector <vector <ll> > edges;
vector <node> g;
ll n;
vector <ll> added;


void CrtG()
{
	cin >> n;
	edges.resize(n,vector <ll> (n,0));
	g.resize(n + 1);
	
	added.resize(n);
	
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			cin >> edges[i][j];
		}
	}
}

void OutG() 
{
	for(const auto& i : edges)
	{
		for(const auto& v : i)
		{
			cout << v << "\t";
		}
		cout << endl;
	}
}

void neww(ll start)
{
	for(int i = 0;i < n;i++)
	{
		if(g[i].pr > edges[start][i])
		{
			g[i].pr = edges[start][i];
			g[i].sv = start;
			g[i].ev = i;
		  }  
	} 
}

void prim(ll start)
{
	ll tmp = 32767;
	ll idx = 0;
	
	for(int i = 0;i < n;i++)
	{
		g[i].pr = edges[start][i];
		g[i].sv = start;
		g[i].ev = i;  
	} 
	
	for(int e = 0;e < n - 1;e++)
	{
		for(int i = 0;i < n;i++)
		{
			if(g[i].pr > 0&&g[i].pr < tmp)
			{
				tmp = g[i].pr;
				idx = i;
			}
		}
		
		cout << g[idx].sv+1<<" -> " << g[idx].ev+1<< "  :  " << g[idx].pr;
		cout << endl;
		added[idx] = 0;
		g[idx].pr = 0;		
		tmp = 32767;
		neww(idx);
	}
}

int main()
{
	if(!freopen("MinimumSpaningTreePrim.in","r",stdin))
	{
		cerr << "error!";
		return 1;	
	}	
	CrtG();
	OutG();
	prim(0); 
	return 0;
}
