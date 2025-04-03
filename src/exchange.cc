#include "exchange.hpp"
#include <iostream>
#include <iomanip>

Exchange::Exchange() {}

void Exchange::addStock(const std::string& stockName, double price, int units) {
    if (stocks.find(stockName) != stocks.end()) {
        std::cerr << "Error: Stock with name '" << stockName << "' already exists.\n";
        return;
    }
    stocks[stockName] = std::make_shared<Stock>(stockName, price, units);
}

void Exchange::updateStockPrice(const std::string& stockName, double newPrice) {
    auto it = stocks.find(stockName);
    if (it != stocks.end()) {
        it->second->setPrice(newPrice);
    } else {
        std::cerr << "Error: Stock '" << stockName << "' not found. Cannot update price.\n";
    }
}

void Exchange::displayStocks() const {
    if (stocks.empty()) {
        std::cout << "No stocks available in the exchange.\n";
        return;
    }

    std::cout << "Available Stocks:\n";
    std::cout << std::setw(15) << "Stock Name" << std::setw(10) << "Price" << std::setw(10) << "Units\n";
    for (const auto& pair : stocks) {
        const auto& stock = pair.second;
        std::cout << std::setw(15) << stock->getName()
                  << std::setw(10) << stock->getPrice()
                  << std::setw(10) << stock->getUnits() << "\n";
    }
}

bool Exchange::addBid(const std::string& stockName, const std::shared_ptr<Agent>& agent, int units, double price, bool isBuy) {
    auto it = stocks.find(stockName);
    if (it == stocks.end()) {
        std::cerr << "Error: Stock '" << stockName << "' not found in the exchange.\n";
        return false;
    }

    // Validate the bid
    if (isBuy) {
        if (agent->getFunds() < price * units) {
            std::cerr << "Error: Agent '" << agent->getName() << "' does not have enough funds to place the buy bid.\n";
            return false;
        }
    } else {
        if (agent->getStockUnits(stockName) < units) {
            std::cerr << "Error: Agent '" << agent->getName() << "' does not have enough stock units to place the sell bid.\n";
            return false;
        }
    }

    // Add the bid to the appropriate queue
    Bid bid = {agent, units, price, isBuy};
    if (isBuy) {
        buyBids[stockName].push(bid);
    } else {
        sellBids[stockName].push(bid);
    }

    return true; // Bid successfully added
}

void Exchange::processBids(const std::string& stockName) {
    auto it = stocks.find(stockName);
    if (it == stocks.end()) {
        std::cerr << "Error: Stock '" << stockName << "' not found in the exchange.\n";
        return;
    }

    auto& stock = it->second;
    auto& buyQueue = buyBids[stockName];
    auto& sellQueue = sellBids[stockName];

    while (!buyQueue.empty() && !sellQueue.empty()) {
        Bid buyBid = buyQueue.top();
        Bid sellBid = sellQueue.top();

        // Match buy and sell bids
        if (buyBid.price >= sellBid.price) {
            int transactionUnits = std::min(buyBid.units, sellBid.units);
            double transactionPrice = sellBid.price;

            // Update agents' portfolios and funds
            buyBid.agent->addStock(stockName, transactionUnits);
            buyBid.agent->deductFunds(transactionPrice * transactionUnits);

            sellBid.agent->removeStock(stockName, transactionUnits);
            sellBid.agent->addFunds(transactionPrice * transactionUnits);

            // Update stock units in the exchange
            stock->setUnits(stock->getUnits() - transactionUnits);

            // Update bid units
            buyBid.units -= transactionUnits;
            sellBid.units -= transactionUnits;

            // Remove completed bids
            buyQueue.pop();
            sellQueue.pop();

            if (buyBid.units > 0) {
                buyQueue.push(buyBid);
            }
            if (sellBid.units > 0) {
                sellQueue.push(sellBid);
            }

            std::cout << "Transaction: " << transactionUnits << " units of '" << stockName
                      << "' at $" << transactionPrice << " per unit.\n";
        } else {
            break; // No more matching bids
        }
    }
}

void Exchange::displayStockInfo(const std::string& stockName) const {
    auto it = stocks.find(stockName);
    if (it != stocks.end()) {
        const auto& stock = it->second;
        std::cout << "Stock Information for: " << stock->getName() << "\n";
        std::cout << "  Price: " << stock->getPrice() << "\n";
        std::cout << "  Units: " << stock->getUnits() << "\n";
        std::cout << "  Open: " << stock->getOpen() << "\n";
        std::cout << "  Close: " << stock->getClose() << "\n";
        std::cout << "  High: " << stock->getHigh() << "\n";
        std::cout << "  Low: " << stock->getLow() << "\n";
        std::cout << "  Previous Close: " << stock->getPreviousClose() << "\n";
        std::cout << "  Upper Circuit: " << stock->getUpperCircuit() << "\n";
        std::cout << "  Lower Circuit: " << stock->getLowerCircuit() << "\n";
    } else {
        std::cerr << "Error: Stock '" << stockName << "' not found in the exchange.\n";
    }
}

std::shared_ptr<Stock> Exchange::getStock(const std::string& stockName) const {
    auto it = stocks.find(stockName);
    if (it != stocks.end()) {
        return it->second;
    }
    std::cerr << "Error: Stock '" << stockName << "' not found in the exchange.\n";
    return nullptr; // Return nullptr if the stock is not found
}

void Exchange::addAgent(const std::shared_ptr<Agent>& agent) {
    agents.push_back(agent);
}

void Exchange::removeAgent(const std::string& agentName) {
    for (auto it = agents.begin(); it != agents.end(); ++it) {
        if ((*it)->getName() == agentName) {
            agents.erase(it);
            std::cout << "Agent '" << agentName << "' removed from the exchange.\n";
            return;
        }
    }
    std::cerr << "Error: Agent '" << agentName << "' not found.\n";
}

void Exchange::displayAgents() const {
    if (agents.empty()) {
        std::cout << "No agents registered with the exchange.\n";
        return;
    }

    std::cout << "Agents Registered with the Exchange:\n";
    for (const auto& agent : agents) {
        agent->displayPortfolio();
        std::cout << "-------------------------\n";
    }
}