#include "MagnifyWidget.h"
#include <QtWidgets>
#include <QtDebug>
#include <QVBoxLayout>
#include "PointerWidget.h"

FMagnifyGlass* FMagnifyGlass::instance = nullptr;

float FMagnifyGlass::MgfSize = 400;

FMagnifyWidget::FMagnifyWidget(QWidget *parent /*= 0*/)
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	//setParent(0); // Create TopLevel-Widget
	//setAttribute(Qt::WA_NoSystemBackground, true);
	setAttribute(Qt::WA_TranslucentBackground, true);
	//setAttribute(Qt::WA_InputMethodTransparent, true);

	screenshotLabel = new QLabel(this);

	screenshotLabel->setScaledContents(true);

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(screenshotLabel);

	resize(FMagnifyGlass::MgfSize, FMagnifyGlass::MgfSize);
}

void FMagnifyWidget::moveEvent(QMoveEvent* me)
{
	QWidget::moveEvent(me);


	if (!isVisible())
	{
		QScreen* screen = QGuiApplication::primaryScreen();

		QPixmap pixmap = screen->grabWindow(0, FPointer::Get()->GetWidget()->x(), FPointer::Get()->GetWidget()->y(), FPointer::PointerSize, FPointer::PointerSize);

		screenshotLabel->setPixmap(pixmap);
	}

}

void FMagnifyWidget::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);

	qInfo() << "\nMousePRessed\n" << event->x() << event->y();
}

void FMagnifyGlass::ShowAt(QPoint point)
{
	if (!Widget)
	{
		Widget = new FMagnifyWidget;
	}
	Hide();
	OriginPoint = point;

	const float HalfMgfSize = MgfSize * 0.5f;

	point -= QPoint(HalfMgfSize, HalfMgfSize);
	ClampToScreen(point, MgfSize);
	Widget->move(point);
	Widget->show();

}

void FMagnifyGlass::ClampToScreen(QPoint& point, int WidgetSize)
{
	QRect rec = QApplication::desktop()->screenGeometry();
	const int screenWidth = rec.width();
	const int screenHeight = rec.height();

	if (point.x() < 0)
	{
		point.setX(0);
	}

	if (point.x() + WidgetSize > screenWidth)
	{
		point.setX(screenWidth - WidgetSize);
	}

	if (point.y() < 0)
	{
		point.setY(0);
	}

	if (point.y() + WidgetSize > screenHeight)
	{
		point.setY(screenHeight - WidgetSize);
	}
}

void FMagnifyGlass::Hide()
{
	if (Widget)
	{
		Widget->hide();
	}
}

bool FMagnifyGlass::IsVisible() const
{
	return Widget && Widget->isVisible();

}

void FMagnifyGlass::MapGlobalPoint(QPoint& OutPoint)
{
	OutPoint = Widget->mapFromGlobal(OutPoint);

	int localX = OutPoint.x();
	int localY = OutPoint.y();

	float XRatio = localX / (float)Widget->width();
	float YRatio = localY / (float)Widget->height();

	int newLocalX = (int)(XRatio * FPointer::PointerSize);
	int newLocalY = (int)(YRatio * FPointer::PointerSize);


	OutPoint.setX(newLocalX);
	OutPoint.setY(newLocalY);

	OutPoint += GetOriginTopLeft();
}

QPoint FMagnifyGlass::GetOriginTopLeft()
{
	const float HalfPointerSize = FPointer::PointerSize * 0.5f;
	return OriginPoint - QPoint(HalfPointerSize, HalfPointerSize);
}




