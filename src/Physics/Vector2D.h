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
class IObject
{
    public:
      virtual void Draw() = 0;
      virtual void Update(float dt) = 0;
      virtual void Clean() = 0;
};
struct Properties
{
    public:
        Properties(string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE)
        {
            X = x;
            Y = y;
            Flip = flip;
            Width = width;
            Height = height;
            TextureID = textureID;
        }

    public:
        string TextureID;
        int Width, Height;
        float X, Y;
        SDL_RendererFlip Flip;
};

class GameObject : public IObject
{
    public:
        GameObject(Properties* props)
            : m_TextureID(props->TextureID), m_Width(props->Width), m_Height(props->Height), m_Flip(props->Flip){  m_Transform = new Transform(props->X, props->Y);}
        virtual void Draw() = 0;
        virtual void Clean() = 0;
        virtual void Update(float dt) = 0;

    protected:
        Transform* m_Transform;
        string m_TextureID;
        int m_Width, m_Height;
        SDL_RendererFlip m_Flip;
};

#endif
