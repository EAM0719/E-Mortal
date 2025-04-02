#include <iostream>
#include <windows.h>
#include <csignal>
#include "exanima_values.hpp"

// Added this so I didn't have to manually include the user32 library everytime I compile
#pragma comment (lib, "user32.lib")

// My precious prototypes...:
void sh_exit(int n);
void pwc(char *str, int color, HANDLE conhan);
void rainbow(char *str, HANDLE conhan);

int main(void) {
	SetConsoleTitleW(L"E-Mortal");

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	// Displaying version information
	pwc("Compatible with Exanima Version: ", 14, console);
	pwc(version, 10, console);
	std::cout << std::endl;

	HWND exanima_window = FindWindowW(NULL, L"Exanima");

	// If an application named `Exanima` is not found, it will exit.
	if (exanima_window == NULL) {
		pwc("ERROR: ", 12, console);
		pwc("Couldn't find Exanima...\n", 14, console);
		std::cout << "Exiting..." << std::endl;
		
		Sleep(3000); // Giving the user some time to read the message before the application exits.
		return -1;
	}

	DWORD processID = 0;
	GetWindowThreadProcessId(exanima_window, &processID);

	HANDLE exanima_process 		= OpenProcess(PROCESS_ALL_ACCESS, true, processID);
	DWORD player_address		= 0;
	uint64_t max_health_value	= maxhealth;

	signal(SIGINT, sh_exit);
	
	rainbow("Death is for mortals...\n", console);
	
	// This is where the Next Step In The Operation happens *locked in alien music*:
	ReadProcessMemory(exanima_process, (void*)player_entity, &player_address, 4, NULL);
	while(true) {
		WriteProcessMemory(exanima_process, (void*)(player_address + health_offset), &max_health_value, 8, NULL);
	}

	return 0;
}

// Signal handler to handle all the signals...:
void sh_exit(int n) {
	std::cout << "Exiting..." << std::endl;
	Sleep(500);
	exit(n);
}

// Print With Color:
void pwc(char *str, int color, HANDLE conhan) {
	SetConsoleTextAttribute(conhan, color);
	std::cout << str;
	SetConsoleTextAttribute(conhan, 15);
}

// Make Text Rainbow!!!:
void rainbow(char *str, HANDLE conhan) {
	for(int i = 0; i < strlen(str); i++) {
		SetConsoleTextAttribute(conhan, (i % 7) + 9);
		std::cout << str[i];
	}
	SetConsoleTextAttribute(conhan, 15);
}
