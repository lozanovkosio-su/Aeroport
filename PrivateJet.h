#ifndef UNTITLED2_PRIVATEJET_H
#define UNTITLED2_PRIVATEJET_H
#include "Plane.h"
#include <iostream>
#include <string>
#include <vector>
#include <optional>

class PrivateJet : public Plane {
public:
    int requiredLenght() const override;
    void decreaseHealth() override;
    double getTax() const override;
};


#endif //UNTITLED2_PRIVATEJET_H