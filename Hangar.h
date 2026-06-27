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
    Hangar(const std::string& id,
         unsigned capacity,
         double sum = 0.0);
};


#endif //UNTITLED2_HANGAR_H