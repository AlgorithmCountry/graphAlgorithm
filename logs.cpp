#include <iostream>
#include <stdio.h>
#include <windows.h>

using namespace std;

int main()
{
	for(int i = 0;i < 6;i++)
	{
		int x;
		x=MessageBox(GetForegroundWindow(),"i","true",i + 1);
		cout << x; 
	}
	
	return 0;
}
