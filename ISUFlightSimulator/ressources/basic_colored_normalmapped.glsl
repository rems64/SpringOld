//shader vertex
#version 330 core
layout (location = 0) in vec3 vertex_modelspace;
layout (location = 1) in vec3 normal_modelspace;
layout (location = 2) in vec2 uvs_in;
layout (location = 3) in vec3 tangent_modelspace;
layout (location = 4) in vec3 bitangent_modelspace;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

out vec2 UV;
out vec3 vertex_worldspace;
out vec3 vertex_cameraspace;
out vec3 normal_worldspace;
out vec3 normal;
out mat3 tbn_matrix;

void main()
{
    gl_Position = u_projection * vec4(vertex_modelspace, 1.0);
    UV = uvs_in;
    vertex_worldspace = (u_model * vec4(vertex_modelspace, 1.0)).xyz;
    vertex_cameraspace = (u_view * vec4(vertex_worldspace, 1.0)).xyz;

    vec3 tangent_worldspace   = normalize(vec3(u_model * vec4(tangent_modelspace,   0.0)));
    vec3 bitangent_worldspace = normalize(vec3(u_model * vec4(bitangent_modelspace, 0.0)));
    normal_worldspace    = normalize(vec3(u_model * vec4(normal_modelspace,    0.0)));
    tbn_matrix = mat3(tangent_worldspace, bitangent_worldspace, normal_worldspace);
    normal = normal_modelspace;
};

//shader fragment
#version 330 core
out vec4 color;
in vec2 UV;
in vec3 vertex_worldspace;
in vec3 vertex_cameraspace;
in vec3 normal_worldspace;
in mat3 tbn_matrix;


uniform vec3 u_diffuse_color;
uniform sampler2D u_diffuse_texture;
uniform sampler2D u_normal_texture;

struct PointLight {
    vec3 position;
    vec3 color;
    float power;
};  
#define NBR_POINT_LIGHTS 8
uniform PointLight pointLights[NBR_POINT_LIGHTS];

const float ambientStrength = 0.8f;
const vec3 ambientColor = vec3(1.0, 1.0, 1.0);

void main()
{
    color = (texture(u_diffuse_texture, UV)*0.5 + vec4(u_diffuse_color.xyz, 1.0)) * vec4((ambientColor * ambientStrength), 1.0);
    vec3 texNormal = texture(u_normal_texture, UV).rgb;
    texNormal = texNormal * 2.0 - 1.0;  // From 0;1 to -1;1
    texNormal = normalize(tbn_matrix * texNormal);
    vec3 viewDir = normalize(vec3(0.0, 0.0, 6.0) - vertex_worldspace.xyz);
    //color = vec4(0.0, 0.0, 0.0, 1.0);
    //color = vec4(abs(normal).xyz, 1.0);
    for(int i = 0; i < NBR_POINT_LIGHTS; i++)
    {
        if(pointLights[i].power!=0.0)
        {
            vec3 lightDir = normalize(pointLights[i].position - vertex_worldspace.xyz);
            // diffuse shading
            float diff = max(dot(texNormal, lightDir), 0.0);

            vec3 reflectDir = reflect(-lightDir, texNormal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0.5);

            // combine results
            vec3 diffuse = pointLights[i].color * diff * texture(u_diffuse_texture, UV).xyz;
            vec3 specular = pointLights[i].color * spec;
            float dist = length(pointLights[i].position - vertex_worldspace.xyz);
            float attenuation = pointLights[i].power / dist;
            diffuse *= attenuation;
            specular *= attenuation;
            color += vec4(diffuse+specular, 0.0);
        }
    }
}