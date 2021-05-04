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

out vec3 normal;

void main()
{
    gl_Position = u_projection * vec4(vertex_modelspace, 1.0);
    normal = normal_modelspace;
};

//shader geometry
#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in vec3 normal[];
const float mag = 0.1f;

uniform mat4 u_projection;

void main()
{
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + u_projection * (vec4(normal[0], 0.0)*mag);
    EmitVertex();

    EndPrimitive();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + u_projection * (vec4(normal[1], 0.0)*mag);
    EmitVertex();

    EndPrimitive();

    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position + u_projection * (vec4(normal[2], 0.0)*mag);
    EmitVertex();

    EndPrimitive();
}


//shader fragment
#version 330 core
out vec4 color;

void main()
{
    color = vec4(.137, .380, .867, 1.0);
}