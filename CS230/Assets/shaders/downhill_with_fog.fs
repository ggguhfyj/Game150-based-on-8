#version 330 core

// Input attributes from the vertex shader
in vec2 fragTexCoord;
in vec4 fragColor;

// Output color for the fragment
out vec4 finalColor;

// Uniforms passed from your C++ code
uniform sampler2D texture0; // This is your main scene texture
uniform float hillFactor;   // Controls the downhill curve
uniform vec4 fogColor;      // The color of the fog

void main()
{
    // --- Downhill Effect ---
    vec2 bentTexCoord = fragTexCoord;
    // Apply the bending effect only to the ground (the bottom half of the screen)
    if (bentTexCoord.y > 0.5) {
        // Remap the y-coordinate for the ground from [0.5, 1.0] to [0.0, 1.0]
        // to calculate the bend intensity.
        float bend = (1.0 - (bentTexCoord.y - 0.5) * 2.0) * hillFactor;

        // Apply the curve
        bentTexCoord.x = bentTexCoord.x - 0.5;
        bentTexCoord.x = bentTexCoord.x / (1.0 + bend);
        bentTexCoord.x = bentTexCoord.x + 0.5;
    }

    // Get the original color from the scene texture
    vec4 texelColor = texture(texture0, bentTexCoord);

    // --- Fog Effect ---
    float fogFactor = 0.0;
    // Apply fog only to the ground
    if (fragTexCoord.y > 0.5) {
        // Create a smooth gradient for the fog.
        // It's fully dense at the horizon (y=0.5) and fades out completely by y=0.8.
        fogFactor = 1.0 - smoothstep(0.5, 0.8, fragTexCoord.y);
    }

    // Blend the original texel color with the fog color
    finalColor = mix(texelColor, fogColor, fogFactor) * fragColor;
}