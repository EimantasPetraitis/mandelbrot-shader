#version 460 core

layout(location = 0) in vec4 position;

uniform vec2 u_BoundsX;
uniform vec2 u_BoundsY;

out vec2 v_Coordinates;

void main()
{

    gl_Position = position;
    v_Coordinates = vec2(
        mix(u_BoundsX[0], u_BoundsX[1], position.x * 0.5 + 0.5),
        mix(u_BoundsY[0], u_BoundsY[1], position.y * 0.5 + 0.5)
    );

};