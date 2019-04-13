#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

vector<vector<int> > gam;
vector<vector<int> > gal;
vector<vector<int> > gial;
vector<char> name;
vector<int> indegree; 
int n; 
int temp;

void CrtG()
{
	cin>>n;
	gam.resize(n+1,vector<int>(n+1,0));
	gal.resize(n+1);
	gial.resize(n+1);
	indegree.resize(n+1,0);
	name.resize(n+1);
	for(int i = 1; i <= n; i++)
	{
		cin>> name[i];
	}
	for(int i =1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			cin>>temp;
			if(temp > 0)
			{
				gam[i][j] = temp;
				gal[i].push_back(j);
				gial[j].push_back(i);
			}
		}
	}
}

void FindIndegreeByAM()
{
	bool dagFlag = false;
	for(int c = 1; c <= n; c++)
	{
		temp = 0;
		for(int r = 1; r <=n; r++)
		{
			if(gam[r][c] > 0)
			{
				temp++;
			}
		}
		indegree[c] = temp;
		if(temp == 0)
		{
			dagFlag = true;
		}
	}
	if(!dagFlag)
	{
		cout<<"this is a direct cyclic graph"<<endl;
	}
}
