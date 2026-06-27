//
// Created by Kosio Lozanov on 24.06.26.
//

#ifndef UNTITLED2_AVIOCOMPANY_H
#define UNTITLED2_AVIOCOMPANY_H
#include <iostream>
#include <string>
#include <vector>
#include "Plane.h"
#include "Flight.h"





class AvioCompany {
    std::string name;
    double firmBalance;
    std::vector<std::shared_ptr<Plane>> listOfPlanes;
    std::vector<std::shared_ptr<Flight>> listOfFlights;

public:
    AvioCompany() = default;
    AvioCompany(const std::string& name, double initialBalance);
    void setBalance(double newB);
    bool chechFlight(std::shared_ptr<Flight>& flight) const;
    friend std::ostream& operator<<(std::ostream& os, const AvioCompany& ac);
    friend std::istream& operator>>(std::istream& is, AvioCompany& ac);
};


#endif //UNTITLED2_AVIOCOMPANY_H