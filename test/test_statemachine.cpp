#include <gtest/gtest.h>
#include <statemachine.hpp>

TEST(GameStateMachineTest, InitialState) {
    GameSM game;
    EXPECT_TRUE(dynamic_cast<ClosedState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, TransitionFromClosedToOpen) {
    GameSM game;
    game.pushButton();
    EXPECT_TRUE(dynamic_cast<OpenState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, TransitionFromOpenToClosed) {
    GameSM game;
    game.pushButton(); // Open the door
    game.pushButton(); // Close the door
    EXPECT_TRUE(dynamic_cast<ClosedState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, TransitionFromClosedToLocked) {
    GameSM game;
    game.TurnKey();
    EXPECT_TRUE(dynamic_cast<LockedState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, TransitionFromLockedToClosed) {
    GameSM game;
    game.TurnKey(); // Lock the door
    game.TurnKey(); // Unlock the door
    EXPECT_TRUE(dynamic_cast<ClosedState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, TransitionFromOpenToLocked) {
    GameSM game;
    game.pushButton(); // Open the door
    game.TurnKey(); // Try to lock the door
    EXPECT_TRUE(dynamic_cast<OpenState*>(game.getCurrentState()) != nullptr);
}

TEST(GameStateMachineTest, LockedStatePushButton) {
    GameSM game;
    game.TurnKey(); // Lock the door
    game.pushButton(); // Try to open the door
    EXPECT_TRUE(dynamic_cast<LockedState*>(game.getCurrentState()) != nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}