#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;
out vec4 finalColor;

uniform mat4 matModel;
uniform mat4 matView;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    // Textures
    vec4 color = texture(texture0, fragTexCoord);
    vec4 specular = texture(texture1, fragTexCoord);
    vec4 normal = vec4(normalize(texture(texture2, fragTexCoord) * 2.0 - 1.0).rgb, 0.0);

    // Lighting
    vec3 worldNormal = normalize(mat3(matModel) * fragNormal);
    vec3 lightDir = normalize(vec3(-200.0, 100.0, 0.0));
    float diff = max(dot(worldNormal, lightDir), 0.08);

    finalColor = vec4(diff * color.rgb, 1.0) ;
}
