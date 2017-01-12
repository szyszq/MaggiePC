#pragma once
#include <eyex\EyeX.h>


class FExeXModule
{
public:
	~FExeXModule() { instance = nullptr; }

	void Init();
	void Shutdown();

	static FExeXModule* Get()
	{
		if (instance == nullptr)
			instance = new FExeXModule;
		return instance;
	}

	void GetEyeCoords(int& OutX, int& OutY);
	void SetEyeCoords(int InX, int InY);

private:
	static FExeXModule* instance;

	static TX_CONTEXTHANDLE hContext;
	static TX_TICKET hConnectionStateChangedTicket;
	static TX_TICKET hEventHandlerTicket;

	int EyeX;
	int EyeY;
};
