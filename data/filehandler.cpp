// filehandler.cpp
// written by Jake Morgan
// last updated: 2026-03-17

#include "filehandler.h"
#include <fstream>
#include <stdexcept>

// ---- Implementation of FileHandler class ----
void FileHandler::saveToFile(const std::string& filename, const std::string& data) {
    std::ofstream outFile(filename); // Open the file for writing
    if (!outFile) {
        throw std::runtime_error("Could not open file for writing: " + filename); // Throw an error if the file cannot be opened
    }
    outFile << data; // Write the data to the file
    outFile.close(); // Close the file
}

std::string FileHandler::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename); // Open the file for reading
    if (!inFile) {
        throw std::runtime_error("Could not open file for reading: " + filename); // Throw an error if the file cannot be opened
    }
    std::string data((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>()); // Read the entire contents of the file into a string
    inFile.close(); // Close the file
    return data; // Return the loaded data as a string
}

bool FileHandler::deleteFile(const std::string& filename) {
    if (std::remove(filename.c_str()) == 0) { // Attempt to delete the file
        return true; // Return true if the file was successfully deleted
    } else {
        return false; // Return false if the file could not be deleted (e.g., it does not exist)
    }
}

// end of filehandler.cpp