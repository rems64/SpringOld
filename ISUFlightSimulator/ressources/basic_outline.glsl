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

uniform isampler2D u_indices;
uniform int u_index;


uniform vec3 u_camera_location;

void main()
{
    float offset = 0.002;
    int right   = int(texture(u_indices, vec2(UV.x + offset, UV.y)).r == u_index);
    int left    = int(texture(u_indices, vec2(UV.x - offset, UV.y)).r == u_index);
    int bottom  = int(texture(u_indices, vec2(UV.x, UV.y + offset)).r == u_index);
    int top     = int(texture(u_indices, vec2(UV.x, UV.y - offset)).r == u_index);
    int sum = right + left + bottom + top;

    int indice = texture(u_indices, vec2(UV.x + offset, UV.y)).r + texture(u_indices, vec2(UV.x - offset, UV.y)).r + texture(u_indices, vec2(UV.x, UV.y + offset)).r + texture(u_indices, vec2(UV.x, UV.y + offset)).r;
    if(sum>1 && sum<4)
    {
        color = vec4(1.0, 0.7, 0.0, 1.0);
    }
    else
    {
        color = vec4(0.0, 0.0, 0.0, 0.0);
    }
}