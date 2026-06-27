#ifndef UNTITLED2_PASSENGERPLANE_H
#define UNTITLED2_PASSENGERPLANE_H
#include "Plane.h"
#include <iostream>
#include <string>
#include <vector>
#include <optional>


class PassengerPlane : public Plane {
public:
    int requiredLenght() const override;
    void decreaseHealth() override;
    double getTax() const override;
};


#endif //UNTITLED2_PASSENGERPLANE_H