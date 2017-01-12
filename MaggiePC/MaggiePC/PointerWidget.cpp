#include "PointerWidget.h"
#include <QVBoxLayout>
#include <QtWidgets>
#include <QtDebug>
#include "EyeXModule.h"
#include <MagnifyWidget.h>

FPointer* FPointer::instance = nullptr;
float FPointer::PointerSize = 92;

FPointerWidget::FPointerWidget(QWidget *parent)
	:QWidget(parent)
{
	bExectingAction = false;
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowTransparentForInput);
	//setParent(0); // Create TopLevel-Widget
	setAttribute(Qt::WA_NoSystemBackground, true);
	setAttribute(Qt::WA_TranslucentBackground, true);
	setAttribute(Qt::WA_InputMethodTransparent, true);

	QTimer *timer = new QTimer(this);

	FixationTimer = new QTimer(this);
	FixationTimer->setSingleShot(true);
	connect(timer, SIGNAL(timeout()), this, SLOT(UpdatePosition()));
	connect(FixationTimer, SIGNAL(timeout()), this, SLOT(OnFixation()));

	timer->start(10);
	resize(FPointer::PointerSize, FPointer::PointerSize);

	LastPosition = QPoint(0, 0);

	ActionDelegate = nullptr;
}

FPointerWidget::~FPointerWidget()
{

}

void FPointerWidget::UpdatePosition()
{
	int x, y;

	if (FPointer::Get()->GetSimulateMovement())
	{
		x = QCursor::pos().x();
		y = QCursor::pos().y();
	}
	else
	{
		FExeXModule::Get()->GetEyeCoords(x, y);
	}

	QPoint CurrentPos = QPoint(x, y) - QPoint(size().width() * 0.5f, size().height() * 0.5f);
	if ((CurrentPos - LastPosition).manhattanLength() < 15)
	{
		CurrentPos = LastPosition;
	}

	//FMagnifyGlass::Get()->ClampToScreen(CurrentPos, POINTER_SIZE);
	move(CurrentPos);

	QLineF line(LastPosition, CurrentPos);

	if (ActionDelegate)
	{
		if ((CurrentPos - LastPosition).manhattanLength() < 15)
		{
			if (FixationTimer && !FixationTimer->isActive() && !bExectingAction)
			{
				bExectingAction = true;
				FixationTimer->start(500);
			}
		}
		else
		{
			if (FixationTimer)
			{
				FixationTimer->stop();
				bExectingAction = false;
			}
		}
	}

	raise();

	LastPosition = CurrentPos;
}

void FPointerWidget::OnFixation()
{
	qDebug() << "Fixated " << LastPosition.x() << " " << LastPosition.y();
	if (ActionDelegate)
	{
		QPoint mappedActionPoint = mapToGlobal(rect().center());

		if (bShowMagnifierNextAction)
		{
			hide();
			FMagnifyGlass::Get()->ShowAt(mappedActionPoint);
			show();
			bShowMagnifierNextAction = false;
			return;
		}

		if (FMagnifyGlass::Get()->IsVisible())
		{
			QRect r = FMagnifyGlass::Get()->Widget->geometry();
			if (r.contains(mappedActionPoint))
			{
				FMagnifyGlass::Get()->MapGlobalPoint(mappedActionPoint);
				FMagnifyGlass::Get()->Hide();
				ActionDelegate(mappedActionPoint);
				ActionDelegate = nullptr;
				repaint();
			}
			else
			{
				FMagnifyGlass::Get()->Hide();
				ActionDelegate = nullptr;
				repaint();
				return;
			}
		}


	}
}

void FPointerWidget::paintEvent(QPaintEvent *pe)
{
	QPainter p(this);
	p.setBrush(Qt::transparent);
	p.setRenderHint(QPainter::Antialiasing);

	p.drawEllipse(rect());
	p.setBrush(ActionDelegate ? Qt::green : Qt::red);
	p.drawEllipse(0, 0, 10, 10);
	p.drawLine(-100, -100, 100, 100);
}

//////////////////////////////////////////////////////////////////////////
// POINTER
//////////////////////////////////////////////////////////////////////////
bool FPointer::Intersects(QWidget* otherWidget) const
{
	if (otherWidget && PointerWidget)
	{
		QPoint centerPoint = PointerWidget->mapToGlobal(PointerWidget->rect().center());
		centerPoint = otherWidget->mapFromGlobal(centerPoint);
		return otherWidget->rect().contains(centerPoint);
	}

	return false;
}

QPoint FPointer::GetCenter() const
{
	return PointerWidget->mapToGlobal(PointerWidget->rect().center());
}

void FPointer::Test()
{
	qDebug() << "Debug function called!";
}

FPointer::FPointer()
{
	bSimulateMovement = false;
	PointerWidget = new FPointerWidget();
	PointerWidget->show();
}


FPointer::FPointer(QWidget* parent /*= 0*/)
{
	bSimulateMovement = false;
	PointerWidget = new FPointerWidget(parent);
	PointerWidget->show();
}