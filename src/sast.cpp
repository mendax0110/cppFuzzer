/**
 * @file sast.cpp
 * @author Adrian Goessl
 * @brief This is the implementation of the static analyzer
 * @version 0.1
 * @date 2023-10-05
 * 
 * @copyright MIT 2023
 * 
 */
#include "../src/includes/sast.h"

using namespace std;
using namespace sast;

/// @brief This is the static code analyzer method \name runSast
/// @param fileName This is the file name
/// @return This method returns 0 for success and 1 for failure
int sastInternals::runSast(string fileName)
{
    cout << "-------------------------------------------------------------------------\n";
    cout << "Running the static analyzer on " << fileName << endl;
    cout << "-------------------------------------------------------------------------\n";

    try
    {
        // open the file
        ifstream inputFile(fileName);

        if (!inputFile.is_open())
        {
            throw runtime_error("Failed to open the input file");
        }

        // store the content of the file in a string
        stringstream buffer;

        buffer << inputFile.rdbuf();

        string fileContent = buffer.str();

        analyzeKeywords(fileContent);

        analyzeSQLInjection(fileContent);

        // close the file
        inputFile.close();

        return 0;

    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief This is the function to create the regex pattern and search for keywords \name analyzeKeywords
/// @param content This is the content of the file
void sastInternals::analyzeKeywords(const string& content) 
{
    string controlFlowKeywords = "if|while|for|switch|case|default|";
    string memoryManagementKeywords = "new|delete|malloc|free";
    string fileHandlingKeywords = "open|read|write|close";
    string concurrencyKeywords ="thread|mutex|lock|unlock|semaphone|condition_variable";
    string stringManipulationKeywords = "strlen|strcpy|strcat|strncpy|strncat";
    string numericTypes = "int|float|double|long|short|char|bool|unsigned";
    string securityKeywords = "strcpy|strcat|gets|sprintf";

    string combinePattern = "(" + controlFlowKeywords + "|" + memoryManagementKeywords + "|" + 
                                fileHandlingKeywords + "|" + concurrencyKeywords + "|" + 
                                stringManipulationKeywords + "|" + numericTypes + "|" + 
                                securityKeywords + ")";

    regex keywordsRegex(combinePattern, regex_constants::icase);

    smatch match;

    if(regex_search(content, match, keywordsRegex))
    {
        cout << "Keyword found: "  << match[0] << endl;
    }
    else
    {
        cout << "No keyword found." << endl;
    }

    cout << "-------------------------------------------------------------------------\n";
}

void sastInternals::analyzeSQLInjection(const string& content) 
{
    // Detect potential SQL injection patterns
    string sqlInjectionKeywords = "select|insert|update|delete|drop|alter|truncate|exec|union";

    regex sqlInjectionRegex(sqlInjectionKeywords, regex_constants::icase);

    smatch matches;
    auto it = content.cbegin();

    while (regex_search(it, content.cend(), matches, sqlInjectionRegex)) 
    {
        cout << "Potential SQL injection found: " << matches[0] << endl;
        it = matches.suffix().first;
    }

    cout << "-------------------------------------------------------------------------\n";
}

/// @brief This is the cleanup method \name cleanup, this will be used to cleanup resources
/// @return This will return 0 for success and 1 for failure
int sastInternals::cleanUp()
{
    try
    {
        // TODO: Cleanup resources
        
        return 0;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}
