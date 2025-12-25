#include "../include/User.h"

User::User() : id(""), password(""), userType(UserType::NONE) {}

User::User(const std::string &id, const std::string &password, UserType type)
    : id(id), password(password), userType(type) {}

std::string User::getId() const { return id; }
std::string User::getPassword() const { return password; }
UserType User::getUserType() const { return userType; }

void User::setId(const std::string &id) { this->id = id; }
void User::setPassword(const std::string &password) { this->password = password; }

bool User::authenticate(const std::string &inputPassword) const
{
    return password == inputPassword;
}
