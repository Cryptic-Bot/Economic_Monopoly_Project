//
//  Jobs.hpp
//  Pic 10A??
//
//  Created by Madelyne Goforth on 8/4/25.
//

#ifndef JOBS_HPP
#define JOBS_HPP

//#include "Players.hpp"
#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

class GameManager;

class Job {
public:
    string name;
    int baseSalary;
    
    string abilityName;
    string description;
    int abilityCooldown; // in turns
    int turnsUntilAbilityAvailable;
    
    // Constructor
    Job(const string& n, int salary, const string& abilityName, const string& desc, int cooldown)
      : name(n), baseSalary(salary), description(desc), abilityCooldown(cooldown), turnsUntilAbilityAvailable(0) {}
    
    // Random Income Assigner for use with Constructor (for iVolatility mode)
        void randomIncomeMachine();

    // Static version for generating a random salary before construction
        static int randomIncomeValue();
    
    // Virtual function if you want volatile subclasses
        virtual void onRoundPassed() {} // By default, do nothing

    // Optional: reset cooldown for ability after usage
    void resetCooldown() { turnsUntilAbilityAvailable = abilityCooldown; }
};

class Freelancer : public Job {
    int roundsUntilReroll; // Number of rounds until next reroll (for volatility)

public:
    Freelancer()
        : Job("Freelancer", 0, "Side Hustle",
              "Unpredictable income—rerolled every random set of rounds", 1)
    {
        randomIncomeMachine();
        setRandomRerollInterval();
    }

    void onRoundPassed() override {
        if (--roundsUntilReroll <= 0) {
            randomIncomeMachine();
            setRandomRerollInterval();
            cout << name << " income rerolled to $" << baseSalary << endl;
        }
    }
private:
    void setRandomRerollInterval() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 4); // Every 1-4 rounds
        roundsUntilReroll = dis(gen);
    }
};

class Unemployed : public Job {
public:
    Unemployed() : Job("Unemployed", 0, "Panhandle", "Get $50 from every player", 4) {}
};

class Comrade : public Job {
public:
    Comrade() : Job("Comrade", 200, "Be a good comrade", "Say hello to the other comrades", 1) {}
};

class Investor : public Job {
public:
    Investor() : Job("Investor", 350, "Dividend Bonus", "Earn $30 bonus when someone pays rent to you.", 1) {}
};

class Doctor : public Job {
public:
    Doctor() : Job("Doctor", 315, "Medical Aid", "Negate next negative random event affecting you", 3) {}
};

class Lawyer : public Job {
public:
    Lawyer() : Job("Lawyer", 290, "Legal Defense", "Can reduce litigation penalties by 50%.", 3) {}
};

class Economist : public Job {
public:
    Economist() : Job("Economist", 265, "Market Insight", "Can create economic forcasts to predict the future.", 5) {}
};

class Banker : public Job {
public:
    Banker() : Job("Banker", 230, "Loan Negotiation", "Reduce interest on bank loans by $5", 2) {}
};

class TechGuru : public Job {
public:
    TechGuru() : Job("Tech Guru", 200, "Startup Funding", "Collect $50 if you own both utilities when passing Go", 1) {}
};

class RealEstateAgent : public Job {
public:
    RealEstateAgent() : Job("Real Estate Agent", 200, "Bargain", "Pay $50 less for unowned property", 1) {}
};
    
class Hitman : public Job {
public:
    Hitman() : Job("Hitman", 100, "Sabotage", "Cancel one oponent's ability use this turn", 5) {}
};

class PoliceOfficer : public Job {
public:
    PoliceOfficer() : Job("Police Officer", 200, "Law & Order", "Charge $25 fine to another player, once every 3 rounds.", 3) {}
};
    
class Accountant : public Job {
public:
    Accountant() : Job("Accountant", 200, "Follow the moneytrail", "View other player's financial transactions", 2) {}
};

class AIchatbot : public Job {
public:
    AIchatbot() : Job("AI Chatbot", 250, "Query", "Dupe the humans", 3) {}
};

class Alien : public Job {
public:
    Alien() : Job("Alien from Kepler-22b", 150, "Divide and Conquer", "Multiply money by 1.1 through special alien techniques", 5) {}
};

class Teacher : public Job {
public:
    Teacher() : Job("Teacher", 180, "Inspire", "Once every 3 rounds, boost another player's income by $20 this turn", 3) {}
};

class Artist : public Job {
public:
    Artist() : Job("Artist", 120, "Sell Art", "Random chance (1 in 4 each turn) to earn an extra $80 'gallery bonus'", 1) {}
};

class SoftwareEngineer : public Job {
public:
    SoftwareEngineer() : Job("Software Engineer", 320, "Debug", "Can skip a rent payment once every 4 rounds.", 4) {}
};

class RetailWorker : public Job {
public:
    RetailWorker() : Job("Retail Worker", 80, "Discount Day", "Save $25 next time you buy a property", 2) {}
};

class Chef : public Job {
public:
    Chef() : Job("Chef", 180, "Cater Party", "Receive $40 bonus from each player when you pass GO; cooldown 3 rounds.", 3) {}
};

class SocialWorker : public Job {
public:
    SocialWorker() : Job("Social Worker", 125, "Advocate", "Block a fee for yourself or another, once every 4 rounds.", 4) {}
};

class FastFoodWorker : public Job {
public:
    FastFoodWorker() : Job("Fast Food Worker", 70, "Employee Meal", "Save $10 when buying property, once every 2 rounds.", 2) {}
};

class Barista : public Job {
public:
    Barista() : Job("Barista", 85, "Morning Rush", "Earn $15 bonus when passing GO.", 2) {}
};

class Waiter : public Job {
public:
    Waiter() : Job("Waiter", 110, "Tips", "Collect $10 from every player who lands on your property; max once per round.", 1) {}
};

class Mechanic : public Job {
public:
    Mechanic() : Job("Mechanic", 150, "Quick Fix", "Pay half for repairs.", 2) {}
};

class Nurse : public Job {
public:
    Nurse() : Job("Nurse", 230, "Night Shift", "Earn $40 bonus if you roll doubles, once every 3 rounds.", 3) {}
};

class Electrician : public Job {
public:
    Electrician() : Job("Electrician", 250, "Power Up", "Collect double rent from utilities once every 4 rounds.", 4) {}
};

class Scientist : public Job {
public:
    Scientist() : Job("Scientist", 320, "Innovation Grant", "Collect $70 bonus when landing on Chance.", 3) {}
};

class Entrepreneur : public Job {
public:
    Entrepreneur() : Job("Entrepreneur", 550, "Startup Boom", "Pay $70 fee every 4 rounds, but get double bonuses on 'Community Chest'.", 4) {}
};

#endif // JOBS_HPP

