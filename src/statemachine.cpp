#include <iostream>
#include <statemachine.hpp>
#include <cassert>



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

void GameSM::printCurrentState()
{
    auto presentState = this->getCurrentState();
    std::cout << "Current state: " << typeid(*presentState).name() << std::endl;

}

 GameSM::GameSM(GameState* initialState)
    {

        currentState = initialState;
          if (dynamic_cast<InitializedState*>(currentState))
          {

            stateID = StateID::INITIALIZED;

          }
          else if (dynamic_cast<PlayingState*>(currentState))
          {
            stateID = StateID::PLAYING;
          }
          else if (dynamic_cast<AnalyzingState*>(currentState))
          {
            stateID = StateID::ANALYZING;
          }
          else if (dynamic_cast<LoadingState*>(currentState))
          {
            stateID = StateID::LOADING;
          }
          else if (dynamic_cast<SavingState*>(currentState))
          {
            stateID = StateID::SAVING;
          }
          else if (dynamic_cast<ConcludedState*>(currentState))
          {
            stateID = StateID::CONCLUDED;
          }
          else if (dynamic_cast<TerminatedState*>(currentState))
          {
            stateID = StateID::TERMINATED;
          }
          else if (dynamic_cast<PauseState*>(currentState))
          {
            stateID = StateID::PAUSED;
          }
          else if (dynamic_cast<OpenState*>(currentState))
          {
            stateID = StateID::OPEN;
          }
          else if (dynamic_cast<ClosedState*>(currentState))
          {
            stateID = StateID::CLOSED;
          }
          else if (dynamic_cast<LockedState*>(currentState))
          {
            stateID = StateID::LOCKED;
          }

    };



GameSM::GameSM(const GameSM& other) {
    if (dynamic_cast<InitializedState*>(other.currentState)) {
        currentState = new InitializedState();
        stateID = StateID::INITIALIZED;
    } else if (dynamic_cast<PlayingState*>(other.currentState)) {
        currentState = new PlayingState();
        stateID = StateID::PLAYING;
    } else if (dynamic_cast<AnalyzingState*>(other.currentState)) {
        currentState = new AnalyzingState();
        stateID = StateID::ANALYZING;
    }
    else if (dynamic_cast<LoadingState*>(other.currentState)) {
        currentState = new LoadingState();
        stateID = StateID::LOADING;
    }
    else if (dynamic_cast<PauseState*>(other.currentState)) {
        currentState = new PauseState();
        stateID = StateID::PAUSED;
    } 
    else if (dynamic_cast<SavingState*>(other.currentState)) {
        currentState = new SavingState();
        stateID = StateID::SAVING;
    } else if (dynamic_cast<ConcludedState*>(other.currentState)) {
        currentState = new ConcludedState();
        stateID = StateID::CONCLUDED;
    } else if (dynamic_cast<TerminatedState*>(other.currentState)) {
        currentState = new TerminatedState();
        stateID = StateID::TERMINATED;
    } else if (dynamic_cast<OpenState*>(other.currentState)) {
        currentState = new OpenState();
        stateID = StateID::OPEN;
    } else if (dynamic_cast<ClosedState*>(other.currentState)) {
        currentState = new ClosedState();
        stateID = StateID::CLOSED;
    } else if (dynamic_cast<LockedState*>(other.currentState)) {
        currentState = new LockedState();
        stateID = StateID::LOCKED;
    }



}


GameSM& GameSM::operator=(const GameSM& other) {
    if (this == &other) {
        return *this;
    }
    delete currentState;
    currentState = other.currentState;
    if (dynamic_cast<InitializedState*>(other.currentState)) {
        stateID = StateID::INITIALIZED;
    } else if (dynamic_cast<PlayingState*>(other.currentState)) {
        stateID = StateID::PLAYING;
    } else if (dynamic_cast<AnalyzingState*>(other.currentState)) {
        stateID = StateID::ANALYZING;
    } else if (dynamic_cast<LoadingState*>(other.currentState)) {
        stateID = StateID::LOADING;
    } else if (dynamic_cast<SavingState*>(other.currentState)) {
        stateID = StateID::SAVING;
    } else if (dynamic_cast<ConcludedState*>(other.currentState)) {
        stateID = StateID::CONCLUDED;
    } else if (dynamic_cast<TerminatedState*>(other.currentState)) {
        stateID = StateID::TERMINATED;
    } else if (dynamic_cast<PauseState*>(other.currentState)) {
        stateID = StateID::PAUSED;
    } else if (dynamic_cast<OpenState*>(other.currentState)) {
        stateID = StateID::OPEN;
    } else if (dynamic_cast<ClosedState*>(other.currentState)) {
        stateID = StateID::CLOSED;
    } else if (dynamic_cast<LockedState*>(other.currentState)) {
        stateID = StateID::LOCKED;
    }
    return *this;
}

void GameSM::startSM()
{
    currentState->handleAppLaunched(this);
    std::cout << "State machine started. Current state: " << typeid(*currentState).name() << std::endl;
}

void GameSM::stopSM()
{
    currentState->handleEndGame(this);
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
    StateID newStateID = newState->getStateID2();
    StateID currStateID = currentState->getStateID2();

 
    std::cout << "Transitioning from state: " << typeid(*currentState).name() << " to state: " << typeid(*newState).name() << std::endl;
 
    assert((newStateID != currStateID) && "Invalid state reentry");
    if (newStateID != currStateID)
    {    
        delete currentState;
        currentState = newState;
    }
}

GameState* GameSM::getCurrentState()
{

return this->currentState;

}

  StateID GameState::getStateID()
  {
    return stateID;
  }

InitializedState::InitializedState() {
    std::cout << "InitializedState created.\n";
    GameState::stateID=StateID::INITIALIZED;
}

StateID InitializedState::getStateID()
{
return this->stateID;


}


void InitializedState::handleAppLaunched(GameSM* game){
    std::cout << "Application launched. Transitioning to InitializedState.\n";
    game->SetState(new InitializedState());
}
void InitializedState::handleNewGame(GameSM* game){
    std::cout << "Starting a new game. Transitioning to PlayingState.\n";
        game->SetState(new PlayingState());
}
void InitializedState::handleLoadGame(GameSM* game){
    std::cout << "Loading a game. Transitioning to LoadingState.\n";
        game->SetState(new LoadingState());
}


PlayingState::PlayingState() {
    std::cout << "PlayingState created.\n";
    GameState::stateID=StateID::PLAYING;
}

StateID PlayingState::getStateID()
{
return this->stateID;


}



void PlayingState::handleNewGame(GameSM* game) {

assert(false && "Invalid state transition: PlayingState::handleNewGame");

}
void PlayingState::handleLoadGame(GameSM* game) {
    assert(false && "Invalid state transition: PlayingState::handleLoadGame");
}
void PlayingState::handleBoardReady(GameSM* game) {
    assert(false && "Invalid state transition: PlayingState::handleBoardReady");
}
void PlayingState::handleSaveGame(GameSM* game) {
std::cout << "Loading a game. Transitioning to SavingState.\n";
        game->SetState(new SavingState());
}
void PlayingState::handleEndGame(GameSM* game) {
    std::cout << "Ending the game. Transitioning to TerminatedState.\n";
        game->SetState(new TerminatedState());
}
void PlayingState::handleGameOver(GameSM* game) {
    std::cout << "Game over. Transitioning to ConcludedState.\n";
    game->SetState(new ConcludedState());
}
void PlayingState::handleTurn(GameSM* game) {
    std::cout << "Player's turn. Transitioning to AnalyzingState.\n";
        game->SetState(new AnalyzingState());
}
void PlayingState::handlePieceMoved(GameSM* game) {
    std::cout << "Piece moved. Transitioning to PlayingState.\n";
        game->SetState(new PlayingState());
}
void PlayingState::handlePause(GameSM* game) {
    std::cout << "Pausing the game. Transitioning to PauseState.\n";
        game->SetState(new PauseState());
}
void PlayingState::handleResume(GameSM* game) {
    std::cout << "Resuming the game. Transitioning to PlayingState.\n";
        game->SetState(new PlayingState());
}


AnalyzingState::AnalyzingState() {
    std::cout << "AnalyzingState created.\n";
    GameState::stateID=StateID::ANALYZING;
}

StateID AnalyzingState::getStateID()
{
return this->stateID;


}


void AnalyzingState::handleTurn(GameSM* game) {
    assert(false && "Invalid state transition: AnalyzingState::handleTurn");
}

void AnalyzingState::handlePieceMoved(GameSM* game){
    std::cout << "Analyzing move. Transitioning to PlayingState.\n";
    game->SetState(new PlayingState());
}



SavingState::SavingState() {
    std::cout << "SavingState created.\n";
    GameState::stateID=StateID::ANALYZING;
}

StateID SavingState::getStateID()
{
return this->stateID;
}


void SavingState::handleBoardReady(GameSM* game)
{
    std::cout << "Board is ready. Transitioning to PlayingState.\n";
    game->SetState(new PlayingState());

}


LoadingState::LoadingState() {
    std::cout << "LoadingState created.\n";
    GameState::stateID=StateID::LOADING;
}

StateID LoadingState::getStateID()
{
return this->stateID;
}

void LoadingState::handleBoardReady(GameSM* game){
    std::cout << "Board is ready. Transitioning to PlayingState.\n";
        game->SetState(new PlayingState());
}


PauseState::PauseState() {
    std::cout << "PauseState created.\n";
    GameState::stateID=StateID::LOADING;
}

StateID PauseState::getStateID()
{
return this->stateID;
}



void PauseState::handleResume(GameSM* game){
    std::cout << "Resuming from pause. Transitioning to PlayingState.\n";
        game->SetState(new PlayingState());
}



ConcludedState::ConcludedState() {
    std::cout << "ConcludedState created.\n";
    GameState::stateID=StateID::CONCLUDED;
}

StateID ConcludedState::getStateID()
{
return this->stateID;
}




void ConcludedState::handleEndGame(GameSM* game)
{

    game->SetState(new TerminatedState());
}

TerminatedState::TerminatedState() {
    std::cout << "TerminatedState created.\n";
    GameState::stateID=StateID::TERMINATED;
}

StateID TerminatedState::getStateID()
{
return this->stateID;
}


void TerminatedState::handleAppLaunched(GameSM* game)
{

    std::cout << "Application launched in TerminatedState. Performing Cleanup\n";
    
}


OpenState::OpenState() {
    std::cout << "OpenState created.\n";
    GameState::stateID=StateID::OPEN;
}

StateID OpenState::getStateID()
{
return this->stateID;
}



void OpenState::handlePushButtonEvent(GameSM* game) {
    std::cout << "Closing the door.\n";
    game->SetState(new ClosedState());
}

void OpenState::handleKeyTurnEvent(GameSM* game) {
    std::cout << "Door is open, not unlock possible.\n";
}


ClosedState::ClosedState() {
    std::cout << "ClosedState created.\n";
    GameState::stateID=StateID::CLOSED;
}

StateID ClosedState::getStateID()
{
return this->stateID;
}



void ClosedState::handlePushButtonEvent(GameSM* game) {
    std::cout << "Opening the door.\n";
    game->SetState(new OpenState());
}

void ClosedState::handleKeyTurnEvent(GameSM* game) {
    std::cout << "Locking the door.\n";
    game->SetState(new LockedState());
}


LockedState::LockedState() {
    std::cout << "LockedState created.\n";
    GameState::stateID=StateID::LOCKED;
}

StateID LockedState::getStateID()
{
return this->stateID;
}



void LockedState::handlePushButtonEvent(GameSM* game) {
    std::cout << "Door is locked. Cannot open.\n";
}

void LockedState::handleKeyTurnEvent(GameSM* game) {
    std::cout << "Unlocking the door.\n";
    game->SetState(new ClosedState());
}