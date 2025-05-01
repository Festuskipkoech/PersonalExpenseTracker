#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure with CMake
cmake ..

# Build the project
make

# Return to parent directory
cd ..

echo "Build complete. Run with ./build/ExpenseTracker"