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
        delete game;
    }
};

TEST(GameStateMachineTest, InitializedStateToPlayingState) {
    GameSM game(new InitializedState());
    game.getCurrentState()->handleNewGame(&game);
    EXPECT_TRUE(dynamic_cast<PlayingState*>(game.getCurrentState()) != nullptr);
}


TEST(GameStateMachineTest, PlayingStateToPauseState) {
    GameSM game(new PauseState);
    game.getCurrentState()->handlePause(&game);
    EXPECT_TRUE(dynamic_cast<PauseState*>(game.getCurrentState()) != nullptr);
}


TEST(GameStateMachineTest, PauseStateToPlayingState) {
    GameSM game(new PauseState);
    game.getCurrentState()->handleResume(&game);
    EXPECT_TRUE(dynamic_cast<PlayingState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, PlayingStateToConcludedState) {
    GameSM game(new PlayingState);
    game.getCurrentState()->handleGameOver(&game);
    EXPECT_TRUE(dynamic_cast<ConcludedState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, ConcludedStateToTerminatedState) {
    GameSM game(new ConcludedState());
    game.getCurrentState()->handleEndGame(&game);
    EXPECT_TRUE(dynamic_cast<TerminatedState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, InitializedStateToLoadingState) {
    GameSM game(new InitializedState());
    game.getCurrentState()->handleLoadGame(&game);
    EXPECT_TRUE(dynamic_cast<LoadingState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, LoadingStateToPlayingState) {
    GameSM game(new LoadingState());
    game.getCurrentState()->handleBoardReady(&game);
    EXPECT_TRUE(dynamic_cast<PlayingState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, PlayingStateToSavingState) {
    GameSM game(new PlayingState);
    game.getCurrentState()->handleSaveGame(&game);
    EXPECT_TRUE(dynamic_cast<SavingState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, SavingStateToPlayingState) {
    GameSM game(new SavingState());
    game.getCurrentState()->handleBoardReady(&game);
    EXPECT_TRUE(dynamic_cast<PlayingState*>(game.getCurrentState()) != nullptr);
}
TEST(GameStateMachineTest, InvalidTransitionPlayingStateToNewGame) {
    GameSM game(new InitializedState());
    game.printCurrentState();
    game.getCurrentState()->handleNewGame(&game);
    game.printCurrentState();
   EXPECT_DEATH(game.getCurrentState()->handleNewGame(&game), "Invalid");
}

TEST(GameStateMachineTest, InvalidTransitionPlayingStateToLoadGame) {
    GameSM game(new PlayingState());
    EXPECT_DEATH(game.getCurrentState()->handleLoadGame(&game), "Invalid state transition: PlayingState::handleLoadGame");
}

TEST(GameStateMachineTest, InvalidTransitionPlayingStateToBoardReady) {
    GameSM game(new PlayingState());
    EXPECT_DEATH(game.getCurrentState()->handleBoardReady(&game), "Invalid state transition: PlayingState::handleBoardReady");
}

TEST(GameStateMachineTest, InvalidTransitionAnalyzingStateToTurn) {
    GameSM game(new AnalyzingState());
    EXPECT_DEATH(game.getCurrentState()->handleTurn(&game), "Invalid state transition: AnalyzingState::handleTurn");
}

TEST(GameStateMachineTest, InvalidStateRentryInitializedStateToInitialzedState) {
    GameSM game(new InitializedState());
    EXPECT_DEATH(game.SetState(new InitializedState()), "Invalid state reentry");
}
TEST(GameStateMachineTest, InvalidStateRentryPlayingStateToPlayingState) {
    GameSM game(new PlayingState());
    EXPECT_DEATH(game.SetState(new PlayingState()), "Invalid state reentry");
}

TEST(GameStateMachineTest, InvalidStateRentryPauseStateToPauseState) {
    GameSM game(new PauseState());
    EXPECT_DEATH(game.SetState(new PauseState()), "Invalid state reentry");
}

TEST(GameStateMachineTest, InvalidStateRentryLoadingStateToLoadingState) {
    GameSM game(new LoadingState());
    EXPECT_DEATH(game.SetState(new LoadingState()), "Invalid state reentry");
}

TEST(GameStateMachineTest, InvalidStateRentrySavingStateToSavingState) {
    GameSM game(new SavingState());
    EXPECT_DEATH(game.SetState(new SavingState()), "Invalid state reentry");
}

TEST(GameStateMachineTest, InvalidStateRentryConcludedStateToConcludedState) {
    GameSM game(new ConcludedState());
    EXPECT_DEATH(game.SetState(new ConcludedState()), "Invalid state reentry");
}


TEST(GameStateMachineTest, InvalidStateRentryTerminatedStateToTerminatedState) {
    GameSM game(new TerminatedState());
    EXPECT_DEATH(game.SetState(new TerminatedState()), "Invalid state reentry");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

