#include "GameManager.h"

GameManager::GameManager(GameState initialState)
	: currentState{initialState} {};

void GameManager::start() { currentState = GameState::inGame; }
void GameManager::end() { currentState = GameState::postGame; }

GameState GameManager::getState() const { return currentState; }