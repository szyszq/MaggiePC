#pragma once

#include "MaggieTypes.h"
#include <QtWidgets/qpushbutton.h>
#include "IGazeWidget.h"

class FGazeButton : public QPushButton, public IGazeWidget
{

public:


	FGazeButton(const QString &text, FActionDelegate InActionDelegate = nullptr, FMouseActionDelegate InMouseActionDelegate = nullptr, bool InbShowMagnifier = false);

	virtual ~FGazeButton();

	// IGazeWidget interface
	virtual bool IsGazeWidgetVisible() const override;
	virtual QRect GetRect() const override;
	virtual void OnGazePointEnter() override;
	virtual void OnGazePointLeave() override;
	virtual bool IsGazeUpon() const override;

	FActionDelegate ActionDelegate;
	FMouseActionDelegate MouseActionDelegate;

	public slots:
	void paintEvent(QPaintEvent *pe);
	void CheckForPointerIntersection();
	void UpdateProgressBar();
	void timerEvent(QTimerEvent *event);

private:
	bool bIsHovered;

	class QProgressBar* ProgressBar;
	class QTimer* ActiveTimer;
	int ActiveTimerID;

	bool bShowMagnifier = false;
};
