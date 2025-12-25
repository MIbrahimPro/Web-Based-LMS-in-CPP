#ifndef USER_H
#define USER_H

#include <string>

enum class UserType
{
    NONE,
    ADMIN,
    TEACHER,
    STUDENT
};

class User
{
protected:
    std::string id;
    std::string password;
    UserType userType;

public:
    User();
    User(const std::string &id, const std::string &password, UserType type);
    virtual ~User() = default;

    std::string getId() const;
    std::string getPassword() const;
    UserType getUserType() const;

    void setId(const std::string &id);
    void setPassword(const std::string &password);

    virtual bool authenticate(const std::string &inputPassword) const;
    virtual std::string toCSV() const = 0; 
    virtual void fromCSV(const std::string &csvLine) = 0;
    virtual std::string getDisplayName() const = 0;
};

#endif
