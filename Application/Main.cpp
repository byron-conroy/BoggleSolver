#include "BoggleApplication.h"

#include <exception>
#include <iostream>

int main(int argc, char** argv)
{
    BoggleApplication application;

    try{
        application.Run(argc, argv);
    }
    catch (std::exception& exception)
    {
        std::cerr << "Error running Boggle Application - " << exception.what() << std::endl;
    }

    return 0;
}
