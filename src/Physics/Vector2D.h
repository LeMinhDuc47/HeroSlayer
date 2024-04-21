#ifndef VECTOR2D_H
#define VECTOR2D_H
#include<SDL.h>
#include <bits/stdc++.h>
#include"Point.h"
#define UNI_MASS 1.0f
#define GRAVITY 9.8f

#define FORWARD 1
#define BACKWARD -1

#define UPWARD 1
#define DOWNWARD -1

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
: m_TextureID(props->TextureID), m_Width(props->Width), m_Height(props->Height), m_Flip(props->Flip){  m_Transform = new Transform(props->X, props->Y);
        float px=props->X+ props->Width/2;
        float py=props->Y+ props->Height/2;
        m_Origin= new Point(px,py);
}
        Point* GetOrigin(){return m_Origin;}
        virtual void Draw() = 0;
        virtual void Clean() = 0;
        virtual void Update(float dt) = 0;

    protected:
        Point* m_Origin;
        Transform* m_Transform;
        string m_TextureID;
        int m_Width, m_Height;
        SDL_RendererFlip m_Flip;
};
class Character : public GameObject
{
    public:
        Character(Properties* props): GameObject(props) {}

        virtual void Draw() = 0;
        virtual void Clean() = 0;
        virtual void Update(float dt) = 0;

    protected:
        string m_Name;
};
class RigidBody
{
    public:
        RigidBody()
        {
            m_Mass = UNI_MASS;
            m_Gravity = GRAVITY;
        }
        void SetMass(float mass) { m_Mass = mass; }
        void SetGravity(float gravity) { m_Gravity = gravity; }

         void ApplyForce(Vector2D F) { m_Force = F; }
         void ApplyForceX(float Fx) { m_Force.X = Fx; }
         void ApplyForceY(float Fy) { m_Force.Y = Fy; }
         void UnSetForce() { m_Force = Vector2D(0, 0); }

         void ApplyFriction(Vector2D Fr) { m_Friction = Fr; }
         void UnSetFriction() { m_Friction = Vector2D(0, 0); }

        float GetMass() { return m_Mass; }
         Vector2D Position() { return m_Position; }
         Vector2D Velocity() { return m_Velocity; }
         Vector2D Acceleration() { return m_Acceleration; }

        // update methods
        void Update(float dt)
        {
            m_Acceleration.X = (m_Force.X + m_Friction.X) / m_Mass;
            m_Acceleration.Y = m_Gravity + m_Force.Y / m_Mass;
            m_Velocity = m_Acceleration * dt;
            m_Position = m_Velocity * dt;
        }

    private:
        float m_Mass;
        float m_Gravity;

        Vector2D m_Force;
        Vector2D m_Friction;

        Vector2D m_Position;
        Vector2D m_Velocity;
        Vector2D m_Acceleration;
};
#endif
