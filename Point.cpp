#include "stdafx.h"
#include "Point.h"

Point Point::Add(Point point)
{
	Point a;
	a.x = this->x + point.x;
	a.y = this->y + point.y;
	return a;
}

Point Point::Del(Point point)
{
	Point a;
	a.x = this->x - point.x;
	a.y = this->x - point.y;
	return a;
}