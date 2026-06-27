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
    for (std::shared_ptr<Flight>& ptr:listOfFlights) {
        if (ptr->getCode() == flight->getCode()) {
            return true;
        }
    }
    return false;
}
