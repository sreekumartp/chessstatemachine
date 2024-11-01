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
    
GameSM::GameSM(const GameSM& other) {
    if (dynamic_cast<InitializedState*>(other.currentState)) {
        currentState = new InitializedState();
    } else if (dynamic_cast<PlayingState*>(other.currentState)) {
        currentState = new PlayingState();
    } else if (dynamic_cast<AnalyzingState*>(other.currentState)) {
        currentState = new AnalyzingState();
    }
    else if (dynamic_cast<LoadingState*>(other.currentState)) {
        currentState = new LoadingState();
    }
    else if (dynamic_cast<PauseState*>(other.currentState)) {
        currentState = new PauseState();
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
    delete currentState;
    currentState = newState;
}

GameState* GameSM::getCurrentState()
{

return this->currentState;

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

void AnalyzingState::handleTurn(GameSM* game) {
    assert(false && "Invalid state transition: AnalyzingState::handleTurn");
}

void AnalyzingState::handlePieceMoved(GameSM* game){
    std::cout << "Analyzing move. Transitioning to PlayingState.\n";
    game->SetState(new PlayingState());
}


void SavingState::handleBoardReady(GameSM* game)
{
    std::cout << "Board is ready. Transitioning to PlayingState.\n";
    game->SetState(new PlayingState());

}

void LoadingState::handleBoardReady(GameSM* game){
    std::cout << "Board is ready. Transitioning to PlayingState.\n";
        game->SetState(new PlayingState());
}

void PauseState::handleResume(GameSM* game){
    std::cout << "Resuming from pause. Transitioning to PlayingState.\n";
        game->SetState(new PlayingState());
}

void ConcludedState::handleEndGame(GameSM* game)
{

    game->SetState(new TerminatedState());
}

void TerminatedState::handleAppLaunched(GameSM* game)
{

    std::cout << "Application launched in TerminatedState. Performing Cleanup\n";
    
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