// 姓名：李腾俊     学号：2109050104     班级 ：数据2101

#include<iostream>
#include<string>
using namespace std;

bool stringMatch(string pattern, string text)
{
	int patternLength = pattern.size();
	int textLength = text.size();
	int i, j;
	bool **match = new bool *[patternLength+1];
	for(i = 0; i < patternLength+1; i++)
	{
		match[i] = new bool[textLength+1];
	}
	match[0][0] = true;
	
	for(j = 1; j <= textLength; j++)
	{
		match[0][j] = false;
	}
	
	for(i = 1; i <= patternLength; i++)
	{
		if(pattern[i-1] == '*')
			match[i][0] = match[i-1][0];
		else
			match[i][0] = false;
	}
	
	for(i = 1; i <= patternLength; i++)
	{
		for(j = 1; j <= textLength; j++)
		{
			if(pattern[i-1] == '*')
				match[i][j] = (match[i-1][j] || match[i][j-1]);
			else if(pattern[i-1] == '?')
				match[i][j] = match[i-1][j-1];
			else
				match[i][j] = (match[i-1][j-1] && (pattern[i-1] == text[j-1]));
		}
	}
	
	return match[patternLength][textLength];
}

int main()
{
	string text = "ABCDEF";
	string pattern = "?B*F";
	cout << "Text: " << text << endl;
	cout << "Pattern: " << pattern << endl;
	if(stringMatch(pattern, text))
		cout << "Text matches the pattern" << endl;
	else
		cout << "Not match the pattern" << endl;
}