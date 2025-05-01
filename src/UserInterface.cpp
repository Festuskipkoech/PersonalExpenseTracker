#include "UserInterface.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <regex>
#include <vector>

// Constructor
UserInterface::UserInterface(const std::string& dataDir) : expenseManager(dataDir) {}

// Main method to run the application
void UserInterface::run() {
    bool running = true;
    
    while (running) {
        displayMainMenu();
        
        std::string choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (choice == "1") {
            bool expenseMenuRunning = true;
            while (expenseMenuRunning) {
                displayExpenseMenu();
                
                std::string expenseChoice;
                std::cout << "Enter your choice (0 to go back): ";
                std::cin >> expenseChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                if (expenseChoice == "1") {
                    handleAddExpense();
                } else if (expenseChoice == "2") {
                    handleViewExpenses();
                } else if (expenseChoice == "3") {
                    handleDeleteExpense();
                } else if (expenseChoice == "0") {
                    expenseMenuRunning = false;
                } else {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
        } else if (choice == "2") {
            bool categoryMenuRunning = true;
            while (categoryMenuRunning) {
                displayCategoryMenu();
                
                std::string categoryChoice;
                std::cout << "Enter your choice (0 to go back): ";
                std::cin >> categoryChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                if (categoryChoice == "1") {
                    handleAddCategory();
                } else if (categoryChoice == "2") {
                    handleViewCategories();
                } else if (categoryChoice == "3") {
                    handleUpdateCategory();
                } else if (categoryChoice == "4") {
                    handleDeleteCategory();
                } else if (categoryChoice == "0") {
                    categoryMenuRunning = false;
                } else {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
        } else if (choice == "3") {
            bool reportMenuRunning = true;
            while (reportMenuRunning) {
                displayReportMenu();
                
                std::string reportChoice;
                std::cout << "Enter your choice (0 to go back): ";
                std::cin >> reportChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                if (reportChoice == "1") {
                    handleViewTotalExpenses();
                } else if (reportChoice == "2") {
                    handleViewExpensesByCategory();
                } else if (reportChoice == "3") {
                    handleViewExpensesByDateRange();
                } else if (reportChoice == "4") {
                    handleViewCategoryDistribution();
                } else if (reportChoice == "5") {
                    handleViewMonthlySummary();
                } else if (reportChoice == "0") {
                    reportMenuRunning = false;
                } else {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
        } else if (choice == "0") {
            std::cout << "Thank you for using Personal Expense Tracker. Goodbye!" << std::endl;
            running = false;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

// Display menus
void UserInterface::displayMainMenu() const {
    std::cout << "\n===== Personal Expense Tracker =====" << std::endl;
    std::cout << "1. Expense Management" << std::endl;
    std::cout << "2. Category Management" << std::endl;
    std::cout << "3. Reports" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

void UserInterface::displayExpenseMenu() const {
    std::cout << "\n===== Expense Management =====" << std::endl;
    std::cout << "1. Add Expense" << std::endl;
    std::cout << "2. View Expenses" << std::endl;
    std::cout << "3. Delete Expense" << std::endl;
    std::cout << "0. Back to Main Menu" << std::endl;
}

void UserInterface::displayCategoryMenu() const {
    std::cout << "\n===== Category Management =====" << std::endl;
    std::cout << "1. Add Category" << std::endl;
    std::cout << "2. View Categories" << std::endl;
    std::cout << "3. Update Category" << std::endl;
    std::cout << "4. Delete Category" << std::endl;
    std::cout << "0. Back to Main Menu" << std::endl;
}

void UserInterface::displayReportMenu() const {
    std::cout << "\n===== Reports =====" << std::endl;
    std::cout << "1. View Total Expenses" << std::endl;
    std::cout << "2. View Expenses by Category" << std::endl;
    std::cout << "3. View Expenses by Date Range" << std::endl;
    std::cout << "4. View Category Distribution" << std::endl;
    std::cout << "5. View Monthly Summary" << std::endl;
    std::cout << "0. Back to Main Menu" << std::endl;
}

// Expense management handlers
void UserInterface::handleAddExpense() {
    std::cout << "\n===== Add Expense =====" << std::endl;
    
    // Get expense details
    double amount;
    std::string amountStr;
    do {
        std::cout << "Enter amount: $";
        std::cin >> amountStr;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (!isValidDouble(amountStr) || (amount = std::stod(amountStr)) <= 0);
    
    std::string description;
    std::cout << "Enter description: ";
    std::getline(std::cin, description);
    
    std::string date = getValidDate();
    
    // Display available categories
    auto categories = expenseManager.getAllCategories();
    std::cout << "\nAvailable Categories:" << std::endl;
    for (const auto& category : categories) {
        std::cout << category.getId() << ". " << category.getName() << std::endl;
    }
    
    // Get category ID
    int categoryId;
    std::string categoryIdStr;
    bool validCategory = false;
    
    do {
        std::cout << "Enter category ID: ";
        std::cin >> categoryIdStr;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (isValidInt(categoryIdStr)) {
            categoryId = std::stoi(categoryIdStr);
            
            for (const auto& category : categories) {
                if (category.getId() == categoryId) {
                    validCategory = true;
                    break;
                }
            }
        }
        
        if (!validCategory) {
            std::cout << "Invalid category ID. Please try again." << std::endl;
        }
    } while (!validCategory);
    
    // Add expense
    expenseManager.addExpense(amount, description, date, categoryId);
    std::cout << "Expense added successfully." << std::endl;
}

void UserInterface::handleViewExpenses() {
    std::cout << "\n===== View Expenses =====" << std::endl;
    
    auto expenses = expenseManager.getAllExpenses();
    if (expenses.empty()) {
        std::cout << "No expenses found." << std::endl;
        return;
    }
    
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(10) << "Amount" 
              << std::setw(30) << "Description" 
              << std::setw(12) << "Date" 
              << std::setw(20) << "Category" << std::endl;
    std::cout << std::string(77, '-') << std::endl;
    
    for (const auto& expense : expenses) {
        std::cout << std::left << std::setw(5) << expense.getId() 
                  << "$" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << expense.getAmount() << " " 
                  << std::left << std::setw(30) << expense.getDescription() 
                  << std::setw(12) << expense.getDate() 
                  << std::setw(20) << expense.getCategoryName() << std::endl;
    }
}

void UserInterface::handleDeleteExpense() {
    std::cout << "\n===== Delete Expense =====" << std::endl;
    
    // Display expenses
    handleViewExpenses();
    
    // Get expense ID to delete
    int id;
    std::string idStr;
    std::cout << "\nEnter the ID of the expense to delete (0 to cancel): ";
    std::cin >> idStr;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (!isValidInt(idStr)) {
        std::cout << "Invalid ID. Operation cancelled." << std::endl;
        return;
    }
    
    id = std::stoi(idStr);
    if (id == 0) {
        std::cout << "Operation cancelled." << std::endl;
        return;
    }
    
    // Delete expense
    auto expense = expenseManager.getExpense(id);
    if (expense.getId() == 0) {
        std::cout << "Expense with ID " << id << " not found." << std::endl;
        return;
    }
    
    expenseManager.deleteExpense(id);
    std::cout << "Expense deleted successfully." << std::endl;
}

// Category management handlers
void UserInterface::handleAddCategory() {
    std::cout << "\n===== Add Category =====" << std::endl;
    
    std::string name;
    std::cout << "Enter category name: ";
    std::getline(std::cin, name);
    
    std::string description;
    std::cout << "Enter category description (optional): ";
    std::getline(std::cin, description);
    
    expenseManager.addCategory(name, description);
    std::cout << "Category added successfully." << std::endl;
}

void UserInterface::handleViewCategories() {
    std::cout << "\n===== View Categories =====" << std::endl;
    
    auto categories = expenseManager.getAllCategories();
    if (categories.empty()) {
        std::cout << "No categories found." << std::endl;
        return;
    }
    
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(20) << "Name" 
              << std::setw(50) << "Description" << std::endl;
    std::cout << std::string(75, '-') << std::endl;
    
    for (const auto& category : categories) {
        std::cout << std::left << std::setw(5) << category.getId() 
                  << std::setw(20) << category.getName() 
                  << std::setw(50) << category.getDescription() << std::endl;
    }
}

void UserInterface::handleUpdateCategory() {
    std::cout << "\n===== Update Category =====" << std::endl;
    
    // Display categories
    handleViewCategories();
    
    // Get category ID to update
    int id;
    std::string idStr;
    std::cout << "\nEnter the ID of the category to update (0 to cancel): ";
    std::cin >> idStr;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (!isValidInt(idStr)) {
        std::cout << "Invalid ID. Operation cancelled." << std::endl;
        return;
    }
    
    id = std::stoi(idStr);
    if (id == 0) {
        std::cout << "Operation cancelled." << std::endl;
        return;
    }
    
    // Get category
    auto category = expenseManager.getCategory(id);
    if (category.getId() == 0) {
        std::cout << "Category with ID " << id << " not found." << std::endl;
        return;
    }
    
    // Get updated details
    std::string name;
    std::cout << "Enter new name (leave empty to keep '" << category.getName() << "'): ";
    std::getline(std::cin, name);
    if (name.empty()) {
        name = category.getName();
    }
    
    std::string description;
    std::cout << "Enter new description (leave empty to keep current): ";
    std::getline(std::cin, description);
    if (description.empty()) {
        description = category.getDescription();
    }
    
    // Update category
    expenseManager.updateCategory(id, name, description);
    std::cout << "Category updated successfully." << std::endl;
}

void UserInterface::handleDeleteCategory() {
    std::cout << "\n===== Delete Category =====" << std::endl;
    
    // Display categories
    handleViewCategories();
    
    // Get category ID to delete
    int id;
    std::string idStr;
    std::cout << "\nEnter the ID of the category to delete (0 to cancel): ";
    std::cin >> idStr;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (!isValidInt(idStr)) {
        std::cout << "Invalid ID. Operation cancelled." << std::endl;
        return;
    }
    
    id = std::stoi(idStr);
    if (id == 0) {
        std::cout << "Operation cancelled." << std::endl;
        return;
    }
    
    // Delete category
    auto category = expenseManager.getCategory(id);
    if (category.getId() == 0) {
        std::cout << "Category with ID " << id << " not found." << std::endl;
        return;
    }
    
    expenseManager.deleteCategory(id);
    std::cout << "Category deleted successfully." << std::endl;
}

// Report handlers
void UserInterface::handleViewTotalExpenses() {
    std::cout << "\n===== Total Expenses =====" << std::endl;
    
    double total = expenseManager.getTotalExpenses();
    std::cout << "Total expenses: $" << std::fixed << std::setprecision(2) << total << std::endl;
}

void UserInterface::handleViewExpensesByCategory() {
    std::cout << "\n===== Expenses by Category =====" << std::endl;
    
    // Display categories
    auto categories = expenseManager.getAllCategories();
    std::cout << "Available Categories:" << std::endl;
    for (const auto& category : categories) {
        std::cout << category.getId() << ". " << category.getName() << std::endl;
    }
    
    // Get category ID
    int categoryId;
    std::string categoryIdStr;
    std::cout << "\nEnter category ID (0 to cancel): ";
    std::cin >> categoryIdStr;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (!isValidInt(categoryIdStr)) {
        std::cout << "Invalid category ID. Operation cancelled." << std::endl;
        return;
    }
    
    categoryId = std::stoi(categoryIdStr);
    if (categoryId == 0) {
        std::cout << "Operation cancelled." << std::endl;
        return;
    }
    
    // Get category
    auto category = expenseManager.getCategory(categoryId);
    if (category.getId() == 0) {
        std::cout << "Category with ID " << categoryId << " not found." << std::endl;
        return;
    }
    
    // Display expenses for the category
    auto expenses = expenseManager.getExpensesByCategory(categoryId);
    if (expenses.empty()) {
        std::cout << "No expenses found for category: " << category.getName() << std::endl;
        return;
    }
    
    std::cout << "\nExpenses for category: " << category.getName() << std::endl;
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(10) << "Amount" 
              << std::setw(30) << "Description" 
              << std::setw(12) << "Date" << std::endl;
    std::cout << std::string(57, '-') << std::endl;
    
    for (const auto& expense : expenses) {
        std::cout << std::left << std::setw(5) << expense.getId() 
                  << "$" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << expense.getAmount() << " " 
                  << std::left << std::setw(30) << expense.getDescription() 
                  << std::setw(12) << expense.getDate() << std::endl;
    }
    
    // Display total
    double total = expenseManager.getTotalExpensesByCategory(categoryId);
    std::cout << "\nTotal expenses for category: $" << std::fixed << std::setprecision(2) << total << std::endl;
}

void UserInterface::handleViewExpensesByDateRange() {
    std::cout << "\n===== Expenses by Date Range =====" << std::endl;
    
    // Get date range
    std::cout << "Enter start date (YYYY-MM-DD): ";
    std::string startDate = getValidDate();
    
    std::cout << "Enter end date (YYYY-MM-DD): ";
    std::string endDate = getValidDate();
    
    // Ensure start date is before end date
    if (startDate > endDate) {
        std::cout << "Error: Start date must be before end date." << std::endl;
        return;
    }
    
    // Display expenses in date range
    auto expenses = expenseManager.getExpensesByDateRange(startDate, endDate);
    if (expenses.empty()) {
        std::cout << "No expenses found between " << startDate << " and " << endDate << std::endl;
        return;
    }
    
    std::cout << "\nExpenses between " << startDate << " and " << endDate << ":" << std::endl;
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(10) << "Amount" 
              << std::setw(30) << "Description" 
              << std::setw(12) << "Date" 
              << std::setw(20) << "Category" << std::endl;
    std::cout << std::string(77, '-') << std::endl;
    
    for (const auto& expense : expenses) {
        std::cout << std::left << std::setw(5) << expense.getId() 
                  << "$" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << expense.getAmount() << " " 
                  << std::left << std::setw(30) << expense.getDescription() 
                  << std::setw(12) << expense.getDate() 
                  << std::setw(20) << expense.getCategoryName() << std::endl;
    }
    
    // Display total
    double total = expenseManager.getTotalExpensesByDateRange(startDate, endDate);
    std::cout << "\nTotal expenses: $" << std::fixed << std::setprecision(2) << total << std::endl;
}

void UserInterface::handleViewCategoryDistribution() {
    std::cout << "\n===== Category Distribution =====" << std::endl;
    
    auto distribution = expenseManager.getExpenseDistributionByCategory();
    if (distribution.empty()) {
        std::cout << "No expenses found." << std::endl;
        return;
    }
    
    double totalExpenses = expenseManager.getTotalExpenses();
    if (totalExpenses == 0) {
        std::cout << "No expenses found." << std::endl;
        return;
    }
    
    std::cout << std::left << std::setw(20) << "Category" 
              << std::setw(15) << "Amount" 
              << std::setw(10) << "Percentage" << std::endl;
    std::cout << std::string(45, '-') << std::endl;
    
    for (const auto& [category, amount] : distribution) {
        double percentage = (amount / totalExpenses) * 100;
        std::cout << std::left << std::setw(20) << category 
                  << "$" << std::right << std::setw(13) << std::fixed << std::setprecision(2) << amount << " " 
                  << std::right << std::setw(8) << std::fixed << std::setprecision(2) << percentage << "%" << std::endl;
    }
    
    std::cout << std::string(45, '-') << std::endl;
    std::cout << std::left << std::setw(20) << "Total" 
              << "$" << std::right << std::setw(13) << std::fixed << std::setprecision(2) << totalExpenses << std::endl;
}

void UserInterface::handleViewMonthlySummary() {
    std::cout << "\n===== Monthly Summary =====" << std::endl;
    
    // Get year
    int year;
    std::string yearStr;
    do {
        std::cout << "Enter year: ";
        std::cin >> yearStr;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (!isValidInt(yearStr) || (year = std::stoi(yearStr)) < 1900 || year > 2100);
    
    // Get monthly summary
    auto monthlySummary = expenseManager.getMonthlyExpenseSummary(year);
    
    // Check if there are any expenses
    bool hasExpenses = false;
    for (const auto& [month, amount] : monthlySummary) {
        if (amount > 0) {
            hasExpenses = true;
            break;
        }
    }
    
    if (!hasExpenses) {
        std::cout << "No expenses found for year " << year << std::endl;
        return;
    }
    
    // Display monthly summary
    std::cout << "\nMonthly Summary for " << year << ":" << std::endl;
    std::cout << std::left << std::setw(15) << "Month" 
              << std::setw(15) << "Amount" << std::endl;
    std::cout << std::string(30, '-') << std::endl;
    
    const std::vector<std::string> monthNames = {
        "January", "February", "March", "April", "May", "June", 
        "July", "August", "September", "October", "November", "December"
    };
    
    double yearTotal = 0.0;
    
    for (int i = 0; i < 12; i++) {
        std::stringstream ss;
        ss << year << "-" << std::setw(2) << std::setfill('0') << (i + 1);
        std::string monthKey = ss.str();
        
        double amount = monthlySummary[monthKey];
        yearTotal += amount;
        
        if (amount > 0) {
            std::cout << std::left << std::setw(15) << monthNames[i] 
                      << "$" << std::right << std::setw(13) << std::fixed << std::setprecision(2) << amount << std::endl;
        }
    }
    
    std::cout << std::string(30, '-') << std::endl;
    std::cout << std::left << std::setw(15) << "Total" 
              << "$" << std::right << std::setw(13) << std::fixed << std::setprecision(2) << yearTotal << std::endl;
}

// Helper methods
std::string UserInterface::getValidDate() const {
    std::string date;
    bool validDate = false;
    
    do {
        std::cout << "Enter date (YYYY-MM-DD, leave empty for today): ";
        std::getline(std::cin, date);
        
        if (date.empty()) {
            // Use current date
            std::time_t now = std::time(nullptr);
            std::tm* now_tm = std::localtime(&now);
            
            std::ostringstream oss;
            oss << std::put_time(now_tm, "%Y-%m-%d");
            date = oss.str();
            validDate = true;
        } else {
            validDate = isValidDate(date);
            if (!validDate) {
                std::cout << "Invalid date format. Please use YYYY-MM-DD." << std::endl;
            }
        }
    } while (!validDate);
    
    return date;
}

bool UserInterface::isValidDate(const std::string& date) const {
    std::regex dateRegex("\\d{4}-\\d{2}-\\d{2}");
    if (!std::regex_match(date, dateRegex)) {
        return false;
    }
    
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));
    
    if (month < 1 || month > 12) {
        return false;
    }
    
    if (day < 1) {
        return false;
    }
    
    // Check days in month
    const std::vector<int> daysInMonth = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Adjust for leap year
    int maxDays = daysInMonth[month];
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
        maxDays = 29;
    }
    
    return day <= maxDays;
}

bool UserInterface::isValidDouble(const std::string& str) const {
    std::regex doubleRegex("^[0-9]+(\\.[0-9]+)?$");
    return std::regex_match(str, doubleRegex);
}

bool UserInterface::isValidInt(const std::string& str) const {
    std::regex intRegex("^[0-9]+$");
    return std::regex_match(str, intRegex);
}