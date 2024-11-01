#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <stack>
#include <sstream>
#include <map>
#include <unordered_map>

std::unordered_map<std::string, std::string> variables;

// Function to set a variable
void setVariable(const std::string &name, const std::string &value)
{
    variables[name] = value;
}

// Function to get a variable value
std::string getVariable(const std::string &name)
{
    if (variables.find(name) != variables.end())
    {
        return variables[name];
    }
    throw std::runtime_error("Undefined variable: " + name);
}

double getValue(const std::string &input)
{
    if (variables.find(input) != variables.end())
    {
        return std::stod(variables[input]);
    }
    return std::stod(input);
}

class Solution
{
    std::stack<double> num;
    std::stack<char> op;
    std::unordered_map<char, int> priority{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

    void eval()
    {
        if (op.empty())
            return;

        double b = num.top();
        num.pop();

        double a = num.top();
        num.pop();

        char c = op.top();
        op.pop();

        switch (c)
        {
        case '+':
            num.push(a + b);
            break;
        case '-':
            num.push(a - b);
            break;
        case '*':
            num.push(a * b);
            break;
        case '/':
            if (b == 0)
            {
                throw std::runtime_error("Division by zero error.");
            }
            num.push(a / b);
            break;
        }
    }

public:
    double calculate(std::string s)
    {
        for (int i = 0, N = s.size(); i < N; ++i)
        {
            if (s[i] == ' ')
                continue;

            if (isdigit(s[i]))
            {
                // Parsing numbers
                double n = 0;
                while (i < N && isdigit(s[i]))
                    n = n * 10 + s[i++] - '0';
                if (i < N && s[i] == '.')
                {
                    ++i;
                    double decimalPlace = 0.1;
                    while (i < N && isdigit(s[i]))
                    {
                        n += (s[i++] - '0') * decimalPlace;
                        decimalPlace *= 0.1;
                    }
                }
                --i;
                num.push(n);
            }
            else if (isalpha(s[i]))
            {
                // Parsing variable names
                std::string varName;
                while (i < N && (isalnum(s[i]) || s[i] == '_'))
                {
                    varName += s[i++];
                }
                --i;

                // Convert the variable value to a number and push to stack
                std::string varValueStr = getVariable(varName);
                double varValue = std::stod(varValueStr);
                num.push(varValue);
            }
            else if (s[i] == '(')
            {
                op.push(s[i]);
            }
            else if (s[i] == ')')
            {
                while (!op.empty() && op.top() != '(')
                {
                    eval();
                }
                op.pop();
            }
            else
            {
                // Operators (+, -, *, /)
                while (!op.empty() && op.top() != '(' && priority[op.top()] >= priority[s[i]])
                {
                    eval();
                }
                op.push(s[i]);
            }
        }

        while (!op.empty())
        {
            eval();
        }

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

void add(const std::string &a, const std::string &b)
{
    double numA = getValue(a);
    double numB = getValue(b);
    std::cout << "Result: " << (numA + numB) << std::endl;
}

void subtract(const std::string &a, const std::string &b)
{
    double numA = getValue(a);
    double numB = getValue(b);
    std::cout << "Result: " << (numA - numB) << std::endl;
}

void multiply(const std::string &a, const std::string &b)
{
    double numA = getValue(a);
    double numB = getValue(b);
    std::cout << "Result: " << (numA * numB) << std::endl;
}

void divide(const std::string &a, const std::string &b)
{

    double numA = getValue(a);
    double numB = getValue(b);
    if (numB == 0)
    {
        std::cout << "We cannot divide by 0." << std::endl;
        return;
    }
    std::cout << "Result: " << (numA / numB) << std::endl;
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
        if (command.rfind("set ", 0) == 0)
        {
            size_t toPos = command.find(" to ");
            if (toPos != std::string::npos)
            {
                std::string varName = command.substr(4, toPos - 4);
                std::string value = command.substr(toPos + 4);
                setVariable(varName, value);
            }
            else
            {
                std::cout << "Invalid syntax for set command. Use: set <variable_name> to <value>" << std::endl;
            }
            space();
        }
        else if (command.rfind("show: ", 0) == 0)
        {
            std::string message = command.substr(6);

            if (variables.find(message) != variables.end())
            {
                std::cout << getVariable(message) << std::endl;
            }
            else
            {
                show(message);
            }

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
            std::string message = command.substr(i + 1); // Extract the message after the number
            repeat(times, message);

            space();
        }
        else if (command.rfind("add ", 0) == 0)
        {
            size_t toPos = command.find(" to ");
            std::string a = command.substr(4, toPos - 4);
            std::string b = command.substr(toPos + 4);
            add(a, b);
            space();
        }
        else if (command.rfind("subtract ", 0) == 0)
        {
            size_t fromPos = command.find(" from ");
            std::string b = command.substr(9, fromPos - 9);
            std::string a = command.substr(fromPos + 6);
            subtract(a, b);
            space();
        }
        else if (command.rfind("multiply ", 0) == 0)
        {
            size_t byPos = command.find(" by ");
            std::string a = command.substr(9, byPos - 9);
            std::string b = command.substr(byPos + 4);
            multiply(a, b);
            space();
        }
        else if (command.rfind("divide ", 0) == 0)
        {
            size_t byPos = command.find(" by ");
            std::string a = command.substr(7, byPos - 7);
            std::string b = command.substr(byPos + 4);
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
            try
            {
                double result = solution.calculate(expression);
                std::cout << "Result: " << result << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }

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
