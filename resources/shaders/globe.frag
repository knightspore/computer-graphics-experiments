#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;
out vec4 finalColor;

uniform mat4 matModel;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    // Textures
    vec4 color = texture(texture0, fragTexCoord);
    vec4 specular = texture(texture1, fragTexCoord);
    vec4 normal = texture(texture2, fragTexCoord);

    // Lighting
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 worldNormal = normalize(mat3(matModel) * fragNormal);
    vec3 lightDir = normalize(vec3(-200.0, 100.0, 0.0));

    float diffuse = max(dot(worldNormal, lightDir), 0.00); // diffuse w ambient minimum

    float specularStrength = pow(max(dot(reflect(-lightDir, worldNormal), worldNormal), 0.0), 4096.0); // shininess
    vec3 specularColor = specular.rgb * specularStrength;

    vec3 diff = diffuse * lightColor * color.rgb + specularColor;

    // Final FinalColor
    finalColor = vec4(diff, 1.0);
}
