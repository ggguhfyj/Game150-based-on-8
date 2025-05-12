

#include "../Game/Asteroid.h"
#include "Mode1.h"
#include "../Engine/Engine.h"
//awdawd
Asteroid::Asteroid()
{
}
Asteroid::Asteroid(Math::vec2 start_position) :
    GameObject(start_position),
    current_state(&state_landing)
{
    sprite.Load("Assets/Asteroid.spt");
    current_state->Enter(this);
}

void Asteroid::Update(double dt) {
    current_state->Update(this, dt);
    sprite.Update(dt);
    UpdatePosition(dt * GetVelocity());
    current_state->CheckExit(this);
}


//void Asteroid::Load()
//{
//    
//    position = start_position;
//    velocity = {0,0};
//    sprite.Load("Assets/Asteroid.spt");
//    current_state = &state_bouncing;
//    current_state->Enter(this);
//
//}




//void Asteroid::Draw(Math::TransformationMatrix camera_matrix)
//{
//    sprite.Draw(camera_matrix * object_matrix);
//
//}


void Asteroid::change_state(State* new_state)
{
    current_state = new_state;
    current_state->Enter(this);
}

void Asteroid::State_Bouncing::Enter(Asteroid* asteroid)
{
    //if (asteroid->position.y <= Mode1::floor)
    if (asteroid->GetPosition().y <= Mode1::floor)
    {
        asteroid->sprite.PlayAnimation(static_cast<int>(Animations::None));
        //asteroid->velocity.y = Asteroid::bounce_velocity;
        asteroid->SetVelocity({ 0,bounce_velocity });
    }
    else {
        //asteroid->velocity.y = 0;

        asteroid->SetVelocity({0,0});
    }
    asteroid->SetVelocity({ 0,bounce_velocity });
    
}

void Asteroid::State_Bouncing::Update(Asteroid* asteroid, double dt)
{
    //asteroid->velocity.y -= Mode1::gravity * dt;
    asteroid->UpdateVelocity({ 0, -Mode1::gravity * dt });
    //asteroid->position += asteroid->velocity * dt;
}

void Asteroid::State_Bouncing::CheckExit(Asteroid* asteroid) {
    if (asteroid->GetPosition().y < Mode1::floor) {
        asteroid->SetPosition({ asteroid->GetPosition().x, Mode1::floor });
        asteroid->SetVelocity({ asteroid->GetVelocity().x, 0 });
        asteroid->change_state(&asteroid->state_landing);
    }
}


void Asteroid::State_Landing::Enter(Asteroid* asteroid)
{
    asteroid->sprite.PlayAnimation(static_cast<int>(Animations::state_land));
    //asteroid->velocity.y = 0;
    asteroid->SetVelocity({ asteroid->GetVelocity().x,0 });
    //asteroid->position.y = Mode1::floor;
    asteroid->SetPosition({ asteroid->GetPosition().x,Mode1::floor}); //
}

void Asteroid::State_Landing::Update(Asteroid* asteroid, double dt)
{
    dt; asteroid;
}

void Asteroid::State_Landing::CheckExit(Asteroid* asteroid)
{
    if (asteroid->sprite.AnimationEnded()) {
        asteroid->change_state(&asteroid->state_bouncing);
    }
}
