//shader vertex
#version 330 core
layout (location = 0) in vec3 vertex_modelspace;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec4 positionScale;

uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 UV;

void main()
{
    //vec4 tempPos = u_projection * vec4((vertex_modelspace*positionScale.w)+positionScale.xyz, 1.0);
    //tempPos /= tempPos.w;
    vec3 cameraRight_worldspace =   vec3(u_view[0][0], u_view[1][0], u_view[2][0]);
    vec3 cameraUp_worldspace    =   vec3(u_view[0][1], u_view[1][1], u_view[2][1]);
    vec3 tempPos = positionScale.xyz + cameraRight_worldspace * vertex_modelspace.x * positionScale.w + cameraUp_worldspace * vertex_modelspace.y * positionScale.w;
    gl_Position = u_projection * vec4(tempPos, 1.0);
    UV = uvs;
};


//shader fragment
#version 330 core
layout (location = 0) out vec4 color;
layout (location = 1) out int index;
in vec2 UV;

uniform vec3 u_diffuse_color;
uniform sampler2D u_diffuse_texture;
uniform int u_index;

void main()
{
    color = texture(u_diffuse_texture, UV);
    index = u_index;
    //color = vec4(gl_FragCoord.z, 0.0, 0.0, 1.0);
}