#include "../include/Teacher.h"
#include <sstream>

Teacher::Teacher() : User(), teacherId(""), name("")
{
    userType = UserType::TEACHER;
}

Teacher::Teacher(const std::string &teacherId, const std::string &name, const std::string &password)
    : User(teacherId, password, UserType::TEACHER), teacherId(teacherId), name(name) {}

std::string Teacher::getTeacherId() const { return teacherId; }
std::string Teacher::getName() const { return name; }

void Teacher::setTeacherId(const std::string &teacherId)
{
    this->teacherId = teacherId;
    this->id = teacherId;
}
void Teacher::setName(const std::string &name) { this->name = name; }

std::string Teacher::toCSV() const
{
    return teacherId + "," + name + "," + password;
}

void Teacher::fromCSV(const std::string &csvLine)
{
    std::stringstream ss(csvLine);
    std::string token;

    if (std::getline(ss, token, ','))
    {
        teacherId = token;
        id = token;
    }
    if (std::getline(ss, token, ','))
    {
        name = token;
    }
    if (std::getline(ss, token, ','))
    {
        password = token;
    }
    userType = UserType::TEACHER;
}

std::string Teacher::getDisplayName() const
{
    return name;
}
