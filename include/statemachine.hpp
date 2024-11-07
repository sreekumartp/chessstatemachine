#ifndef STATEMACHINE_H
#define STATEMACHINE_H


enum class StateID
{
    UNKNOWN,
    INITIALIZED,
    PLAYING,
    ANALYZING,
    LOADING,
    SAVING,
    CONCLUDED,
    TERMINATED,
    PAUSED,
    OPEN,
    CLOSED,
    LOCKED
};

class GameSM; // Forward declaration


// interface
class GameState
{
protected:

    StateID stateID;

public:
    virtual void handlePushButtonEvent(GameSM* door) ;
    virtual void handleKeyTurnEvent(GameSM* door) ;
 
    virtual void handleAppLaunched(GameSM* game) ;
    virtual void handleNewGame(GameSM* game) ;
    virtual void handleLoadGame(GameSM* game) ;
    virtual void handleBoardReady(GameSM* game) ;
    virtual void handleSaveGame(GameSM* game) ;
    virtual void handleEndGame(GameSM* game) ;
    virtual void handleGameOver(GameSM* game) ;
    virtual void handleTurn(GameSM* game) ;
    virtual void handlePieceMoved(GameSM* game) ;
    virtual void handlePause(GameSM* game) ;
    virtual void handleResume(GameSM* game) ;
    
    virtual ~GameState() = default;

    virtual StateID getStateID();

       StateID getStateID2() const {
        return stateID;
    }
};

//state objects

class InitializedState:public GameState
{
public:
    InitializedState();
    StateID getStateID() override;
    void handleAppLaunched(GameSM* game) override;
    void handleNewGame(GameSM* game) override;
    void handleLoadGame(GameSM* game) override;
   
};


class PlayingState:public GameState
{
public:
    PlayingState();
    StateID getStateID() override;

    void handleNewGame(GameSM* game) override;
    void handleLoadGame(GameSM* game) override;
    void handleBoardReady(GameSM* game) override;
    void handleSaveGame(GameSM* game) override;
    void handleEndGame(GameSM* game) override;
    void handleGameOver(GameSM* game) override;
    void handleTurn(GameSM* game) override;
    void handlePieceMoved(GameSM* game) override;
    void handlePause(GameSM* game) override;
    void handleResume(GameSM* game) override;
    };

class AnalyzingState:public GameState
{
public:
    AnalyzingState();
    StateID getStateID() override;
    void handleTurn(GameSM* game) override;
    void handlePieceMoved(GameSM* game) override;
};

class LoadingState:public GameState
{
public:
    LoadingState();
    StateID getStateID() override;
    void handleBoardReady(GameSM* game) override;
   
};

class SavingState:public GameState
{
public:
    SavingState();
    StateID getStateID() override;
    void handleBoardReady(GameSM* game) override;
};


class ConcludedState:public GameState
{
public:
    ConcludedState();
    StateID getStateID() override;       
    void handleEndGame(GameSM* game) override;
};


class TerminatedState:public GameState
{
public:
    TerminatedState();
    StateID getStateID() override;   
    void handleAppLaunched(GameSM* game) override;
    
};

class PauseState:public GameState
{
public:
    PauseState();
    StateID getStateID() override;   
    void handleResume(GameSM* game) override;
    
};

class OpenState:public GameState
{
public:
    OpenState();
    StateID getStateID() override;   
    void handlePushButtonEvent(GameSM* door) override;
    void handleKeyTurnEvent(GameSM* door) override;
};

class ClosedState:public GameState
{
public:
    ClosedState();
    StateID getStateID() override;  
    void handlePushButtonEvent(GameSM* door) override;
    void handleKeyTurnEvent(GameSM* door) override;
};

class LockedState:public GameState
{
public:
    LockedState();
    StateID getStateID() override;  
    void handlePushButtonEvent(GameSM* door) override;
    void handleKeyTurnEvent(GameSM* door) override;
};



class GameSM
{
private:

    StateID stateID;
    
public: 
    GameState* currentState;
    GameSM(const GameSM& other);
    GameSM& operator=(const GameSM& other); 
    explicit GameSM(GameState* initialState);
    GameSM(){currentState=new InitializedState();  stateID=StateID::INITIALIZED;};
   
    void pushButton();
    void startSM();
    void stopSM();  
    void TurnKey();
    void SetState(GameState* newState);
    GameState* getCurrentState();
    void printCurrentState();

};







#endif