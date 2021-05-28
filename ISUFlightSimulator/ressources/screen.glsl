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
out vec4 color;

in vec2 UV;

uniform sampler2D u_framebuffer;

void main()
{
    color = vec4(1.0) - texture(u_framebuffer, UV);
}