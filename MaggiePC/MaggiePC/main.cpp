#include "maggiepc.h"
#include <QtWidgets/QApplication>
#include "EyeXModule.h"
#include "PointerWidget.h"

#pragma comment (lib, "Tobii.EyeX.Client.lib")

int main(int argc, char *argv[])
{
	FExeXModule::Get()->Init();

	QApplication a(argc, argv);
	MaggiePC w;
	
	w.show();
	
	return a.exec();
}
