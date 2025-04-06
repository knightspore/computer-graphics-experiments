#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;
out vec4 finalColor;

uniform mat4 matModel;
uniform mat4 matView;

void main() {
    // Get world normal for Sphere (ie. non-rotating)
    vec3 worldNormal = normalize(mat3(matModel) * fragNormal);

    // Set light source direction
    vec3 lightDir = normalize(vec3(-200.0, 100.0, 0.0));

    // Set light intensity + ambient light
    float diff = max(dot(worldNormal, lightDir), 0.05);

    // Paint the globe with the normal, with a light source
    finalColor = vec4(fragNormal + fragColor.rgb, 1.0);
    finalColor.rgb *= diff;
}
