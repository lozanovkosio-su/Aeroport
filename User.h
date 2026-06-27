#ifndef UNTITLED2_USER_H
#define UNTITLED2_USER_H
#include <iostream>
#include <string>
#include <vector>
#include "Ticket.h"


enum class Role {
    traveler,
    dispetcher,
    admin
};


class User {
protected:
    std::string name;
    std::string password;
    Role role;
    std::vector<std::shared_ptr<Ticket>> tickets;

public:
    User(const std::string& name_, const std::string& password_, const Role& role_);
    const std::string& getName() const;
    const std::string& getPass() const;
    const Role& getRole() const;
    const std::vector<std::shared_ptr<Ticket>>& getTickets() const;
};


#endif //UNTITLED2_USER_H