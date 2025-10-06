// Economy.cpp
// Pic 10A??
//
// Created by Madelyne Goforth on 8/11/25.
//

#include "Economy.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>

std::map<int, std::map<std::string, double>> playerMarketShare;
std::vector<MonopolyInfo> monopolySectors;

// Economy Functions

Economy::Economy() {
    std::random_device rd;
    rng.seed(rd());
    scale = "LARGE";
    consumption = 102000;
    investment = 27000;
    governmentSpending = 25500;
    netExports = -4500;
    unemploymentRate = 5.0;
    cpiInflationRate = 2.0;
    ppiInflationRate = 1.5;
    gdpDeflator = 2.0;
    aggregateInflationRate = 2.0;
    businessConfidence = 70;
    federalFundsRate = 2.0;
    onRRP = 1.8;
    discountRate = 2.5;
    interestOnReserves = 1.9;
    quantitativeEasing = false;
    bankInterestRate = 3.0;
    initEventSystem();
    updateGDP();
}

void Economy::updateGDP() {
    gdp = consumption + investment + governmentSpending + netExports;
}

void Economy::updateAggregateInflation() {
    aggregateInflationRate = (cpiInflationRate * 0.5) +
                             (ppiInflationRate * 0.3) +
                             (gdpDeflator * 0.2);
}

void Economy::propagateEffects() {
    double potentialGDP = 2000.0;
    double outputGap = (gdp - potentialGDP) / potentialGDP;
    unemploymentRate = std::max(0.0, 5.0 - (outputGap * 10));
    if (unemploymentRate < 5.0) {
        cpiInflationRate += (5.0 - unemploymentRate) * 0.2;
    } else {
        cpiInflationRate -= (unemploymentRate - 5.0) * 0.1;
    }
    cpiInflationRate = std::max(0.0, cpiInflationRate);
    double rateEffect = federalFundsRate - 2.0;
    investment -= rateEffect * 10;
    consumption -= rateEffect * 5;
    investment = std::max(0.0, investment);
    consumption = std::max(0.0, consumption);
    updateGDP();
    updateAggregateInflation();
}

double Economy::randomDouble(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng);
}

void Economy::displayState() const {
    std::cout << "GDP: " << gdp
              << "\nC: " << consumption
              << " I: " << investment
              << " G: " << governmentSpending
              << " NX: " << netExports
              << "\nUnemployment: " << unemploymentRate << "%"
              << "\nCPI: " << cpiInflationRate << "%"
              << " PPI: " << ppiInflationRate << "%"
              << " GDP Deflator: " << gdpDeflator << "%"
              << "\nAggregate Inflation: " << aggregateInflationRate << "%"
              << "\nBusiness Confidence: " << businessConfidence
              << "\nFFR: " << federalFundsRate << "%"
              << " QE: " << (quantitativeEasing ? "Yes" : "No")
              << "\n---------------------\n";
}

void Economy::initEventSystem() {
    baseEventProb = {
        {"consumer_confidence_boom", 0.10},
        {"investment_shock", 0.08},
        {"fiscal_stimulus", 0.07},
        {"trade_war", 0.07},
        {"inflation_shock", 0.07},
        {"fed_policy_change", 0.08},
        {"bank_crisis", 0.05},
        {"natural_disaster", 0.06},
        {"housing_bubble", 0.07},
        {"supply_chain_disruption", 0.06},
        {"tax_change", 0.07},
        {"productivity_innovation", 0.07},
        {"labor_strike", 0.05}
    };
    eventInfluence = {
        {"bank_crisis", {{"fed_policy_change", 1.5}, {"investment_shock", 1.3}}},
        {"inflation_shock", {{"fed_policy_change", 1.2}, {"tax_change", 1.2}}},
        {"trade_war", {{"inflation_shock", 1.1}, {"investment_shock", 1.2}}},
        {"housing_bubble", {{"bank_crisis", 1.4}}},
        {"productivity_innovation", {{"consumer_confidence_boom", 1.3}}}
    };
    for (auto &p : baseEventProb) {
        eventCount[p.first] = 0;
    }
    if (scale == "LARGE") {
        monopolySectors = {
            {"Energy", 0.60},
            {"Housing", 0.60},
            {"Utilities", 0.60},
            {"Transportation", 0.60},
            {"Food", 0.60},
            {"Luxury Goods", 0.60}
        };
    }
}

void Economy::triggerRandomEvent() {
    std::string chosen = selectWeightedRandomEvent();
    if (chosen == "consumer_confidence_boom") consumerConfidenceBoom();
    else if (chosen == "investment_shock") investmentShock();
    else if (chosen == "fiscal_stimulus") fiscalStimulus();
    else if (chosen == "trade_war") tradeWar();
    else if (chosen == "inflation_shock") inflationShock();
    else if (chosen == "fed_policy_change") federalReservePolicyChange();
    else if (chosen == "bank_crisis") bankCrisis();
    else if (chosen == "natural_disaster") naturalDisaster();
    else if (chosen == "housing_bubble") housingBubble();
    else if (chosen == "supply_chain_disruption") supplyChainDisruption();
    else if (chosen == "tax_change") taxChange();
    else if (chosen == "productivity_innovation") productivityInnovation();
    else if (chosen == "labor_strike") laborStrike();
    eventCount[chosen]++;
    propagateEffects();
    updateBankInterestRate();
    updateMonopolyEffects();
}

std::string Economy::selectWeightedRandomEvent() {
    std::map<std::string, double> adjusted = baseEventProb;
    for (auto &evt : eventCount) {
        int count = evt.second;
        if (count > 0 && eventInfluence.count(evt.first)) {
            for (auto &influence : eventInfluence[evt.first]) {
                adjusted[influence.first] *= std::pow(influence.second, count);
            }
        }
    }
    double total = 0.0;
    for (auto &p : adjusted) total += p.second;
    if (total <= 0.0) {
        for (auto &p : adjusted) p.second = baseEventProb[p.first];
        total = 0.0;
        for (auto &p : adjusted) total += p.second;
    }
    for (auto &p : adjusted) p.second /= total;
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double roll = dist(rng);
    double cumulative = 0.0;
    for (auto &p : adjusted) {
        cumulative += p.second;
        if (roll <= cumulative) return p.first;
    }
    return adjusted.begin()->first;
}

// Events

void Economy::consumerConfidenceBoom() {
    double change = randomDouble(-15, 15);
    businessConfidence += change;
    consumption += change * 5;
    std::cout << "[Event] Consumer Confidence "
              << (change >= 0 ? "Boom!" : "Slump!") << "\n";
}
void Economy::investmentShock() {
    double change = randomDouble(-100, 100);
    investment += change;
    businessConfidence += change * 0.05;
    std::cout << "[Event] Investment Shock: " << change << "\n";
}
void Economy::fiscalStimulus() {
    double change = randomDouble(50, 200);
    governmentSpending += change;
    std::cout << "[Event] Fiscal Stimulus: +" << change << " G\n";
}
void Economy::tradeWar() {
    double change = randomDouble(-100, 50);
    netExports += change;
    businessConfidence -= 5;
    std::cout << "[Event] Trade War Impact: " << change << " NX\n";
}
void Economy::inflationShock() {
    double change = randomDouble(-1.5, 2.5);
    cpiInflationRate += change;
    ppiInflationRate += change * 0.8;
    std::cout << "[Event] Inflation Shock: " << change << "%\n";
}
void Economy::federalReservePolicyChange() {
    double change = randomDouble(-1.0, 1.0);
    federalFundsRate += change;
    std::cout << "[Event] Fed Policy Change: rates "
              << (change >= 0 ? "up" : "down") << " by " << change << "%\n";
}
void Economy::bankCrisis() {
    investment -= randomDouble(50, 150);
    businessConfidence -= 20;
    quantitativeEasing = true;
    std::cout << "[Event] Banking Crisis! QE Activated.\n";
}
void Economy::naturalDisaster() {
    consumption -= randomDouble(50, 200);
    investment -= randomDouble(50, 100);
    governmentSpending += randomDouble(30, 120);
    std::cout << "[Event] Natural Disaster disrupts economy.\n";
}
void Economy::housingBubble() {
    double change = randomDouble(-150, 150);
    investment += change;
    businessConfidence += change * 0.05;
    std::cout << "[Event] Housing Bubble/Correction.\n";
}
void Economy::supplyChainDisruption() {
    ppiInflationRate += randomDouble(0.5, 2.0);
    investment -= randomDouble(20, 80);
    std::cout << "[Event] Supply Chain Disruption.\n";
}
void Economy::taxChange() {
    double change = randomDouble(-2.0, 2.0);
    consumption += change * 50;
    investment += change * 30;
    std::cout << "[Event] Tax policy adjusted.\n";
}
void Economy::productivityInnovation() {
    investment += randomDouble(20, 100);
    consumption += randomDouble(20, 80);
    businessConfidence += 10;
    std::cout << "[Event] Productivity Innovation Boost.\n";
}
void Economy::laborStrike() {
    unemploymentRate += randomDouble(0.5, 2.0);
    businessConfidence -= 5;
    std::cout << "[Event] Major Labor Strike.\n";
}

double Economy::calculatePlayerIncome(const std::string& jobClass, double baseSalary, bool& unemployedFlag) {
    double income = baseSalary;
    std::uniform_real_distribution<double> dist(0.0, 100.0);
    double roll = dist(rng);
    if (roll < unemploymentRate) {
        unemployedFlag = true;
        return 0.0;
    } else {
        unemployedFlag = false;
    }
    double inflationImpact = (cpiInflationRate / 100.0);
    income *= (1.0 - inflationImpact * 0.5);

    if (businessConfidence > 70) {
        income *= 1.05;
    } else if (businessConfidence < 50) {
        income *= 0.95;
    }

    if (federalFundsRate > 3.0) {
        income *= 0.97;
    } else if (federalFundsRate < 1.0) {
        income *= 1.02;
    }

    if (income < 0) income = 0;
    return income;
}

void Economy::updateBankInterestRate() {
    double inflationEffect = cpiInflationRate * 0.4;
    double confidenceEffect = (100.0 - businessConfidence) * 0.03;
    double policyEffect = (federalFundsRate - 2.0) * 0.5;
    double noise = randomDouble(-0.25, 0.25);
    bankInterestRate = 2.0 + inflationEffect + confidenceEffect + policyEffect + noise;
    bankInterestRate = std::clamp(bankInterestRate, 0.5, 12.0);
}

bool Economy::checkPlayerMonopoly(int playerID, const std::string& sector) {
    auto it = playerMarketShare.find(playerID);
    if (it != playerMarketShare.end()) {
        if (it->second.count(sector)) {
            for (auto &sectorInfo : monopolySectors) {
                if (sectorInfo.sector == sector) {
                    return it->second.at(sector) >= sectorInfo.threshold * 100.0;
                }
            }
        }
    }
    return false;
}

void Economy::updateMonopolyEffects() {
    for (auto &playerData : playerMarketShare) {
        int playerID = playerData.first;
        for (auto &shareData : playerData.second) {
            const std::string &sector = shareData.first;
            double share = shareData.second;
            for (auto &sectorInfo : monopolySectors) {
                if (sectorInfo.sector == sector && share >= sectorInfo.threshold * 100.0) {
                    std::cout << "[Monopoly Power] Player " << playerID
                              << " controls the " << sector << " market!\n";
                    double sectorInflationBoost = 2.0;
                    if (scale == "LARGE")
                        cpiInflationRate += sectorInflationBoost;
                    if (randomDouble(0.0, 1.0) < 0.2) {
                        std::cout << "[Regulation Warning] Government investigates monopoly in " << sector << "\n";
                    }
                }
            }
        }
    }
}
