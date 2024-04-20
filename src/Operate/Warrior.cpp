#include"Warrior.h"
#include"TextureManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include"Input.h"
using namespace std;

Warrior::Warrior(Properties* props): Character(props)
{
    m_RigidBody= new RigidBody();
    m_Animation=new Animation();
  m_Animation->SetProps(m_TextureID, 1, 8, 100);
}

void Warrior::Draw()
{
   m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt)
{
    m_Animation->SetProps("player", 1, 8, 100);
    m_RigidBody->UnSetForce();
        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
                m_RigidBody->ApplyForceX(5*BACKWARD);
            m_Animation->SetProps("Player_run", 1, 8, 100,SDL_FLIP_HORIZONTAL);
        }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
{
     m_RigidBody->ApplyForceX(5*FORWARD);
    m_Animation->SetProps("player_run", 1, 8, 100);
}
    m_RigidBody->Update(0.2);
    m_RigidBody->ApplyForce(5);
    m_Transform->TranslateX(m_RigidBody->Position().X);
     //m_Transform->TranslateY(m_RigidBody->Position().Y);
  m_Animation->Update();

}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean();
}