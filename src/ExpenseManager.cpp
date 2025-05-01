#include "ExpenseManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <filesystem>

// Constructor
ExpenseManager::ExpenseManager(const std::string& dataDir) : dataDirectory(dataDir), nextExpenseId(1), nextCategoryId(1) {
    // Create data directory if it doesn't exist
    std::filesystem::create_directories(dataDirectory);
    
    // Set file paths
    expensesFilePath = dataDirectory + "/expenses.csv";
    categoriesFilePath = dataDirectory + "/categories.csv";
    
    // Load existing data
    loadCategories();
    loadExpenses();
}

// Private helper methods
void ExpenseManager::loadExpenses() {
    std::ifstream file(expensesFilePath);
    if (!file.is_open()) {
        return;
    }
    
    std::string line;
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            Expense expense = Expense::fromCSV(line);
            expenses.push_back(expense);
            if (expense.getId() >= nextExpenseId) {
                nextExpenseId = expense.getId() + 1;
            }
        }
    }
    
    file.close();
}

void ExpenseManager::loadCategories() {
    std::ifstream file(categoriesFilePath);
    if (!file.is_open()) {
        // Add default categories if the file doesn't exist
        addCategory("Food", "Groceries, restaurants, etc.");
        addCategory("Transportation", "Gas, public transit, etc.");
        addCategory("Housing", "Rent, utilities, etc.");
        addCategory("Entertainment", "Movies, games, etc.");
        addCategory("Other", "Miscellaneous expenses");
        return;
    }
    
    std::string line;
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            std::stringstream ss(line);
            std::string token;
            std::vector<std::string> tokens;
            
            while (std::getline(ss, token, ',')) {
                tokens.push_back(token);
            }
            
            if (tokens.size() >= 3) {
                int id = std::stoi(tokens[0]);
                Category category(id, tokens[1], tokens[2]);
                categories.push_back(category);
                if (id >= nextCategoryId) {
                    nextCategoryId = id + 1;
                }
            }
        }
    }
    
    file.close();
}

void ExpenseManager::saveExpenses() {
    std::ofstream file(expensesFilePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for saving expenses." << std::endl;
        return;
    }
    
    // Write header
    file << "id,amount,description,date,categoryId,categoryName" << std::endl;
    
    // Write data
    for (const auto& expense : expenses) {
        file << expense.toCSV() << std::endl;
    }
    
    file.close();
}

void ExpenseManager::saveCategories() {
    std::ofstream file(categoriesFilePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for saving categories." << std::endl;
        return;
    }
    
    // Write header
    file << "id,name,description" << std::endl;
    
    // Write data
    for (const auto& category : categories) {
        file << category.getId() << "," 
             << category.getName() << "," 
             << category.getDescription() << std::endl;
    }
    
    file.close();
}

std::string ExpenseManager::getCurrentDate() const {
    std::time_t now = std::time(nullptr);
    std::tm* now_tm = std::localtime(&now);
    
    std::ostringstream oss;
    oss << std::put_time(now_tm, "%Y-%m-%d");
    return oss.str();
}

// Expense management
void ExpenseManager::addExpense(double amount, const std::string& description, 
                               const std::string& date, int categoryId) {
    // Find category name
    std::string categoryName = "Unknown";
    for (const auto& category : categories) {
        if (category.getId() == categoryId) {
            categoryName = category.getName();
            break;
        }
    }
    
    // Use provided date or current date if empty
    std::string expenseDate = date.empty() ? getCurrentDate() : date;
    
    // Create and add expense
    Expense expense(nextExpenseId++, amount, description, expenseDate, categoryId, categoryName);
    expenses.push_back(expense);
    
    // Save to file
    saveExpenses();
}

void ExpenseManager::deleteExpense(int id) {
    auto it = std::find_if(expenses.begin(), expenses.end(), 
                          [id](const Expense& e) { return e.getId() == id; });
    
    if (it != expenses.end()) {
        expenses.erase(it);
        saveExpenses();
    }
}

Expense ExpenseManager::getExpense(int id) const {
    auto it = std::find_if(expenses.begin(), expenses.end(), 
                          [id](const Expense& e) { return e.getId() == id; });
    
    if (it != expenses.end()) {
        return *it;
    }
    
    return Expense(); // Return default expense if not found
}

std::vector<Expense> ExpenseManager::getAllExpenses() const {
    return expenses;
}

std::vector<Expense> ExpenseManager::getExpensesByCategory(int categoryId) const {
    std::vector<Expense> result;
    
    for (const auto& expense : expenses) {
        if (expense.getCategoryId() == categoryId) {
            result.push_back(expense);
        }
    }
    
    return result;
}

std::vector<Expense> ExpenseManager::getExpensesByDateRange(const std::string& startDate, 
                                                          const std::string& endDate) const {
    std::vector<Expense> result;
    
    for (const auto& expense : expenses) {
        if (expense.getDate() >= startDate && expense.getDate() <= endDate) {
            result.push_back(expense);
        }
    }
    
    return result;
}

// Category management
void ExpenseManager::addCategory(const std::string& name, const std::string& description) {
    Category category(nextCategoryId++, name, description);
    categories.push_back(category);
    saveCategories();
}

void ExpenseManager::deleteCategory(int id) {
    // Do not allow deletion if expenses exist with this category
    auto expensesWithCategory = getExpensesByCategory(id);
    if (!expensesWithCategory.empty()) {
        std::cerr << "Cannot delete category: There are expenses associated with this category." << std::endl;
        return;
    }
    
    auto it = std::find_if(categories.begin(), categories.end(), 
                          [id](const Category& c) { return c.getId() == id; });
    
    if (it != categories.end()) {
        categories.erase(it);
        saveCategories();
    }
}

void ExpenseManager::updateCategory(int id, const std::string& name, const std::string& description) {
    auto it = std::find_if(categories.begin(), categories.end(), 
                          [id](const Category& c) { return c.getId() == id; });
    
    if (it != categories.end()) {
        it->setName(name);
        it->setDescription(description);
        
        // Update category name in expenses
        for (auto& expense : expenses) {
            if (expense.getCategoryId() == id) {
                expense.setCategoryName(name);
            }
        }
        
        saveCategories();
        saveExpenses();
    }
}

Category ExpenseManager::getCategory(int id) const {
    auto it = std::find_if(categories.begin(), categories.end(), 
                          [id](const Category& c) { return c.getId() == id; });
    
    if (it != categories.end()) {
        return *it;
    }
    
    return Category(); // Return default category if not found
}

std::vector<Category> ExpenseManager::getAllCategories() const {
    return categories;
}

// Reporting
double ExpenseManager::getTotalExpenses() const {
    double total = 0.0;
    
    for (const auto& expense : expenses) {
        total += expense.getAmount();
    }
    
    return total;
}

double ExpenseManager::getTotalExpensesByCategory(int categoryId) const {
    double total = 0.0;
    
    for (const auto& expense : expenses) {
        if (expense.getCategoryId() == categoryId) {
            total += expense.getAmount();
        }
    }
    
    return total;
}

double ExpenseManager::getTotalExpensesByDateRange(const std::string& startDate, 
                                                 const std::string& endDate) const {
    double total = 0.0;
    
    for (const auto& expense : expenses) {
        if (expense.getDate() >= startDate && expense.getDate() <= endDate) {
            total += expense.getAmount();
        }
    }
    
    return total;
}

std::map<std::string, double> ExpenseManager::getExpenseDistributionByCategory() const {
    std::map<std::string, double> distribution;
    
    for (const auto& category : categories) {
        distribution[category.getName()] = getTotalExpensesByCategory(category.getId());
    }
    
    return distribution;
}

std::map<std::string, double> ExpenseManager::getMonthlyExpenseSummary(int year) const {
    std::map<std::string, double> monthlySummary;
    
    // Initialize months
    for (int month = 1; month <= 12; month++) {
        std::stringstream ss;
        ss << year << "-" << std::setw(2) << std::setfill('0') << month;
        monthlySummary[ss.str()] = 0.0;
    }
    
    // Sum expenses by month
    for (const auto& expense : expenses) {
        std::string yearMonth = expense.getDate().substr(0, 7); // Extract YYYY-MM
        if (yearMonth.substr(0, 4) == std::to_string(year)) {
            monthlySummary[yearMonth] += expense.getAmount();
        }
    }
    
    return monthlySummary;
}