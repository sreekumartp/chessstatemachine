#include <statemachine.hpp>

int main()
{

GameSM myGame;

while(true)
{

        std::cout << "Enter event ('p' for PushButton, 't' for TurnKey, 'q' to quit): ";

                char input;

                std::cin >> input;

    if (input == 'p')
    {
        myGame.pushButton();
    }
    else if (input == 't')
    {
        myGame.TurnKey();
    }
    }
}