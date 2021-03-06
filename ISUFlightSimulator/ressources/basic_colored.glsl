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

void main()
{
    gl_Position = u_projection * vec4(vertex_modelspace, 1.0);
    UV = uvs_in;
    vertex_worldspace = (u_model * vec4(vertex_modelspace, 1.0)).xyz;
    normal_worldspace    = normalize(vec3(u_model * vec4(normal_modelspace,    0.0)));
};

//shader fragment
#version 330 core
layout (location = 0) out vec4 color;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec3 position;
layout (location = 3) out vec4 specular;
layout (location = 4) out int index;

in vec2 UV;
in vec3 vertex_worldspace;
in vec3 normal_worldspace;

uniform int u_index;
uniform sampler2D u_diffuse_texture;
uniform sampler2D u_normal_texture;

void main()
{
    color = texture(u_diffuse_texture, UV);
    normal = normal_worldspace;
    position = vertex_worldspace;
    specular = vec4(1.0, 0.0, 0.0, 0.0);
    index = u_index;
}