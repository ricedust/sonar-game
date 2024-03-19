#pragma once

extern int componentCounter;

template <typename T>
int getID() {
	static int componentID = componentCounter++;
	return componentID;
}