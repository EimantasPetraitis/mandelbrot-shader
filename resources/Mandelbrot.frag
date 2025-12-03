#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_coordinates;

void main()
{

    mat2 c = mat2(
        v_coordinates.x, v_coordinates.y, // first column
        -v_coordinates.y, v_coordinates.x
    );
    mat2 z = mat2(0.0, 0.0, 0.0, 0.0);

    for (int i = 0 ; i < 32 ; i++)
    {

        mat2 new_z = z*z + c;
        z = new_z;

        float sqrMagnitude = z[0][0]*z[0][0] + z[1][0]*z[1][0];
        if (sqrMagnitude >= 4)
        {
            color = vec4(0.0, 1.0, 1.0, 1.0);
            return;
        }
            
    }

    color = vec4(0.0, 0.0, 0.0, 1.0);

};