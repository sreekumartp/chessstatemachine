#include <statemachine.hpp>

int main()
{

    GameSM myGame(new InitializedState());


    myGame.SetState(new PlayingState());

    myGame.getCurrentState()->handleNewGame(&myGame);



}