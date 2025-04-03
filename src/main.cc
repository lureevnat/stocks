#include <iostream>
#include "exchange.hpp"
#include "agent.hpp"

int main() {
    std::cout << "Welcome to the Stocks Application!\n";

    // Create an Exchange object
    Exchange exchange;

    // Add a stock to the exchange
    exchange.addStock("Idea", 120.75, 300);

    // Display initial stock information
    exchange.displayStockInfo("Idea");

    // Create agents
    auto agent1 = std::make_shared<Agent>("John Doe", 10000.00);
    auto agent2 = std::make_shared<Agent>("Jane Smith", 15000.00);

    // Add initial stock units to agents
    agent1->addStock("Idea", 20); // Agent1 starts with 20 units of "Idea"
    agent2->addStock("Idea", 10); // Agent2 starts with 10 units of "Idea"

    // Display agents' initial portfolios
    std::cout << "\nInitial Agent Portfolios:\n";
    agent1->displayPortfolio();
    agent2->displayPortfolio();

    // Agents place bids
    if (!exchange.addBid("Idea", agent1, 10, 121.00, true)) { // Agent1 wants to buy 10 units at $121.00
        std::cerr << "Error: Agent1's buy bid could not be added.\n";
    }
    if (!exchange.addBid("Idea", agent2, 5, 120.50, false)) { // Agent2 wants to sell 5 units at $120.50
        std::cerr << "Error: Agent2's sell bid could not be added.\n";
    }

    // Process bids
    exchange.processBids("Idea");

    // Display updated stock information
    exchange.displayStockInfo("Idea");

    // Display agents' updated portfolios
    std::cout << "\nUpdated Agent Portfolios:\n";
    agent1->displayPortfolio();
    agent2->displayPortfolio();

    return 0;
}