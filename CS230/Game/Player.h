#pragma once

#include <raylib.h>

class Player {
public:
    float fuel = 100.0f;
    float maxFuel = 100.0f;
    int money = 0;
    float humanity = 0.0f;
    float fuelBurnRate = 10.0f; 
    float expresswayBurnRate = 0.3f; 

    void Update(float speed, float deltaTime); 
    void DrawFuelBar(Vector2 screenPosition);  
   // void SetBurnRate(bool onExpressway); 
};
