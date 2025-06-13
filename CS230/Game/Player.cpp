#include "Player.h"

void Player::Update(float speed, float deltaTime) {
    if (speed > 0.1f && fuel > 0.0f) {
        fuel -= fuelBurnRate * deltaTime * (speed / 100.0f);
        if (fuel < 0.0f) fuel = 0.0f;
    }
}

//void Player::Expressway_Fuel_Consumption() {
//
//}

void Player::DrawFuelBar(Vector2 screenPosition) {
    float barWidth = 200.0f;
    float barHeight = 20.0f;
    float ratio = fuel / maxFuel;

    Color fillColor = (ratio > 0.5f) ? GREEN : (ratio > 0.2f) ? ORANGE : RED;

    
    DrawRectangle((int)screenPosition.x, (int)screenPosition.y, (int)barWidth, (int)barHeight, DARKGRAY);
  
    DrawRectangle((int)screenPosition.x, (int)screenPosition.y, (int)(barWidth * ratio), (int)barHeight, fillColor);
   
    DrawRectangleLines((int)screenPosition.x, (int)screenPosition.y, (int)barWidth, (int)barHeight, BLACK);

    
    DrawText(TextFormat("Fuel: %.0f%%", ratio * 100.0f), (int)screenPosition.x + 5, (int)screenPosition.y + 2, 14, BLACK);
}