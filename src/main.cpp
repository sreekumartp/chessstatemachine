#include <statemachine.hpp>
#include <iostream>

int main()
{

GameSM myGame(new InitializedState());

    while(true)
    {

            std::cout << "Enter event ('s' for start State Machine , 'q' to quit): " << std::endl;

                    char input;

                    std::cin >> input;

        if (input == 's')
        {
            myGame.startSM();
        }
        if (input == 'q')
        {
        std::cout << "Exiting game...\n";
        break;
        }

        
    }

}