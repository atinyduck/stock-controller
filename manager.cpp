// manager.cpp
// written by Jake Morgan
// last updated: 2026-03-17


#include "manager.h"

// ---- Implementation of Manager class ----
//    -- Constructor
Manager::Manager() : products() {} // Initialize the manager with an empty product list


//    -- Getters
std::vector<Product> Manager::getAllProducts() const {
    return products; // Return the list of all products
}

double Manager::getTotalInventoryValue() const {
    double totalValue = 0.0; // Initialize total value to zero
    for (const auto& product : products) {
        totalValue += product.getTotalValue(); // Add the total value of each product to the total inventory value
    }
    return totalValue; // Return the calculated total inventory value
}

//    -- Product management functions
void Manager::addProduct(const Product& product) {
    if (findProductById(product.getId()) != nullptr) {
        throw std::invalid_argument("Product with the same ID already exists.");
    }
    products.push_back(product); // Add the product to the list
}

void Manager::removeProduct(int productId) {
    // Validate that the product ID is non-negative
    if (productId < 0) {
        throw std::invalid_argument("Product ID cannot be negative.");
    }
    // Look for the product by ID and remove it if found
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getId() == productId) {
            products.erase(it); // Remove the product from the list
            return;
        }
    }
    throw std::runtime_error("Product with the specified ID not found."); // Throw an error
}

Product* Manager::findProductById(int productId) {
    for (auto& product : products) {
        if (product.getId() == productId) {
            return &product; // Return a pointer to the found product
        }
    }
    return nullptr; // Return nullptr if the product is not found
}        


//    -- Parser
Manager Manager::parseFromString(const std::string& str) {
    Manager manager; // Create a new manager object
    // Expected format: "Manager with X products:\nid,name,description,quantity,price\n..."
    size_t pos = str.find("Manager with ");
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid manager string format.");
    }
    pos += 13; // Move past "Manager with "
    size_t endPos = str.find(" products:");
    if (endPos == std::string::npos) {
        throw std::invalid_argument("Invalid manager string format.");
    }
    int productCount = std::stoi(str.substr(pos, endPos - pos)); // Extract the number of products
    size_t currentPos = str.find("\n", endPos) + 1; // Move to the start of the product list
    for (int i = 0; i < productCount; ++i) {
        endPos = str.find("\n", currentPos);
        if (endPos == std::string::npos) {
            throw std::invalid_argument("Invalid manager string format: missing product entries.");
        }
        std::string productStr = str.substr(currentPos, endPos - currentPos); // Extract the string representation of the product
        manager.addProduct(Product::parseFromString(productStr)); // Parse the product and add it to the manager's list
        currentPos = endPos + 1; // Move to the start of the next product entry
    }
    return manager; // Return the parsed manager object
}

//    -- Serializer
std::string Manager::serializeToString() const {
    std::string result = "Manager with " + std::to_string(products.size()) + " products:\n"; // Start the string representation with the number of products
    for (const auto& product : products) {
        result += Product::serializeToString(product) + "\n"; // Append the string representation of each product to the result
    }
    return result; // Return the complete string representation of the manager and its products
}

//    -- Visualization
void Manager::displayInventory() const {
    // Display all products
    std::string output = "===-------------------===\n     Total Value: $" + std::to_string(getTotalInventoryValue()) 
                       + "\nCurrent Inventory:";
    for (const auto& product : getAllProducts()) {
        output += product.display(); // Append the user-friendly string representation of each product to the output
    }
}

// end of manager.cpp