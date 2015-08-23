#include "sworld.h"
#include <iostream>
#include "global.h"

int main( int argc, char *argv[] )
{
	CSWorld *newWorld = new CSWorld();
	currentWorld = newWorld;
	newWorld->Simulate();
	return 0;
}
