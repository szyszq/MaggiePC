#pragma once
#include <QtWidgets/QWidget>

class FMagnifyWidget : public QWidget
{
	Q_OBJECT

public:
	FMagnifyWidget(QWidget *parent = 0);

	class QLabel* screenshotLabel;

	public slots:
	void moveEvent(QMoveEvent* me);

	virtual void mousePressEvent(QMouseEvent *event) override;
};

class FMagnifyGlass
{
public:
	~FMagnifyGlass() { instance = nullptr; }

	static FMagnifyGlass* Get()
	{
		if (instance == nullptr)
			instance = new FMagnifyGlass;
		return instance;
	}

	static float MgfSize;

	void ShowAt(QPoint point);
	void Hide();
	void ClampToScreen(QPoint& point, int WidgetSize);

	bool IsVisible() const;

	void MapGlobalPoint(QPoint& OutPoint);
	QPoint GetOriginTopLeft();
	QPoint OriginPoint;

	QWidget* Widget;
private:
	FMagnifyGlass()
		: Widget(nullptr)
	{}
	static FMagnifyGlass* instance;
};

