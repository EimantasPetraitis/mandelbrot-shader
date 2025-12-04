#version 460 core

#define MAX_ITERATIONS 256

layout(location = 0) out vec4 color;

in vec2 v_Coordinates;

vec4 determineColor(
    int iterations, int maxIterations
)
{

    /* Determines the color of a pixel outside the Mandelbrot set
    based on the number of iterations needed to escape 
    (this method uses a simplified HSV to RGB calculation).
    */

    float h = 6 * float(iterations)/float(maxIterations);
    float x = h - int(h);

    if (h >= 0 && h < 1)
        return vec4(1.0, x, 0.0, 1.0);
    else if (h >= 1 && h < 2)
        return vec4(1.0-x, 1.0, 0.0, 1.0);
    else if (h >= 2 && h < 3)
        return vec4(0.0, 1.0, x, 1.0);
    else if (h >= 3 && h < 4)
        return vec4(0.0, 1.0-x, 1.0, 1.0);
    else if (h >= 4 && h < 5)
        return vec4(x, 0.0, 1.0, 1.0);
    else if (h >= 5)
        return vec4(1.0, 0.0, 1.0-x, 1.0);

}

void main()
{

    mat2 c = mat2(
        v_Coordinates.x, v_Coordinates.y, // first column
        -v_Coordinates.y, v_Coordinates.x
    );
    mat2 z = mat2(0.0, 0.0, 0.0, 0.0);

    for (int i = 0 ; i < MAX_ITERATIONS ; i++)
    {

        mat2 new_z = z*z + c;
        z = new_z;

        float sqrMagnitude = z[0][0]*z[0][0] + z[1][0]*z[1][0];
        if (sqrMagnitude >= 4)
        {
            color = determineColor(i, MAX_ITERATIONS);
            return;
        }
            
    }

    color = vec4(0.0, 0.0, 0.0, 1.0);

};