// product.cpp
// written by Jake Morgan
// last updated: 2026-03-17

#include "product.h"
#include <iomanip>


// ---- Implementation of Product class ----
//      -- Constructor 
Product::Product(int id, const std::string& name, const std::string& description, int quantity, double price)
    : id(id), name(name), description(description), quantity(quantity), price(price) {}

//      -- Getters
int Product::getId() const { return id; } // Return the product ID 
std::string Product::getName() const { return name; } // Return the product name
std::string Product::getDescription() const { return description; } // Return the product description
int Product::getQuantity() const { return quantity; } // Return the current quantity of the product
double Product::getPrice() const { return price; } // Return the current price of the product
double Product::getTotalValue() const { return quantity * price; } // Calculate and return the total value of the product (quantity * price)

//     -- Setters
void Product::setQuantity(int quantity) {
    // Validate that the quantity is positive
    if (quantity < 0) { throw std::invalid_argument("Quantity cannot be negative.");}

    this->quantity = quantity; // Update the quantity of the product
}

void Product::setPrice(double price) {
    // Validate that the price is postive
    if (price < 0) { throw std::invalid_argument("Price cannot be negative."); }

    this->price = price; // Update the price of the product
}

//     -- Parser
Product Product::parseFromString(const std::string& str) {
    // Expected format: "id,name,description,quantity,price"
    size_t pos = 0; 
    int id;
    std::string name;
    std::string description;
    int quantity;
    double price;

    // Parse ID
    pos = str.find(',');
    if (pos == std::string::npos) { throw std::invalid_argument("Invalid format: missing fields."); }
    id = std::stoi(str.substr(0, pos));
    
    // Parse Name
    size_t start = pos + 1;
    pos = str.find(',', start);
    if (pos == std::string::npos) { throw std::invalid_argument("Invalid format: missing fields."); }
    name = str.substr(start, pos - start);
    
    // Parse Description
    start = pos + 1;
    pos = str.find(',', start);
    if (pos == std::string::npos) { throw std::invalid_argument("Invalid format: missing fields."); }
    description = str.substr(start, pos - start);
    
    // Parse Quantity
    start = pos + 1;
    pos = str.find(',', start);
    if (pos == std::string::npos) { throw std::invalid_argument("Invalid format: missing fields."); }
    quantity = std::stoi(str.substr(start, pos - start));
    
    // Parse Price
    price = std::stod(str.substr(pos + 1));

    return Product(id, name, description, quantity, price); // Return a new Product object created from the parsed string
}

//     -- Serlializer
std::string Product::serializeToString(const Product& product) {
    return std::to_string(product.getId()) + "," + 
           product.getName() + "," + 
           product.getDescription() + "," + 
           std::to_string(product.getQuantity()) + "," + 
           std::to_string(product.getPrice()); // Convert the Product object to a string in the format "id,name,description,quantity,price"
}

//     -- Visualization
std::string Product::display() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    
    return    "\n           ID: " + std::to_string(getId())
            + "\n         Name: " + getName()
            + "\n  Description: " + getDescription()
            + "\n     Quantity: " + std::to_string(getQuantity())
            + "\n        Price: $" + (oss.str().empty() ? std::to_string(getPrice()) : std::to_string(getPrice()));
}

// end of product.cpp