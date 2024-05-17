#ifndef POINT_H
#define POINT_H

#include <bits/stdc++.h>
using namespace std;

class Point
{
	public:
		float X, Y;

	public:
		Point(float X = 0, float Y = 0) : X(X), Y(Y) {};

		//ADD+
		inline Point operator+ (const Point& p2) const {
			return Point(X + p2.X, Y + p2.Y);
		}

		//ADD+=
		inline friend Point operator +=(Point& p1, const Point& p2) {
			p1.X += p2.X;
			p1.Y += p2.Y;
			return p1;
		}

		//SUBTRACT -
		inline Point operator- (const Point& p2) const {
			return Point(X - p2.X, Y - p2.Y);
		}

		//SUBTRACT-=
		inline friend Point operator -=(Point& p1, const Point& p2) {
			p1.X -= p2.X;
			p1.Y -= p2.Y;
			return p1;
		}

		//MULTIPLI*
		inline Point operator* (const float scalar) const {
			return Point(X * scalar, Y * scalar);
		}

		//KC
		static float KC(const Point a, const Point b) {
			return sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y));
		}

		void Log(string msg = "") {
			cout << msg << " (X Y) = (" << X << " " << Y << ")" << endl;
		}

};

#endif //

