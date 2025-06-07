#version 330 core

// Input attributes from the vertex shader
in vec2 fragTexCoord;
in vec4 fragColor;

// Output color for the fragment
out vec4 finalColor;

// Uniforms passed from your C++ code
uniform sampler2D texture0; // This is your rendered scene
uniform float hillFactor;   // The value you control with 'I' and 'K' keys

void main()
{
    // Start with the original texture coordinates
    vec2 warpedCoords = fragTexCoord;

    // Calculate the horizontal distance from the center of the screen.
    // fragTexCoord.x ranges from 0.0 (left) to 1.0 (right).
    // We convert this to a -1.0 to 1.0 range to get a centered value.
    float centerOffset = fragTexCoord.x * 2.0 - 1.0;

    // Apply a parabolic curve to the vertical texture coordinate.
    // The (centerOffset * centerOffset) creates a curve that is lowest in the middle.
    // The 'hillFactor' controls the steepness of this curve.
    warpedCoords.y += hillFactor * (centerOffset * centerOffset);
    
    // Check if the new warped coordinate is still within the texture's bounds
    if (warpedCoords.y >= 0.0 && warpedCoords.y <= 1.0)
    {
        // If it is, sample the texture at the new, warped position
        finalColor = texture(texture0, warpedCoords) * fragColor;
    }
    else
    {
        // If the coordinate is outside the texture, make the pixel transparent.
        // This will happen at the top corners when the hill effect is strong.
        finalColor = vec4(0.0, 0.0, 0.0, 0.0);
    }
}