#pragma once

class IGazeWidget
{
public:

	virtual bool IsGazeWidgetVisible() const = 0;
	virtual QRect GetRect() const = 0;
	virtual void OnGazePointEnter() = 0;
	virtual void OnGazePointLeave() = 0;
	virtual bool IsGazeUpon() const = 0;
};


