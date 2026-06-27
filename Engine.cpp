#include "Engine.h"
#include "Admin.h"
#include "Dispatcher.h"
#include <string>
#include <iostream>
#include <vector>
#include "Passenger.h"
#include <fstream>


bool checkCommandSize(int num, int size) {
    if (num != size) {
        return false;
    }
    return true;
}

void Engine::start() {
    Admin admin = Admin::getInstance();
    Engine::users.push_back(std::make_unique<Admin>(admin));
    std::shared_ptr<User> currentUser = nullptr;
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
        if (command == "login" && currentUser==nullptr) {
            if (checkCommandSize(3, inputParts.size())){std::cout<<"Invalid Command";continue;}
            std::string name = inputParts[1];
            std::string password = inputParts[2];
            for (std::shared_ptr<User>& ptr: users) {
                if (ptr->getName() == name && ptr->getPass() == password) {
                    currentUser = ptr;
                }
            }
        }else if (command == "load" && currentUser == nullptr) {
            std::ifstream file("airport_data.txt");
            if (file.peek() == std::ifstream::traits_type::eof()){
                std::cout << "Nothing saved, starting a new one";
                continue;
            }
        }else if (command == "save" && currentUser == nullptr) {
            std::ofstream file("airport_data.txt");

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
                users.push_back(std::make_shared<Passenger>(name,password,Role::dispetcher));
            }else {
                std::cout << "You are trying to register admin or "
                             "unexisting position - please try again";
                continue;
            }
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
            }else if (command == "add-baggage") {
                if (checkCommandSize(3, inputParts.size())){std::cout<<"Invalid Command";continue;}
                psg->addBagggage(inputParts[1], std::stoi(inputParts[2]));
            }else if (command == "cancel-ticket") {
                if (checkCommandSize(2, inputParts.size())){std::cout<<"Invalid Command";continue;}
                psg->cancelTicket(inputParts[1]);
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
            }else if (command == "build-hangar") {
                if (checkCommandSize(4, inputParts.size())){std::cout<<"Invalid Command";continue;}
                admin.buildHangar(inputParts[1], std::stoi(inputParts[2]),
                    std::stod(inputParts[3]));
            }else if (command == "close-runaway") {
                if (checkCommandSize(2, inputParts.size())){std::cout<<"Invalid Command";continue;}
                admin.closeRunway(inputParts[1]);
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
            }else if (command == "delay-flight") {
                if (checkCommandSize(3, inputParts.size())){std::cout<<"Invalid Command";continue;}
                dis->delayFlight(inputParts[1]);
            }else if (command == "free-runaway") {
                if (checkCommandSize(2, inputParts.size())){std::cout<<"Invalid Command";continue;}
                dis->freeRunaway(std::stoi(inputParts[1]));
            }
        }
    }
}

Engine & Engine::getInstance() {
    static Engine eng;
    return eng;
}
