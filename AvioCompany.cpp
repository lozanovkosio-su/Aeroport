//
// Created by Kosio Lozanov on 24.06.26.
//

#include "AvioCompany.h"

AvioCompany::AvioCompany(const std::string& name, double initialBalance)
    : name(name), firmBalance(initialBalance)
{
    // Векторите listOfPlanes и listOfFlights се инициализират
    // автоматично като празни (няма нужда да пишеш нищо в тялото).
}

void AvioCompany::setBalance(double newB) {
    firmBalance += newB;
}

bool AvioCompany::chechFlight(std::shared_ptr<Flight> &flight) const{
    for (const std::shared_ptr<Flight>& ptr:listOfFlights) {
        if (ptr->getCode() == flight->getCode()) {
            return true;
        }
    }
    return false;
}

#include <iomanip>

std::ostream& operator<<(std::ostream& os, const AvioCompany& ac) {
    os << std::quoted(ac.name) << ' ' << ac.firmBalance;
    return os;
}

std::istream& operator>>(std::istream& is, AvioCompany& ac) {
    std::string tName;
    double tBalance;

    if (is >> std::quoted(tName) >> tBalance) {
        ac.name = tName;
        ac.firmBalance = tBalance;
    }
    return is;
}
