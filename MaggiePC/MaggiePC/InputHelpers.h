#pragma once
#include <Windows.h>

// Define some input codes so other files can use platform types in non-direct way
#define INPUT_LMB MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP
#define INPUT_LMB_DOWN MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN
#define INPUT_LMB_UP MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP
#define INPUT_RMB MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP
#define INPUT_MOUSE3 MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_MIDDLEUP

class FInputHelpers
{
public:

	static void MakeMouseInputFromCursorPosition(int InX, int InY, INPUT& Outinput)
	{
		const double XSCALEFACTOR = 65535.0f / (GetSystemMetrics(SM_CXSCREEN) - 1);
		const double YSCALEFACTOR = 65535.0f / (GetSystemMetrics(SM_CYSCREEN) - 1);

		Outinput.type = INPUT_MOUSE;

		double px = InX *XSCALEFACTOR;
		double py = InY *YSCALEFACTOR;
		Outinput.mi.dx = (LONG)px;
		Outinput.mi.dy = (LONG)py;
		Outinput.mi.time = 0;
	}

	static void SendKeyInput(WORD vkey)
	{
		INPUT input;
		input.type = INPUT_KEYBOARD;
		input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC); // hardware scan code for key
		input.ki.time = 0;
		input.ki.dwExtraInfo = 0;

		input.ki.wVk = vkey;
		input.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &input, sizeof(INPUT));
	}

	static void SendKeyInputFromChar(char inChar)
	{
		INPUT i;
		i.type = INPUT_KEYBOARD;

		i.ki.wScan = inChar;
		i.ki.time = 0;
		i.ki.dwExtraInfo = 0;

		i.ki.wVk = 0;
		i.ki.dwFlags = KEYEVENTF_UNICODE;
		SendInput(1, &i, sizeof(INPUT));
	}
};

