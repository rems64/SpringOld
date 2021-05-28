//shader vertex
#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 u_light_space;
uniform mat4 u_model_space;

void main()
{
    gl_Position = u_light_space * u_model_space * vec4(position, 1.0);
};

//shader fragment
#version 330 core
void main()
{
    // Only depth
}