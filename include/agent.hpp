#ifndef AGENT_HPP
#define AGENT_HPP

#include <string>
#include <unordered_map>

class Agent {
public:
    Agent(const std::string& name, double initialFunds);

    // Getters
    std::string getName() const;
    double getFunds() const;

    // Stock management
    void addStock(const std::string& stockName, int units);
    void removeStock(const std::string& stockName, int units);
    int getStockUnits(const std::string& stockName) const;

    // Funds management
    void addFunds(double amount);
    void deductFunds(double amount);

    // Display agent's portfolio
    void displayPortfolio() const;

private:
    std::string name;
    double funds;
    std::unordered_map<std::string, int> stockPortfolio; // Maps stock name to units owned
};

#endif // AGENT_HPP