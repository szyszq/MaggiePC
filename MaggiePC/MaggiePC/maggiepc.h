#ifndef MAGGIEPC_H
#define MAGGIEPC_H

#include <QtWidgets/QMainWindow>
#include "ui_maggiepc.h"

class MaggiePC : public QMainWindow
{
	Q_OBJECT

public:
	MaggiePC(QWidget *parent = 0);
	~MaggiePC();

private:
	Ui::MaggiePCClass ui;
};

#endif // MAGGIEPC_H
