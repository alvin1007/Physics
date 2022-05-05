#include "main.h"
#include "System.h"

int main(int argc, char* argv[]) {
	System* MainSystem = new System;

	if (!MainSystem->Init())
		return -1;

	if (!MainSystem->Render())
		return -1;

	if (!MainSystem->Clear())
		return -1;

	return 0;
}