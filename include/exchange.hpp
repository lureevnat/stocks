#ifndef EXCHANGE_HPP
#define EXCHANGE_HPP

#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <memory>
#include "stock.hpp"
#include "agent.hpp"

struct Bid {
    std::shared_ptr<Agent> agent;
    int units;
    double price;
    bool isBuy; // true for buy, false for sell

    // Comparator for priority queue (higher price for buy, lower price for sell)
    bool operator<(const Bid& other) const {
        if (isBuy) {
            return price < other.price; // Higher price has higher priority for buy
        } else {
            return price > other.price; // Lower price has higher priority for sell
        }
    }
};

class Exchange {
public:
    Exchange();

    // Stock management
    void addStock(const std::string& stockName, double price, int units);
    void updateStockPrice(const std::string& stockName, double newPrice);
    void displayStocks() const;
    void displayStockInfo(const std::string& stockName) const;
    std::shared_ptr<Stock> getStock(const std::string& stockName) const;

    // Agent management
    void addAgent(const std::shared_ptr<Agent>& agent);
    void removeAgent(const std::string& agentName);
    void displayAgents() const;

    // Bidding system
    bool addBid(const std::string& stockName, const std::shared_ptr<Agent>& agent, int units, double price, bool isBuy);
    void processBids(const std::string& stockName);

private:
    std::unordered_map<std::string, std::shared_ptr<Stock>> stocks; // Stocks managed by the exchange
    std::vector<std::shared_ptr<Agent>> agents; // Agents registered with the exchange
    std::unordered_map<std::string, std::priority_queue<Bid>> buyBids; // Buy bids for each stock
    std::unordered_map<std::string, std::priority_queue<Bid>> sellBids; // Sell bids for each stock
};

#endif // EXCHANGE_HPP