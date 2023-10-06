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
int sast::sastInternals::runSast(string fileName)
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

        // perform the static analysis, so check for the following:
        string Keywords = "goto|break|continue|return|throw|exit|abort|assert";

        regex KeywordsRegex(Keywords);

        smatch match;

        if (regex_search(fileContent, match, KeywordsRegex))
        {
            cout << "The file contains the following keywords: " << match.str() << endl;
            cout << "-------------------------------------------------------------------------\n";
        }
        else
        {
            cout << "The file does not contain any keywords" << endl;
            cout << "-------------------------------------------------------------------------\n";
        }

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

/// @brief This is the cleanup method \name cleanup, this will be used to cleanup resources
/// @return This will return 0 for success and 1 for failure
int sast::sastInternals::cleanUp()
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
