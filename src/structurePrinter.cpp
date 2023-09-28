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
/// @return This method returns 0 if the file structure was printed successfully
int structurePrinterInternals::printStructure(string folderName)
{
    cout << "Printing the file structure of " << folderName << endl;

    for (const auto & entry : filesystem::directory_iterator(folderName))
    {
        cout << entry.path() << endl;
    }

    return 0;
}