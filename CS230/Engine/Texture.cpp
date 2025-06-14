/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/
#include "Texture.h"
#include "Engine.h"
#include <rlgl.h>

CS230::Texture::Texture(const std::filesystem::path& file_name) {
    texture = LoadTexture(file_name.string().c_str());
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
}

CS230::Texture::Texture(Texture2D given_texture) {
    texture = given_texture;
}

CS230::Texture::~Texture() {
    UnloadTexture(texture);
}

CS230::Texture::Texture(Texture&& temporary) noexcept : texture(temporary.texture) {
    temporary.texture.id = 0;
    temporary.texture.width = 0;
    temporary.texture.height = 0;
    temporary.texture.mipmaps = 0;
    temporary.texture.format = 0;
}

CS230::Texture& CS230::Texture::operator=(Texture&& temporary) noexcept {
    std::swap(texture.id, temporary.texture.id);
    std::swap(texture.width, temporary.texture.width);
    std::swap(texture.height, temporary.texture.height);
    std::swap(texture.mipmaps, temporary.texture.mipmaps);
    std::swap(texture.format, temporary.texture.format);
    return *this;
}

CS230::Texture::Texture() :texture({ 0 }) {}

void CS230::Texture::Draw(Math::TransformationMatrix display_matrix, unsigned int color) { // just a simplified call to the more verbose function
    Draw(display_matrix, { 0, 0 }, { texture.width, texture.height }, color);
}

void CS230::Texture::Draw(Math::TransformationMatrix display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size, unsigned int color) {


    const double render_height = rlGetFramebufferHeight(); //current frame buffer
    Math::vec2 bottom_left = display_matrix * Math::vec2{ 0, 0 };
    Math::vec2 bottom_right = display_matrix * Math::vec2{ double(frame_size.x), 0 };
    Math::vec2 top_left = display_matrix * Math::vec2{ 0, double(frame_size.y) };
    Math::vec2 top_right = display_matrix * Math::vec2{ double(frame_size.x), double(frame_size.y) };
    //four corners of the screen, stretched out and manipulated by the display matrix, position to be drawn to screen. change this for a mode 7 effect


    bottom_left.y = bottom_left.y * -1 + render_height;
    bottom_right.y = bottom_right.y * -1 + render_height;
    top_left.y = top_left.y * -1 + render_height;
    top_right.y = top_right.y * -1 + render_height;
    //some kind of translation


    const float left_u = float(texel_position.x) / float(texture.width);
    const float right_u = (float(texel_position.x) + frame_size.x) / float(texture.width);
    const float bottom_v = (float(texel_position.y) + frame_size.y) / float(texture.height);
    const float top_v = float(texel_position.y) / float(texture.height);
    //sample area. defined by the start point and the width of the texture

    rlSetTexture(texture.id);
    rlBegin(RL_QUADS);

    rlColor4ub(
        static_cast<unsigned char>((color & 0xFF000000) >> 24),
        static_cast<unsigned char>((color & 0x00FF0000) >> 16),
        static_cast<unsigned char>((color & 0x0000FF00) >> 8),
        static_cast<unsigned char>((color & 0x000000FF) >> 0));
    rlNormal3f(0.0f, 0.0f, 1.0f);

    rlTexCoord2f(left_u, top_v);
    rlVertex2f(float(top_left.x), float(top_left.y));

    rlTexCoord2f(left_u, bottom_v);
    rlVertex2f(float(bottom_left.x), float(bottom_left.y));

    rlTexCoord2f(right_u, bottom_v);
    rlVertex2f(float(bottom_right.x), float(bottom_right.y));

    rlTexCoord2f(right_u, top_v);
    rlVertex2f(float(top_right.x), float(top_right.y));

    rlEnd();
    rlSetTexture(0);
}

void CS230::Texture::DrawPerspective(Math::TransformationMatrix display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size, unsigned int color) {

    const double render_height = rlGetFramebufferHeight(); //current frame buffer
    Math::vec2 bottom_left = Math::vec2{ 0, 0 };
    Math::vec2 bottom_right =  Math::vec2{ double(frame_size.x), 0 };
    Math::vec2 top_left = Math::vec2{ 0, double(frame_size.y) };
    Math::vec2 top_right =  Math::vec2{ double(frame_size.x), double(frame_size.y) };
    //four corners of the screen, stretched out and manipulated by the display matrix, position to be drawn to screen. change this for a mode 7 effect


    bottom_left.y = bottom_left.y * -1 + render_height;
    bottom_right.y = bottom_right.y * -1 + render_height;
    top_left.y = top_left.y * -1 + render_height;
    top_right.y = top_right.y * -1 + render_height;
    //some kind of translation


     float left_u = float(texel_position.x) ;
     float right_u = (float(texel_position.x) + frame_size.x);
     float bottom_v = (float(texel_position.y) + frame_size.y) ;
     float top_v = float(texel_position.y) ;

     Math::vec2 offset = { 0.0, 0.0 }; //slanted effect

     Math::vec2 bottom_left_tex  = display_matrix * (Math::vec2{ left_u, bottom_v });
     Math::vec2 bottom_right_tex = display_matrix * (Math::vec2{ right_u, bottom_v } );
     Math::vec2 top_left_tex     = display_matrix  * (Math::vec2{ left_u, top_v } + offset);
     Math::vec2 top_right_tex  = display_matrix  * (Math::vec2{ right_u, top_v } - offset) ;

    //sample area. defined by the start point and the width of the texture

    rlSetTexture(texture.id);
    rlBegin(RL_QUADS);

    rlColor4ub(
        static_cast<unsigned char>((color & 0xFF000000) >> 24),
        static_cast<unsigned char>((color & 0x00FF0000) >> 16),
        static_cast<unsigned char>((color & 0x0000FF00) >> 8),
        static_cast<unsigned char>((color & 0x000000FF) >> 0));
    rlNormal3f(0.0f, 0.0f, 1.0f);

    rlTexCoord2f((float)top_left_tex.x/ float(texture.width), (float)top_left_tex.y / float(texture.height));
    rlVertex2f(float(top_left.x), float(top_left.y));

    //rlTexCoord2f(left_u, bottom_v);
    rlTexCoord2f((float)bottom_left_tex.x / float(texture.width), (float)bottom_left_tex.y / float(texture.height));
    rlVertex2f(float(bottom_left.x), float(bottom_left.y));
    
    //rlTexCoord2f(right_u, bottom_v);
    rlTexCoord2f((float)bottom_right_tex.x / float(texture.width), (float)bottom_right_tex.y / float(texture.height));
    rlVertex2f(float(bottom_right.x), float(bottom_right.y));

    //rlTexCoord2f(right_u, top_v);
    rlTexCoord2f((float)top_right_tex.x / float(texture.width), (float)top_right_tex.y / float(texture.height));
    rlVertex2f(float(top_right.x), float(top_right.y));

    rlEnd();
    rlSetTexture(0);
}


Math::ivec2 CS230::Texture::GetSize() const {
    return { texture.width, texture.height };
}
