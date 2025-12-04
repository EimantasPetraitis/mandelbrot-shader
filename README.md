# mandelbrot-shader

A rendering of the Mandelbrot Set implemented in GLSL shaders.
Contrary to [my older Python implementation](https://github.com/EimantasPetraitis/mandelbrot-set), this one is much faster as it runs on the GPU,
and it no longer is just a static image (panning and zooming using the mouse is supported).

In the GLSL shader code complex numbers are implemented using 2x2 matrices:
a number $a + bi$ is represented by $\begin{pmatrix}a & -b\\b & a\end{pmatrix}$. Complex number addition and multiplication are replaced by matrix operations.

This project uses OpenGL with GLFW and GLEW.

## Building and Running

1. Build the project with CMake.
    ```bat
    cmake --build build --config Debug
    ```

2. Run ```build/Mandelbrot.exe``` with the Git root directory as the working directory.
    ```bat
    cd mandelbrot-shader
    start build/Mandelbrot.exe
    ```