//shader vertex
#version 330 core
layout (location = 0) in vec3 vertex_modelspace;
layout (location = 1) in vec3 normal_modelspace;
layout (location = 2) in vec2 uvs_in;

uniform mat4 u_projection;
uniform mat4 u_modelprojection;
uniform mat4 u_viewprojection;
uniform vec3 u_lightposition;


out vec3 vertex_worldspace;
out vec3 vertex_cameraspace;
out vec3 eyedirection_cameraspace;
out vec3 lightposition_cameraspace;
out vec3 lightdirection_cameraspace;
out vec3 normals_modelspace;
out vec3 normal_cameraspace;
out vec3 lightposition_worldspace;

void main()
{
    gl_Position = u_projection * vec4(vertex_modelspace, 1.0);                                              // Output

    vertex_worldspace = (u_modelprojection * vec4(vertex_modelspace, 1.0)).xyz;                             // Position of the vertex in world space
    
    vertex_cameraspace = (u_viewprojection * vec4(vertex_worldspace, 1.0)).xyz;                             // Vector that goes from the vertex to the camera in camera space 
    eyedirection_cameraspace = vec3(0.,0.,0.) - vertex_cameraspace;

    lightposition_cameraspace = (u_viewprojection * vec4(u_lightposition,1.0)).xyz;
    lightdirection_cameraspace = eyedirection_cameraspace + lightposition_cameraspace;

    normals_modelspace = normal_modelspace;
    normal_cameraspace = (u_viewprojection * vec4(normal_modelspace,0)).xyz;

    lightposition_worldspace = u_lightposition;
};


//shader fragment
#version 330 core
out vec4 color;

in vec3 vertex_worldspace;
in vec3 vertex_cameraspace;


in vec3 eyedirection_cameraspace;
in vec3 lightposition_cameraspace;
in vec3 lightdirection_cameraspace;
in vec3 normals_modelspace;
in vec3 normal_cameraspace;

in vec3 lightposition_worldspace;

void main()
{
    vec3 norm = normalize(normals_modelspace);
    vec3 lightDir = normalize(lightposition_worldspace - vertex_worldspace);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);                                      // diff * lightColor
    vec3 result = (vec3(0.2, 0.2, 0.2) + diffuse) * vec3(1.0, 1.0, 1.0);            // (ambiant + diffuse) * objectColor
    color = vec4(result, 1.0);
}