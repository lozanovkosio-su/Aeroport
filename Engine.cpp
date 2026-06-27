#include "Engine.h"
#include "Admin.h"
#include "Dispatcher.h"
#include <string>
#include <iostream>
#include <vector>
#include "Passenger.h"
#include <fstream>
#include <iomanip>
std::vector<std::shared_ptr<Flight>> Engine::flights = {};
std::vector<Runaway> Engine::runaways = {};
std::vector<Hangar> Engine::hangars = {};
std::vector<std::shared_ptr<User>> Engine::users = {};
std::vector<AvioCompany> Engine::airlines = {};

bool checkCommandSize(int num, int size) {
    if (num == size) {
        std::cout<<std::endl;
        std::cout << "Command taken" <<std::endl;
        return false;
    }
    return true;
}

void Engine::start() {
    Admin admin = Admin::getInstance();
    Engine::users.push_back(std::make_unique<Admin>(admin));
    std::shared_ptr<User> currentUser = nullptr;
    bool isStarted = false;
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        std::vector<std::string> inputParts;
        std::string word = "";
        bool flag = false;
        for (const char symbol:input) {
            if (symbol == ' ') {
                inputParts.push_back(word);
                word = "";
                continue;
            }
            word += symbol;
        }
        if (!word.empty()) {
            inputParts.push_back(word);
        }
        std::string command = inputParts[0];
        if (command == "login" && currentUser==nullptr && isStarted) {
            if (checkCommandSize(3, inputParts.size())){std::cout<<"Invalid Command";continue;}
            std::string name = inputParts[1];
            std::string password = inputParts[2];
            for (std::shared_ptr<User>& ptr: users) {
                if (ptr->getName() == name && ptr->getPass() == password) {
                    currentUser = ptr;
                }
            }
            std::print("Succesfuly logged in user: {}", name);
        }else if (command == "load" && currentUser == nullptr && !isStarted) {
            isStarted = true;
            std::ifstream file("airport_data.txt");
            if (file.peek() == std::ifstream::traits_type::eof()){
                std::cout << "Nothing saved, starting a new one" <<std::endl;
                continue;
            }
            int flightsCount;
            file >> flightsCount;
            for (int i = 0; i < flightsCount;i++) {
                Flight flight{};
                file >> flight;
                std::shared_ptr<Flight> ptr = std::make_shared<Flight>(flight);
                Engine::flights.push_back(ptr);
            }
            int runawaysCount;
            file >> runawaysCount;
            for (int i = 0; i < runawaysCount; i++) {
                Runaway runaway{};
                file >> runaway;
                Engine::runaways.push_back(runaway);
            }
            int hangarsCount;
            file >> hangarsCount;
            for (int i = 0; i < hangarsCount; i++) {
                Hangar hangar{};
                file >> hangar;
                Engine::hangars.push_back(hangar);
            }
            int airlinesCount;
            file >> airlinesCount;
            for (int i = 0; i < airlinesCount; i++) {
                AvioCompany company{};
                file >> company;
                Engine::airlines.push_back(company);
            }
            int usersCount;
            if (file >> usersCount) {
                for (int i = 0; i < usersCount; i++) {
                    std::string tName, tPass;
                    int tRoleInt;

                    if (file >> std::quoted(tName) >> std::quoted(tPass) >> tRoleInt) {
                        Role role = static_cast<Role>(tRoleInt);

                        if (role == Role::traveler) {
                            Engine::users.push_back(std::make_shared<Passenger>(tName, tPass, role));
                        }
                        else if (role == Role::dispetcher) {
                            Engine::users.push_back(std::make_shared<Dispatcher>(tName, tPass, role));
                        }
                        else if (role == Role::admin) {
                        }
                    }
                }
            }
        }else if (!isStarted) {
            std::cout << "You have to load first";continue;
        }else if (command == "save" && currentUser == nullptr) {
            std::ofstream file("airport_data.txt");
            file << Engine::flights.size() << std::endl;
            for (std::shared_ptr<Flight>& ptr : Engine::flights) {
                file << *ptr << std::endl;
            }
            file << Engine::runaways.size() << std::endl;
            for (const Runaway& r : Engine::runaways) {
                file << r << std::endl;
            }
            file << Engine::hangars.size() << std::endl;
            for (const Hangar& h : Engine::hangars) {
                file << h << std::endl;
            }
            file << Engine::users.size() << std::endl;
            for (const std::shared_ptr<User>& ptr : Engine::users) {
                file << *ptr << std::endl;
            }
            file << Engine::airlines.size() << std::endl;
            for (const AvioCompany& comp : Engine::airlines) {
                file << comp << std::endl;
            }
            Engine::flights.clear();
            Engine::runaways.clear();
            Engine::users.clear();
            Engine::hangars.clear();
            Engine::airlines.clear();
            std::cout << "System saved";
        }else if (command == "register" && currentUser == nullptr) {
            if (checkCommandSize(4, inputParts.size())){std::cout<<"Invalid Command";continue;}
            std::string name = inputParts[1];
            std::string password = inputParts[2];
            for (std::shared_ptr<User>& ptr: users) {
                if (ptr->getName() == name) {
                    std::cout << "User with this name already exist!";
                    flag = true;
                    break;
                }
            }
            if (flag) {
                continue;
            }
            std::string role = inputParts[3];
            if (role == "Passenger") {
                users.push_back(std::make_shared<Passenger>(name,password,Role::traveler));
            }else if (role == "Dispatcher") {
                users.push_back(std::make_shared<Dispatcher>(name,password,Role::dispetcher));
            }else {
                std::cout << "You are trying to register admin or "
                             "unexisting position - please try again";
                continue;
            }
            std::print("User {} succesfuly registered", name);
        }else if (command == "logout" && currentUser!=nullptr) {
            currentUser = nullptr;
            std::cout << "Logged out succesfuly!";
            continue;
        }else if (command == "add-funds" && currentUser->getRole() == Role::traveler) {
            if (checkCommandSize(2, inputParts.size())){std::cout<<"Invalid Command";continue;}
            double amaount = std::stod(inputParts[1]);
            std::shared_ptr<Passenger> psg = std::static_pointer_cast<Passenger>(currentUser);
            if (amaount < 0) {
                std::cout << "Invalid argument";
                continue;
            }
            psg->addFunds(amaount);
            std::print("{} EUR added", inputParts[1]);
        }else if (command == "list-flights" && currentUser->getRole() == Role::traveler) {
            if (checkCommandSize(2, inputParts.size())){std::cout<<"Invalid Command";continue;}
            std::shared_ptr<Passenger> psg = std::static_pointer_cast<Passenger>(currentUser);
            psg->listFlights(inputParts[1]);
        }else if (currentUser->getRole() == Role::traveler) {
            std::shared_ptr<Passenger> psg = std::static_pointer_cast<Passenger>(currentUser);
            if (command == "filter-flights") {
                if (checkCommandSize(2, inputParts.size())){std::cout<<"Invalid Command";continue;}
                psg->filterFlights(std::stoi(inputParts[1]));
            }else if (command == "book-ticket") {
                if (checkCommandSize(3, inputParts.size())){std::cout<<"Invalid Command";continue;}
                psg->bookTicket(inputParts[1], inputParts[2]);
            }else if (command == "upgrade-ticket") {
                if (checkCommandSize(3, inputParts.size())){std::cout<<"Invalid Command";continue;}
                psg->upgradeTicket(inputParts[1], inputParts[2]);
                std::print("You upgraded your ticket to {}",inputParts[2]);
            }else if (command == "add-baggage") {
                if (checkCommandSize(3, inputParts.size())){std::cout<<"Invalid Command";continue;}
                psg->addBagggage(inputParts[1], std::stoi(inputParts[2]));
            }else if (command == "cancel-ticket") {
                if (checkCommandSize(2, inputParts.size())){std::cout<<"Invalid Command";continue;}
                psg->cancelTicket(inputParts[1]);
                std::print("You sucesfully cancelled ticket for flight: {}", inputParts[1]);
            }
            //mytickets
        }else if (currentUser->getRole() == Role::admin) {
            Admin &admin = Admin::getInstance();
            if (command == "build-runway") {
                if (checkCommandSize(3, inputParts.size())){std::cout<<"Invalid Command";continue;}
                if (inputParts.size() == 4) {
                    if (inputParts[3] == "ILS") {
                        admin.buildRunaway(std::stoi(inputParts[1]),
                        std::stoi(inputParts[2]),
                        optionalExtentions::ils);
                    }else if (inputParts[3] == "VIP") {
                        admin.buildRunaway(std::stoi(inputParts[1]),
                        std::stoi(inputParts[2]),
                        optionalExtentions::ils);
                    }else {
                        admin.buildRunaway(std::stoi(inputParts[1]),
                         std::stoi(inputParts[2]),
                         optionalExtentions::heavy);
                    }
                }else if (inputParts.size() == 5) {
                    if (inputParts[4] == "VIP") {
                        admin.buildRunaway(std::stoi(inputParts[1]),
                        std::stoi(inputParts[2]),
                        optionalExtentions::ils,optionalExtentions::VIP);
                    }else {
                        if (inputParts[3] == "VIP") {
                            admin.buildRunaway(std::stoi(inputParts[1]),
                        std::stoi(inputParts[2]),optionalExtentions::VIP,
                        optionalExtentions::heavy);
                        }else {
                            admin.buildRunaway(std::stoi(inputParts[1]),
                        std::stoi(inputParts[2]),
                        optionalExtentions::ils,
                        optionalExtentions::heavy);
                        }
                    }
                }else if (inputParts.size() == 6) {
                    admin.buildRunaway(std::stoi(inputParts[1]),
                        std::stoi(inputParts[2]),
                        optionalExtentions::ils,optionalExtentions::VIP,
                        optionalExtentions::heavy);
                }else {
                    admin.buildRunaway(std::stoi(inputParts[1]),
                        std::stoi(inputParts[2]),
                        std::nullopt,std::nullopt);
                }
                std::print("You succesfully builded {} runaway",inputParts[1]);
            }else if (command == "build-hangar") {
                if (checkCommandSize(4, inputParts.size())){std::cout<<"Invalid Command";continue;}
                admin.buildHangar(inputParts[1], std::stoi(inputParts[2]),
                    std::stod(inputParts[3]));
            }else if (command == "close-runaway") {
                if (checkCommandSize(2, inputParts.size())){std::cout<<"Invalid Command";continue;}
                admin.closeRunway(inputParts[1]);
                std::print("You succesfuly closed runaway: {}",inputParts[1]);
            }else if (command == "set-weather") {
                if (checkCommandSize(2, inputParts.size())){std::cout<<"Invalid Command";continue;}
                admin.setTime(inputParts[1]);
            }else if (command == "register-airline") {
                if (checkCommandSize(3, inputParts.size())){std::cout<<"Invalid Command";continue;}
                admin.registerAirline(inputParts[1],std::stod(inputParts[2]));
            }
        }else if (currentUser->getRole() == Role::dispetcher) {
            std::shared_ptr<Dispatcher> dis = std::static_pointer_cast<Dispatcher>(currentUser);
            if (command == "list-airspace") {
                dis->listAirspace();
            }else if (command == "assign-runaway") {
                if (checkCommandSize(3, inputParts.size())){std::cout<<"Invalid Command";continue;}
                dis->assignRunaway(inputParts[1],std::stoi(inputParts[2]));
                std::print("You succesfully assigned flight {} to {}", inputParts[1],inputParts[2]);
            }else if (command == "delay-flight") {
                if (checkCommandSize(3, inputParts.size())){std::cout<<"Invalid Command";continue;}
                dis->delayFlight(inputParts[1]);
            }else if (command == "free-runaway") {
                if (checkCommandSize(2, inputParts.size())){std::cout<<"Invalid Command";continue;}
                dis->freeRunaway(std::stoi(inputParts[1]));
                std::print("You succesfully freed runaway {}", inputParts[1]);
            }
        }else if (command == "end") {
            break;
        }else {
            std::cout << "Invalid Command" <<std::endl;
            continue;
        }
    }
}

Engine & Engine::getInstance() {
    static Engine eng;
    return eng;
}
