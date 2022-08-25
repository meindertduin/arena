#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D baseTexture;
uniform vec3 viewPos;

struct Material {
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

#define MAX_DIR_LIGHTS 4
#define MAX_POINT_LIGHTS 8

layout (std140) uniform Lights {
    int dirLightsCount;
    DirLight dirLights[MAX_DIR_LIGHTS];
    int pointLightsCount;
    PointLight pointLights[MAX_POINT_LIGHTS];
};

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 pixel) {
    // ambient
    vec3 ambient = light.ambient * pixel;

    // diffuse
    vec3 pos = vec3(0, 2, 0);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * pixel;

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec;

    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

vec3 CalulateDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 pixel) {
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0f);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * pixel;
    vec3 diffuse = light.diffuse * diff * pixel;
    vec3 specular = light.specular * spec  * pixel;

    return (ambient + diffuse);
}

void main()
{
    vec3 texturePixel = vec3(texture(baseTexture, TexCoord));

    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result;
    for (int i = 0; i < dirLightsCount; i++) {
        result += CalulateDirLight(dirLights[i], normal, viewDir, texturePixel);
    }
    for (int i = 0; i < pointLightsCount; i++) {
        result += CalculatePointLight(pointLights[i], normal, viewDir, texturePixel);
    }

    FragColor = vec4(result, 1.0);
}


