// 姓名：李腾俊     学号：2109050104     班级 ：数据2101

#include <iostream>
#include <cstring>
const int MaxSize = 100;
using namespace std;

int minimum(int a, int b, int c)
{
	int t;
	t = a < b ? a : b;
	return t < c ? t : c;
}

int calculateDistance(string str1, string str2)
{
	int m = str1.size();
    int n = str2.size();
	int i, j;
	int **dist = new int *[m+1];
	for(i = 0; i < m+1; i++)
	{
		dist[i] = new int[n+1];
	}
	for(i = 0; i <= m; i++)
	{
		dist[i][0] = i;
	}
	for(j = 0; j <= n; j++)
	{	
		dist[0][j] = j;
	}
	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= n; j++)
		{
			if(str1[i-1] == str2[j-1])
			{
				dist[i][j] = dist[i-1][j-1];
			}
			else
			{
				dist[i][j] = minimum(dist[i-1][j-1] + 1, dist[i-1][j] + 1, dist[i][j-1] + 1);
			}
			
		}
		
	}
	return dist[m][n];
}

int main()
{
	string str1 = "lohse";
    string str2 = "scott";
	cout << "String 1: " << str1 << endl;
	cout << "String 2: " << str2 << endl;
    int result = calculateDistance(str1, str2);
    cout << "edit distance is " << result << endl;
}