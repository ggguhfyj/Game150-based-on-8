#pragma once
#include <raylib.h>
#include <raymath.h>
#include "..\Engine\Engine.h"
#include "mapGen.h"
#include "..\Game\newmapGen.h"
#include "..\Engine\Window.h"
#include <unordered_set>

class Mode7 {
private:
    // Camera frustum structure (defines viewing volume for mode7 effect)
    struct Frustum {
        Vector2 Far1;
        Vector2 Far2;
        Vector2 Near1;
        Vector2 Near2;
    };

    // --- Player and camera movement ---
    static inline float fRotationSpeed = 0.0f;      // Current rotation speed (radians/sec)
    static inline float fRotationAccel = 6.0f;      // Rotation acceleration
    static inline float fRotationDamping = 2.0f;    // Damping for rotation
    static inline float fMaxRotationSpeed = 1.8f;   // Maximum rotation speed
    static inline float fWorldX = 0.0f;             // Player world X position
    static inline float fWorldY = 0.0f;             // Player world Y position
    static inline float fWorldA = 0.0f;             // Player/view rotation angle
    static inline float fNear = -171;               // Near plane distance
    static inline float fFar = 28;                  // Far plane distance
    static inline float fFoVHalf = 1.3f;            // Half of field of view (radians)
    static inline float fSpeed = 200.0f;            // Current forward speed
    static inline float fMaxSpeed = 300.0f;         // Maximum forward speed
    static inline float fStartSpeed = 0.0f;         // Initial speed (unused)
    static inline float skyOffset = 0.0f;           // Sky scrolling offset

    // --- Rendering and window parameters ---
    static inline Vector2 windowsize = { 300,200 }; // Window (screen) size in pixels
    static inline Vector2 position = { 0,0 };       // Drawing start position

    // --- Textures and graphics assets ---
    static inline Texture2D texSky;                 // Sky background texture
    static inline Texture2D texMap;                 // Ground map texture
    static inline Texture2D windowtabs;             // Misc. UI asset
    static inline Texture2D trafficlightsTex;       // Traffic light/decoration texture
    static inline Texture2D player[6];              // Player sprite textures (side view)
    static inline Texture2D BWplayer[6];            // Black&White player textures
    static inline Texture2D VPplayer[6];            // Vaporwave player textures
    static inline Texture2D FovplayerRight[18];     // POV right hand frames
    static inline Texture2D FovplayerLeft[18];      // POV left hand frames
    static inline Texture2D trees[3];               // Tree textures
    static inline Image imgMap;                     // Map as image (for pixel access)

    static inline Frustum frustum;                  // View frustum for mode7 projection

    // --- Rendering helpers ---
    static void DrawMode7Line(int y);               // Draw a horizontal scanline (mode7 effect)
    static inline Color DrawFog(Color color);        // Draw fog/blend effect

    static inline const int blowup_scale = 4;       // Pixel upscaling for mode7 draw

    // --- Player animation ---
    static inline int playersprites = 3;            // Player sprite frame index
    static inline bool right;                       // Player facing direction
    static inline int counter = 0;                  // Animation counter

    // --- Fog/overlay colors ---
    static inline unsigned char R = 155;
    static inline unsigned char G = 155;
    static inline unsigned char B = 155;
    static inline unsigned char A = 100;
    static inline unsigned char BASE = 100;

    // --- Player screen and movement state ---
    static inline float fPlayerScreenX;             // Player X position on screen (for rendering)
    static inline float fPlayerHSpeed = 0.0f;       // Player horizontal speed (side movement)
    static inline float fPlayerHAccel = 300.0f;     // Player horizontal acceleration
    static inline float fPlayerHDamping = 200.0f;   // Damping for horizontal movement
    static inline float fMaxPlayerHSpeed = 200.0f;  // Max horizontal speed

    // --- Collision and effects ---
    static inline int tree_collision_count = 0;                     // Total tree collision count
    static inline std::unordered_set<Math::vec2> already_collided_trees; // Set of collided trees (legacy, not used in per-frame logic)
    static inline float screen_flash = 0.0f; // Red flash overlay effect (0: none, 1: max)
    static inline float fade_speed = 0.5f;

public:
    // Load all textures and initialize game state
    static void Load();
    // Main update logic (movement, collision, etc)
    static void Update();
    // Draw everything to the screen
    static void Draw();
    // Release all loaded resources
    static void unload();
    // Draw player sprite or animation
    static void DrawPlayer();
};
