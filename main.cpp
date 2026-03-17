// main.cpp
// written by Jake Morgan
// last updated: 2026-03-17

#include "manager.h"
#include "data/filehandler.h"
#include "render.h" 

#include <iostream>
#include <string> // for std::string

bool displayInventory(const Manager& manager); // Display the current inventory of products in a user-friendly format
bool addProduct(Manager& manager); // Prompt the user for product details and add a new product to the manager's inventory
bool removeProduct(Manager& manager); // Prompt the user for a product ID and remove the corresponding product from the manager's inventory
bool saveInventory(const Manager& manager, const std::string& filename); // Save the current inventory to a file using the FileHandler class
bool loadInventory(Manager& manager, const std::string& filename); // Load inventory data
void quitApplication(); // Perform any necessary cleanup and exit the application
std::string getUserInput(const std::string& prompt); // Get input from the user


int main() {
    
    splashTitle(); // Show the splash screen at the start of the application
    simulateLoading(); // Simulate loading the database with a progress bar

    Manager manager = Manager(); // Create an instance of the Manager class to manage the inventory

    while (true) {
        displayMenuTable(); // Display the main menu options to the user
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

std::string getUserInput(const std::string& prompt) {
    std::cout << prompt; // Display the prompt to the user
    std::string input;
    std::getline(std::cin, input); // Read a line of input from the user
    return input; // Return the user's input as a string
}

// ---- Implementation of main application functions ----
bool displayInventory(const Manager& manager) { // Option 1: Display the current inventory of products
    if (manager.getAllProducts().empty()) {
        std::cout << "\n *** Inventory is empty. ***" << std::endl; // Inform the user if there are no products in the inventory
        return false; // Return false to indicate that the inventory is empty
    }
    std::cout << renderInventoryTable(manager.getAllProducts()) << std::endl; // Render the inventory display 
    return true; // Return true to indicate successful display
}

bool addProduct(Manager& manager) { // Option 2: Prompt the user for product details and add a new product to the inventory
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

bool removeProduct(Manager& manager) { // Option 3: Prompt the user for a product ID and remove the corresponding product from the inventory
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

bool saveInventory(const Manager& manager, const std::string& filename) { // Option 4: Save the current inventory to a file using the FileHandler class
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

bool loadInventory(Manager& manager, const std::string& filename) { // Option 5: Load inventory data from a file using the FileHandler class and update the manager's inventory
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

void quitApplication() { // Option 6: Perform any necessary cleanup and exit the application
    std::cout << "Exiting application. Goodbye!" << std::endl; // Display a goodbye message to the user
    std::exit(0); // Exit the application with a success status code
}


// end of main.cpp