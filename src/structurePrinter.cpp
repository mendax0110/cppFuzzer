/**
 * @file structurePrinter.cpp
 * @author Adrian Goessl
 * @brief Functions and Method to print the file structure in the terminal
 * @version 0.1
 * @date 2023-09-28
 * 
 * @copyright MIT 2023
 * 
 */
#include "../src/includes/structurePrinter.h"

using namespace std;
using namespace structurePrinter;

/// @brief This is the method to print the file structure
/// @param folderName With this parameter the user can specify the folder to print
/// @return This method returns 0 if the file structure was printed successfully, otherwise it returns 1
int structurePrinterInternals::printStructure(string folderName)
{
    try
    {
        cout << "-------------------------------------------------------------------------------------------------\n";
        cout << "Printing the file structure of " << folderName << endl;
        cout << "-------------------------------------------------------------------------------------------------\n";

        for (const auto & entry : filesystem::directory_iterator(folderName))
        {
            cout << entry.path() << endl;

            // save the path to a object
            filesystem::path path = entry.path();
            
            // safe the path as a string
            string pathString = path.string();
        }

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief This is the method to print the file structure recursive
/// @param folderName This is the folder to print
/// @return This method returns 0 if the file structure was printed successfully, otherwise it returns 1
int structurePrinterInternals::printStructureRecursive(const std::filesystem::path& currentPath)
{
    try
    {
        if (std::filesystem::is_directory(currentPath))
        {
            cout << "-------------------------------------------------------------------------------------------------\n";
            cout << "Printing the file structure of " << currentPath << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            
            for (const auto& entry : std::filesystem::directory_iterator(currentPath))
            {
                std::cout << entry.path() << std::endl;

                if (std::filesystem::is_directory(entry))
                {
                    // Recursively call printStructureRecursive for subdirectories
                    printStructureRecursive(entry);
                }
            }
        }

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief This is the method to view the folder structure
/// @param folderName This is the folder to view
/// @param fileEnding This is the file ending to search for
/// @param fileContent This is the file content to search for
/// @return This will return 0 if the folder structure was viewed successfully, otherwise it will return 1
int structurePrinterInternals::folderStructureViewer(string folderName, string fileEnding, string fileContent)
{
    try
    {
        // move through the folder structure
        for(const auto & entry : filesystem::recursive_directory_iterator(folderName))
        {
            // save the path to a object
            filesystem::path path = entry.path();

            // safe the path as a string
            string pathString = path.string();

            // check if the file has the correct file ending
            if(pathString.find(fileEnding) != string::npos)
            {
                // check if the file contains the correct content
                if(pathString.find(fileContent) != string::npos)
                {
                    cout << "Found the file: " << pathString << endl;
                }
            }
        }

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
