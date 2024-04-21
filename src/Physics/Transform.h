#ifndef TRANSFORM_H
#define TRANSFORM_H
#include<bits/stdc++.h>
#include "Vector2D.h"
using namespace std;
class Transform
{

    public:
        float X, Y;

    public:
        Transform(float x = 0, float y = 0): X(x), Y(y) {}
        void Log(string msg = "")
        {
        cout << msg << "(X Y) = (" << X << " " << Y << ")" <<endl;
        }

    public:
        inline void TranslateX(float x) { X += x; }
        inline void TranslateY(float y) { Y += y; }
        inline void Translate(Vector2D v) { X += v.X; Y += v.Y; }
};

#endif
