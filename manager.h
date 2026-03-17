// manager.h
// written by Jake Morgan
// last updated: 2026-03-17

#ifndef MANAGER_H
#define MANAGER_H

#include "product.h"
#include <vector>
#include <string>

class Manager {
    private:
        std::vector<Product> products; // List of products under the manager's control

    public:
        // constructor
        Manager(); // Initialize the manager with an empty product list

        // getters
        std::vector<Product> getAllProducts() const; // Return a list of all products
        double getTotalInventoryValue() const; // Calculate and return the total value of all products in inventory

        // setters
        void setTitle(const std::string& title); // Set the title of the manager

        // product management functions
        void addProduct(const Product& product); // Add a new product to the manager's list
        void removeProduct(int productId); // Remove a product from the manager's list by its
        Product* findProductById(int productId); // Find and return a pointer to a product by its ID

        // parser
        Manager parseFromString(const std::string& str); // Parse a manager object from a string representation

        // serializer
        std::string serializeToString() const; // Serialize the manager object to a string representation

        // visualization
        void displayInventory() const; // Display the inventory of products in a user-friendly format
};

#endif // MANAGER_H
// end of manager.h