#include <iostream>
#include <statemachine.hpp>
#include <cassert>




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
        stateID = currentState->getStateID();
        
};

GameSM::GameSM(const GameSM& other) 
{

    if (other.currentState) 
    {
        currentState = other.currentState->clone();
    } 
    else 
    {
        currentState = nullptr;
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


void GameSM::SetState(GameState* newState)
{
    StateID newStateID = newState->getStateID();
    StateID currStateID = currentState->getStateID();

 
    std::cout << "Transitioning from state: " << typeid(*currentState).name() << " to state: " << typeid(*newState).name() << std::endl;
 
    assert((newStateID != currStateID) && "Invalid state reentry");

    if (newStateID == currStateID) {
        delete newState;  // Clean up the new state if transition is invalid
        throw std::runtime_error("Invalid state reentry");
    }
    delete currentState;
    currentState = newState;
}

GameState* GameSM::getCurrentState()
{

return this->currentState;

}


InitializedState::InitializedState() {
    std::cout << "InitializedState created.\n";
    GameState::stateID=StateID::INITIALIZED;
}

GameState* InitializedState::clone() const { return new InitializedState(*this); }



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

GameState* PlayingState::clone() const { return new PlayingState(*this); }


void PlayingState::handleNewGame(GameSM* game) {

assert(false && "Invalid state transition: PlayingState::handleNewGame");
throw std::logic_error("Invalid state transition: PlayingState::handleNewGame");

}
void PlayingState::handleLoadGame(GameSM* game) {
    assert(false && "Invalid state transition: PlayingState::handleLoadGame");
    throw std::logic_error("Invalid state transition: PlayingState::handleLoadGame");
}
void PlayingState::handleBoardReady(GameSM* game) {
    assert(false && "Invalid state transition: PlayingState::handleBoardReady");
    throw std::logic_error("Invalid state transition: PlayingState::handleBoardReady");
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

GameState* AnalyzingState::clone() const { return new AnalyzingState(*this); }



void AnalyzingState::handleTurn(GameSM* game) {
    assert(false && "Invalid state transition: AnalyzingState::handleTurn");
    throw std::logic_error("Invalid state transition: PlayingState::handleTurn");
    
}

void AnalyzingState::handlePieceMoved(GameSM* game){
    std::cout << "Analyzing move. Transitioning to PlayingState.\n";
    game->SetState(new PlayingState());
}



SavingState::SavingState() {
    std::cout << "SavingState created.\n";
    GameState::stateID=StateID::SAVING;
}

GameState * SavingState::clone() const {return new SavingState(*this);}


void SavingState::handleBoardReady(GameSM* game)
{
    std::cout << "Board is ready. Transitioning to PlayingState.\n";
    game->SetState(new PlayingState());

}


LoadingState::LoadingState() {
    std::cout << "LoadingState created.\n";
    GameState::stateID=StateID::LOADING;
}

GameState* LoadingState::clone() const{ return new LoadingState(*this);}

void LoadingState::handleBoardReady(GameSM* game){
    std::cout << "Board is ready. Transitioning to PlayingState.\n";
        game->SetState(new PlayingState());
}


PauseState::PauseState() {
    std::cout << "PauseState created.\n";
    GameState::stateID=StateID::PAUSED;
}

GameState *PauseState::clone() const { return new PauseState(*this);}

void PauseState::handleResume(GameSM* game){
    std::cout << "Resuming from pause. Transitioning to PlayingState.\n";
        game->SetState(new PlayingState());
}


GameState * ConcludedState::clone() const {return new ConcludedState(*this);}

ConcludedState::ConcludedState() {
    std::cout << "ConcludedState created.\n";
    GameState::stateID=StateID::CONCLUDED;
}

void ConcludedState::handleEndGame(GameSM* game)
{

    game->SetState(new TerminatedState());
}

TerminatedState::TerminatedState() {
    std::cout << "TerminatedState created.\n";
    GameState::stateID=StateID::TERMINATED;
}

GameState* TerminatedState::clone() const {return new TerminatedState(*this);}

void TerminatedState::handleAppLaunched(GameSM* game)
{

    std::cout << "Application launched in TerminatedState. Performing Cleanup\n";
    
}