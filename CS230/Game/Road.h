/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Road.h
Project:    CS230 Engine
Author:     Junseok lee
Created:    March 29, 2025
*/
#pragma once
#include "..\Engine\Input.h"
#include "..\Engine\Window.h"
#include "..\Engine\Matrix.h"
#include "..\Engine\GameObject.h"

class Road : public CS230::GameObject {
public:
	Road();
	Road(Math::vec2 position);
	void Update(double dt);
	void Draw(Math::TransformationMatrix camera_matrix);
	void DrawPerspective(Math::TransformationMatrix camera_matrix);
	
	//void Reset();
	
private:


	CS230::Sprite road;//for mode7
	Math::vec2 start_position;
	Math::vec2 position;
	Math::vec2 velocity;

	Math::TransformationMatrix object_matrix;

	static constexpr double speed = 700;
	static constexpr double drag = 1;
	static constexpr double rotation_speed = 5;
	static constexpr double scale = 0.75;


};