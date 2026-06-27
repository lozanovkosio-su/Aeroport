//
// Created by Kosio Lozanov on 24.06.26.
//

#include "PassengerPlane.h"
#include "Flight.h"
#include "Engine.h"


int PassengerPlane::requiredLenght() const {
    return 2000;
}

void PassengerPlane::decreaseHealth() {
    health -= 35;
    if (health <= 20) {
        availableForFlights = false;
    }
}


double Plane::getTax() const {
    double tax = 0;
    for (std::shared_ptr<Flight>& ptr:Engine::flights) {
        if (ptr->getCode() == id) {
            for (std::shared_ptr<Ticket>& tick:ptr->getTickets()) {
                tax += tick->getAmaount();
            }
        }
    }
    return 0.1*tax;
}
std::unique_ptr<Plane> PassengerPlane::clone() const {
    return std::make_unique<PassengerPlane>(*this);
}