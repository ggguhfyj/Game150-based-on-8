#pragma once

#include <vector>
#include <raylib.h>
#include <utility> // For std::pair
#include <unordered_map>
#include "..\Engine\Vec2.h"
#include <array>
#include <cstdio>
#include <iostream>
#include <memory> // fot std::hash
namespace std
{
	template <>
	struct hash<Math::vec2>
	{
		auto operator()(const Math::vec2& v) const -> size_t
		{
			return std::hash<float>{}((const float)v.x) ^ std::hash<float>{}((const float)v.y);
		}
	};
}


class newMapGen {
	enum spritetype {
		tree1,
		tree2,
		rails,
		pole,
		human,
		chasm

	};
	struct value {
		spritetype sprite;
		bool is_drawn;

	};
	static inline Texture2D shadow_for_tree1_tex;
	static inline Texture2D shadow_for_tree2_tex;
	static inline Texture2D chasm_tex;
	static inline Texture2D shadow_for_pole_tex;
	static inline Texture2D snow_texture;
	
public:
	
	static void LoadTextures();
	static void generatesnowTexture();
	//static  void drawFallingSnow();
	//static  bool is_in_buffer(int x, int y);
	
	static inline std::unordered_map<Math::vec2, value> mapsprites;
	//Math::vec2 is the key

};
//bool operator==(Math::vec2 a, Math::vec2 b) { return a.x == b.x && a.y == b.y; }
