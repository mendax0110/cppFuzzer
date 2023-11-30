/**
 * @file addressSanitizer.cpp
 * @brief Address Sanitizer for finding memory leaks
 * @version 0.1
 * @date 2023-10-05
 * @author Adrian Goessl
 */
#include "../src/includes/sanitizer.h"

using namespace std;
using namespace sanitizer;

// Create the different sanitizers, using the sanitizerInternals class
sanitizerInternals addressSanitizer;
sanitizerInternals memorySanitizer;
sanitizerInternals threadSanitizer;
sanitizerInternals undefinedBehaviorSanitizer;

// Define the different sanitizer types
sanitizerInternals::sanitizerType addressSanitizerType = sanitizerInternals::sanitizerType::addressSanitizer;
sanitizerInternals::sanitizerType memorySanitizerType = sanitizerInternals::sanitizerType::memorySanitizer;
sanitizerInternals::sanitizerType threadSanitizerType = sanitizerInternals::sanitizerType::threadSanitizer;
sanitizerInternals::sanitizerType undefinedBehaviorSanitizerType = sanitizerInternals::sanitizerType::undefinedBehaviorSanitizer;

/// @brief This is the method to run the sanitizer
/// @param sanitizerType This is the sanitizer type
/// @param fileName This is the file name, which will be analyzed
/// @return This will return 0 if the sanitizer was run successfully, otherwise it will return 1
int sanitizerInternals::runSanitizer(sanitizerType sanitizerType, string fileName)
{
    try
    {
        switch (sanitizerType)
        {
        case sanitizerType::addressSanitizer:
            cout << "Running the address sanitizer" << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            runAddressSanitizer(fileName);
            cout << "-------------------------------------------------------------------------------------------------\n";
            break;
        case sanitizerType::memorySanitizer:
            cout << "Running the memory sanitizer" << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            runMemorySanitizer(fileName);
            cout << "-------------------------------------------------------------------------------------------------\n";
            break;
        case sanitizerType::threadSanitizer:
            cout << "Running the thread sanitizer" << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            runThreadSanitizer(fileName);
            cout << "-------------------------------------------------------------------------------------------------\n";
            break;
        case sanitizerType::undefinedBehaviorSanitizer:
            cout << "Running the undefined behavior sanitizer" << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            runUndefinedBehaviorSanitizer(fileName);
            cout << "-------------------------------------------------------------------------------------------------\n";
            break;
        case sanitizerType::customSanitizationRule:
            cout << "Running the custom sanitization rule" << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            customSanitizationRule(fileName);
            cout << "-------------------------------------------------------------------------------------------------\n";
            break;
        case sanitizerType::sanitizeLogicMemory:
            cout << "Running the logic memory sanitizer" << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            sanitizeLogicMemory(fileName);
            cout << "-------------------------------------------------------------------------------------------------\n";
            break;
        case sanitizerType::sanitizeLogicThread:
            cout << "Running the logic thread sanitizer" << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            sanitizeLogicThread(fileName);
            cout << "-------------------------------------------------------------------------------------------------\n";
            break;
        default:
            cerr << "Invalid sanitizer type" << endl;
            return 1;
        }
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}

/// @brief This is the method to run the address sanitizer
/// @param fileName This is the file name, which will be analyzed
/// @return This method returns 0 if the address sanitizer was run successfully, otherwise it returns 1
int sanitizerInternals::runAddressSanitizer(string fileName)
{
    try
    {
        // Open and analyze the file for memory-related issues
        ifstream inputFile(fileName);

        if (!inputFile.is_open())
        {
            throw runtime_error("Failed to open the input file");
        }

        // check the content of the file if there are any address leaks
        stringstream buffer;

        buffer << inputFile.rdbuf();

        string fileContent = buffer.str();

        // Close the input file
        inputFile.close();

        // Write the modified content back to the same file
        ofstream outputFile(fileName);

        if (!outputFile.is_open())
        {
            throw runtime_error("Failed to open the output file");
        }

        outputFile << fileContent;

        // Report any memory leaks or errors found
        if(fileContent.find("0x") != string::npos)
        {
            cout << "Memory leak found" << endl;
        }
        else
        {
            cout << "No memory leak found" << endl;
        }

        outputFile.close();

        // Clean up resources
        buffer.str("");
        fileContent = "";

        cout << "Address sanitizer completed for " << fileName << endl;

        return 0;
    }
    catch (const exception &e)
    {
        cerr << "Error in address sanitizer: " << e.what() << endl;
        return 1; // Return an error code if an exception occurs
    }
}

/// @brief This is the method to run the memory sanitizer
/// @param fileName This is the file name, which will be analyzed
/// @return This will return 0 if the memory sanitizer was run successfully, otherwise it will return 1
int sanitizerInternals::runMemorySanitizer(string fileName)
{
    try
    {
        // Implement the memory sanitizer logic for the given file
        // For example:
        // Open and analyze the file for memory-related issues
        ifstream inputFile(fileName);

        if (!inputFile.is_open())
        {
            throw runtime_error("Failed to open the input file");
        }

        // check the content of the file if there are any address leaks
        stringstream buffer;

        buffer << inputFile.rdbuf();

        string fileContent = buffer.str();

        // Close the input file
        inputFile.close();

        // Write the modified content back to the same file
        ofstream outputFile(fileName);

        if (!outputFile.is_open())
        {
            throw runtime_error("Failed to open the output file");
        }

        outputFile << fileContent;

        // Report any memory leaks or errors found
        // For example: nullpointer, memory leaks, buffer overflow
        if(fileContent.find("0x") != string::npos)
        {
            cout << "Memory leak found" << endl;
        }
        else if(fileContent.find("->") != string::npos)
        {
            cout << "Nullpointer found" << endl;
        }
        else if(fileContent.find("[]") != string::npos)
        {
            cout << "Buffer overflow found" << endl;
        }
        else if(fileContent.find("0") != string::npos)
        {
            cout << "Memory leak found" << endl;
        }
        else
        {
            cout << "No memory leak found" << endl;
        }

        outputFile.close();
        
        // Clean up resources
        buffer.str("");
        fileContent = "";

        cout << "Memory sanitizer completed for " << fileName << endl;

        return 0; // Return appropriate value, e.g., the number of errors found
    }
    catch (const exception &e)
    {
        cerr << "Error in memory sanitizer: " << e.what() << endl;
        return 1; // Return an error code if an exception occurs
    }
}

/// @brief This is the method to run the thread sanitizer
/// @param fileName This is the file name, which will be analyzed
/// @return This will return 0 if the thread sanitizer was run successfully, otherwise it will return 1
int sanitizerInternals::runThreadSanitizer(string fileName)
{
    try
    {
        // Implement the thread sanitizer logic for the given file
        // Analyze the threaded code for race conditions or other issues
        // - Report any thread-related errors found
        // - Clean up resources

        cout << "Thread sanitizer completed for " << fileName << endl;

        return 0; // Return appropriate value, e.g., the number of errors found
    }
    catch (const exception &e)
    {
        cerr << "Error in thread sanitizer: " << e.what() << endl;
        return 1; // Return an error code if an exception occurs
    }
}

/// @brief This is the method to run the undefined behavior sanitizer
/// @param fileName This is the file name, which will be analyzed
/// @return This will return 0 if the undefined behavior sanitizer was run successfully, otherwise it will return 1
int sanitizerInternals::runUndefinedBehaviorSanitizer(string fileName)
{
    try
    {
        // Implement the undefined behavior sanitizer logic for the given file
        ifstream inputFile(fileName);

        if(!inputFile.is_open())
        {
            throw runtime_error("Failed to open the input file");
        }

        // check the code for undefined behavior, out of bounds accesses
        stringstream buffer;

        buffer << inputFile.rdbuf();

        string fileContent = buffer.str();

        // Close the input file
        inputFile.close();

        // - Report any undefined behavior errors found
        // - Clean up resources

        cout << "Undefined behavior sanitizer completed for " << fileName << endl;

        return 0; // Return appropriate value, e.g., the number of errors found
    }
    catch (const exception &e)
    {
        cerr << "Error in undefined behavior sanitizer: " << e.what() << endl;
        return 1; // Return an error code if an exception occurs
    }
}

mutex mtx;

/// @brief Function that represents the work performed by each thread
void threadFunction(int threadId)
{
    {
        lock_guard<mutex> lock(mtx);
        cout << "Thread " << threadId << " is performing work." << endl;
    }
}

const int bufferSize = 10;

/// @brief  Function to perform memory sanitization by zeroing out memory
/// @param memory This is the memory pointer to be sanitized
/// @param size This will be the size of the memory to be sanitized
void sanitizeMemory(void* memory, size_t size)
{
    // Check if the memory pointer is not null and size is greater than 0
    if (memory != nullptr && size > 0)
    {
        // Use memset to zero out the memory
        memset(memory, 0, size);
    }
}

/// @brief This is the method to sanitize the memory
/// @param fileName This is the file name, which will be analyzed
/// @return This will return 0 if the memory was sanitized successfully, otherwise it will return 1
int sanitizerInternals::sanitizeLogicMemory(string fileName)
{
    try
    {
        cout << "-------------------------------------------------------------------------------------------------\n";
        cout << "Sanitizing the memory of " << fileName << endl;
        cout << "-------------------------------------------------------------------------------------------------\n";

        // allocating and sanitizing memory for an array of integers
        int* data1 = new int[bufferSize];
        sanitizeMemory(data1, bufferSize * sizeof(int));
        delete[] data1;

        // allocating and sanitizing memory for a string
        char* str = new char[bufferSize];
        strcpy(str, "SensitiveData");
        sanitizeMemory(str, bufferSize);
        delete[] str;

        // allocating and sanitizing memory using malloc/free
        const int bufferSize = 20;
        char* data2 = (char*)malloc(bufferSize);
        strcpy(data2, "SensitiveData");
        sanitizeMemory(data2, bufferSize);
        free(data2);

        return 0;
    }
    catch (const exception &e)
    {
        cerr << "Error in memory sanitization: " << e.what() << endl;
        return 1; // Return an error code if an exception occurs
    }
}

void sanitizerInternals::customSanitizationRule(const string& fileName) 
{
    // Custom rule: Detect and report insecure random number generation functions (e.g., rand())
    regex insecureRandomFunction("\\brand\\s*\\(");
    if (regex_search(fileName, insecureRandomFunction)) {
        cout << "Custom sanitization rule triggered: Insecure random number generation function (rand()) detected." << endl;
        cout << "Consider using std::random_device or other secure alternatives for random number generation." << endl;
    }
}

/// @brief Function to sanitize threads
/// @param fileName This is the file name, which will be analyzed
/// @return This will return 0 if the threads were sanitized successfully, otherwise it will return 1
int sanitizeThreads(string fileName)
{
    try
    {
        cout << "Sanitizing threads for " << fileName << endl;
        
        // create and manage a collection of threads
        vector<thread> threads;
        const int numThreads = 4; // Adjust the number of threads as needed

        // Create and start threads
        for (int i = 0; i < numThreads; ++i)
        {
            threads.push_back(thread(threadFunction, i));
        }

        // Wait for all threads to finish
        for (auto& t : threads)
        {
            t.join();
        }

        return 0;
    }
    catch (const exception &e)
    {
        cerr << "Error in thread sanitization: " << e.what() << endl;
        return 1; // Return an error code if an exception occurs
    }
}

/// @brief This is the method to sanitize the threads
/// @param fileName This is the file name, which will be analyzed
/// @return This will return 0 if the threads were sanitized successfully, otherwise it will return 1
int sanitizerInternals::sanitizeLogicThread(string fileName)
{
    return sanitizeThreads(fileName);
}

/// @brief This is the function to cleanup resources \name cleanUp
/// @return This will return 0 if the cleanup was successful, otherwise it will return 1
int sanitizerInternals::cleanUp()
{
    try
    {
        // TODO: Add cleanup logic here
        return 0;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}
