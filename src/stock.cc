#include "stock.hpp"

Stock::Stock(const std::string& name, double price, int units)
    : name(name), price(price), units(units), open(0.0), close(0.0), high(0.0), low(0.0),
      previous_close(0.0), upper_circuit(0.0), lower_circuit(0.0) {}

std::string Stock::getName() const {
    return name;
}

double Stock::getPrice() const {
    return price;
}

int Stock::getUnits() const {
    return units;
}

double Stock::getOpen() const {
    return open;
}

double Stock::getClose() const {
    return close;
}

double Stock::getHigh() const {
    return high;
}

double Stock::getLow() const {
    return low;
}

double Stock::getPreviousClose() const {
    return previous_close;
}

double Stock::getUpperCircuit() const {
    return upper_circuit;
}

double Stock::getLowerCircuit() const {
    return lower_circuit;
}

void Stock::setPrice(double price) {
    this->price = price;
}

void Stock::setOpen(double open) {
    this->open = open;
}

void Stock::setClose(double close) {
    this->close = close;
}

void Stock::setHigh(double high) {
    this->high = high;
}

void Stock::setLow(double low) {
    this->low = low;
}

void Stock::setPreviousClose(double previousClose) {
    this->previous_close = previousClose;
}

void Stock::setUpperCircuit(double upperCircuit) {
    this->upper_circuit = upperCircuit;
}

void Stock::setLowerCircuit(double lowerCircuit) {
    this->lower_circuit = lowerCircuit;
}

void Stock::setUnits(int units) {
    this->units = units;
}