// product.h
// written by Jake Morgan
// last updated: 2026-03-17

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <stdexcept>

class Product {
    private:
        int id;
        std::string name;
        std::string description;
        int quantity;
        double price;

    public:
        Product(int id, const std::string& name, const std::string& description, int quantity, double price);

        // Getters
        int getId() const;
        std::string getName() const;
        std::string getDescription() const;
        int getQuantity() const;
        double getPrice() const;
        double getTotalValue() const;

        // Setters
        void setQuantity(int quantity);
        void setPrice(double price);

        // Parser
        static Product parseFromString(const std::string& str);

        // Serializer
        static std::string serializeToString(const Product& product);

        // Visualization
        std::string display() const; // Return a user-friendly string representation of the product
};

#endif // PRODUCT_H
// end of product.h