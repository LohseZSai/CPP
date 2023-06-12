#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class CalculateSystem {
    private:
        int maxQuestions;
        int questionCount;
        int correctCount;
        double num1, num2, result;
        char operatorType;
        time_t startTime, endTime;
        int minOperand, maxOperand;
        int timeLimit;

        // 生成指定范围内的随机整数
        int generateNumber() {
            return rand() % (maxOperand - minOperand + 1) + minOperand;
        }

        // 生成随机运算符
        char generateOperator() {
            char operators[] = {'+', '-', '*', '/'};
            int index = rand() % 4;
            return operators[index];
        }

        // 检查答案是否正确
        bool checkAnswer(double answer) {
            bool correct = answer == result;
            if (correct) {
                correctCount++;
                cout << "正确!\n";
            } else {
                cout << "错误!\n";
            }
            return correct;
        }

        // 显示题目
        void displayQuestion() {
            cout << (questionCount + 1) << "." << "你看看这道题等于多少:  " << num1 << " " << operatorType << " " << num2 << "?\n";
        }

        // 检查是否超时
        bool isTimeUp() {
            time_t now = time(NULL);
            return (now - startTime) >= timeLimit;
        }

    public:
        CalculateSystem(int maxQuestions = 10, int minOperand = 1, int maxOperand = 10, int timeLimit = 60) {
            srand(time(NULL));
            this->maxQuestions = maxQuestions;
            this->minOperand = minOperand;
            this->maxOperand = maxOperand;
            this->timeLimit = timeLimit;
        }

        void startQuiz() {
            questionCount = 0;
            correctCount = 0;
            startTime = time(NULL);
        }

        void endQuiz() {
            endTime = time(NULL);
            cout << "You answered " << correctCount << " out of " << questionCount << " questions correctly in " << (endTime - startTime) << " seconds." << endl;
        }

        // 用于判断是不是该结束程序了
        bool isQuizOver() {
            return questionCount == maxQuestions || isTimeUp();
        }

        // 该函数用于题目的生成
        void generateQuestion() {
            if (isQuizOver()) {
                return;
            }
            num1 = generateNumber();
            num2 = generateNumber();
            operatorType = generateOperator();
            switch (operatorType) {
                case '+': result = num1 + num2; break;
                case '-': result = num1 - num2; break;
                case '*': result = num1 * num2; break;
                case '/': result = num1 / num2; break;
            }
            displayQuestion();
            questionCount++;
        }

        // 该函数用于测试人员回答系统随机出现的题目
        bool answerQuestion(double answer) {
            bool correct = checkAnswer(answer);
            if (isQuizOver()) {
                endQuiz();
            }
            return correct;
        }
};

int main() {
    int maxQuestions, minOperand, maxOperand, timeLimit;
    cout << "请输入题目数量: ";
    cin >> maxQuestions;
    cout << "请输入操作数的最小值: ";
    cin >> minOperand;
    cout << "请输入操作数的最大值: ";
    cin >> maxOperand;
    cout << "请输入时间限制(秒): ";
    cin >> timeLimit;

    CalculateSystem quiz(maxQuestions, minOperand, maxOperand, timeLimit);
    double answer;

    quiz.startQuiz();

    do {
        quiz.generateQuestion();
        cout << "输入你的答案: ";
        cin >> answer;
    } while (quiz.answerQuestion(answer));

    return 0;
}
