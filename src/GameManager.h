#pragma once

enum class GameState { preGame, inGame, postGame };

class GameManager {
	GameState currentState{GameState::preGame};

   public:
	GameManager() = default;
	GameManager(GameState initialState);

	void start();
	void end();

	GameState getState();
};
