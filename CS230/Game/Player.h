#pragma once

#include <raylib.h>

class Player {
public:
    float fuel = 100.0f;
    float maxFuel = 100.0f;
    int money = 0;
    float humanity = 0.0f;
    float fuelBurnRate = 10.0f; // 초당 연료 소모량 (기본값)
    float expresswayBurnRate = 0.3f; 

    void Update(float speed, float deltaTime); // 연료 감소 처리
    void DrawFuelBar(Vector2 screenPosition);  // 연료 게이지 시각화
   // void SetBurnRate(bool onExpressway); // 고속도로에서 연료 감소처리
};