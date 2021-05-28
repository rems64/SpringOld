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
layout (location = 0) out vec4 color;

in vec2 UV;

uniform sampler2D u_color;
uniform sampler2D u_normal;
uniform sampler2D u_position;
uniform sampler2D u_specular;


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
uniform mat4 u_directional_light_space;
uniform sampler2D directional_light_shadow_map;
#define NBR_POINT_LIGHTS 10
uniform PointLight pointLights[NBR_POINT_LIGHTS];

uniform vec3 u_camera_location;
uniform DirectionalLight u_directional_light;

#define NBR_SSAO_SAMPLES 64
uniform vec3 u_ssao_samples[NBR_SSAO_SAMPLES];
#define NBR_SSAO_RANDOM 4
uniform vec3 u_ssao_randoms[NBR_SSAO_RANDOM];
uniform mat4 u_V;
uniform mat4 u_P;
uniform mat4 u_VP;
uniform sampler2D u_camera_depth;
uniform float u_ssao_depth = 0.05f;

vec2 poissonDisk[16] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 ), 
   vec2( -0.91588581, 0.45771432 ), 
   vec2( -0.81544232, -0.87912464 ), 
   vec2( -0.38277543, 0.27676845 ), 
   vec2( 0.97484398, 0.75648379 ), 
   vec2( 0.44323325, -0.97511554 ), 
   vec2( 0.53742981, -0.47373420 ), 
   vec2( -0.26496911, -0.41893023 ), 
   vec2( 0.79197514, 0.19090188 ), 
   vec2( -0.24188840, 0.99706507 ), 
   vec2( -0.81409955, 0.91437590 ), 
   vec2( 0.19984126, 0.78641367 ), 
   vec2( 0.14383161, -0.14100790 ) 
);
float random(vec3 seed, int i)
{
    vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

float lerp(float t, float a, float b)
{
    return t*(b-a) + a;
}

void main()
{
    vec3 albedo             = texture(u_color, UV).rgb;
    vec3 normal             = normalize(texture(u_normal, UV).xyz);
    vec3 position           = texture(u_position, UV).xyz;
    vec3 position_viewspace = vec4(u_V * vec4(position, 1.0)).xyz;
    float specular          = texture(u_specular, UV).a;

    int noiseX              = int(gl_FragCoord.x - 0.5) % 4;
    int noiseY              = int(gl_FragCoord.y - 0.5) % 4;
    vec3 randVec            = u_ssao_randoms[noiseX + (noiseY * 4)];
    vec3 tangent            = normalize(randVec - normal * dot(randVec, normal));
    vec3 bitangent          = cross(normal, tangent);
    mat3 tbn                = mat3(tangent, bitangent, normal);


    vec3 lighting = albedo * 0.1;
    vec3 viewDir = normalize(u_camera_location - position);
    for(int i = 0; i < NBR_POINT_LIGHTS; ++i)
    {
        if(pointLights[i].power > 0.0)
        {
            vec3 lightDir = normalize(pointLights[i].position - position);
            // diffuse shading
            float diff = max(dot(normal, lightDir), 0.0);

            vec3 reflectDir = reflect(-lightDir, normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.5);

            // combine results
            vec3 diffuse = pointLights[i].color * diff * albedo;
            vec3 specular = pointLights[i].color * spec;
            float dist = length(pointLights[i].position - position);
            float attenuation = pointLights[i].power / dist;
            diffuse *= attenuation;
            specular *= attenuation;
            lighting += diffuse;
        }
    }

    // Directional light
    float shadow = 0.0f;
    if(u_directional_light.power!=0)
    {
        vec4 position_lightspace = u_directional_light_space * vec4(position, 1.0);
        vec3 projCoords = position_lightspace.xyz / position_lightspace.w;
        // transform to [0,1] range
        projCoords = projCoords * 0.5 + 0.5;
        // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
        // get depth of current fragment from light's perspective
        float currentDepth = projCoords.z;
        // check whether current frag pos is in shadow

        vec3 lightDir = normalize(-u_directional_light.direction);
        float diff = max(dot(normal, lightDir), 0.0);

        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.5);

        vec3 diffuse = u_directional_light.color * u_directional_light.power * diff * albedo;
        vec3 specular = u_directional_light.color * spec;

        float bias = max(0.1 * (1.0 - dot(normal, lightDir)), 0.005);
        for (int i=0;i<16;i++)
        {
            int index = int(16.0*random(floor(position.xyz*1000.0), i))%16;
            float closestDepth = texture(directional_light_shadow_map, projCoords.xy + poissonDisk[index]/700.0).r;
            shadow += currentDepth - bias > closestDepth ? 0.058823 : -0.058823;
        }
        shadow = clamp(shadow, 0.0, 1.0);

        lighting += diffuse * (1.0 - shadow);

        //lighting = vec3(currentDepth - closestDepth);
    }
    float ssao = 0.0f;
    for(int i = 0; i < NBR_SSAO_SAMPLES; ++i)
    {
        vec3 samplePos = tbn * u_ssao_samples[i];
        samplePos = position + samplePos * u_ssao_depth;

        vec4 offset = vec4(samplePos, 1.0);
        offset      = u_VP * offset;          // from view to clip-space
        offset.xyz /= offset.w;               // perspective divide
        offset.xyz  = offset.xyz * 0.5 + 0.5; // transform to range 0.0 - 1.0

        vec3 sampleDepthComps = texture(u_position, offset.xy).xyz;
        float sampleDepth = vec4(u_VP * vec4(sampleDepthComps, 1.0)).z;
        vec4 basePos = vec4(u_V * vec4(position, 1.0));
        float baseDepth   = vec3(basePos.xyz / basePos.w).z;
        ssao += (sampleDepth >= baseDepth ? 1.0 : 0.0);  
        ssao = samplePos.z;
    }
    //color = vec4(lighting, 1.0);
    color = vec4(vec3(ssao), 1.0);
}