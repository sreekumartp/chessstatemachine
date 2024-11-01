#include <gtest/gtest.h>
#include <statemachine.hpp>

TEST(GameStateMachineTest, InitializedStateToPlayingState) {
    GameSM game;
    game.SetState(new InitializedState());
    game.getCurrentState()->handleNewGame(&game);
    EXPECT_TRUE(dynamic_cast<PlayingState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, PlayingStateToPauseState) {
    GameSM game;
    game.SetState(new PlayingState());
    game.getCurrentState()->handlePause(&game);
    EXPECT_TRUE(dynamic_cast<PauseState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, PauseStateToPlayingState) {
    GameSM game;
    game.SetState(new PauseState());
    game.getCurrentState()->handleResume(&game);
    EXPECT_TRUE(dynamic_cast<PlayingState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, PlayingStateToConcludedState) {
    GameSM game;
    game.SetState(new PlayingState());
    game.getCurrentState()->handleGameOver(&game);
    EXPECT_TRUE(dynamic_cast<ConcludedState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, ConcludedStateToTerminatedState) {
    GameSM game;
    game.SetState(new ConcludedState());
    game.getCurrentState()->handleEndGame(&game);
    EXPECT_TRUE(dynamic_cast<TerminatedState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, InitializedStateToLoadingState) {
    GameSM game;
    game.SetState(new InitializedState());
    game.getCurrentState()->handleLoadGame(&game);
    EXPECT_TRUE(dynamic_cast<LoadingState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, LoadingStateToPlayingState) {
    GameSM game;
    game.SetState(new LoadingState());
    game.getCurrentState()->handleBoardReady(&game);
    EXPECT_TRUE(dynamic_cast<PlayingState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, PlayingStateToSavingState) {
    GameSM game;
    game.SetState(new PlayingState());
    game.getCurrentState()->handleSaveGame(&game);
    EXPECT_TRUE(dynamic_cast<SavingState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, SavingStateToPlayingState) {
    GameSM game;
    game.SetState(new SavingState());
    game.getCurrentState()->handleBoardReady(&game);
    EXPECT_TRUE(dynamic_cast<PlayingState*>(game.getCurrentState()) != nullptr);
}
TEST(GameStateMachineTest, InvalidTransitionPlayingStateToNewGame) {
    GameSM game(new InitializedState());
    game.printCurrentState();
    game.getCurrentState()->handleNewGame(&game);
    game.printCurrentState();
   // EXPECT_DEATH(game.getCurrentState()->handleNewGame(&game), "Invalid state transition: PlayingState::handleNewGame");
   //EXPECT_DEATH(game.getCurrentState()->handleNewGame(&game), "Invalid state transition: PlayingState::handleNewGame");
   EXPECT_DEATH(game.getCurrentState()->handleNewGame(&game), "Invalid");
}

TEST(GameStateMachineTest, InvalidTransitionPlayingStateToLoadGame) {
    GameSM game;
    game.SetState(new PlayingState());
    EXPECT_DEATH(game.getCurrentState()->handleLoadGame(&game), "Invalid state transition: PlayingState::handleLoadGame");
}

TEST(GameStateMachineTest, InvalidTransitionPlayingStateToBoardReady) {
    GameSM game;
    game.SetState(new PlayingState());
    EXPECT_DEATH(game.getCurrentState()->handleBoardReady(&game), "Invalid state transition: PlayingState::handleBoardReady");
}

TEST(GameStateMachineTest, InvalidTransitionAnalyzingStateToTurn) {
    GameSM game;
    game.SetState(new AnalyzingState());
    EXPECT_DEATH(game.getCurrentState()->handleTurn(&game), "Invalid state transition: AnalyzingState::handleTurn");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

