#include <stdio.h>

#include "glad/glad.h"
#define GLFW_INCLUDE_GLEXT
#define NANOVG_GL3_IMPLEMENTATION
#include <GLFW/glfw3.h>
#include "nanovg.h"
#include "nanovg_gl.h"

int width = 640, height = 480;
int wwidth = 640, hheight = 480;
float pxratio = (float)wwidth/(float)width;


int main() {
    //init glfw
    if (!glfwInit())
        return 1;
    GLFWwindow* window = glfwCreateWindow(width, 480, "NanoVG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    //init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize OpenGL context\n");
        return 1;
    }

    //set glfw framebuffer resize callback to update global width and height variables
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
        glViewport(0, 0, w, h);
        width=w;
        height=h;
        pxratio = (float)wwidth/(float)width;
    });

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h) {
        glViewport(0, 0, w, h);
        wwidth=w;
        hheight=h;
        pxratio = (float)wwidth/(float)width;
        printf("pxratio%f\n",pxratio);
    });

    //init nanovg
    NVGcontext* vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
    if (vg == NULL) {
        printf("Could not init nanovg.\n");
        return -1;
    }

    // nvg load font /usr/share/fonts/droid/DroidSans.ttf
    if (nvgCreateFont(vg, "sans", "/usr/share/fonts/droid/DroidSans.ttf") == -1) {
        printf("Could not add font bold.\n");
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        //draw
        nvgBeginFrame(vg, width, height, pxratio);
        nvgBeginPath(vg);

        // Draw rectangle
        nvgRect(vg, 0, 0, 100, 100);
        nvgFillColor(vg, nvgRGBA(255, 0, 0, 255));
        nvgFill(vg);

        // draw Hello world at left upper corner with white color
        nvgFontFace(vg, "sans");
        nvgFontSize(vg, 12.0f);
        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
        nvgText(vg, 0, 0, "Hello World", NULL);
        // draw a red rectangle at (100, 100) with width 100 and height 100
        nvgEndFrame(vg);
        glfwSwapBuffers(window);
        glfwPollEvents();
        //clean up
    }
    nvgDeleteGL3(vg);
    glfwTerminate();
    return 0;
}
