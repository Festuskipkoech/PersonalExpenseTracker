# Personal Expense Tracker - User Manual

## Table of Contents
1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Getting Started](#getting-started)
4. [Features](#features)
   - [Expense Management](#expense-management)
   - [Category Management](#category-management)
   - [Reports](#reports)
5. [Troubleshooting](#troubleshooting)

## Introduction

The Personal Expense Tracker is a command-line application designed to help you manage and track your personal expenses. It allows you to categorize expenses, view reports, and analyze your spending habits. This user manual provides instructions on how to install and use the application.

## Installation

### Prerequisites
- Ubuntu operating system
- g++ compiler (v7.0 or later)
- CMake (v3.10 or later)

### Installation Steps

1. **Install necessary packages**:
   ```bash
   sudo apt update
   sudo apt install build-essential cmake g++ git
   ```

2. **Clone or download the project**:
   If you have the source code as a folder, skip this step.
   Otherwise, download the source code to your machine.

3. **Navigate to the project directory**:
   ```bash
   cd personal_expense_tracker
   ```

4. **Build the application**:
   ```bash
   chmod +x build.sh
   ./build.sh
   ```

5. **Run the application**:
   ```bash
   ./build/ExpenseTracker
   ```

## Getting Started

When you first start the application, the main menu will be displayed:

```
===== Personal Expense Tracker =====
1. Expense Management
2. Category Management
3. Reports
0. Exit
```

Enter the number corresponding to the option you want to select and press Enter.

The application comes with some default expense categories. You can add, update, or delete these as needed.

## Features

### Expense Management

The Expense Management section allows you to:

1. **Add Expense**: 
   - Enter the amount (must be a positive number)
   - Enter a description for the expense
   - Enter the date (in YYYY-MM-DD format) or leave empty for today's date
   - Select a category by entering its ID

2. **View Expenses**:
   - Displays all recorded expenses with details

3. **Delete Expense**:
   - Allows you to delete an expense by its ID

### Category Management

The Category Management section allows you to:

1. **Add Category**:
   - Enter a name for the category
   - Optionally add a description

2. **View Categories**:
   - Displays all available categories

3. **Update Category**:
   - Modify the name and description of an existing category

4. **Delete Category**:
   - Remove a category (only if it has no associated expenses)

### Reports

The Reports section allows you to:

1. **View Total Expenses**:
   - Displays the sum of all your recorded expenses

2. **View Expenses by Category**:
   - Shows all expenses for a specific category
   - Displays the total amount spent in that category

3. **View Expenses by Date Range**:
   - Shows all expenses between two dates
   - Displays the total amount spent during that period

4. **View Category Distribution**:
   - Shows how your expenses are distributed across different categories
   - Displays amounts and percentages for each category

5. **View Monthly Summary**:
   - Shows a month-by-month breakdown of expenses for a specified year
   - Displays the total amount spent in the year

## Troubleshooting

### Data Files
- The application stores expense and category data in CSV files in the `data` directory
- If you experience data-related issues, check if these files exist and are not corrupted
- Default file paths: `data/expenses.csv` and `data/categories.csv`

### Common Issues

1. **Build Errors**:
   - Ensure you have the required packages installed
   - Make sure you have CMake version 3.10 or higher
   - Try deleting the build directory and rebuilding

2. **Runtime Errors**:
   - If the application crashes when loading data, check if the data files are properly formatted
   - Ensure you have read/write permissions for the data directory

3. **Data Not Saving**:
   - Ensure the data directory exists and is writable
   - Check available disk space

### Contact Support
If you encounter issues that aren't covered in this manual, please create an issue in the project repository or contact the developer for assistance.