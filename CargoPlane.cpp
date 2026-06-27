//
// Created by Kosio Lozanov on 24.06.26.
//

#include "CargoPlane.h"

int CargoPlane::requiredLenght() const {
    return 3000;
}

void CargoPlane::decreaseHealth() {
    health -= 45;
    if (health <= 20) {
        availableForFlights = false;
    }
}

double CargoPlane::getTax() const {
    return 15*capacity;
}

std::unique_ptr<Plane> CargoPlane::clone() const {
    return std::make_unique<CargoPlane>(*this);
}