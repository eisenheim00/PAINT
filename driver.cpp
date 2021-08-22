
/*
 * CSE/ENGR 142 GP142_Demo
 *
 * 1/25/95x
 * Author(s):         Larry Ruzzo
 * Email Address(s):  ruzzo@cs.washington.edu
 *
 * This program is a demo of some of the features of
 * GP142 --- the CSE/ENGR 142 Graphics Package.
 * It includes simple drawing commands, keyboard and mouse
 * interaction, and a simple animation.
 *
 * Revision history:
 * 11/18/97 Dan Boren  - Removed calls to obsolete function GP142_undo()
 *
 */

#include "GP142.h"
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <windows.h>

using namespace std;
#define PI 3.1415926535
#define ANIMATE_MSG "Select \"Animate\"\nOn the \"Run\" Menu"
#define TEXT_SIZE 20

//#include <vector> 

struct Point {
	double x, y;
};
Point topleft, topright, bottomleft, bottomright;
int col = WHITE;
int old_col;
int fill = WHITE;
int findDis(Point p, Point p1)
{
	int num = (p.x - p1.x);
	int num1 = (p.y - p1.y);
	
	num = pow(num, 2);
	num1 = pow(num1, 2);
	int num2 = num + num1;
	//return pow(num2, (1 / 2));
	return sqrt(num2);
}

Point * GetPoints(Point temp1, Point temp2) {
	Point* arr = new Point[9];

	//Mid-Point

	arr[4].x = temp1.x + temp2.x; arr[4].x /= 2;
	arr[4].y = temp1.y + temp2.y; arr[4].y /= 2;

	//First Half

	arr[2].x = temp1.x + arr[4].x; arr[2].x /= 2;
	arr[2].y = temp1.y + arr[4].y; arr[2].y /= 2;

	arr[3].x = arr[2].x + arr[4].x; arr[3].x /= 2;
	arr[3].y = arr[2].y + arr[4].y; arr[3].y /= 2;

	arr[1].x = temp1.x + arr[2].x; arr[1].x /= 2;
	arr[1].y = temp1.y + arr[2].y; arr[1].y /= 2;

	arr[0].x = temp1.x;
	arr[0].y = temp1.y;

	//Second Half

	arr[6].x = temp2.x + arr[4].x; arr[6].x /= 2;
	arr[6].y = temp2.y + arr[4].y; arr[6].y /= 2;

	arr[5].x = arr[6].x + arr[4].x; arr[5].x /= 2;
	arr[5].y = arr[6].y + arr[4].y; arr[5].y /= 2;

	arr[7].x = temp2.x + arr[6].x; arr[7].x /= 2;
	arr[7].y = temp2.y + arr[6].y; arr[7].y /= 2;

	arr[8].x = temp2.x;
	arr[8].y = temp2.y;

	return arr;
}

double triArea(Point p1, Point p2, Point p3)
{
	double n1 = p1.x * (p2.y - p3.y);
	double n2 = p2.x * (p3.y - p1.y);
	double n3 = p3.x * (p1.y - p2.y);
	double sum = n1 + n2 + n3;
	return abs(sum / 2);

}


//Shape** allShapes = nullptr;
//int size = 0;int cap = 0;
//void addshape(Shape * obj)
//{
//	if (allShapes == nullptr)
//	{
//		allShapes = new Shape * ();
//		allShapes[0] = obj;
//		cap = size = 1;
//	}
//	else if (cap == size)
//	{
//		cap *= 2;
//		Shape** temp = new Shape * [cap];
//		for (int i = 0; i < size; i++)
//		{
//			temp[i] = allShapes[i];
//		}
//
//	}
//
//}
//You will use the following 5 functions do to all work

//A) DRAWING FUNCTIONS
//the two drawing functions that you will use to make all shapes
void draw_line(int x1, int y1, int x2, int y2, int color = WHITE, int width = 1) {
	GP142_lineXY(color, x1, y1, x2, y2, width);
}
void draw_rect(int x1, int y1, int x2, int y2, int color = WHITE, int width = 1) {
	GP142_lineXY(color, x1, y1, x1, y2, width);
	GP142_lineXY(color, x1, y2, x2, y2, width);
	GP142_lineXY(color, x2, y1, x1, y1, width);
	GP142_lineXY(color, x2, y1, x2, y2, width);
}
void drawdottedline(int x1, int y1, int x2, int y2, int color = WHITE, int width = 1) {

	Point* arr1, * arr2, * arr3, * arr4;
	Point temp1, temp2, temp3, temp4, temp5;

	temp1.x = x1;
	temp1.y = y1;
	temp5.x = x2;
	temp5.y = y2;
	temp3.x = temp1.x + temp5.x;
	temp3.x = temp3.x / 2;
	temp3.y = temp1.y + temp5.y;
	temp3.y = temp3.y / 2;
	temp2.x = temp1.x + temp3.x;
	temp2.x = temp2.x / 2;
	temp2.y = temp1.y + temp3.y;
	temp2.y = temp2.y / 2;
	temp4.x = temp3.x + temp5.x;
	temp4.x = temp4.x / 2;
	temp4.y = temp3.y + temp5.y;
	temp4.y = temp4.y / 2;
	arr1 = GetPoints(temp1, temp2);
	arr2 = GetPoints(temp2, temp3);
	arr3 = GetPoints(temp3, temp4);
	arr4 = GetPoints(temp4, temp5);

	for (int i = 0; i < 8; i++) {
		if (i % 2 == 0) {
			GP142_lineXY(color, arr1[i].x, arr1[i].y, arr1[i + 1].x, arr1[i + 1].y, 1);
		}
	}
	for (int i = 0; i < 8; i++) {
		if (i % 2 == 0) {
			GP142_lineXY(color, arr2[i].x, arr2[i].y, arr2[i + 1].x, arr2[i + 1].y, 1);
		}
	}
	for (int i = 0; i < 8; i++) {
		if (i % 2 == 0) {
			GP142_lineXY(color, arr3[i].x, arr3[i].y, arr3[i + 1].x, arr3[i + 1].y, 1);
		}
	}
	for (int i = 0; i < 8; i++) {
		if (i % 2 == 0) {
			GP142_lineXY(color, arr4[i].x, arr4[i].y, arr4[i + 1].x, arr4[i + 1].y, 1);
		}
	}

}
//Point trueNeighbor(Point temp,Point centre , Point previous,Point pre,int radius)
//{
//	Point temp2;
//	//temp2.x = temp.x;
//	//temp2.y = temp.y + 1;
//	//if (findDis(temp2, centre) == radius && temp2.x != previous.x && temp2.y != previous.y /*&&temp2.x != pre.x && temp2.y != pre.y*/)
//	//	return temp2;
//	//temp2.x = temp.x;
//	//temp2.y = temp.y - 1;
//	//if (findDis(temp2, centre) == radius && temp2.x != previous.x && temp2.y != previous.y /*&&temp2.x != pre.x && temp2.y != pre.y*/)
//	//	return temp2;
//	//temp2.x = temp.x+1;
//	//temp2.y = temp.y;
//	//if (findDis(temp2, centre) == radius && temp2.x != previous.x && temp2.y != previous.y /*&&temp2.x != pre.x && temp2.y != pre.y*/)
//	//	return temp2;
//	//temp2.x = temp.x-1;
//	//temp2.y = temp.y;
//	//if (findDis(temp2, centre) == radius && temp2.x != previous.x && temp2.y != previous.y /*&&temp2.x != pre.x && temp2.y != pre.y*/)
//	//	return temp2;
//	temp2.x = temp.x + 1;
//	temp2.y = temp.y + 1;
//	int t = findDis(temp2, centre);
//	if (t == radius && temp2.x != previous.x && temp2.y != previous.y /*&&temp2.x != pre.x && temp2.y != pre.y*/)
//		return temp2;
//	temp2.x = temp.x -1;
//	temp2.y = temp.y + 1;
//	t = findDis(temp2, centre);
//
//	if (t == radius && temp2.x != previous.x && temp2.y != previous.y /*&&temp2.x != pre.x && temp2.y != pre.y*/)
//		return temp2;
//	temp2.x = temp.x+1;
//	temp2.y = temp.y - 1;
//	 t = findDis(temp2, centre);
//
//	if (t == radius && temp2.x != previous.x && temp2.y != previous.y /*&&temp2.x != pre.x && temp2.y != pre.y*/)
//		return temp2;
//	temp2.x = temp.x - 1;
//	temp2.y = temp.y - 1;
//	 t = findDis(temp2, centre);
//	if (t == radius && temp2.x != previous.x && temp2.y != previous.y /*&&temp2.x != pre.x && temp2.y != pre.y*/)
//		return temp2;
//}
void draw_circle(int x1, int y1, int radius, int color = WHITE) {
	GP142_circleXY(color, x1, y1, radius);
	//Point centre , base,temp,pre,preprevious;
	//preprevious.x = 2222;		/*x1	137	int*/

	//preprevious.y = 2222;
	//centre.x = x1;
	//centre.y = y1;
	//base.x = x2;
	//base.y = y2;
	//pre.x = base.x;
	//pre.y = base.y;
	//temp = trueNeighbor(base, centre, pre,preprevious, radius);
	//GP142_pixelXY(color, base.x, base.y);
	//int n = 0;
	//while (/*temp.x != base.x && temp.y != base.y*/n!=129600)
	//{
	//	preprevious.x = pre.x;
	//	preprevious.y = pre.y;
	//	pre.x = temp.x;
	//	pre.y = temp.y;
	//	temp = trueNeighbor(temp, centre, pre,preprevious, radius);
	//	GP142_pixelXY(color, temp.x, temp.y);
	//	n++;
}



//B) EVENT HANDLERS
//Mouse handler
void handle_mouse(int x, int y) {
	GP142_printfXY(YELLOW, x, y, 9, "Mouse at (%d,%d)", x, y);
}

//Keyboard handler
void handle_kbd(char c)
{
	//put the character anywhere you want to.
	//I'm putting it on the origin
	GP142_printfXY(WHITE, 0, 0, TEXT_SIZE, "%c", c);
}

//periodic handler you will not need to use because we're not doing animation
void demo_handle_periodic(void) {};


/******************************************************************************
 *
 * The Main Program
 * ----------------
 *
 * The main program takes care of initialization and cleanup, and the high-level
 * control of all actions in the program, but most of the detail work is
 * relegated to sub-functions, so that the structure of main stays clear and
 * simple.
 *
 */

void canvas()
{
	//static Point topleft, topright, bottomleft, bottomright;
	topright.x = 300;
	topright.y = 250;
	topleft.x = -300;
	topleft.y = 250;
	bottomright.x = 300;
	bottomright.y = -250;
	bottomleft.x = -300;
	bottomleft.y = -250;
	draw_line(topright.x, topright.y, topleft.x, topleft.y, WHITE, 1);
	draw_line(topright.x, topright.y, bottomright.x, bottomright.y, WHITE, 1);
	draw_line(bottomleft.x, bottomleft.y, bottomright.x, bottomright.y, WHITE, 1);
	draw_line(bottomleft.x, bottomleft.y, topleft.x, topleft.y, WHITE, 1);
}

void panel1()
{
	draw_rect(-477, 401, -320, -1);
	GP142_printfXY(WHITE, -475, 375, TEXT_SIZE, "OPTIONS:");
	GP142_lineXY(WHITE, -477, 351, -320, 351,1);
	GP142_printfXY(WHITE, -475, 325, TEXT_SIZE, "NEW");
	GP142_lineXY(WHITE, -477, 325, -320, 325, 1);
	GP142_printfXY(WHITE, -475, 300, TEXT_SIZE, "RELOAD");
	GP142_lineXY(WHITE, -477, 300, -320, 300, 1);
	GP142_printfXY(WHITE, -475, 275, TEXT_SIZE, "LINE");
	GP142_lineXY(WHITE, -477, 275, -320, 275, 1);
	GP142_printfXY(WHITE, -475, 250, TEXT_SIZE, "DOTTED LINE");
	GP142_lineXY(WHITE, -477, 250, -320, 250, 1);
	GP142_printfXY(WHITE, -475, 225, TEXT_SIZE, "CURVE");
	GP142_lineXY(WHITE, -477, 225, -320, 225, 1);
	GP142_printfXY(WHITE, -475, 200, TEXT_SIZE, "DOTTED CURVE");
	GP142_lineXY(WHITE, -477, 200, -320, 200, 1);
	GP142_printfXY(WHITE, -475, 175, TEXT_SIZE, "POLYGON");
	GP142_lineXY(WHITE, -477, 175, -320, 175, 1);
	GP142_printfXY(WHITE, -475, 150, TEXT_SIZE, "RECTANGLE");
	GP142_lineXY(WHITE, -477, 150, -320, 150, 1);
	GP142_printfXY(WHITE, -475, 125, TEXT_SIZE, "TRIANGLE");
	GP142_lineXY(WHITE, -477, 125, -320, 125, 1);
	GP142_printfXY(WHITE, -475, 100, TEXT_SIZE, "CIRCLE");
	GP142_lineXY(WHITE, -477, 100, -320, 100, 1);
	GP142_printfXY(WHITE, -475, 75, TEXT_SIZE, "TEXT");
	GP142_lineXY(WHITE, -477, 75, -320, 75, 1);
	GP142_printfXY(WHITE, -475, 50, TEXT_SIZE, "ERASER");
	GP142_lineXY(WHITE, -477, 50, -320, 50, 1);
	GP142_printfXY(WHITE, -475, 25, TEXT_SIZE, "SAVE");
	GP142_lineXY(WHITE, -477, 25, -320, 25, 1);
	GP142_printfXY(WHITE, -475, 0, TEXT_SIZE, "BUCKET");

	draw_rect(399, 401, 490, 175);
	GP142_printfXY(WHITE, 400, 375, TEXT_SIZE, "COLOR:");
	GP142_lineXY(WHITE, 399, 375, 490, 375, 1);
	GP142_printfXY(WHITE, 400, 325, TEXT_SIZE, "WHITE");
	GP142_lineXY(WHITE, 399, 325, 490, 325, 1);
	GP142_printfXY(BLUE, 400, 300, TEXT_SIZE, "BLUE");
	GP142_lineXY(WHITE, 399, 300, 490, 300, 1);
	GP142_printfXY(RED, 400, 275, TEXT_SIZE, "RED");
	GP142_lineXY(WHITE, 399, 275, 490, 275, 1);
	GP142_printfXY(GREEN, 400, 250, TEXT_SIZE, "GREEN");
	GP142_lineXY(WHITE, 399, 250, 490, 250, 1);
	GP142_printfXY(YELLOW, 400, 225, TEXT_SIZE, "YELLOW");
	GP142_lineXY(WHITE, 399, 225, 490, 225, 1);
	GP142_printfXY(ORANGE, 400, 200, TEXT_SIZE, "ORANGE");
	GP142_lineXY(WHITE, 399, 200, 490, 200, 1);
	GP142_printfXY(WHITE, 400, 175, TEXT_SIZE, "BLACK");

	//GP142_rectangleXY(WHITE, -475, -1, -320, -400, 0);
	//GP142_rectangleXY(WHITE, -318, 400, 398, -400, 0);
	//GP142_rectangleXY(WHITE, 400, 174, 490, -400, 0);

}

class Shape
{
protected:
	vector<Point> points;
	int color;
	int n;
public:
	Shape(vector<Point> p, int c, int num)
	{
		n = num;
		//points = new Point[num];
		for (int i = 0; i < n; i++)
		{
			points.push_back(p[i]);
			//points[i].y = p[i].y;
		}
		color = c;
	}
	virtual void draw() = 0;
	virtual bool contains(Point p) = 0;
	virtual int shapeNum() = 0;
	int getsize()
	{
		return n;
	}
	int getcolor()
	{
		return color;
	}
	virtual char* getName() { return "NONE "; };
	virtual bool getstyle() { return 1; };
	vector<Point> getpoints()
	{
		return points;
	}
	virtual int getfillcolor() { return -1; };
	virtual int getradius() { return -1; };
	virtual void changecolor(int c) {};
	virtual void fill(int c) {};

};

class text : public Shape
{
private:
	char* name;
	public:
		text(vector<Point> p, int c, int n) : Shape(p, c, n) 
		{
			int x = points[0].x;
			int y = points[0].y;
			int count = x;
			char arr[100];
			char a;
			int i = 0;
			while (x == points[0].x && y == points[0].y)
			{
				GP142_await_event(&x, &y, &a);
				if (x == 0 && y == 0)
				{
					x = points[0].x;
					y = points[0].y;
				}
				arr[i++] = a;
				//GP142_printfXY(color, count, points[0].y, TEXT_SIZE, "%c", c);
				//count += 10;
			}
			arr[i++] = '\0';
			name = new char[i];
			strcpy(name, arr);
		}
		text(vector<Point> p, int c, int n, char nam[]) : Shape(p, c, n)
		{
			name = new char[strlen(nam) + 1];
			strcpy(name, nam);
		}
		void draw() 
		{
			//int x = points[0].x;
			//int y = points[0].y;
			//int count = x;
			//char c[100];
			//int i = 0;
			//while (x == points[0].x && y == points[0].y)
			//{
			//	GP142_await_event(&x, &y, &c[i++]);
			//	if (x == 0 && y == 0)
			//	{
			//		x = points[0].x;
			//		y = points[0].y;
			//	}

			//	//GP142_printfXY(color, count, points[0].y, TEXT_SIZE, "%c", c);
			//	//count += 10;
			//}
			GP142_textXY(color, points[0].x, points[0].y, TEXT_SIZE, name);
		}
		bool contains(Point p) 
		{
			Point max, min;
			min.x = points[0].x;
			min.y = points[0].y;
			max.x = min.x + 15*strlen(name);
			max.y = min.y + 20;
			if (p.x > min.x && p.x < max.x)
			{
				if (p.y > min.y && p.y < max.y)
					return true;
			}
			return false;
		}
		void changecolor(int c) 
		{
			color = c;
			GP142_textXY(color, points[0].x, points[0].y, TEXT_SIZE, name);
		}
		int shapeNum()
		{
			return 1;
		}
		char* getName()
		{
			return name;
		}
};

class OpenShape : public Shape
{
protected:
	bool style;
public:
	OpenShape(vector<Point> p, int c, int num, bool s) : Shape(p, c, num), style(s) {};
	//virtual void changecolor(int color) = 0;
	bool getstyle()
	{
		return style;
	}
};

class Line : public OpenShape
{
public:
	Line(vector<Point> p, int c, int num, bool s) : OpenShape(p, c, num, s) {};
	void draw()
	{
		if (style)
		{
			GP142_lineXY(color, points[0].x, points[0].y, points[1].x, points[1].y, 1);
		}
		else
		{
			/*Point temp;
			temp.x = (points[0].x + points[1].x) / 16;
			temp.y = (points[0].y + points[1].y) / 16;
			int n = 0;
			for (int i = points[0].x, j = points[0].y; i < points[1].x && j < points[1].y; i += temp.x, j += temp.y)
			{
				if (n % 2 == 0)
					GP142_lineXY(color, i, j, i + temp.x, j + temp.y, 1);

			}*/
			drawdottedline(points[0].x, points[0].y, points[1].x, points[1].y, color, 1);
		}

	}
	bool contains(Point p)
	{
		int sum = findDis(p, points[0]) + findDis(p, points[1]);
		if (sum == findDis(points[0], points[1]))
			return true;
		else return false;
	}
	void changecolor(int c)
	{
		color = c;
		if (style)
		{
			GP142_lineXY(c, points[0].x, points[0].y, points[1].x, points[1].y, 1);
		}
		else
		{
			drawdottedline(points[0].x, points[0].y, points[1].x, points[1].y, c, 1);
		}
	}
	int shapeNum()
	{
		return 2;
	}
};

class curve : public OpenShape
{
public:
	curve(vector<Point> p, int c, int num, bool s) : OpenShape(p, c, num, s) {};
	void draw()
	{
		if (style)
		{
			for (int i = 0; i < n - 1; i++)
			{
				GP142_lineXY(color, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, 1);
			}
		}
		else
		{
			for (int i = 0; i < n - 1; i++)
			{
				drawdottedline(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, color, 1);
			}
		}
	}
	bool contains(Point p)
	{
		for (int i = 0; i < n - 1; i++)
		{
			int sum = findDis(p, points[i]) + findDis(p, points[i + 1]);
			if (sum == findDis(points[i], points[i + 1]))
				return true;
		}
		return false;
	}
	void changecolor(int c)
	{
		color = c;
		if (style)
		{
			for (int i = 0; i < n - 1; i++)
			{
				GP142_lineXY(c, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, 1);
			}
		}
		else
		{
			for (int i = 0; i < n - 1; i++)
			{
				drawdottedline(points[0].x, points[0].y, points[1].x, points[1].y, c, 1);
			}
		}
	}
	int shapeNum()
	{
		return 3;
	}
};

class polygon : public Shape
{
protected:
	int fillcolor;
	bool PointInPolygon(Point p)
	{
		//vector<Point> points = polygon.getPoints();
		int i, j, numOfPoints = points.size();

		bool count = false;

		for (i = 0, j = numOfPoints - 1; i < numOfPoints; j = i++) {
			if (((points[i].y >= p.y) != (points[j].y >= p.y)) &&
				(p.x <= (points[j].x - points[i].x) * (p.y - points[i].y) / (points[j].y - points[i].y) + points[i].x)
				)
				count = !count;
		}

		return count;
	}
public:
	polygon(vector<Point> p, int c, int num, int f) : Shape(p, c, num), fillcolor(f) {};
	void draw()
	{
		for (int i = 0; i < n - 1; i++)
		{
			GP142_lineXY(color, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, 1);
		}
		GP142_lineXY(color, points[0].x, points[0].y, points[n - 1].x, points[n - 1].y, 1);

	}
	bool contains(Point p) 
	{
		return PointInPolygon(p);
	}
	void fill(int c) { fillcolor = c; };
	int shapeNum()
	{
		return 4;
	}
	int getfillcolor()
	{
		return fillcolor;
	}
};

class rectangle : public polygon
{
public:
	rectangle(vector<Point> p, int c, int num, int f) : polygon(p, c, num, f) {};
	void draw()
	{
		draw_rect(points[0].x, points[0].y, points[1].x, points[1].y, color, 1);
	}
	bool contains(Point p) 
	{ 
		Point max, min;
		if (points[0].y < points[1].y)
		{
			if (points[0].x < points[1].x)
			{
				if (p.x > points[0].x && p.x < points[1].x)
				{
					if (p.y > points[0].y && p.y < points[1].y)
					{
						return true;
					}
				}
			}
			if (points[0].x > points[1].x)
			{
				if (p.x < points[0].x && p.x > points[1].x)
				{
					if (p.y > points[0].y && p.y < points[1].y)
					{
						return true;
					}
				}
			}
		}
		else if (points[0].y > points[1].y)
		{
			if (points[0].x < points[1].x)
			{
				if (p.x > points[0].x && p.x < points[1].x)
				{
					if (p.y < points[0].y && p.y > points[1].y)
					{
						return true;
					}
				}
			}
			if (points[0].x > points[1].x)
			{
				if (p.x < points[0].x && p.x > points[1].x)
				{
					if (p.y < points[0].y && p.y > points[1].y)
					{
						return true;
					}
				}
			}
		}
		return false;

	}
	void fill(int c) { fillcolor = c; };
	int shapeNum()
	{
		return 5;
	}
};

class triangle : public polygon
{
public:
	triangle(vector<Point> p, int c, int num, int s) : polygon(p, c, num, s) {};
	void draw()
	{
		draw_line(points[0].x, points[0].y, points[1].x, points[1].y, color, 1);
		draw_line(points[1].x, points[1].y, points[2].x, points[2].y, color, 1);
		draw_line(points[0].x, points[0].y, points[2].x, points[2].y, color, 1);
	}
	bool contains(Point p) 
	{
		double a1 = triArea(p, points[0], points[1]);
		double a2 = triArea(p, points[1], points[2]);
		double a3 = triArea(p, points[0], points[2]);
		double a = triArea(points[0], points[1], points[2]);
		if ((a1 + a2 + a3) == a)
			return true;
		else return false;
	}
	void fill(int c) { fillcolor = c; };
	int shapeNum()
	{
		return 6;
	}
};

class circle : public Shape
{
	int fillcolor;
	int radius;
public:
	circle(vector<Point> p, int c, int num, int f = -1) : Shape(p, c, num), fillcolor(f)
	{
		radius = findDis(points[0], points[1]);
	}
	void draw()
	{
		GP142_circleXY(color, points[0].x, points[0].y, radius);
	}
	bool contains(Point p) 
	{
		int d = findDis(points[0], p);
		if (radius > d)
			return 1;
		else
			return 0;
	}
	void fill(int c) { fillcolor = c; };
	int shapeNum()
	{
		return 7;
	}
	int getfiilcolor()
	{
		return fillcolor;
	}
	int getradius()
	{
		return radius;
	}
};

vector<Shape*> allShapes;




void save()
{
	ofstream fout("E:\\University\\Semester 2\\C++ solutions\\HW4\\gp142Dem\\save.txt", ofstream::out | ofstream::trunc);
	if (fout.fail())
		GP142_textXY(WHITE, 0, 0, TEXT_SIZE, "File Not Open\n");
	else
	{
		for (int i = 0; i < allShapes.size(); i++)
		{
			fout << allShapes[i]->shapeNum() << ' ';
			fout << allShapes[i]->getsize() << ' ';
			fout << allShapes[i]->getcolor() << ' ';
			vector <Point> p = allShapes[i]->getpoints();
			for (int j = 0; j < p.size(); j++)
			{
				fout << p[j].x << ' ';
				fout << p[j].y << ' ';
			}
			switch (allShapes[i]->shapeNum())
			{
			case 1:
				fout << allShapes[i]->getName() << ' ';
				break;
			case 2:
				fout << allShapes[i]->getstyle() << ' ';
				break;
			case 3:
				fout << allShapes[i]->getstyle() << ' ';
				break;
			case 4:
				fout << allShapes[i]->getfillcolor() << ' ';
				break;
			case 5:
				fout << allShapes[i]->getfillcolor() << ' ';
				break;
			case 6:
				fout << allShapes[i]->getfillcolor() << ' ';
				break;
			case 7:
				fout << allShapes[i]->getfillcolor() << ' ';
				fout << allShapes[i]->getradius() << ' ';
				break;
			}
			fout << endl;
		}
	}

	//fout.close();
}

void load()
{
	ifstream fin("E:\\University\\Semester 2\\C++ solutions\\HW4\\gp142Dem\\save.txt"/*, ofstream::out | ofstream::trunc*/);
	if (fin.fail())
		GP142_textXY(WHITE, 0, 0, TEXT_SIZE, "File Not Open\n");
	else
	{
		allShapes.resize(0);
		allShapes.shrink_to_fit();
		char buff[500];
		while (fin.getline(buff, 500))
		{
			int i = 0;
			int shape = buff[i++] - '0';
			i++;
			int n = buff[i++] - '0';
			i++;
			int c = buff[i++] - '0';
			i++;
			vector<Point> p;
			for (int j = 0; j < n; j++)
			{
				Point temp;
				temp.x = 0; temp.y = 0;
				int x = 0, y = 0;
				bool flag = false , flag1 = false;
				while (buff[i] != ' ')
				{
					if (buff[i] == '-')
					{
						flag = true; i++;
					}
					else 
					   temp.x = temp.x * 10 + (buff[i++] - '0');
				}
				if (flag == true)
					temp.x *= -1;
				i++;
				while (buff[i] != ' ')
				{
					if (buff[i] == '-')
					{
						flag1 = true; i++;
					}
					else 
					  temp.y = temp.y * 10 + (buff[i++] - '0');
				}
				if (flag1 == true)
					temp.y *= -1;
				i++;
				p.push_back(temp);
			}
			int f, sh;
			bool flag2 = false;
			if (buff[i] == '-')
			{
				flag2 = true;
				i++;
			}
			Shape* s;
			switch (shape)
			{
			case 1:
				char name[50];
				strcpy(name, buff + i);
				 s = new text(p, c, n,name);
				allShapes.push_back(s);
				break;
			case 2:
				sh = buff[i] - '0';
				if (flag2 == true)
					sh *= -1;
				s = new Line(p, c, n, sh);
				allShapes.push_back(s);
				break;
			case 3:
				sh = buff[i] - '0';
				if (flag2 == true)
					sh *= -1;
				s = new curve(p, c, n, sh);
				allShapes.push_back(s);
				break;
			case 4:
				f = buff[i] - '0';
				if (flag2 == true)
					f *= -1;
				s = new polygon(p, c, n, f);
				allShapes.push_back(s);
				break;
			case 5:
				f = buff[i] - '0';
				if (flag2 == true)
					f *= -1;
				s = new rectangle(p, c, n, f);
				allShapes.push_back(s);
				break;
			case 6:
				f = buff[i] - '0';
				if (flag2 == true)
					f *= -1;
				s = new triangle(p, c, n, f);
				allShapes.push_back(s);
				break;
			case 7:
				f = buff[i] - '0';
				if (flag2 == true)
					f *= -1;
				s = new circle(p, c, n, f);
				allShapes.push_back(s);
				break;
			}
		}
	}
	GP142_clear();
	panel1();
	for (int i = 0; i < allShapes.size(); i++)
	{
		allShapes[i]->draw();
	}
	fin.close();
}



int main(void)
{
	//std::vector<int> abc(5);
	int quit = 0;           /* has user signaled quit yet?                      */
	int mouse_x, mouse_y;
	char key_pressed;
	GP142_open();           /* Open and initialize the GP142 Graphics Window    */
	//canvas();
	panel1();
	int pcount = 0;
	//int points[6];
	int r = 0;
	vector<Point> points;
	Point select;

	//The Event Loop  
	while (!quit) {

		switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {
		case GP142_QUIT:
			quit = 1;   /* set flag to terminate loop                */
			break;

		case GP142_MOUSE:
			//handle_mouse(mouse_x,mouse_y);

			/*points[2 * pcount] = mouse_x;
			points[2 * pcount + 1] = mouse_y;
			pcount++;*/

			pcount++;

			if (pcount == 1)
			{
				if ((mouse_x<-475 || mouse_x>-320) && (mouse_x<500 || mouse_x>400))
				{
					//if (mouse_y > 350 || mouse_y < 100)
						pcount = 0;
				}
				
				select.x = mouse_x;
				select.y = mouse_y;
				
			}
			else if (select.x > -477 && select.x < -320)
			{
				if (select.y < 350 && select.y>325)
				{
					//new
					GP142_clear();
					allShapes.resize(0);
					allShapes.shrink_to_fit();
					panel1();
					pcount = 0;
				}
				if (select.y < 325 && select.y>300)
				{
					//reload
					load();
					pcount = 0;
				}
				else if (select.y < 300 && select.y>275)
				{
					//line
					Point temp;
					temp.x = mouse_x;
					temp.y = mouse_y;
					points.push_back(temp);
					if (pcount == 3)
					{
						Shape* s = new Line(points, col, pcount - 1, 1);
						s->draw();
						allShapes.push_back(s);

						pcount = 0;
						points.resize(0);
						points.shrink_to_fit();
					}

				}
				else if (select.y < 275 && select.y>250)
				{
					//dotted line
					Point temp;
					temp.x = mouse_x;
					temp.y = mouse_y;
					points.push_back(temp);
					if (pcount == 3)
					{
						Shape* s = new Line(points, col, pcount - 1, 0);
						s->draw();
						allShapes.push_back(s);

						pcount = 0;
						points.resize(0);
						points.shrink_to_fit();
					}
				}
				else if (select.y < 250 && select.y>225)
				{
					//curve
					Point temp;
					temp.x = mouse_x;
					temp.y = mouse_y;
					points.push_back(temp);
					
					if (pcount > 3)
					{
						if (points[pcount - 2].x == points[pcount - 3].x && points[pcount - 2].y == points[pcount - 3].y)
						{
							Shape* s = new curve(points, col, pcount - 1, 1);
							s->draw();
							allShapes.push_back(s);

							pcount = 0;
							points.resize(0);
							points.shrink_to_fit();
						}
					}
				}
				else if (select.y < 225 && select.y>200)
				{
					//dotted curve
					Point temp;
					temp.x = mouse_x;
					temp.y = mouse_y;
					points.push_back(temp);

					if (pcount > 3)
					{
						if (points[pcount - 2].x == points[pcount - 3].x && points[pcount - 2].y == points[pcount - 3].y)
						{
							Shape* s = new curve(points, col, pcount - 1, 0);
							s->draw();
							allShapes.push_back(s);

							pcount = 0;
							points.resize(0);
							points.shrink_to_fit();
						}
					}
				}
				else if (select.y < 200 && select.y>175)
				{
					//polygon
					Point temp;
					temp.x = mouse_x;
					temp.y = mouse_y;
					points.push_back(temp);

					if (pcount > 3)
					{
						if (points[pcount - 2].x == points[pcount - 3].x && points[pcount - 2].y == points[pcount - 3].y)
						{
							Shape* s = new polygon(points, col, pcount - 1, WHITE);
							s->draw();
							allShapes.push_back(s);

							pcount = 0;
							points.resize(0);
							points.shrink_to_fit();
						}
					}
				}
				else if (select.y < 175 && select.y>150)
				{
					//rectangle
					Point temp;
					temp.x = mouse_x;
					temp.y = mouse_y;
					points.push_back(temp);
					if (pcount == 3)
					{
						Shape* s = new rectangle(points, col, pcount - 1,col);
						s->draw();
						allShapes.push_back(s);

						pcount = 0;
						points.resize(0);
						points.shrink_to_fit();
					}
				}
				else if (select.y < 150 && select.y>125)
				{
					//Triangle
					Point temp;
					temp.x = mouse_x;
					temp.y = mouse_y;
					points.push_back(temp);
					if (pcount == 4)
					{
						Shape* s = new triangle(points, col, pcount - 1, col);
						s->draw();
						allShapes.push_back(s);
						pcount = 0;
						points.resize(0);
						points.shrink_to_fit();
					}
				}
				else if (select.y < 125 && select.y>100)
				{
					//circle
					Point temp;
					temp.x = mouse_x;
					temp.y = mouse_y;
					points.push_back(temp);
					if (pcount == 3)
					{
						Shape* s = new circle(points, col, pcount - 1);
						s->draw();
						allShapes.push_back(s);
						pcount = 0;
						points.resize(0);
						points.shrink_to_fit();
					}
				}
				else if (select.y < 100 && select.y>75)
				{
				//text
				Point temp;
				temp.x = mouse_x;
				temp.y = mouse_y;
				points.push_back(temp);

				Shape* s = new text(points, col, pcount - 1);
				s->draw();
				allShapes.push_back(s);
				pcount = 0;
				points.resize(0);
				points.shrink_to_fit();
                }
				else if (select.y < 75 && select.y>50)
				{
					//Eraser
					Point temp;
					temp.x = mouse_x;
					temp.y = mouse_y;
					points.push_back(temp);
					bool flag = false;
					for (int i = allShapes.size()-1; i >= 0; --i)
					{
						if (allShapes[i]->contains(temp))
						{
							flag = true;
							allShapes.erase(allShapes.begin() + i);
							break;
						}
					}
					if (flag = true)
					{
						GP142_clear();
						panel1();
						for (int i = 0; i < allShapes.size(); i++)
						{
							allShapes[i]->draw();
						}
					}
					pcount = 0;
					points.resize(0);
					points.shrink_to_fit();
				}
				else if (select.y < 50 && select.y>25)
				{
				   //save
				   save();
				   pcount = 0;
                }
				else if (select.y < 25 && select.y>0)
				{
				   //bucket
				   bool flag = false;
				   bool shape = false;
				   Point temp;
				   temp.x = mouse_x;
				   temp.y = mouse_y;
				   points.push_back(temp);
				   for (int i = 0; i < allShapes.size(); i++)
				   {
					   if (allShapes[i]->contains(points[0]))
					   {
						   shape = true;
						   if (allShapes[i]->shapeNum() == 1 || allShapes[i]->shapeNum() == 2 || allShapes[i]->shapeNum() == 3)
						   {
							   flag = true;
							   allShapes[i]->changecolor(col);
						   }
						   else
						   {
							   allShapes[i]->fill(col);
						   }
					   }
				   }
				   if (shape)
				   {
					   old_col = get_p_color(points[0].x, points[0].y);
					   GP142_bucket_fill(points[0].x, points[0].y, old_col, col);
				   }
				   
				   COLORREF c = get_p_color(temp.x, temp.y);
				  // GP142_bucket_fill(temp.x, temp.y, old_col, col);
				   //set_p_color(temp.x, temp.y, col);
				   //GP142_pixelXY(col, temp.x, temp.y);
				   pcount = 0;
				   points.resize(0);
				   points.shrink_to_fit();
                }
				
			}
			if (select.x < 450 && select.x > 375)
			{
			     if (select.y < 350 && select.y>325)
				 {
					 old_col = col;
					 col = WHITE;
				 }
				 else if (select.y < 325 && select.y>300)
				 {
					 old_col = col;
					 col = BLUE;
				 }
				 else if (select.y < 300 && select.y>275)
				 {
					 old_col = col;

					 col = RED;
				 }
				 else if (select.y < 275 && select.y>250)
				 {
					 old_col = col;

					 col = GREEN;
				 }
				 else if (select.y < 250 && select.y>225)
				 {
					 old_col = col;

					 col = YELLOW;
				 }
				 else if (select.y < 225 && select.y>200)
				 {
					 old_col = col;

					 col = ORANGE;
				 }
				 else if (select.y < 200 && select.y>175)
				 {
					 old_col = col;

					 col = BLACK;
				 }
				 pcount = 0;
			}
			break;

		case GP142_KBD:
			//Keyboard handler
			//handle_kbd(key_pressed);
			pcount = 0;
			break;

		default:
			break;
		}
	}

	GP142_close();          /* Clean up and close graphics window           */

	return 0;
}







//if (pcount == 2)
			//{
			//	pcount = 0;
			//	//draw_rect(points[0], points[1],
			//		//points[2], points[3]);
			//	Point p1, p2;
			//	p1.x = points[0];
			//	p1.y = points[1];
			//	p2.x = points[2];
			//	p2.y = points[3];
			//	r = findDis(p1, p2);
			//	draw_circle(points[0], points[1], r);

			//}

/*if (pcount == 3)
			{
				pcount = 0;
				draw_line(points[0], points[1], points[2], points[3]);
				draw_line(points[2], points[3], points[4], points[5]);
				draw_line(points[4], points[5], points[0], points[1]);

			}*/