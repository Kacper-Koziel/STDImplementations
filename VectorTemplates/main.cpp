#include "Vector.cc"

int main()
{
    Vector<Vector<int>> newVector;

    newVector.resize(5);
    std::cout << newVector.getCapacity();

    for (int i = 0; i < newVector.getSize(); i++)
    {
        newVector.at(i).resize(5);
        std::cout << newVector.at(i).getCapacity() << std::endl;
    }

    for (int i = 0; i < newVector.getSize(); i++)
    {
        for (int j = 0; j < newVector.at(i).getSize(); j++)
        {
            newVector.at(i).at(j) = i * j;
        }
    }


    for (int i = 0; i < newVector.getSize(); i++)
    {
        for (int j = 0; j < newVector.at(i).getSize(); j++)
        {
            std::cout << "i: " << i << ", j: " << j << ", val: " << newVector.at(i).at(j) << std::endl;
        }
    }   
    
}