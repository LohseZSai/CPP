#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
int main()
{
ifstream inf;
inf.open("测试.txt");
if (!inf)
{
cerr << "打开文件失败！" << endl;
// return;

}
char line[100];
while (!inf.eof()) //change inf.eof() to !inf.eof()
{
inf.getline(line, 10);
cout << line << endl;

}
inf.close();
return 0;
}
