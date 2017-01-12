#pragma once
#include <QtWidgets/QWidget>
#include "MaggieTypes.h"


class FPointerWidget : public QWidget
{
	Q_OBJECT

public:
	FPointerWidget(QWidget *parent = 0);
	~FPointerWidget();

	void BeginFixationTimer();

	public slots:
	void UpdatePosition();

	void OnFixation();

	void paintEvent(QPaintEvent *pe);

public:
	FMouseActionDelegate ActionDelegate;
	bool bShowMagnifierNextAction;

private:
	bool bExectingAction;
	QTimer* FixationTimer;
	QPoint LastPosition;
};

//////////////////////////////////////////////////////////////////////////
// POINTER
//////////////////////////////////////////////////////////////////////////
class FPointer
{
public:
	~FPointer() { instance = nullptr; }

	static void Init(QWidget* parent)
	{
		if (instance == nullptr)
			instance = new FPointer(parent);
	}

	static FPointer* Get()
	{
		if (instance == nullptr)
			instance = new FPointer;
		return instance;
	}

	static float PointerSize;

	bool Intersects(QWidget* otherWidget) const;
	QPoint GetCenter() const;

	bool GetSimulateMovement() const { return bSimulateMovement; }
	void SetSimulateMovement(bool val) { bSimulateMovement = val; }

	static void Test();

	FPointerWidget* GetWidget() const { return PointerWidget; }

private:
	bool bSimulateMovement;
	FPointer();
	FPointer(QWidget* parent);
	static FPointer* instance;

	FPointerWidget* PointerWidget;
	
};


