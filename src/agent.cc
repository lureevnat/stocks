#include "agent.hpp"
#include <iostream>
#include <iomanip>

Agent::Agent(const std::string& name, double initialFunds)
    : name(name), funds(initialFunds) {}

std::string Agent::getName() const {
    return name;
}

double Agent::getFunds() const {
    return funds;
}

void Agent::addStock(const std::string& stockName, int units) {
    stockPortfolio[stockName] += units;
}

void Agent::removeStock(const std::string& stockName, int units) {
    auto it = stockPortfolio.find(stockName);
    if (it != stockPortfolio.end()) {
        if (it->second >= units) {
            it->second -= units;
            if (it->second == 0) {
                stockPortfolio.erase(it);
            }
        } else {
            std::cerr << "Error: Not enough units of stock '" << stockName << "' to remove.\n";
        }
    } else {
        std::cerr << "Error: Stock '" << stockName << "' not found in portfolio.\n";
    }
}

int Agent::getStockUnits(const std::string& stockName) const {
    auto it = stockPortfolio.find(stockName);
    if (it != stockPortfolio.end()) {
        return it->second;
    }
    return 0; // Return 0 if the stock is not found
}

void Agent::addFunds(double amount) {
    funds += amount;
}

void Agent::deductFunds(double amount) {
    if (funds >= amount) {
        funds -= amount;
    } else {
        std::cerr << "Error: Insufficient funds to deduct " << amount << ".\n";
    }
}

void Agent::displayPortfolio() const {
    std::cout << "Agent: " << name << "\n";
    std::cout << "Funds: $" << funds << "\n";
    std::cout << "Stock Portfolio:\n";
    std::cout << std::setw(15) << "Stock Name" << std::setw(10) << "Units\n";
    for (const auto& pair : stockPortfolio) {
        std::cout << std::setw(15) << pair.first << std::setw(10) << pair.second << "\n";
    }
}