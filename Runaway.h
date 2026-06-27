//
// Created by Kosio Lozanov on 24.06.26.
//

#ifndef UNTITLED2_RUNAWAY_H
#define UNTITLED2_RUNAWAY_H
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include "Plane.h"



enum class Status {
    Free,
    Occupied,
    Maintenance,
};

enum class optionalExtentions {
    ils,
    VIP,
    heavy
};

class Runaway {
    int id;
    static std::vector<int> ids;
    unsigned lenght;
    Status status;
    std::optional<std::reference_wrapper<Plane>> plane;
    std::vector<optionalExtentions> optionals;
    //optional flight
public:
    Runaway() = default;
    Runaway(int id_,unsigned length,
           Status status,
           const std::optional<std::reference_wrapper<Plane>>& plane,
           const std::vector<optionalExtentions>& optionals);
    int getId() const;
    void setStatus(const Status& newS);
    std::optional<std::reference_wrapper<Plane>>& getPlane();
    bool checkIfItHasILS(const Runaway& r1) const;
    unsigned getLenght() const;
    friend std::ostream& operator<<(std::ostream& os, const Runaway& r);
    friend std::istream& operator>>(std::istream& is, Runaway& r);
};


#endif //UNTITLED2_RUNAWAY_H