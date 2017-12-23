#pragma once
class Point
{
public:
	int x;
	int y;
	int side;//1ºÚ   0°× -1¿Õ
	Point(){}
	Point(int xx,int yy,int ss){x = xx;y = yy;side = ss;}
	~Point(){}
	Point Add(Point point);
	Point Del(Point point);
};

