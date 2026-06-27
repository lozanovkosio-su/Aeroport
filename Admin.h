#ifndef UNTITLED2_ADMIN_H
#define UNTITLED2_ADMIN_H
#include <iostream>
#include <string>

#include "Hangar.h"
#include "Runaway.h"
#include "User.h"
#include "Flight.h"



class Admin : public User {
private:
    double balance = 0;
    Admin(const std::string& name_,
        const std::string& password_, const Role& role_);
    //Admin(const Admin&) = default;
public:
    static Admin& getInstance();
    Runaway buildRunaway(int id, unsigned length,
        const std::optional<optionalExtentions>& firstOptional = std::nullopt,
        const std::optional<optionalExtentions>& secondOptional = std::nullopt,
        const std::optional<optionalExtentions>& thirdOptional = std::nullopt);
    Hangar buildHangar(const std::string id,unsigned capacity,double repairFee);
    void closeRunway(const std::string& runawayId);
    void setTime(const std::string& type);
    void registerAirline(const std::string& name, double capital);
    void setBalance(double newB);
};


#endif //UNTITLED2_ADMIN_H
