#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>

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

void processCommands()
{
    std::string command;

    std::cout << "Enter a command:" << std::endl;
    while (getline(std::cin, command))
    {
        if (command.rfind("show", 0) == 0)
        {
            std::string message = command.substr(5);
            show(message);
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
        }
        else if (command.rfind("add ", 0) == 0)
        {
            int spacePos = command.find(" to ");
            int a = std::stoi(command.substr(4, spacePos - 4));
            int b = std::stoi(command.substr(spacePos + 4));
            add(a, b);
        }
        else if (command.rfind("subtract ", 0) == 0)
        {
            int spacePos = command.find(" from ");
            int b = std::stoi(command.substr(9, spacePos - 9));
            int a = std::stoi(command.substr(spacePos + 6));
            subtract(a, b);
        }
        else if (command.rfind("draw square ", 0) == 0)
        {
            int side = std::stoi(command.substr(12));
            drawSquare(side);
        }
        else if (command.rfind("uppercase ", 0) == 0)
        {
            std::string text = command.substr(10);
            uppercase(text);
        }
        else if (command.rfind("ask ", 0) == 0)
        {
            std::string question = command.substr(4);
            ask(question);
        }
        else if (command == "bye")
        {
            break;
        }
        else
        {
            std::cout << "Unknown command. Try commands like 'show', 'add', 'subtract', 'draw square', 'uppercase', 'ask'." << std::endl;
        }
    }
}

int main()
{
    processCommands();
    return 0;
}
