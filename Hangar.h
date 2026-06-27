//
// Created by Kosio Lozanov on 24.06.26.
//

#ifndef UNTITLED2_HANGAR_H
#define UNTITLED2_HANGAR_H
#include <iostream>
#include <string>
#include <vector>
#include <optional>

class Hangar {
    std::string id;
    static std::vector<std::string> listIds;
    unsigned capacity;
    double sum;

public:
    Hangar() = default;
    Hangar(const std::string& id,
         unsigned capacity,
         double sum = 0.0);
    friend std::ostream& operator<<(std::ostream& os, const Hangar& h);
    friend std::istream& operator>>(std::istream& is, Hangar& h);
};


#endif //UNTITLED2_HANGAR_H