#include "newmapGen.h"

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
	int itree_1 =  GetRandomValue(3, 7);
	//int ipole_1 = GetRandomValue(3, 7);
	int itree_2 = GetRandomValue(3, 7);
	int pill1 = GetRandomValue (1,3);
	
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

	}
	for (int i = 0; i < pill1; i++)
	{
		Math::vec2 textureposition = { (float)GetRandomValue(50,1950),(float)GetRandomValue(50,1950) };

		mapsprites.insert({ textureposition, { pill,false } });
	}
	/*
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

	image = LoadImageFromTexture(target.texture);
	ExportImage(image, "CreatedMap.png");
}

void newMapGen::UnloadTexture()
{
	mapsprites.clear();
	UnloadImage(image);
}

//void newMapGen::drawFallingSnow()
//{
//}
//
//bool newMapGen::is_in_buffer(int x, int y)
//{
//	x;y;
//}
