#pragma once
#include <raylib.h>
#include <raymath.h>
#include "..\Engine\Engine.h"
#include "mapGen.h"

class Mode7 {

private:
	struct Frustum 
	{
		Vector2 Far1;
		Vector2 Far2;
		Vector2 Near1;
		Vector2 Near2;
	};
	static inline float fWorldX = 1900.0f;
	static inline float fWorldY = 1500.0f;
	static inline float fWorldA = 0.1f;
	static inline float fNear = 0.005f;
	static inline float fFar = 50.0f;
	static inline float fFoVHalf = PI / 4.0f;
	static inline float fSpeed = 0.0f;
	static inline float fMaxSpeed = 300.0f;
	static inline float fStartSpeed = 0.0f;
	static inline float skyOffset = 0.0f;

	static inline Vector2 windowsize = { 700,500 };

	static inline Vector2 position = { 100,100 };
	static inline int tabheight = 40;
	static inline Texture2D texSky;
	static inline Texture2D texMap;
	static inline Texture2D windowtabs;
	static inline Texture2D trafficlightsTex;
	static inline Image imgMap;
	static inline Frustum frustum;
	static void DrawMode7Line(int y);
	static void RepositionWindow();
	static void ReSizeWindow();
	
public:
	static void Load();
	static void Update();
	static void Draw();
	static void unload();

	static Vector2 TextureMapPoint(float fx, float fy);

	static float GetPlayerX();
	static float GetPlayerY();
};