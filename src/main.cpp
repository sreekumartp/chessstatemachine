#include <statemachine.hpp>

int main()
{

GameSM myGame;

    while(true)
    {

            std::cout << "Enter event ('s' for start State Machine , 'q' to quit): ";

                    char input;

                    std::cin >> input;

        if (input == 'p')
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