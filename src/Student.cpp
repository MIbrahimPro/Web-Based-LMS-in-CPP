#include "../include/Student.h"
#include <sstream>

Student::Student() : User(), studentId(""), name("")
{
    userType = UserType::STUDENT;
}

Student::Student(const std::string &studentId, const std::string &name, const std::string &password)
    : User(studentId, password, UserType::STUDENT), studentId(studentId), name(name) {}

std::string Student::getStudentId() const { return studentId; }
std::string Student::getName() const { return name; }

void Student::setStudentId(const std::string &studentId)
{
    this->studentId = studentId;
    this->id = studentId;
}
void Student::setName(const std::string &name) { this->name = name; }

std::string Student::toCSV() const
{
    return studentId + "," + name + "," + password;
}

void Student::fromCSV(const std::string &csvLine)
{
    std::stringstream ss(csvLine);
    std::string token;

    if (std::getline(ss, token, ','))
    {
        studentId = token;
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
    userType = UserType::STUDENT;
}

std::string Student::getDisplayName() const
{
    return name;
}
