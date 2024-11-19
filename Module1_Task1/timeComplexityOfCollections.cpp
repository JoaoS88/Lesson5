#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include <random>
#include <functional>

// Template works by:

// A template is a mechanism that allows writing generic code that works with any data type or class.
// It allows a single function or class to handle different data types or containers and maintains type safety and reusability.
//
// Syntax for a template function:
// template <typename Container> { function definition }
//
// Example:
// template <typename Container>
// long long profileBackInsert(Container& container, size_t numElements) { ... }
//
// Capture Clause [typename Container]:
//    - The "typename" keyword declares a template type. "Container" is a placeholder for an actual type that will be used when the function is called.
//    - In the example, "Container" can be any container type like "std::vector", "std::list", or "std::deque", or even a custom container type.
//
// Function Definition Example:
//    - The template function can be written once and reused for any container type that supports the operations used in the function (e.g., push_back, push_front, random access).
//    - This ensures code reusability and avoids duplication, allowing you to handle different container types in the same function.
//
// Calling a Template Function:
//    - When you call a template function like "profileBackInsert", you specify the container type (e.g., "std::vector<int>").
//    - The compiler generates the appropriate version of the function for the specific container type based on the template definition.
//


// Lambda works by:

// A lambda functionis an anonymous function that can be defined inline.
// It allows you to define a function without needing to create a separate named function elsewhere in the code.
//
// The syntax for a lambda function is:
// [capture](parameters) { body }
//
// Capture Clause "[capture]":
//    - The capture clause allows the lambda to "capture" variables from the surrounding scope, either by reference "(&)" or by value.
//    - For example, "[this]" or "[&]" captures all variables by reference, allowing them to be accessed or modified inside the lambda.
//    - In the example, "[&]" captures the variable "container" by reference, which means the lambda can modify it directly.
//
// Parameters (parameters):
//    - Can define parameters if the lambda needs to take inputs.
//    - In example it doesn't need to so the parantheses are empty
//
// Body { body }:
//    - The body of the lambda contains the code that gets executed when the lambda is called. 
//    - In example the body contains the logic to insert elements into the container using "push_back".
//
// Example: 
// long long profileBackInsert(Container& container, size_t numElements) 
// {
//     return measureTime // lambda function, inserts elements into back of container
//     ([&]() { for (size_t i = 0; i < numElements; ++i) { container.push_back(i); } } );
// }                      
// - The lambda [&]() { ... } is passed to the "measureTime" function.
// - The "measureTime" function executes the code inside the lambda.

// function to measure time of execution
long long measureTime(std::function<void()> func)
{
    auto start = std::chrono::high_resolution_clock::now(); // starts the clock
    func(); // performs the operation
    auto end = std::chrono::high_resolution_clock::now();   // ends the clock
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // returns the time taken in microseconds difference between end and start times
}

// profiling insert at the back of the container
template <typename Container>
long long profileBackInsert(Container& container, size_t numElements)
{
    return measureTime([&]()
        {
            for (size_t i = 0; i < numElements; ++i)
            {
                container.push_back(i); // insert at the back (works for vector, list, deque)
            }
        });
}

// profiling insert at the front of the container
template <typename Container>
long long profileFrontInsert(Container& container, size_t numElements)
{
    return measureTime([&]()
        {
            for (size_t i = 0; i < numElements; ++i)
            {
                container.push_front(i); // insert at the front (works for deque and list)
            }
        });
}

// profiling random access (for vector and deque only)
template <typename Container>
long long profileRandomAccess(Container& container, size_t numAccesses)
{
    // ensure container is not empty
    if (container.empty())
    {
        return 0; // no time to measure if the container is empty
    }

    // only proceed for containers that support random access
    if constexpr (std::is_same_v<Container, std::vector<int>> || std::is_same_v<Container, std::deque<int>>)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, container.size() - 1);

        return measureTime([&]()
            {
                for (size_t i = 0; i < numAccesses; ++i)
                {
                    volatile auto x = container[dis(gen)]; // random access to elements
                }
            });
    }
    else
    {
        return 0; // no random access for non-random-access containers like list
    }
}

int main()
{
    // number of elements to insert
    size_t numElements = 100000;
    // number of random accesses to test
    size_t numAccesses = 10000;

    // create containers
    std::vector<int> vec;
    std::list<int> lst;
    std::deque<int> deq;

    // profile insert at the back
    std::cout << "insert at back:" << std::endl;
    std::cout << "vector: " << profileBackInsert(vec, numElements) << " microseconds" << std::endl;
    std::cout << "list: " << profileBackInsert(lst, numElements) << " microseconds" << std::endl;
    std::cout << "deque: " << profileBackInsert(deq, numElements) << " microseconds" << std::endl;

    // profile insert at the front
    // clear containers before the next test
    vec.clear();
    lst.clear();
    deq.clear();
    std::cout << "\ninsert at front:" << std::endl;
    std::cout << "deque: " << profileFrontInsert(deq, numElements) << " microseconds" << std::endl;
    std::cout << "list: " << profileFrontInsert(lst, numElements) << " microseconds" << std::endl;
    std::cout << "vector: insertion at front is inefficient for vector!" << std::endl;

    // profile random access (only for vector and deque)
    std::cout << "\nrandom access:" << std::endl;
    std::cout << "vector: " << profileRandomAccess(vec, numAccesses) << " microseconds" << std::endl;
    std::cout << "deque: " << profileRandomAccess(deq, numAccesses) << " microseconds" << std::endl;
    std::cout << "list: no random access, so not applicable!" << std::endl;

    // summary of the expected performance given the way the different containers work
    std::cout << "\nsummary:" << std::endl;
    std::cout << "1. vector is the fastest for random access due to contiguous memory." << std::endl;
    std::cout << "2. list is the slowest for front insertion because elements need to be shifted." << std::endl;
    std::cout << "3. deque is fast for both front and back insertions, but not as fast as vector for random access." << std::endl;

    return 0;
}



