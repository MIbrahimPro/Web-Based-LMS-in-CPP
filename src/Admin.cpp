#include "../include/Admin.h"
#include <sstream>

Admin::Admin() : User(), username("")
{
    userType = UserType::ADMIN;
}

Admin::Admin(const std::string &username, const std::string &password)
    : User(username, password, UserType::ADMIN), username(username) {}

std::string Admin::getUsername() const { return username; }

void Admin::setUsername(const std::string &username)
{
    this->username = username;
    this->id = username; 
}

std::string Admin::toCSV() const
{
    return username + "," + password;
}

void Admin::fromCSV(const std::string &csvLine)
{
    std::stringstream ss(csvLine);
    std::string token;

    if (std::getline(ss, token, ','))
    {
        username = token;
        id = token;
    }
    if (std::getline(ss, token, ','))
    {
        password = token;
    }
    userType = UserType::ADMIN;
}

std::string Admin::getDisplayName() const
{
    return username;
}
