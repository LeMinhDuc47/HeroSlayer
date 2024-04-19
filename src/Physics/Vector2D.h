#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
using namespace std;
class Vector2D
{
    public:
        float X, Y;

    public:
        Vector2D(float x = 0, float y = 0): X(x), Y(y) {}

    public:
        inline Vector2D operator + (const Vector2D& v2) const
        {
            return Vector2D(X + v2.X, Y + v2.Y);
        }
        inline Vector2D operator - (const Vector2D& v2) const
        {
            return Vector2D(X - v2.X, Y - v2.Y);
        }
        inline Vector2D operator * (const float scalar) const
        {
            return Vector2D(X * scalar, Y * scalar);
        }

        void Log()
        {
            cout << "(X Y) = (" << X << " " << Y << ")" <<endl;
        }
};
class Transform
{

    public:
        float X, Y;

    public:
        Transform(float x = 0, float y = 0): X(x), Y(y) {}
        void Log()
        {
            cout << "(X Y) = (" << X << " " << Y << ")" <<endl;
        }

    public:
        inline void TranslateX(float x) { X += x; }
        inline void TranslateY(float y) { Y += y; }
        inline void Translate(Vector2D v) { X += v.X; Y += v.Y; }
};
#endif
