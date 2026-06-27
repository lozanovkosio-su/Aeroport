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

#include <iomanip>

std::ostream& operator<<(std::ostream& os, const User& u) {
    os << std::quoted(u.name) << ' '
       << std::quoted(u.password) << ' '
       << static_cast<int>(u.role);
    return os;
}

std::istream& operator>>(std::istream& is, User& u) {
    std::string tName, tPass;
    int tRole;

    if (is >> std::quoted(tName) >> std::quoted(tPass) >> tRole) {
        u.name = tName;
        u.password = tPass;
        u.role = static_cast<Role>(tRole);
    }
    return is;
}
