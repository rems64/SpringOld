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
out mat3 tbn_matrix;

void main()
{
    gl_Position = u_projection * vec4(vertex_modelspace, 1.0);
    UV = uvs_in;
    vertex_worldspace = (u_model * vec4(vertex_modelspace, 1.0)).xyz;
    vertex_cameraspace = (u_view * vec4(vertex_worldspace, 1.0)).xyz;

    vec3 tangent_worldspace   = normalize(vec3(u_model * vec4(tangent_modelspace,   0.0)));
    vec3 bitangent_worldspace = normalize(vec3(u_model * vec4(bitangent_modelspace, 0.0)));
    normal_worldspace         = normalize(vec3(u_model * vec4(normal_modelspace,    0.0)));

    tbn_matrix = mat3(tangent_worldspace, -bitangent_worldspace, normal_worldspace);
};

//shader fragment
#version 330 core
//out vec4 color;
layout (location = 0) out vec4 color;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec3 position;
layout (location = 3) out vec4 metRough;
layout (location = 4) out int index;

in vec2 UV;
in vec3 vertex_worldspace;
in vec3 vertex_cameraspace;
in vec3 normal_worldspace;
in mat3 tbn_matrix;


uniform int u_index;
uniform sampler2D u_diffuse_texture;
uniform sampler2D u_normal_texture;
uniform sampler2D u_metallicTexture;
uniform sampler2D u_roughnessTexture;

uniform vec3 u_camera_location = vec3(0.0, 0.0, 6.0);

void main()
{
    vec3 texNormal = texture(u_normal_texture, UV).xyz;
    texNormal = normalize(texNormal * 2.0 - 1.0);  // From 0;1 to -1;1
    texNormal = normalize(tbn_matrix * texNormal);

    color = texture(u_diffuse_texture, UV);
    normal = texNormal;
    position = vertex_worldspace;
    metRough = vec4(texture(u_metallicTexture, UV).r, 1.0-texture(u_roughnessTexture, UV).r, 0.0, 0.0);
    index = u_index;
}