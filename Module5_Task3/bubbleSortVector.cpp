#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm> 
//Task3:

// function to initialise vector with random numbers
inline void initialiseVector(std::vector<int>& myVector)
{
    // using random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    // iterate through vector and at each index place generated random number from (1-100)
    for (std::vector<int>::iterator it = myVector.begin(); it != myVector.end(); ++it)
    {
        *it = dis(gen); // dereference the iterator to assign the random number
    }
}

// function to output vector contents separated by commas
inline void outputVector(const std::vector<int>& myVector)
{
    for (std::vector<int>::const_iterator it = myVector.begin(); it != myVector.end(); ++it)
    {
        std::cout << *it;
        if (it != myVector.end() - 1) // check if it's not the last element
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl; // print a new line after output
}

// function to bubble sort vector
void BubbleSort(std::vector<int>& myVector, int order)
{
    int n = myVector.size();
    // outer loop corresponds to the number of elements to be sorted
    for (int i = 0; i < n - 1; i++)
    {
        // flag for when the array is sorted and doesn't cause any swaps
        bool flag = false;
        // last i elements are already in place
        for (int j = 0; j < n - i - 1; j++)
        {
            // comparing adjacent elements - ascending (order == 1)
            if (order == 1 && myVector[j] > myVector[j + 1])
            {
                // swapping if in the wrong order
                std::swap(myVector[j], myVector[j + 1]);
                // setting flag = true when swap happens
                flag = true;
            }
            // comparing adjacent elements - descending (order == -1)
            else if (order == -1 && myVector[j] < myVector[j + 1])
            {
                // swapping if in the wrong order
                std::swap(myVector[j], myVector[j + 1]);
                // setting flag = true when swap happens
                flag = true;
            }
        }
        // checking if flag is set or not
        if (!flag)
        {
            break; // break if no swaps were made, the vector is already sorted
        }
    }
}

int main()
{
    std::vector<int> myVector;
    myVector.resize(10); // resize to hold 10 elements
    // initialise the vector elements
    initialiseVector(myVector);

    std::cout << "Initial Vector: " << std::endl;
    outputVector(myVector);

    // bubble sort in ascending order
    BubbleSort(myVector, 1);

    std::cout << "Sorted Vector (ascending): " << std::endl;
    outputVector(myVector);

    // bubble sort in descending order
    BubbleSort(myVector, -1);

    std::cout << "Sorted Vector (descending): " << std::endl;
    outputVector(myVector);

    return 0;
}
