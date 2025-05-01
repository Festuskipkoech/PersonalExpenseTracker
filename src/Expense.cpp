#include "Expense.h"
#include <sstream>
#include <iomanip>
#include <vector>

// Default constructor
Expense::Expense() : id(0), amount(0.0), description(""), date(""), categoryId(0), categoryName("") {}

// Parametized constructor
Expense::Expense(int id, double amount, const std::string& description, const std::string& date, int categoryId, const std::string& categoryName) : 
id(id), amount(amount), description(description), date(date), categoryId(categoryId), categoryName(categoryName) {}

// getters
int Expense::getId() const {
    return id;
}

double Expense::getAmount() const {
    return amount;
}

std::string Expense::getDescription() const {
    return description;
}

std::string Expense::getDate() const {
    return date;
}

int Expense::getCategoryId() const {
    return categoryId;
}

std::string Expense::getCategoryName() const {
    return categoryName;
}

// setters
void Expense::setId(int id) {
    this->id = id;
}
void Expense::setAmount(double amount) {
    this->amount = amount;
}
void Expense::setDescription(const std::string& description) {
    this->description = description;
}

void Expense::setDate(const std::string& date) {
    this-> date = date;
}

void Expense::setCategoryId(int categoryId) {
    this-> categoryId = categoryId;
}

void Expense::setCategoryName(const std::string& categoryName) {
    this-> categoryName = categoryName;
}

// other methods

std::string Expense::toString() const {
    std::stringstream ss;
    ss <<"ID: " << id
       <<", Amount: S" << std::fixed << std::setprecision(2) << amount
       <<", Description: " << description
       << ", Date: " << date
       << ", Category: " <<categoryName;
    return ss.str();

}

std::string Expense::toCSV() const {
    std::stringstream ss;
    ss << id << ","
       << amount << ","
       << description << ","
       << date << ","
       << categoryId << ","
       << categoryName;
    return ss.str();
}

Expense Expense::fromCSV(const std::string& csvline) {
    std::stringstream ss(csvline);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if(tokens.size() >= 6){
        int id = std::stoi(tokens[0]);
        double amount = std::stod(tokens[1]);
        std::string description = tokens[2];
        std::string date = tokens[3];
        int categoryId = std::stoi(tokens[4]);
        std::string categoryName = tokens[5];

        return Expense(id, amount, description, date, categoryId, categoryName);
    }

    return Expense();
}