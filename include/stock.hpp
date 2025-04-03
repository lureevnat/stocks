#ifndef STOCK_HPP
#define STOCK_HPP

#include <string>

class Stock {
public:
    Stock(const std::string& name, double price, int units);

    // Getters
    std::string getName() const;
    double getPrice() const;
    int getUnits() const;
    double getOpen() const;
    double getClose() const;
    double getHigh() const;
    double getLow() const;
    double getPreviousClose() const;
    double getUpperCircuit() const;
    double getLowerCircuit() const;

    // Setters
    void setPrice(double price);
    void setOpen(double open);
    void setClose(double close);
    void setHigh(double high);
    void setLow(double low);
    void setPreviousClose(double previousClose);
    void setUpperCircuit(double upperCircuit);
    void setLowerCircuit(double lowerCircuit);
    void setUnits(int units);

private:
    std::string name;
    double price;
    int units;

    // Additional attributes for a day's trading
    double open;
    double close;
    double high;
    double low;
    double previous_close;
    double upper_circuit;
    double lower_circuit;
};

#endif // STOCK_HPP