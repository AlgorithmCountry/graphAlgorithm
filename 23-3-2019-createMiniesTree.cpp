/*
n
1 2 3 . n
2 .
3
.
n

*/
//inputStyle------------------------------------------------//

#include<iostream>
#include<algorithm>
using namespace std;
//head------------------------------------------------------//

int n;
int bg[100][100];
//public----------------------------------------------------//

int gra[100][100];
//prim's----------------------------------------------------//

int ln;
struct t{
	int c1,c2,n;
}l[11000];
int have[100];
//kruskal's-------------------------------------------------//

void into(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			cin>>gra[i][j];
			if(gra[i][j]) l[++ln].n=gra[i][j],l[ln].c1=i,l[ln].c2=j;
		}
	return;
}
void print(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<bg[i][j]<<" ";
		}
		cout<<endl;
	}
	return;
}
//pubic-----------------------------------------------------//

void prim(){
	bg[1][0]=1;
	for(int i=1;i<=n-1;i++){
		int mn=0x7fffff,sc,ec;
		for(int j=1;j<=n;j++)
			if(bg[j][0])
				for(int k=1;k<=n;k++)
					if(!bg[k][0]&&gra[j][k]&&gra[j][k]<mn)
						mn=gra[j][k],sc=j,ec=k;
		bg[ec][sc]=bg[sc][ec]=mn;
		bg[ec][0]=1;
	}
	return;
}
//prim-----------------------------------------------------//

bool cmp(t a,t b){
	return a.n<b.n;
}
void same(int a,int b){
	int t=have[a],bt=have[b];
	for(int i=1;i<=n;i++){
		if(have[i]==bt) have[i]=t;
	}
	return;
}
void kruskal(){
	sort(l+1,l+ln,cmp);
	for(int i=1;i<=n;i++) have[i]=i;
	for(int i=1,k=1;k<=n-1&&i<=ln;i++){
		if(have[l[i].c1]!=have[l[i].c2]){
			same(l[i].c1,l[i].c2);
			bg[l[i].c1][l[i].c2]=bg[l[i].c2][l[i].c1]=l[i].n;
			k++; 
			cout<<"in"<<l[i].c1<<","<<l[i].c2<<":"<<l[i].n<<endl;
		}else{
			cout<<"pass"<<l[i].c1<<","<<l[i].c2<<":"<<l[i].n<<endl;
		}
	}
	return;
}
//kruskal-------------------------------------------------//

int main(){
	into();
	
	//prim();
	kruskal();
	//choose one in the two
	
	print();
	return 0;
}
//main----------------------------------------------------//
