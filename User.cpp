//
// Created by Kosio Lozanov on 17.06.26.
//

#include "User.h"

User::User(const std::string &name_, const std::string &password_, const Role &role_):
name(name_), password(password_), role(role_)
{
}

const std::string & User::getName() const {
    return name;
}

const std::string & User::getPass() const {
    return password;
}

const Role & User::getRole() const {
    return role;
}

const std::vector<std::shared_ptr<Ticket>> & User::getTickets() const {
    return tickets;
}
