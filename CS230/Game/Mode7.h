#pragma once
#include <raylib.h>
#include <raymath.h>
#include "..\Engine\Engine.h"
#include "mapGen.h"
#include "..\Game\newmapGen.h"
#include "..\Engine\Window.h"
class Mode7 {

private:
	struct Frustum 
	{
		Vector2 Far1;
		Vector2 Far2;
		Vector2 Near1;
		Vector2 Near2;
	};
	static inline float fRotationSpeed = 0.0f;
	static inline float fRotationAccel = 6.0f;
	static inline float fRotationDamping = 2.0f;
	static inline float fMaxRotationSpeed = 1.8f;
	
	static inline float fWorldX = 0.0f;
	static inline float fWorldY = 0.0f;
	static inline float fWorldA = 0.0f;
	static inline float fNear = -171;
	static inline float fFar = 28;
	//static inline float fFoVHalf = PI / 4.0f;
	static inline float fFoVHalf = 1.3f;
	static inline float fSpeed = 200.0f;
	static inline float fMaxSpeed = 300.0f;
	static inline float fStartSpeed = 0.0f;
	static inline float skyOffset = 0.0f;

	static inline Vector2 windowsize = { 300,200 };
	static inline Vector2 position = { 0,0 };

	static inline Texture2D texSky;
	static inline Texture2D texMap;
	static inline Texture2D windowtabs;
	static inline Texture2D trafficlightsTex;
	static inline Texture2D player[6];
	static inline Texture2D BWplayer[6];
	static inline Texture2D VPplayer[6];

	static inline Texture2D FovplayerRight[18];
	static inline Texture2D FovplayerLeft[18];

	static inline Texture2D trees[3];
	static inline Image imgMap;

	static inline Frustum frustum;

	static void DrawMode7Line(int y);

	static inline Color DrawFog(Color color);

	static inline const int blowup_scale = 4;

	static inline int playersprites = 3;

	static inline bool right;
	static inline int counter = 0;

	static inline unsigned char R = 155;
	static inline unsigned char G = 155;
	static inline unsigned char B = 155;
	static inline unsigned char A = 100;
	static inline unsigned char BASE = 100;

	static inline float fPlayerScreenX; // Player's current X position on the screen
	static inline float fPlayerHSpeed = 0.0f;      // Player's current horizontal speed
	static inline float fPlayerHAccel = 300.0f;   // Player's horizontal acceleration
	static inline float fPlayerHDamping = 200.0f; // Damping for horizontal movement
	static inline float fMaxPlayerHSpeed = 200.0f;// Maximum horizontal speed for the player

	static inline Sound sound_ski_skidding;
	static inline Music sound_ski_default;
	static inline bool isSkiddingSoundPlaying;
	static inline float musicVolume = 1.0;
	static inline float soundVolume = 1.0;

public:
	static void Load();
	static void Update();
	static void Draw();
	static void unload();
	static void DrawPlayer();
	static void SetVolume(float volume);
};