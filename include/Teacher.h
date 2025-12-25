#ifndef TEACHER_H
#define TEACHER_H

#include "User.h"

class Teacher : public User
{
private:
    std::string teacherId;
    std::string name;

public:
    Teacher();
    Teacher(const std::string &teacherId, const std::string &name, const std::string &password);

    std::string getTeacherId() const;
    std::string getName() const;

    void setTeacherId(const std::string &teacherId);
    void setName(const std::string &name);

    std::string toCSV() const override;
    void fromCSV(const std::string &csvLine) override;
    std::string getDisplayName() const override;
};

#endif
