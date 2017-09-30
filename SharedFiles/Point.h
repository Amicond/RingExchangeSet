#ifndef POINT_H
#define POINT_H

class Point
{
	int x, y;
public:
	Point();
	Point(int x, int y);
	void set(int x, int y);

	int getX() const;
	int getY() const;
	
	void transformRotate();
	void transformMirrorX();
	void transformMirrorY();

	void print(std::ostream &out);

	bool operator==(const Point &p2)const;
	bool operator <(const Point &p2)const;
	Point operator-();
	friend const Point operator+(const Point &a, const Point &b);
	friend const Point operator-(const Point &a, const Point  &b);
};

#endif // !POINT_H