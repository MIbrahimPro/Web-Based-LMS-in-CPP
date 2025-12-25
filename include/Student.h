#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User
{
private:
    std::string studentId;
    std::string name;

public:
    Student();
    Student(const std::string &studentId, const std::string &name, const std::string &password);

    std::string getStudentId() const;
    std::string getName() const;

    void setStudentId(const std::string &studentId);
    void setName(const std::string &name);

    std::string toCSV() const override;
    void fromCSV(const std::string &csvLine) override;
    std::string getDisplayName() const override;
};

#endif
