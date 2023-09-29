/**
 * @file structurePrinter.h
 * @author Adrian Goessl
 * @brief HEader file for the structure printer
 * @version 0.1
 * @date 2023-09-28
 * 
 * @copyright MIT 2023
 * 
 */
#include <iostream>
#include <filesystem>
#include <string>

#ifndef STRUCTUREPRINTER_H
#define STRUCTUREPRINTER_H

/// @brief The structurePrinter namespace \name structurePrinter
namespace structurePrinter
{
    /// @brief The structurePrinterInternals class, which has the public and private members \class structurePrinterInternals   
    class structurePrinterInternals
    {
    public:
        int printStructure(std::string folderName); 
        int printStructureRecursive(std::string folderName);
        int folderStructureViewer(std::string folderName, std::string fileEnding, std::string fileContent);

    private:
        
    };
};



#endif // !STRUCTUREPRINTER_H