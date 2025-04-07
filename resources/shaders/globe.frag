#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;
out vec4 finalColor;

uniform mat4 matModel;
uniform mat4 matView;
uniform sampler2D texture0;

void main() {

    // Lighting
    vec3 worldNormal = normalize(mat3(matModel) * fragNormal);
    vec3 lightDir = normalize(vec3(-200.0, 100.0, 0.0));
    vec3 lightColor = vec3(0.8, 0.6, 0.98);
    float diff = max(dot(worldNormal, lightDir), 0.08);

    vec4 texColor = texture(texture0, fragTexCoord);
    finalColor = vec4(texColor.rgb * diff, 1.0);
}
