#include "Component.h"

int getID() {
	static int componentID = componentCounter++;
	return componentID;
}