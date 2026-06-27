#ifndef UNTITLED2_PLANE_H
#define UNTITLED2_PLANE_H
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <memory>

enum class PlaneType {
    cargo,
    passengerP,
    privateJ
};

class Plane {
protected:
    std::string id;
    std::vector<std::string> listIds;
    unsigned health = 100;
    PlaneType type;
    unsigned capacity;
    bool availableForFlights = true;
    double flightTax;
public:
    const unsigned getCapacity() const;
    const std::string& getId() const;
    virtual int requiredLenght() const = 0;
    virtual ~Plane() = default;
    virtual void decreaseHealth() = 0;
    virtual double getTax() const = 0;
};


#endif //UNTITLED2_PLANE_H