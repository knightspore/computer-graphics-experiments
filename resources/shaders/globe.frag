#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;
out vec4 finalColor;

uniform mat4 matModel;
uniform mat4 matView;
uniform sampler2D texture0;

void main() {
    vec4 texColor = texture(texture0, fragTexCoord);
    finalColor = texColor;
}

// Lighting experiments
// Get world normal for Sphere (ie. non-rotating)
// vec3 worldNormal = normalize(mat3(matModel) * fragNormal);
// Set light source direction
// vec3 lightDir = normalize(vec3(-200.0, 100.0, 0.0));
// Set light intensity + ambient light
// float diff = max(dot(worldNormal, lightDir), 0.05);
