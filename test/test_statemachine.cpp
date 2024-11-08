#include <gtest/gtest.h>
#include <statemachine.hpp>


class GameStateMachineTest : public ::testing::Test {
public:
    GameSM* game;
    
    void SetUp() override {
        // Code for setting up before each test
        game = new GameSM();
    }

    void TearDown() override {
        // Code for cleaning up after each test
        // delete game;
    }
};


TEST_F(GameStateMachineTest, InitializedStateToPlayingState) {
   
    
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ( currStateID, StateID::INITIALIZED);
    
    game->getCurrentState()->handleNewGame(game);
    
    StateID newStateID = game->getCurrentState()->getStateID();
    // Verify post-transition state
    EXPECT_EQ(newStateID, StateID::PLAYING);
    auto* playingState = dynamic_cast<PlayingState*>(game->getCurrentState());
    ASSERT_NE(nullptr, playingState);
}


TEST_F(GameStateMachineTest, PlayingStateToPauseState) {

    game->SetState(new PlayingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::PLAYING);

    game->getCurrentState()->handlePause(game);

    StateID newStateID = game->getCurrentState()->getStateID();
    // Verify post-transition state
    EXPECT_EQ(newStateID, StateID::PAUSED);
    auto* pauseState = dynamic_cast<PauseState*>(game->getCurrentState());
    ASSERT_NE(nullptr, pauseState);


}



TEST_F(GameStateMachineTest, PauseStateToPlayingState) {
    game->SetState(new PauseState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::PAUSED);

    game->getCurrentState()->handleResume(game);

    StateID newStateID = game->getCurrentState()->getStateID();
    // Verify post-transition state
    EXPECT_EQ(newStateID, StateID::PLAYING);
    auto* playingState = dynamic_cast<PlayingState*>(game->getCurrentState());
    ASSERT_NE(nullptr, playingState);
}

TEST_F(GameStateMachineTest, PlayingStateToConcludedState) {

    game->SetState(new PlayingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::PLAYING);

    game->getCurrentState()->handleGameOver(game);

    StateID newStateID = game->getCurrentState()->getStateID();
    // Verify post-transition state
    EXPECT_EQ(newStateID, StateID::CONCLUDED);
    auto* concludedState = dynamic_cast<ConcludedState*>(game->getCurrentState());
    ASSERT_NE(nullptr, concludedState);
    
}

TEST_F(GameStateMachineTest, ConcludedStateToTerminatedState) {

    game->SetState(new ConcludedState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::CONCLUDED);

    game->getCurrentState()->handleEndGame(game);

    StateID newStateID = game->getCurrentState()->getStateID();
    // Verify post-transition state
    EXPECT_EQ(newStateID, StateID::TERMINATED);
    auto* terminatedState = dynamic_cast<TerminatedState*>(game->getCurrentState());
    ASSERT_NE(nullptr, terminatedState);

}

TEST_F(GameStateMachineTest, InitializedStateToLoadingState) {

    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::INITIALIZED);

    game->getCurrentState()->handleLoadGame(game);

    StateID newStateID = game->getCurrentState()->getStateID();
    // Verify post-transition state
    EXPECT_EQ(newStateID, StateID::LOADING);
    auto* loadingState = dynamic_cast<LoadingState*>(game->getCurrentState());
    ASSERT_NE(nullptr, loadingState);

}

TEST_F(GameStateMachineTest, LoadingStateToPlayingState) {

    game->SetState(new LoadingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::LOADING);

    game->getCurrentState()->handleBoardReady(game);

    StateID newStateID = game->getCurrentState()->getStateID();
    // Verify post-transition state
    EXPECT_EQ(newStateID, StateID::PLAYING);
    auto* playingState = dynamic_cast<PlayingState*>(game->getCurrentState());
    ASSERT_NE(nullptr, playingState);
}

TEST_F(GameStateMachineTest, PlayingStateToSavingState) {

    game->SetState(new PlayingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::PLAYING);

    game->getCurrentState()->handleSaveGame(game);

    StateID newStateID = game->getCurrentState()->getStateID();
    // Verify post-transition state
    EXPECT_EQ(newStateID, StateID::SAVING);
    auto* savingState = dynamic_cast<SavingState*>(game->getCurrentState());
    ASSERT_NE(nullptr, savingState);

}

TEST_F(GameStateMachineTest, SavingStateToPlayingState) {
    game->SetState(new SavingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::SAVING);

    game->getCurrentState()->handleBoardReady(game);

    StateID newStateID = game->getCurrentState()->getStateID();
    // Verify post-transition state
    EXPECT_EQ(newStateID, StateID::PLAYING);
    auto* playingState = dynamic_cast<PlayingState*>(game->getCurrentState());
    ASSERT_NE(nullptr, playingState);

}
TEST_F(GameStateMachineTest, InvalidTransitionPlayingStateToNewGame) {

    game->SetState(new PlayingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::PLAYING);

    // Attempt invalid transition
    EXPECT_DEATH(game->getCurrentState()->handleNewGame(game), "Invalid state transition: PlayingState::handleNewGame");
}

TEST_F(GameStateMachineTest, InvalidTransitionPlayingStateToLoadGame) {
    game->SetState(new PlayingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::PLAYING);

    // Attempt invalid transition
    EXPECT_DEATH(game->getCurrentState()->handleLoadGame(game), "Invalid state transition: PlayingState::handleLoadGame");

}
 

TEST_F(GameStateMachineTest, InvalidTransitionPlayingStateToBoardReady) {
    game->SetState(new PlayingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::PLAYING);

    // Attempt invalid transition
    EXPECT_DEATH(game->getCurrentState()->handleBoardReady(game), "Invalid state transition: PlayingState::handleBoardReady");

}

TEST_F(GameStateMachineTest, InvalidTransitionAnalyzingStateToTurn) {
    game->SetState(new AnalyzingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::ANALYZING);

    // Attempt invalid transition
    EXPECT_DEATH(game->getCurrentState()->handleTurn(game), "Invalid state transition: AnalyzingState::handleTurn");

}

TEST_F(GameStateMachineTest, InvalidStateRentryInitializedStateToInitialzedState) {
    
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::INITIALIZED);

    // Attempt invalid transition
    EXPECT_DEATH(game->SetState(new InitializedState()), "Invalid state reentry");
}



TEST_F(GameStateMachineTest, InvalidStateRentryPlayingStateToPlayingState) {

    game->SetState(new PlayingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::PLAYING);

    // Attempt invalid transition
    EXPECT_DEATH(game->SetState(new PlayingState()), "Invalid state reentry");

}

TEST_F(GameStateMachineTest, InvalidStateRentryPauseStateToPauseState) {
    game->SetState(new PauseState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::PAUSED);

    // Attempt invalid transition
    EXPECT_DEATH(game->SetState(new PauseState()), "Invalid state reentry");

}

TEST_F(GameStateMachineTest, InvalidStateRentryLoadingStateToLoadingState) {

    game->SetState(new LoadingState());

    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::LOADING);

    // Attempt invalid transition
    EXPECT_DEATH(game->SetState(new LoadingState()), "Invalid state reentry");

}

TEST_F(GameStateMachineTest, InvalidStateRentrySavingStateToSavingState) {

    game->SetState(new SavingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::SAVING);

    // Attempt invalid transition
    EXPECT_DEATH(game->SetState(new SavingState()), "Invalid state reentry");
}

TEST_F(GameStateMachineTest, InvalidStateRentryConcludedStateToConcludedState) {
    game->SetState(new ConcludedState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::CONCLUDED);

    // Attempt invalid transition
    EXPECT_DEATH(game->SetState(new ConcludedState()), "Invalid state reentry");

}


TEST_F(GameStateMachineTest, InvalidStateRentryTerminatedStateToTerminatedState) {

    game->SetState(new TerminatedState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::TERMINATED);

    // Attempt invalid transition
    EXPECT_DEATH(game->SetState(new TerminatedState()), "Invalid state reentry");

}

TEST_F(GameStateMachineTest, PlayingStateToAnalyzingState) {

    game->SetState(new PlayingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::PLAYING);

    game->getCurrentState()->handleTurn(game);

    StateID newStateID = game->getCurrentState()->getStateID();
    // Verify post-transition state
    EXPECT_EQ(newStateID, StateID::ANALYZING);
    auto* analyzingState = dynamic_cast<AnalyzingState*>(game->getCurrentState());
    ASSERT_NE(nullptr, analyzingState);
}



TEST_F(GameStateMachineTest, AnalyzingStateToPlayingState) {

    game->SetState(new AnalyzingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::ANALYZING);

    game->getCurrentState()->handlePieceMoved(game);

    StateID newStateID = game->getCurrentState()->getStateID();
    // Verify post-transition state
    EXPECT_EQ(newStateID, StateID::PLAYING);
    auto* playingState = dynamic_cast<PlayingState*>(game->getCurrentState());
    ASSERT_NE(nullptr, playingState);
}

TEST_F(GameStateMachineTest, PlayingStateHandleTurn) {
    game->SetState(new PlayingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::PLAYING);

    game->getCurrentState()->handleTurn(game);

    StateID newStateID = game->getCurrentState()->getStateID();
    // Verify post-transition state
    EXPECT_EQ(newStateID, StateID::ANALYZING);
    auto* analyzingState = dynamic_cast<AnalyzingState*>(game->getCurrentState());
    ASSERT_NE(nullptr, analyzingState);

}

TEST_F(GameStateMachineTest, AnalyzingStateHandlePieceMoved) {
    game->SetState(new AnalyzingState());
    StateID currStateID = game->getCurrentState()->getStateID();

    // Verify pre-transition state
    EXPECT_EQ(currStateID, StateID::ANALYZING);

    game->getCurrentState()->handlePieceMoved(game);

    StateID newStateID = game->getCurrentState()->getStateID();
    // Verify post-transition state
    EXPECT_EQ(newStateID, StateID::PLAYING);
    auto* playingState = dynamic_cast<PlayingState*>(game->getCurrentState());
    ASSERT_NE(nullptr, playingState);

 }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}