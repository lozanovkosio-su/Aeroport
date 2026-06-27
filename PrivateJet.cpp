//
// Created by Kosio Lozanov on 24.06.26.
//

#include "PrivateJet.h"

int PrivateJet::requiredLenght() const {
    return 1000;
}

void PrivateJet::decreaseHealth() {
    health -= 25;
    if (health <= 20) {
        availableForFlights = false;
    }
}

double PrivateJet::getTax() const {
    return 5000;
}
