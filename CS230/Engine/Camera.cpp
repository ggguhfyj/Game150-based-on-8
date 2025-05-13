#include "Camera.h"
#include "../Engine/Engine.h"
#include <string>
#include "Matrix.h"

CS230::Camera::Camera(Math::rect player_zone) : player_zone(player_zone), position({ 0.0f, 0.0f })
{
    camerarotation = 0;
}

void CS230::Camera::SetPosition(Math::vec2 new_position)
{
    position = new_position;
}

const Math::vec2& CS230::Camera::GetPosition() const
{
    return position;
}

void CS230::Camera::SetLimit(Math::irect new_limit)
{
    limit = new_limit;
}

void CS230::Camera::SetRotation(double rotation)
{
    camerarotation = rotation;
}

void CS230::Camera::Update(const Math::vec2& player_position) {


    if (player_position.x > player_zone.top_right.x + position.x)
    {
        position.x = player_position.x - player_zone.top_right.x;
    }
    if (player_position.x - position.x < player_zone.bottom_left.x) {
        position.x = player_position.x - player_zone.bottom_left.x;
    }

    if (position.x < limit.bottom_left.x)
    {
        position.x = limit.bottom_left.x;
    }
    if (position.x > limit.top_right.x) {
        position.x = limit.top_right.x;
    }
    if (position.y < limit.bottom_left.y) {
        position.y = limit.bottom_left.y;
    }
    if (position.y > limit.top_right.y) {
        position.y = limit.top_right.y;
    }
}

Math::TransformationMatrix CS230::Camera::GetMatrix() {
    return Math::TranslationMatrix(-position);
}

Math::TransformationMatrix CS230::Camera::GetoffsetMatrix()
{
 
    Math::vec2 window_size = static_cast<Math::vec2>(Engine::GetWindow().GetSize());
    Math::vec2 screen_center = window_size / 2.0;

    // 2. Create the individual transformation matrices
    //    - Translate to screen center: Moves the final view origin to the middle.
    //    - Rotate view: Rotates by the inverse of the camera/car rotation.
    //    - Translate car to origin: Moves the point we rotate around (car's position) to (0,0).
    Math::TranslationMatrix translate_to_center(screen_center);
    Math::RotationMatrix rotate_view(-camerarotation);
    Math::TranslationMatrix translate_car_to_origin(-position); // 'position' should match car's position
    
    // 3. Combine the matrices. Read operations right-to-left:
    //    First, translate the world so the car is at the origin.
    //    Second, rotate the translated world.
    //    Finally, translate the rotated world so the origin (where the car is) moves to the screen center.
    return translate_to_center * translate_car_to_origin;//*rotate_view
}
