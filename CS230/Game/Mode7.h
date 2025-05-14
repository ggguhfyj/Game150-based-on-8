#include <raylib.h>
#include <raymath.h>
#include "..\Engine\Engine.h"

class Mode7 {
private:
	struct Frustum 
	{
		Vector2 Far1;
		Vector2 Far2;
		Vector2 Near1;
		Vector2 Near2;
	};
	static inline float fWorldX = 0.0f;
	static inline float fWorldY = 0.0f;
	static inline float fWorldA = 0.1f;
	static inline float fNear = 0.005f;
	static inline float fFar = 50.0f;
	static inline float fFoVHalf = PI / 4.0f;
	static inline float fSpeed = 100.0f;
	static inline float skyOffset = 0.0f;

	static inline Vector2 windowsize = { 700,500 };
	static inline Texture2D texSky;
	static inline Texture2D texMap;
	static inline Image imgMap;
	static inline Frustum frustum;
	static void DrawMode7Line(int y, Vector2 position);
public:
	static void Load();
	static void Update();
	static void Draw(Vector2 position );
	static void unload();

};