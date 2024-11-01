#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <stack>
#include <sstream>
#include <map>
#include <unordered_map>

#include <stack>
#include <unordered_map>
#include <string>
#include <cctype>

class Solution
{
    std::stack<double> num; // Change to double to handle floating-point numbers
    std::stack<char> op;
    std::unordered_map<char, int> priority{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

    void eval()
    {
        double b = num.top();
        num.pop(); // Use double
        char c = op.top();
        op.pop();
        switch (c)
        {
        case '+':
            num.top() += b;
            break;
        case '-':
            num.top() -= b;
            break;
        case '*':
            num.top() *= b;
            break;
        case '/':
            if (b == 0)
            {
                throw std::runtime_error("Division by zero"); // Handle division by zero
            }
            num.top() /= b;
            break;
        }
    }

public:
    double calculate(std::string s)
    { // Change return type to double
        for (int i = 0, N = s.size(); i < N; ++i)
        {
            if (s[i] == ' ')
                continue;
            if (isdigit(s[i]))
            {
                double n = 0; // Use double
                while (i < N && isdigit(s[i]))
                    n = n * 10 + s[i++] - '0';
                if (i < N && s[i] == '.')
                { // Handle decimal point
                    ++i;
                    double decimalPlace = 0.1;
                    while (i < N && isdigit(s[i]))
                    {
                        n += (s[i++] - '0') * decimalPlace;
                        decimalPlace *= 0.1;
                    }
                }
                --i; // Decrement to counter the for loop increment
                num.push(n);
            }
            else if (s[i] == '(')
            {
                op.push(s[i]);
            }
            else if (s[i] == ')')
            {
                while (op.top() != '(')
                    eval();
                op.pop();
            }
            else
            {
                while (op.size() && op.top() != '(' && priority[op.top()] >= priority[s[i]])
                    eval();
                op.push(s[i]);
            }
        }
        while (op.size())
            eval();
        return num.top();
    }
};

std::string trimLeadingSpaces(const std::string &input)
{
    size_t start = input.find_first_not_of(" ");
    return (start == std::string::npos) ? "" : input.substr(start);
}

void show(const std::string &message)
{
    std::cout << message << std::endl;
}

void repeat(int times, const std::string &message)
{
    for (int i = 0; i < times; i++)
    {
        show(message);
    }
}

void add(int a, int b)
{
    std::cout << "Result: " << (a + b) << std::endl;
}

void subtract(int a, int b)
{
    std::cout << "Result: " << (a - b) << std::endl;
}

void multiply(int a, int b)
{
    std::cout << "Result: " << (a * b) << std::endl;
}

void divide(float a, float b)
{
    if (b == 0)
    {
        std::cout << "We cannot divide by 0." << std::endl;
        return;
    }
    std::cout << "Result: " << (a / b) << std::endl;
}

void drawSquare(int side)
{
    for (int i = 0; i < side; ++i)
    {
        for (int j = 0; j < side; ++j)
        {
            std::cout << "* ";
        }
        std::cout << std::endl;
    }
}

void uppercase(const std::string &text)
{
    std::string result = text;
    for (char &c : result)
    {
        c = toupper(c);
    }
    std::cout << "Uppercase: " << result << std::endl;
}

void ask(const std::string &question)
{
    std::cout << question << std::endl;
    std::string response;
    getline(std::cin, response);
    std::cout << "You said: " << response << std::endl;
}

void space()
{
    std::cout << "-------------------------------------------" << std::endl;
}

void processCommands()
{
    std::string command;

    std::cout << "Enter a command:" << std::endl;
    while (getline(std::cin, command))
    {
        std::cout << std::endl;
        if (command.rfind("show:", 0) == 0)
        {
            std::string message = command.substr(6);
            show(message);
            space();
        }
        else if (command.rfind("repeat", 0) == 0)
        {
            command = command.substr(0, 7) + trimLeadingSpaces(command.substr(7));
            int i = 7;
            int times = 0;
            while (command.size() > i)
            {
                if (isdigit(command[i]))
                {
                    times = times * 10 + (command[i++] - '0');
                }
                else
                {
                    break;
                }
            }
            std::string message = command.substr(9);
            repeat(times, message);
            space();
        }
        else if (command.rfind("add ", 0) == 0)
        {
            int spacePos = command.find(" to ");
            int a = std::stoi(command.substr(4, spacePos - 4));
            int b = std::stoi(command.substr(spacePos + 4));
            add(a, b);
            space();
        }
        else if (command.rfind("subtract ", 0) == 0)
        {
            int spacePos = command.find(" from ");
            int b = std::stoi(command.substr(9, spacePos - 9));
            int a = std::stoi(command.substr(spacePos + 6));
            subtract(a, b);
            space();
        }
        else if (command.rfind("multiply ", 0) == 0)
        {
            int spacePos = command.find(" by ");
            int a = std::stoi(command.substr(9, spacePos - 9));
            int b = std::stoi(command.substr(spacePos + 4));
            multiply(a, b);
            space();
        }
        else if (command.rfind("divide ", 0) == 0)
        {
            int spacePos = command.find(" by ");
            float a = std::stof(command.substr(7, spacePos - 7));
            float b = std::stof(command.substr(spacePos + 4));
            divide(a, b);
            space();
        }
        else if (command.rfind("draw square ", 0) == 0)
        {
            int side = std::stoi(command.substr(12));
            drawSquare(side);
            space();
        }
        else if (command.rfind("uppercase: ", 0) == 0)
        {
            std::string text = command.substr(10);
            uppercase(text);
            space();
        }
        else if (command.rfind("ask: ", 0) == 0)
        {
            std::string question = command.substr(5);
            ask(question);
            space();
        }
        else if (command.rfind("evaluate: ", 0) == 0)
        {
            Solution solution;
            std::string expression = command.substr(10);
            double result = solution.calculate(expression);
            std::cout << "Result: " << result << std::endl;
            space();
        }
        else if (command == "bye")
        {
            break;
        }
        else
        {
            std::cout << "Unknown command. Try commands like 'show:', 'add', 'subtract', 'draw square', 'uppercase:', 'ask:', 'evaluate:'." << std::endl;
            space();
        }
    }
}

int main()
{
    processCommands();
    return 0;
}
