#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User
{
private:
    std::string username;

public:
    Admin();
    Admin(const std::string &username, const std::string &password);

    std::string getUsername() const;

    void setUsername(const std::string &username);

    std::string toCSV() const override;
    void fromCSV(const std::string &csvLine) override;
    std::string getDisplayName() const override;
};

#endif
