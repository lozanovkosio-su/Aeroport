#ifndef UNTITLED2_CARGOPLANE_H
#define UNTITLED2_CARGOPLANE_H
#include "Plane.h"
#include <iostream>
#include <string>
#include <vector>
#include <optional>


class CargoPlane : public Plane {
public:
    int requiredLenght() const override;
    void decreaseHealth() override;
    double getTax() const override;
    std::unique_ptr<Plane> clone() const override;
};


#endif //UNTITLED2_CARGOPLANE_H