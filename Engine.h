//
// Created by Kosio Lozanov on 24.06.26.
//

#ifndef UNTITLED2_ENGINE_H
#define UNTITLED2_ENGINE_H
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <memory>
#include "Plane.h"
#include "Ticket.h"
#include "Flight.h"
#include "Runaway.h"
#include "Hangar.h"
#include "User.h"
#include "AvioCompany.h"







class Engine {
    Engine() = default;
public:
    void start();
    static Engine& getInstance();
    static std::vector<std::shared_ptr<Flight>> flights;
    static std::vector<Runaway> runaways;
    static std::vector<Hangar> hangars;
    static std::vector<std::shared_ptr<User>> users;
    static std::vector<AvioCompany> airlines;
};


#endif //UNTITLED2_ENGINE_H