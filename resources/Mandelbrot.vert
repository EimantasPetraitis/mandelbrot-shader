#version 460 core

layout(location = 0) in vec4 position;

out vec2 v_coordinates;

void main()
{

    gl_Position = position;
    v_coordinates = vec2(position);

};