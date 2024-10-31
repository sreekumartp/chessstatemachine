#include <iostream>
#include <statemachine.hpp>




void GameState::handlePushButtonEvent(GameSM* game){} ;
void GameState::handleKeyTurnEvent(GameSM* game) {};

void GameState::handleAppLaunched(GameSM* game){} ;
void GameState::handleNewGame(GameSM* game){} ;
void GameState::handleLoadGame(GameSM* game){} ;
void GameState::handleBoardReady(GameSM* game){} ;
void GameState::handleSaveGame(GameSM* game){} ;
void GameState::handleEndGame(GameSM* game){} ;
void GameState::handleGameOver(GameSM* game){} ;
void GameState::handleTurn(GameSM* game){} ;
void GameState::handlePieceMoved(GameSM* game){} ;
void GameState::handlePause(GameSM* game){} ;
void GameState::handleResume(GameSM* game){} ;
    
    
GameSM::GameSM(const GameSM& other) {
    if (dynamic_cast<OpenState*>(other.currentState)) {
        currentState = new OpenState();
    } else if (dynamic_cast<ClosedState*>(other.currentState)) {
        currentState = new ClosedState();
    } else if (dynamic_cast<LockedState*>(other.currentState)) {
        currentState = new LockedState();
    }
}
GameSM& GameSM::operator=(const GameSM& other) {
    if (this == &other) {
        return *this;
    }
    delete currentState;
    currentState = other.currentState;
    return *this;
}
void GameSM::pushButton()
{
    currentState->handlePushButtonEvent(this);
}

void GameSM::TurnKey()
{
    currentState->handleKeyTurnEvent(this);
}

void GameSM::SetState(GameState* newState)
{
    delete currentState;
    currentState = newState;
}

GameState* GameSM::getCurrentState()
{

return this->currentState;

}

void OpenState::handlePushButtonEvent(GameSM* game) {
    std::cout << "Closing the door.\n";
    game->SetState(new ClosedState());
}

void OpenState::handleKeyTurnEvent(GameSM* game) {
    std::cout << "Door is open, not unlock possible.\n";
}

void ClosedState::handlePushButtonEvent(GameSM* game) {
    std::cout << "Opening the door.\n";
    game->SetState(new OpenState());
}

void ClosedState::handleKeyTurnEvent(GameSM* game) {
    std::cout << "Locking the door.\n";
    game->SetState(new LockedState());
}

void LockedState::handlePushButtonEvent(GameSM* game) {
    std::cout << "Door is locked. Cannot open.\n";
}

void LockedState::handleKeyTurnEvent(GameSM* game) {
    std::cout << "Unlocking the door.\n";
    game->SetState(new ClosedState());
}


void InitializedState::handleAppLaunched(GameSM* game){}
void InitializedState::handleNewGame(GameSM* game){}
void InitializedState::handleLoadGame(GameSM* game){}

void PlayingState::handleNewGame(GameSM* game) {}
void PlayingState::handleLoadGame(GameSM* game) {}
void PlayingState::handleBoardReady(GameSM* game) {}
void PlayingState::handleSaveGame(GameSM* game) {}
void PlayingState::handleEndGame(GameSM* game) {}
void PlayingState::handleGameOver(GameSM* game) {}
void PlayingState::handleTurn(GameSM* game) {}
void PlayingState::handlePieceMoved(GameSM* game) {}
void PlayingState::handlePause(GameSM* game) {}
void PlayingState::handleResume(GameSM* game) {}

void AnalyzingState::handleTurn(GameSM* game) {}
void AnalyzingState::handlePieceMoved(GameSM* game){}

void LoadingState::handleBoardReady(GameSM* game){}

void PauseState::handleResume(GameSM* game){}