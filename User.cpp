#include "User.hpp"

User::User()
{
    this->username = "";
    this->password = "";
    this->isAdmin = false;
}

User::User(const string &username, const string &password, const bool &isAdmin)
{
    this->setUsername(username);
    this->setPassword(password);
    this->setIsAdmin(isAdmin);
}

void User::printUserInFile(ofstream &out)
{
    string admin = (this->isAdmin) ? "admin" : "notAdmin";
    out << this->username << " " << this->password << " " << admin << std ::endl;
}

void User::setUsername(const string &username)
{
    if (username.empty())
    {
        throw std::invalid_argument("Invalid username.");
    }
    this->username = username;
}

void User::setPassword(const string &password)
{
    if (password.empty())
    {
        throw std::invalid_argument("Invalid password.");
    }
    this->password = password;
}

void User::setIsAdmin(const bool isAdmin)
{
    this->isAdmin = isAdmin;
}

string User::getUsername() const
{
    return this->username;
}

string User::getPassword() const
{
    return this->password;
}

bool User::getIsAdmin() const
{
    return this->isAdmin;
}