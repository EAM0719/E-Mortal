#include <iostream>
#include <windows.h>
#include <csignal>
#include "exanima_values.h"

#pragma comment (lib, "user32.lib")

void sh_exit(int n);
void pwc(char *str, int color, HANDLE conhan);
void rainbow(char *str, HANDLE conhan);

int main(void)
{
	SetConsoleTitleW(L"E-Mortal");

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	pwc("Compatible with Exanima Version: ", 14, console);
	pwc(version, 10, console);
	std::cout << std::endl;

	HWND exanima_window = FindWindowW(NULL, L"Exanima");
	
	if (exanima_window == NULL) {
		pwc("ERROR: ", 12, console);
		pwc("Couldn't find Exanima...\n", 14, console);
		std::cout << "Exiting..." << std::endl;
		Sleep(3000);
		return -1;
	}

	DWORD processID = 0;
	GetWindowThreadProcessId(exanima_window, &processID);

	HANDLE exanima_process = OpenProcess(PROCESS_ALL_ACCESS, true, processID);

	DWORD player_address	= 0;
	DWORD max_health_value	= maxhealth;

	signal(SIGINT, sh_exit);
	
	rainbow("Death is for mortals...\n", console);
	while (true) {
		ReadProcessMemory(exanima_process, (void*)player_entity, &player_address, 4, NULL);
		WriteProcessMemory(exanima_process, (void*)(player_address + health_offset), &max_health_value, 4, NULL);
		WriteProcessMemory(exanima_process, (void*)(player_address + max_health_offset), &max_health_value, 4, NULL);
	}

	return 0;
}

void sh_exit(int n) 
{
	std::cout << "Exiting..." << std::endl;
	Sleep(500);
	exit(n);
}

//Print With Color:
void pwc(char *str, int color, HANDLE conhan)
{
	SetConsoleTextAttribute(conhan, color);
	std::cout << str;
	SetConsoleTextAttribute(conhan, 15);
}

//Make Text Rainbow!!!
void rainbow(char *str, HANDLE conhan)
{
	for(int i = 0; i < strlen(str); i++){
    	SetConsoleTextAttribute(conhan, (i%7)+9);
        std::cout << str[i];
    }
    SetConsoleTextAttribute(conhan, 15);
}