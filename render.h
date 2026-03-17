// render.h
// written by Jake Morgan
// last updated: 2026-03-17

#ifndef RENDER_H
#define RENDER_H

#include "product.h"
#include "manager.h"

#include <iostream>
#include <vector>
#include <thread> // for sleep
#include <chrono> // for milliseconds
#include <iomanip>

void splashTitle(); // Display the splash screen with the application title
void displayMenu(); // Display the main menu options to the user
void showProgressBar(int progress, int total); // Display a progress bar in the console based on the current progress and total steps
void simulateLoading(); // Simulate loading the database with a progress bar
std::string renderTitleRow(); // Helper function to render a single row of the inventory table
std::string renderProductRow(const Product& product); // Helper function to render a single product as a formatted row in the inventory table
std::string renderInventoryTable(const std::vector<Product>& products); // Helper function to render the entire inventory as a formatted table  

#endif // RENDER_H
// end of render.h