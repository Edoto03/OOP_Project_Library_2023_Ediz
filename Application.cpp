#include "Application.hpp"

Application &Application::getInstance()
{
    static Application object;

    return object;
}

void Application::process()
{
    cout << "Welcome to Ediz's Library. Firstly, please enter a filename where you want to store all your users: " << std ::endl;
    string UserFile;
    cin >> UserFile;
    this->app.setUsersFile(UserFile);
    cin.ignore();

    string command;
    do
    {
        cout << ">";
        std::getline(cin, command);
        this->app.commands(command);
    } while (command != "exit");
}