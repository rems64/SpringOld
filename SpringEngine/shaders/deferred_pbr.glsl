//shader vertex
#version 330 core
layout (location = 0) in vec2 inputPosition;
layout (location = 1) in vec2 inputUv;

out vec2 UV;

void main()
{
    gl_Position = vec4(inputPosition.x, inputPosition.y, 1.0, 1.0);
    UV = inputUv;
};

//shader fragment
#version 330 core

const vec3 defaultColor = vec3(0, 0.74117647058, 0.26666666666);
const float pi = 3.14159265359;

struct PointLight {
    vec3 position;
    vec3 color;
    float power;
};

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float power;
};

float computeAttenuation(vec3 position, PointLight light)
{
    float dist = distance(position, light.position);
    return light.power / (dist*dist);
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

float distributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = pi * denom * denom;
	
    return num / denom;
}

float geometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}
float geometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = geometrySchlickGGX(NdotV, roughness);
    float ggx1  = geometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

#define NBR_POINT_LIGHTS 4
layout (location = 0) out vec4 color;

in vec2 UV;

uniform sampler2D u_color;
uniform sampler2D u_normal;
uniform sampler2D u_position;
uniform sampler2D u_metRough;

uniform vec3 u_cameraLocation_ws;
uniform PointLight u_pointLights[NBR_POINT_LIGHTS];
uniform DirectionalLight u_directionalLight;

void main()
{
    vec3 albedo      = texture(u_color, UV).rgb;
    vec3 position_ws = texture(u_position, UV).xyz;
    vec3 normal_ws   = texture(u_normal, UV).xyz;
    //float specularIn = texture(u_specMetRough, UV).r;
    float metallic   = texture(u_metRough, UV).r;
    float roughness  = texture(u_metRough, UV).g;
    //roughness = pow(2.0 / (2.0 + roughness/4), 0.5);
    vec3 viewRay_ws  = normalize(u_cameraLocation_ws - position_ws);

    vec3 Lo = vec3(0.0);
    for(int i=0; i<NBR_POINT_LIGHTS; i++)
    {
        vec3 lightRay_ws = normalize(u_pointLights[i].position - position_ws);
        vec3 halfRay_ws = normalize(viewRay_ws + lightRay_ws);
        vec3 radiance = u_pointLights[i].color * computeAttenuation(position_ws, u_pointLights[i]);

        // Not my code
        vec3 F0 = vec3(0.04);
        F0      = mix(F0, albedo, metallic);
        vec3 F  = fresnelSchlick(max(dot(halfRay_ws, viewRay_ws), 0.0), F0);

        float NDF = distributionGGX(normal_ws, halfRay_ws, roughness);
        float G   = geometrySmith(normal_ws, viewRay_ws, lightRay_ws, roughness);
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(normal_ws, viewRay_ws), 0.0) * max(dot(normal_ws, lightRay_ws), 0.0);
        vec3 specular     = numerator / max(denominator, 0.001);
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;
        float NdotL = max(dot(normal_ws, lightRay_ws), 0.0);
        Lo += vec3(kD * albedo / pi + specular) * radiance * NdotL;
    }

    //for(int i=0; i<1; i++)
    {
        vec3 lightRay_ws = normalize(u_directionalLight.direction);
        vec3 halfRay_ws = normalize(viewRay_ws + lightRay_ws);
        vec3 radiance = u_directionalLight.color;

        // Not my code
        vec3 F0 = vec3(0.04);
        F0      = mix(F0, albedo, metallic);
        vec3 F  = fresnelSchlick(max(dot(halfRay_ws, viewRay_ws), 0.0), F0);

        float NDF = distributionGGX(normal_ws, halfRay_ws, roughness);
        float G   = geometrySmith(normal_ws, viewRay_ws, lightRay_ws, roughness);
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(normal_ws, viewRay_ws), 0.0) * max(dot(normal_ws, lightRay_ws), 0.0);
        vec3 specular     = numerator / max(denominator, 0.001);
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;
        float NdotL = max(dot(normal_ws, lightRay_ws), 0.0);
        Lo += vec3(kD * albedo / pi + specular) * radiance * NdotL;
    }

    vec3 ambient = vec3(0.03) * albedo; //* ambient occlusion;
    color = vec4(ambient + Lo, 1.0);
}