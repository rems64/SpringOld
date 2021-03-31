//shader vertex
#version 330 core
layout (location = 0) in vec3 vertex_modelspace;
layout (location = 1) in vec3 normal_modelspace;
layout (location = 2) in vec2 uvs_in;

uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * vec4(vertex_modelspace, 1.0);
};


//shader fragment
#version 330 core
out vec4 color;

uniform vec3 u_diffuse_color;

void main()
{
    color = vec4(u_diffuse_color.xyz, 1.0);
}