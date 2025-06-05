#include "newmapGen.h"
#include "Setting.h"
#include "Mode7.h"

void newMapGen::LoadTextures()
{
	shadow_for_tree1_tex = LoadTexture("Assets/MapGen/tree1shadow.png");
	shadow_for_tree2_tex = LoadTexture("Assets/MapGen/tree1shadow.png");
	chasm_tex            = LoadTexture("Assets/MapGen/tree1shadow.png");
	shadow_for_pole_tex  = LoadTexture("Assets/MapGen/tree1shadow.png");


	snow_texture = LoadTexture("Assets/MapGen/snow_texture.png");
}

void newMapGen::generatesnowTexture()
{
	RenderTexture2D target = LoadRenderTexture(2000, 2000);
	BeginTextureMode(target);
	
	//int ichasm_1 = GetRandomValue(3, 7);
	int itree_1;
	int itree_2;

	switch (Mode7::current_difficulty) {
		case Difficulty::Easy:
			itree_1 = GetRandomValue(1, 4);
			itree_2 = GetRandomValue(1, 4);
			break;
		case Difficulty::Normal:
			itree_1 = GetRandomValue(3, 7);
			itree_2 = GetRandomValue(3, 7);
			break;
		case Difficulty::Hard:
			itree_1 = GetRandomValue(5, 10);
			itree_2 = GetRandomValue(5, 10);
			break;
		default:
			itree_1 = GetRandomValue(3, 7);
			itree_2 = GetRandomValue(3, 7);
			break;
	}
	//int ipole_1 = GetRandomValue(3, 7);
	
	DrawTexture(snow_texture,0,0,WHITE);

	for (int i = 0; i < itree_1;i++)
	{
		Math::vec2 textureposition = { (float)GetRandomValue(50,1950),(float)GetRandomValue(50,1950) };
		DrawTextureV(shadow_for_tree1_tex, { (float)textureposition.x,(float)textureposition.y }, WHITE);
		
		mapsprites.insert({ textureposition, { tree1,false } });
	}
	for (int i = 0; i < itree_2;i++)
	{
		Math::vec2 textureposition = { (float)GetRandomValue(50,1950),(float)GetRandomValue(50,1950) };
		DrawTextureV(shadow_for_tree2_tex, { (float)textureposition.x,(float)textureposition.y }, WHITE);
		mapsprites.insert({ textureposition, { tree2,false } });

	}/*
	for (int i = 0; i < ipole_1;i++)
	{
		Math::vec2 textureposition = { (float)GetRandomValue(50,1950),(float)GetRandomValue(50,1950) };
		DrawTextureV(shadow_for_pole_tex, { (float)textureposition.x,(float)textureposition.y }, WHITE);
		mapsprites.insert({ textureposition, { pole,false } });

	}
	for (int i = 0; i < ichasm_1;i++)
	{
		Math::vec2 textureposition = { (float)GetRandomValue(50,1950),(float)GetRandomValue(50,1950) };
		DrawTextureV(chasm_tex, { (float)textureposition.x,(float)textureposition.y }, WHITE);
		mapsprites.insert({ textureposition, { chasm,false } });


	}*/



	EndTextureMode();

	Image image = LoadImageFromTexture(target.texture);
	ExportImage(image, "CreatedMap.png");
}

//void newMapGen::drawFallingSnow()
//{
//}
//
//bool newMapGen::is_in_buffer(int x, int y)
//{
//	x;y;
//}
