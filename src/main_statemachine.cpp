#include <statemachine.hpp>
#include <iostream>
#include <limits>

int main()
{

GameSM myGame(new InitializedState());

    while(true)
    {

    std::cout << "Enter event ('p' for start State Machine, 'q' to quit): ";
    char input;
        if (!(std::cin >> input)) 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }
        
    }

}