#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <map>
#include <set>


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
    PAUSED
};


 static const std::map<StateID , std::set<StateID> > validTransitions = {

{StateID::INITIALIZED,{StateID::PLAYING,StateID::LOADING}},
{StateID::PLAYING,{StateID::ANALYZING,StateID::CONCLUDED,StateID::SAVING,StateID::PAUSED,StateID::TERMINATED}},
{StateID::LOADING,{StateID::PLAYING}},
{StateID::SAVING,{StateID::PLAYING,StateID::CONCLUDED}},
{StateID::PAUSED,{StateID::PLAYING}},
{StateID::ANALYZING,{StateID::PLAYING}},
{StateID::CONCLUDED,{StateID::TERMINATED,StateID::SAVING}},
{StateID::TERMINATED,{}}

 };



class GameSM; // Forward declaration


// interface
class GameState
{
protected:

    StateID stateID;

public:
 
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


    StateID getStateID() const { return stateID;}

    virtual GameState* clone() const = 0;

};

//state objects

class InitializedState:public GameState
{
public:
    InitializedState();
    void handleNewGame(GameSM* game) override;
    void handleLoadGame(GameSM* game) override;
    GameState* clone() const override;
};


class PlayingState:public GameState
{
public:
    PlayingState();
    GameState* clone() const override;
    void handleNewGame(GameSM* game) override;
    void handleLoadGame(GameSM* game) override;
    void handleBoardReady(GameSM* game) override;
    void handleSaveGame(GameSM* game) override;
    void handleEndGame(GameSM* game) override;
    void handleGameOver(GameSM* game) override;
    void handleTurn(GameSM* game) override;
    void handlePause(GameSM* game) override;
    void handleResume(GameSM* game) override;
    };

class AnalyzingState:public GameState
{
public:
    AnalyzingState();
    GameState* clone() const override;
    void handleTurn(GameSM* game) override;
    void handlePieceMoved(GameSM* game) override;
};

class LoadingState:public GameState
{
public:
    LoadingState();
    GameState* clone() const override;
    void handleBoardReady(GameSM* game) override;
   
};

class SavingState:public GameState
{
public:
    SavingState();
    GameState* clone() const override;
    void handleBoardReady(GameSM* game) override;
};


class ConcludedState:public GameState
{
public:
    ConcludedState();
    GameState* clone() const override;    
    void handleEndGame(GameSM* game) override;
};


class TerminatedState:public GameState
{
public:
    TerminatedState();
    GameState* clone() const override;    
    void handleAppLaunched(GameSM* game) override;
    
};

class PauseState:public GameState
{
public:
    PauseState();
    GameState* clone() const override;       
    void handleResume(GameSM* game) override;
    
};


class GameSM
{
private:
   
    StateID stateID;
    bool isValid(StateID from , StateID to);
       
public: 
    GameState* currentState;
    GameSM(const GameSM& other);
    GameSM& operator=(const GameSM& other); 
    explicit GameSM(GameState* initialState);
    GameSM(){currentState=new InitializedState();  stateID=StateID::INITIALIZED;};

    void startSM();
    void stopSM();  
    void TurnKey();
    void SetState(GameState* newState);
    GameState* getCurrentState();
    void printCurrentState();

};







#endif