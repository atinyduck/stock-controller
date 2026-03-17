// render.cpp
// written by Jake Morgan
// last updated: 2026-03-17

#include "render.h"

void showProgressBar(int progress, int total) {
    float percentage = (float)progress / total;
    int barWidth = 40;

    std::cout << "\r>"; // Move cursor to start of line and print start of bar
    
    int pos = barWidth * percentage;
    for (int i = 0; i < barWidth; ++i) {
        if (i <= pos) std::cout << "█";      // Completed or Current part 
        else std::cout << "▓";               // Empty part
    }
    
    std::cout << "< " << int(percentage * 100.0) << "% " << std::flush; // Print percentage and flush output
}


void simulateLoading() { // Simulate loading the database with a progress bar
    std::cout << "Loading..." << std::endl;
    int totalSteps = 100;
    for (int i = 0; i <= totalSteps; ++i) {
        showProgressBar(i, totalSteps); // Update the progress bar with the current progress
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate time-consuming loading with a short sleep
    }
    std::cout << std::endl; // Move to the next line after the progress bar is complete
}

void splashTitle() { // Display the splash screen with the application title
    // ANSI Color Codes
    std::string green = "\033[32m";
    std::string bold  = "\033[1m";
    std::string reset = "\033[0m";

    std::cout << green << bold; // Set text color to green and make it bold
    std::cout << "\t┌─────────────────────────┐" << std::endl;
    std::cout << "\t>  Stock Controller v1.0  <" << std::endl;
    std::cout << "\t└─────────────────────────┘\n" << std::endl;
    std::cout << reset; // Reset text formatting to default
}


void displayMenuTable() { // Display the main menu options to the user
    std::cout << "│ Menu Options                      |" << std::endl;
    std::cout << "├────┬──────────────────────────────┤" << std::endl;
    std::cout << "│ 1  │ Display Inventory            │" << std::endl;
    std::cout << "│ 2  │ Add Product                  │" << std::endl;
    std::cout << "│ 3  │ Remove Product               │" << std::endl;
    std::cout << "│ 4  │ Save Inventory to File       │" << std::endl;
    std::cout << "│ 5  │ Load Inventory from File     │" << std::endl;
    std::cout << "│ 6  │ Quit Application             │\n" << std::endl;
}

// table rendering functions
std::string renderTitleRow() { // Helper function to render a single row of the inventory table
    return "│ ID │ Name           │ Description                │ Quantity │ Price  │ Total Value │\n"
           "├────┼────────────────┼────────────────────────────┼──────────┼────────┼─────────────┤\n";
}

std::string renderProductRow(const Product& product) { // Helper function to render a single product as a row in the inventory table
    std::ostringstream oss;
    oss << "│ " << std::setw(2) << product.getId() << " │ "
        << std::setw(14) << product.getName() << " │ "
        << std::setw(26) << product.getDescription() << " │ "
        << std::setw(8) << product.getQuantity() << " │ "
        << std::setw(6) << std::fixed << std::setprecision(2) << product.getPrice() << " │ "
        << std::setw(11) << std::fixed << std::setprecision(2) << product.getTotalValue() << " │\n";
    return oss.str(); // Return the formatted string representation of the product row
}

std::string renderInventoryTable(const std::vector<Product>& products) { // Helper function to render the entire inventory as a formatted table
    std::string table = renderTitleRow(); // Start with the title row of the table
    for (const auto& product : products) {
        table += renderProductRow(product); // Append each product as a row in the table
    }
    return table; // Return the complete string representation of the inventory table
}
// end of render.cpp