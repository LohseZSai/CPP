#include <iostream>
#include <string>

std::string intToString(int number) {
    std::string result;

    // 处理特殊情况：当输入为0时，直接返回字符串"0"
    if (number == 0) {
        result = "0";
        return result;
    }

    // 处理负数情况
    bool isNegative = false;
    if (number < 0) {
        isNegative = true;
        number = -number; // 取绝对值
    }

    // 逐位提取数字并添加到结果字符串中
    while (number > 0) {
        char digit = '0' + (number % 10); // 提取最低位的数字
        result = digit + result; // 添加到结果字符串的最前面
        number /= 10; // 去掉已经处理的最低位
    }

    // 如果是负数，在结果字符串前面添加负号
    if (isNegative) {
        result = '-' + result;
    }

    return result;
}

int main() {
    int number = -123;
    std::string strNumber = intToString(number);
    std::cout <<  strNumber << std::endl;

    return 0;
}