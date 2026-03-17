// filerhandler.h
// written by Jake Morgan
// last updated: 2026-03-17

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class FileHandler {
    public:
        static void saveToFile(const std::string& filename, const std::string& data); // Save the given data to a file with the specified filename
        static std::string loadFromFile(const std::string& filename); // Load and return the contents of a file with the specified filename as a string
        bool deleteFile(const std::string& filename); // Delete the file with the specified filename and return true if the deletion was successful, false otherwise
};

#endif // FILEHANDLER_H
// end of filehandler.h