// 姓名：李腾俊     学号：2109050104     班级 ：数据2101
#include <iostream>
#include <cstring>
using namespace std;


bool CheckDuplicate(char arr[], int start, int end)
{
	if (end > start)
	{
		for (int i = start; i < end; i++)
		{
			if (arr[end] == arr[i])
				return false;
		}
	}
	return true;
}

void Permutation(char arr[], int start, int length)
{
	int index;
	char temp;
	if (start == length)
	{
		for (index = 0; index < length; index++)
			cout << arr[index];
		cout << endl;
		return;
	}

	for (index = start; index <= length - 1; index++)
	{
		if (CheckDuplicate(arr, start, index))
		{
			temp = arr[index];
			arr[index] = arr[start];
			arr[start] = temp;
			Permutation(arr, start + 1, length);
			temp = arr[index];
			arr[index] = arr[start];
			arr[start] = temp;
		}
	}
}

void Permute(char arr[])
{
	Permutation(arr, 0, strlen(arr));
}

//测试函数
int main()
{
	char arr[] = "112";
	Permute(arr);
	return 0;
}