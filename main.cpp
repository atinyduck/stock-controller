// main.cpp
// written by Jake Morgan
// last updated: 2026-03-17

#include "manager.h"
#include "data/filehandler.h"
#include <iostream>
#include <string> // for std::string
#include <thread> // for sleep
#include <chrono> // for milliseconds

void splashTitle(); // Display the splash screen with the application title
void displayMenu(); // Display the main menu options to the user
bool displayInventory(const Manager& manager); // Display the current inventory of products in a user-friendly format
bool addProduct(Manager& manager); // Prompt the user for product details and add a new product to the manager's inventory
bool removeProduct(Manager& manager); // Prompt the user for a product ID and remove the corresponding product from the manager's inventory
bool saveInventory(const Manager& manager, const std::string& filename); // Save the current inventory to a file using the FileHandler class
bool loadInventory(Manager& manager, const std::string& filename); // Load inventory data
void quitApplication(); // Perform any necessary cleanup and exit the application
void showProgressBar(int progress, int total); // Display a progress bar in the console based
void simulateLoading(); // Simulate loading the database with a progress bar
std::string getUserInput(const std::string& prompt); // Get input from the user


int main() {
    
    splashTitle(); // Show the splash screen at the start of the application
    simulateLoading(); // Simulate loading the database with a progress bar

    Manager manager = Manager(); // Create an instance of the Manager class to manage the inventory

    while (true) {
        displayMenu(); // Display the main menu options to the user
        std::string choice = getUserInput("Enter your choice: "); // Get the user's menu choice

        switch (choice[0]) { // Use the first character of the input to determine the menu choice
            case '1':
                displayInventory(manager); // Display the current inventory
                break;
            case '2':
                addProduct(manager); // Add a new product to the inventory
                break;
            case '3':
                removeProduct(manager); // Remove a product from the inventory
                break;
            case '4':
                saveInventory(manager, "inventory.txt"); // Save the inventory to a file
                break;
            case '5':
                loadInventory(manager, "inventory.txt"); // Load the inventory from a file
                break;
            case '6':
                quitApplication(); // Exit the application
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl; // Handle invalid menu choices
        }
    }

    return 0; // Return success status code (though this line will never be reached due to the infinite loop)
};

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

std::string getUserInput(const std::string& prompt) {
    std::cout << prompt; // Display the prompt to the user
    std::string input;
    std::getline(std::cin, input); // Read a line of input from the user
    return input; // Return the user's input as a string
}

void simulateLoading() {
    std::cout << "Loading database..." << std::endl;
    int totalSteps = 100;
    for (int i = 0; i <= totalSteps; ++i) {
        showProgressBar(i, totalSteps); // Update the progress bar with the current progress
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate time-consuming loading with a short sleep
    }
    std::cout << std::endl; // Move to the next line after the progress bar is complete
}

void splashTitle() {
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

void displayMenu() {
    std::cout << "Please select an option:" << std::endl;
    std::cout << "  1  View Inventory" << std::endl;
    std::cout << "  2  Add Product" << std::endl;
    std::cout << "  3  Remove Product" << std::endl;
    std::cout << "  4  Save Inventory" << std::endl;
    std::cout << "  5  Load Inventory" << std::endl;
    std::cout << "  6  Exit" << std::endl;
}

bool displayInventory(const Manager& manager) {
    if (manager.getAllProducts().empty()) {
        std::cout << "Inventory is empty." << std::endl; // Inform the user if there are no products in the inventory
        return false; // Return false to indicate that the inventory is empty
    }
    std::cout << manager.display() << std::endl; // Call the manager's method to display the inventory
    return true; // Return true to indicate successful display
}

bool addProduct(Manager& manager) {
    try {
        std::string promt = "Enter product details (id,name,description,quantity,price): ";
        std::string input = getUserInput(promt); // Get product details from the user

        Product newProduct = Product::parseFromString(input); // Parse the input string to create a new Product object
        manager.addProduct(newProduct); // Add the new product to the manager's inventory
    }
    catch (const std::exception& e) {
        std::cerr << "Error adding product: " << e.what() << std::endl; // Handle any errors that occur during parsing or adding
        std::string correctFormat = "Correct format: id,name,description,quantity,price (e.g., \"3,Thingamajig,A versatile thingamajig,20,9.99\")";
        std::cout << correctFormat << std::endl; // Provide the user with the correct
        return false; // Return false to indicate that the product was not added successfully
    }
    return true; // Return true to indicate success
}

bool removeProduct(Manager& manager) {
    try {
        std::string input = getUserInput("Enter the ID of the product to remove: "); // Get the product ID from the user
        int productId = std::stoi(input); // Convert the input string to an integer ID
        manager.removeProduct(productId); // Attempt to remove the product with the specified ID
    }
    catch (const std::exception& e) {
        std::cerr << "Error removing product: " << e.what() << std::endl; // Handle any errors that occur during input conversion or removal
        return false; // Return false to indicate that the product was not removed successfully
    }
    return true; // Return true to indicate success
}

bool saveInventory(const Manager& manager, const std::string& filename) {
    try {
        std::string data = manager.serializeToString(); // Serialize the manager's inventory to a string
        FileHandler::saveToFile(filename, data); // Save the serialized data to a file
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving inventory: " << e.what() << std::endl; // Handle any errors that occur during serialization or file saving
        return false; // Return false to indicate that the inventory was not saved successfully
    }
    return true; // Return true to indicate success
}

bool loadInventory(Manager& manager, const std::string& filename) {
    try {
        std::string data = FileHandler::loadFromFile(filename); // Load inventory data from the specified file
        manager = manager.parseFromString(data); // Parse the loaded data to update the manager's inventory
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading inventory: " << e.what() << std::endl; // Handle any errors that occur during file loading or parsing
        return false; // Return false to indicate that the inventory was not loaded successfully
    }
    return true; // Return true to indicate success
}

void quitApplication() {
    std::cout << "Exiting application. Goodbye!" << std::endl; // Display a goodbye message to the user
    std::exit(0); // Exit the application with a success status code
}


// end of main.cpp