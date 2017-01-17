#include "GazeButton.h"
#include <QtWidgets>
#include "PointerWidget.h"

FGazeButton::FGazeButton(const QString &text, FActionDelegate InActionDelegate, FMouseActionDelegate InMouseActionDelegate, bool InbShowMagnifier)
	: QPushButton(text)
	, bIsHovered(false)
	, ActionDelegate(InActionDelegate)
	, MouseActionDelegate(InMouseActionDelegate)
	, bShowMagnifier(InbShowMagnifier)
{
	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(CheckForPointerIntersection()));
	ProgressBar = new QProgressBar(this);
	ProgressBar->setMaximum(100);
	ProgressBar->setMinimum(0);
	ProgressBar->setValue(0);
	ProgressBar->setTextVisible(false);
	ProgressBar->setMaximumHeight(10);
	//ProgressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QVBoxLayout* vlay = new QVBoxLayout(this);
	vlay->setSpacing(0);
	vlay->setMargin(0);

	vlay->addWidget(ProgressBar, 1, Qt::AlignBottom);

	setLayout(vlay);
	timer->start(10);
}

FGazeButton::~FGazeButton()
{

}

void FGazeButton::CheckForPointerIntersection()
{
	if (FPointer::Get()->Intersects(this))
	{
		if (!bIsHovered)
		{
			bIsHovered = true;
			ActiveTimerID = startTimer(10);
			//ProgressBar->setValue(50);
		}
	}
	else
	{
		if (bIsHovered)
		{
			bIsHovered = false;

			if (ActiveTimerID != 0)
			{
				killTimer(ActiveTimerID);
			}
			ProgressBar->setValue(0);
		}
	}

}

void FGazeButton::UpdateProgressBar()
{

}

void FGazeButton::timerEvent(QTimerEvent* event)
{
	if (ProgressBar)
	{
		ProgressBar->setValue(ProgressBar->value() + 2);
		int currentValue = ProgressBar->value();
		int maxValue = ProgressBar->maximum();
		if (currentValue >= maxValue)
		{
			if (ActionDelegate)
			{
				(*ActionDelegate)();
				//ProgressBar->setValue(0);
			}

			if (MouseActionDelegate)
			{
				FPointer::Get()->GetWidget()->bShowMagnifierNextAction = bShowMagnifier;
				FPointer::Get()->GetWidget()->ActionDelegate = MouseActionDelegate;
				FPointer::Get()->GetWidget()->repaint();
			}

			killTimer(event->timerId());
			ActiveTimerID = 0;
		}
	}
}

bool FGazeButton::IsGazeWidgetVisible() const
{
	return true;
}

QRect FGazeButton::GetRect() const
{
	return rect();
}

void FGazeButton::OnGazePointEnter()
{

}

void FGazeButton::OnGazePointLeave()
{

}

bool FGazeButton::IsGazeUpon() const
{
	return bIsHovered;
}

void FGazeButton::paintEvent(QPaintEvent *pe)
{
	QPushButton::paintEvent(pe);
}