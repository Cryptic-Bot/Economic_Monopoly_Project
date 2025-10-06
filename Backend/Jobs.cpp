//
//  Jobs.cpp
//  Pic 10A?? / Economic Monopoly
//

#include "Jobs.hpp"

// Static random salary generator (for constructors or general use)
int Job::randomIncomeValue() {
    constexpr double mean = 200.0;
    constexpr double stddev = 50.0;
    constexpr int minIncome = 0;
    constexpr int maxIncome = 400;
    constexpr int increment = 10;

    static random_device rd;
    static mt19937 gen(rd());
    normal_distribution<> dist(mean, stddev);

    int salary;
    while (true) {
        double val = dist(gen);
        salary = static_cast<int>(std::round(val / increment) * increment);
        if (salary >= minIncome && salary <= maxIncome) break;
    }
    return salary;
}

// Member function: assigns random income directly to *this*
void Job::randomIncomeMachine() {
    baseSalary = randomIncomeValue();
}
