/**
 * @file macroBase.h
 * @author Adrian Goessl
 * @brief This is the header file for the macroBase
 * @version 0.1
 * @date 2024-02-01
 * 
 * @copyright MIT 2023
 * 
 */
#ifndef MACROBASE_H
#define MACROBASE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

/*
 * @brief This is the macro for the catch with consequence proceed
 */
#define CATCH_WITH_CONSEQUENCE_PROCEED(condition, consequence) \
    if (condition) \
    { \
        consequence; \
    }

/*
 * @brief This is the macro for the catch with consequence return
 */
#define CATCH_WITH_CONSEQUENCE_RETURN(condition, consequence, returnValue) \
    if (condition) \
    { \
        consequence; \
        return returnValue; \
    }

/*
 * @brief This is the macro to log the stack trace
 */ 
#define LOG_STACK_TRACE() \
    std::cout << "Stack trace: " << std::endl; \
    std::cout << "File: " << __FILE__ << std::endl; \
    std::cout << "Line: " << __LINE__ << std::endl; \
    std::cout << "Function: " << __func__ << std::endl;

/*
 * @brief This is the macro to log the stack trace with return
 */ 
#define LOG_STACK_TRACE_WITH_RETURN(returnValue) \
    std::cout << "Stack trace: " << std::endl; \
    std::cout << "File: " << __FILE__ << std::endl; \
    std::cout << "Line: " << __LINE__ << std::endl; \
    std::cout << "Function: " << __func__ << std::endl; \
    return returnValue;

/*
 * @brief This is the macro to create a hashmap
 */ 
#define CREATE_HASHMAP(hashmapName, keyType, valueType) \
    std::unordered_map<keyType, valueType> hashmapName; \
    hashmapName.reserve(1000); \
    hashmapName.max_load_factor(0.75); \

#endif // !MACROBASE_H