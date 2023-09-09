#include <stdio.h>

#include <string>
#include <iostream>
#include <sstream>

#include <xkbcommon/xkbcommon.h>

#include "glad/glad.h"
#define GLFW_INCLUDE_GLEXT
#define NANOVG_GL3_IMPLEMENTATION
#include <GLFW/glfw3.h>
#include "nanovg.h"
#include "nanovg_gl.h"

#include "args.h"
#include "file_parse.h"
#include "edit_view.h"
#include "cursor.h"


void print_key(int key);


int fb_width = 640, fb_height = 480;
int wwidth = 640, hheight = 480;
// float pxratio = (float)wwidth/(float)width;
FILE *fd;

struct WindowContainer  {
    EditView *edit_view;
    struct xkb_context *xkb_ctx;
    struct xkb_state *xkb_state;
} window_container;

int main(int argc, char **argv) {
    /** Initialize an Xkeyboard context */
    struct xkb_context *xkb_ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    struct xkb_keymap  *keymap = xkb_keymap_new_from_names(xkb_ctx, nullptr, XKB_KEYMAP_COMPILE_NO_FLAGS);
    struct xkb_state* xkb_state = xkb_state_new(keymap);
    window_container.xkb_ctx = xkb_ctx;
    window_container.xkb_state = xkb_state;

    /** GUI Initialization **/

    if (!glfwInit())
        return 1;
    GLFWwindow* window = glfwCreateWindow(fb_width, 480, "NanoVG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return 1;
    }

    glfwSetWindowUserPointer(window, (void*)&window_container);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize OpenGL context\n");
        return 1;
    }

    NVGcontext* vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
    if (vg == NULL) {
        printf("Could not init nanovg.\n");
        return -1;
    }

    /** Instantiate classes **/
    EditView edit_view(vg);
    window_container.edit_view = &edit_view;

    /** Register callbacks **/

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
        glViewport(0, 0, w, h);
        fb_width=w;
        fb_height=h;
    });

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h) {
        wwidth=w;
        hheight=h;
    });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        struct WindowContainer *wc = (struct WindowContainer *)glfwGetWindowUserPointer(window);

        // Translate GLFW key code to XKB key code
        xkb_keycode_t xkb_key = key-27;
        xkb_state_update_key(wc->xkb_state, xkb_key, action == GLFW_PRESS ? XKB_KEY_DOWN : XKB_KEY_UP);
        xkb_keysym_t sym = xkb_state_key_get_one_sym(wc->xkb_state, xkb_key);
        char keyString[32];
        xkb_keysym_get_name(sym, keyString, 32*sizeof(char));
        printf("%4d\t%4d\t%4d\t%4d\n", key, scancode, action, mods);
        print_key(key);
        if (
            (
                (key >= 'A' && key <= 'Z') ||
                (key == ' ')
            ) &&
            (action == 1)
           ) {
                wc->edit_view->putc(key);
        }

    });

/** NanoVG load font /usr/share/fonts/droid/DroidSans.ttf **/
    if (nvgCreateFont(vg, "sans", "/usr/share/fonts/droid/DroidSans.ttf") == -1) {
        printf("Could not add font\n");
        return -1;
    }

    /** Main Loop **/
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        //draw
        nvgBeginFrame(vg, fb_width, fb_height, (float)fb_width/wwidth);
            edit_view.draw_text();
        nvgEndFrame(vg);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //clean up
    nvgDeleteGL3(vg);
    glfwTerminate();
    return 0;
}

/**
 * 50 es m y m es 77
 * */


void print_key(int key) {
    switch (key) {
        case GLFW_KEY_GRAVE_ACCENT:
            printf("GLFW_KEY_GRAVE_ACCENT\n");
            break;
        case GLFW_KEY_1:
            printf("GLFW_KEY_1\n");
            break;
        case GLFW_KEY_2:
            printf("GLFW_KEY_2\n");
            break;
        case GLFW_KEY_3:
            printf("GLFW_KEY_3\n");
            break;
        case GLFW_KEY_4:
            printf("GLFW_KEY_4\n");
            break;
        case GLFW_KEY_5:
            printf("GLFW_KEY_5\n");
            break;
        case GLFW_KEY_6:
            printf("GLFW_KEY_6\n");
            break;
        case GLFW_KEY_7:
            printf("GLFW_KEY_7\n");
            break;
        case GLFW_KEY_8:
            printf("GLFW_KEY_8\n");
            break;
        case GLFW_KEY_9:
            printf("GLFW_KEY_9\n");
            break;
        case GLFW_KEY_0:
            printf("GLFW_KEY_0\n");
            break;
        case GLFW_KEY_SPACE:
            printf("GLFW_KEY_SPACE\n");
            break;
        case GLFW_KEY_MINUS:
            printf("GLFW_KEY_MINUS\n");
            break;
        case GLFW_KEY_EQUAL:
            printf("GLFW_KEY_EQUAL\n");
            break;
        case GLFW_KEY_Q:
            printf("GLFW_KEY_Q\n");
            break;
        case GLFW_KEY_W:
            printf("GLFW_KEY_W\n");
            break;
        case GLFW_KEY_E:
            printf("GLFW_KEY_E\n");
            break;
        case GLFW_KEY_R:
            printf("GLFW_KEY_R\n");
            break;
        case GLFW_KEY_T:
            printf("GLFW_KEY_T\n");
            break;
        case GLFW_KEY_Y:
            printf("GLFW_KEY_Y\n");
            break;
        case GLFW_KEY_U:
            printf("GLFW_KEY_U\n");
            break;
        case GLFW_KEY_I:
            printf("GLFW_KEY_I\n");
            break;
        case GLFW_KEY_O:
            printf("GLFW_KEY_O\n");
            break;
        case GLFW_KEY_P:
            printf("GLFW_KEY_P\n");
            break;
        case GLFW_KEY_LEFT_BRACKET:
            printf("GLFW_KEY_LEFT_BRACKET\n");
            break;
        case GLFW_KEY_RIGHT_BRACKET:
            printf("GLFW_KEY_RIGHT_BRACKET\n");
            break;
        case GLFW_KEY_A:
            printf("GLFW_KEY_A\n");
            break;
        case GLFW_KEY_S:
            printf("GLFW_KEY_S\n");
            break;
        case GLFW_KEY_D:
            printf("GLFW_KEY_D\n");
            break;
        case GLFW_KEY_F:
            printf("GLFW_KEY_F\n");
            break;
        case GLFW_KEY_G:
            printf("GLFW_KEY_G\n");
            break;
        case GLFW_KEY_H:
            printf("GLFW_KEY_H\n");
            break;
        case GLFW_KEY_J:
            printf("GLFW_KEY_J\n");
            break;
        case GLFW_KEY_K:
            printf("GLFW_KEY_K\n");
            break;
        case GLFW_KEY_L:
            printf("GLFW_KEY_L\n");
            break;
        case GLFW_KEY_SEMICOLON:
            printf("GLFW_KEY_SEMICOLON\n");
            break;
        case GLFW_KEY_APOSTROPHE:
            printf("GLFW_KEY_APOSTROPHE\n");
            break;
        case GLFW_KEY_Z:
            printf("GLFW_KEY_Z\n");
            break;
        case GLFW_KEY_X:
            printf("GLFW_KEY_X\n");
            break;
        case GLFW_KEY_C:
            printf("GLFW_KEY_C\n");
            break;
        case GLFW_KEY_V:
            printf("GLFW_KEY_V\n");
            break;
        case GLFW_KEY_B:
            printf("GLFW_KEY_B\n");
            break;
        case GLFW_KEY_N:
            printf("GLFW_KEY_N\n");
            break;
        case GLFW_KEY_M:
            printf("GLFW_KEY_M\n");
            break;
        case GLFW_KEY_COMMA:
            printf("GLFW_KEY_COMMA\n");
            break;
        case GLFW_KEY_PERIOD:
            printf("GLFW_KEY_PERIOD\n");
            break;
        case GLFW_KEY_SLASH:
            printf("GLFW_KEY_SLASH\n");
            break;
        case GLFW_KEY_BACKSLASH:
            printf("GLFW_KEY_BACKSLASH\n");
            break;
        case GLFW_KEY_ESCAPE:
            printf("GLFW_KEY_ESCAPE\n");
            break;
        case GLFW_KEY_TAB:
            printf("GLFW_KEY_TAB\n");
            break;
        case GLFW_KEY_LEFT_SHIFT:
            printf("GLFW_KEY_LEFT_SHIFT\n");
            break;
        case GLFW_KEY_RIGHT_SHIFT:
            printf("GLFW_KEY_RIGHT_SHIFT\n");
            break;
        case GLFW_KEY_LEFT_CONTROL:
            printf("GLFW_KEY_LEFT_CONTROL\n");
            break;
        case GLFW_KEY_RIGHT_CONTROL:
            printf("GLFW_KEY_RIGHT_CONTROL\n");
            break;
        case GLFW_KEY_LEFT_ALT:
            printf("GLFW_KEY_LEFT_ALT\n");
            break;
        case GLFW_KEY_RIGHT_ALT:
            printf("GLFW_KEY_RIGHT_ALT\n");
            break;
        case GLFW_KEY_LEFT_SUPER:
            printf("GLFW_KEY_LEFT_SUPER\n");
            break;
        case GLFW_KEY_RIGHT_SUPER:
            printf("GLFW_KEY_RIGHT_SUPER\n");
            break;
        case GLFW_KEY_MENU:
            printf("GLFW_KEY_MENU\n");
            break;
        case GLFW_KEY_NUM_LOCK:
            printf("GLFW_KEY_NUM_LOCK\n");
            break;
        case GLFW_KEY_CAPS_LOCK:
            printf("GLFW_KEY_CAPS_LOCK\n");
            break;
        case GLFW_KEY_PRINT_SCREEN:
            printf("GLFW_KEY_PRINT_SCREEN\n");
            break;
        case GLFW_KEY_SCROLL_LOCK:
            printf("GLFW_KEY_SCROLL_LOCK\n");
            break;
        case GLFW_KEY_PAUSE:
            printf("GLFW_KEY_PAUSE\n");
            break;
        case GLFW_KEY_DELETE:
            printf("GLFW_KEY_DELETE\n");
            break;
        case GLFW_KEY_BACKSPACE:
            printf("GLFW_KEY_BACKSPACE\n");
            break;
        case GLFW_KEY_ENTER:
            printf("GLFW_KEY_ENTER\n");
            break;
        case GLFW_KEY_HOME:
            printf("GLFW_KEY_HOME\n");
            break;
        case GLFW_KEY_END:
            printf("GLFW_KEY_END\n");
            break;
        case GLFW_KEY_PAGE_UP:
            printf("GLFW_KEY_PAGE_UP\n");
            break;
        case GLFW_KEY_PAGE_DOWN:
            printf("GLFW_KEY_PAGE_DOWN\n");
            break;
        case GLFW_KEY_INSERT:
            printf("GLFW_KEY_INSERT\n");
            break;
        case GLFW_KEY_LEFT:
            printf("GLFW_KEY_LEFT\n");
            break;
        case GLFW_KEY_RIGHT:
            printf("GLFW_KEY_RIGHT\n");
            break;
        case GLFW_KEY_DOWN:
            printf("GLFW_KEY_DOWN\n");
            break;
        case GLFW_KEY_UP:
            printf("GLFW_KEY_UP\n");
            break;
        case GLFW_KEY_F1:
            printf("GLFW_KEY_F1\n");
            break;
        case GLFW_KEY_F2:
            printf("GLFW_KEY_F2\n");
            break;
        case GLFW_KEY_F3:
            printf("GLFW_KEY_F3\n");
            break;
        case GLFW_KEY_F4:
            printf("GLFW_KEY_F4\n");
            break;
        case GLFW_KEY_F5:
            printf("GLFW_KEY_F5\n");
            break;
        case GLFW_KEY_F6:
            printf("GLFW_KEY_F6\n");
            break;
        case GLFW_KEY_F7:
            printf("GLFW_KEY_F7\n");
            break;
        case GLFW_KEY_F8:
            printf("GLFW_KEY_F8\n");
            break;
        case GLFW_KEY_F9:
            printf("GLFW_KEY_F9\n");
            break;
        case GLFW_KEY_F10:
            printf("GLFW_KEY_F10\n");
            break;
        case GLFW_KEY_F11:
            printf("GLFW_KEY_F11\n");
            break;
        case GLFW_KEY_F12:
            printf("GLFW_KEY_F12\n");
            break;
        case GLFW_KEY_F13:
            printf("GLFW_KEY_F13\n");
            break;
        case GLFW_KEY_F14:
            printf("GLFW_KEY_F14\n");
            break;
        case GLFW_KEY_F15:
            printf("GLFW_KEY_F15\n");
            break;
        case GLFW_KEY_F16:
            printf("GLFW_KEY_F16\n");
            break;
        case GLFW_KEY_F17:
            printf("GLFW_KEY_F17\n");
            break;
        case GLFW_KEY_F18:
            printf("GLFW_KEY_F18\n");
            break;
        case GLFW_KEY_F19:
            printf("GLFW_KEY_F19\n");
            break;
        case GLFW_KEY_F20:
            printf("GLFW_KEY_F20\n");
            break;
        case GLFW_KEY_F21:
            printf("GLFW_KEY_F21\n");
            break;
        case GLFW_KEY_F22:
            printf("GLFW_KEY_F22\n");
            break;
        case GLFW_KEY_F23:
            printf("GLFW_KEY_F23\n");
            break;
        case GLFW_KEY_F24:
            printf("GLFW_KEY_F24\n");
            break;
        case GLFW_KEY_KP_DIVIDE:
            printf("GLFW_KEY_KP_DIVIDE\n");
            break;
        case GLFW_KEY_KP_MULTIPLY:
            printf("GLFW_KEY_KP_MULTIPLY\n");
            break;
        case GLFW_KEY_KP_SUBTRACT:
            printf("GLFW_KEY_KP_SUBTRACT\n");
            break;
        case GLFW_KEY_KP_ADD:
            printf("GLFW_KEY_KP_ADD\n");
            break;
        case GLFW_KEY_KP_0:
            printf("GLFW_KEY_KP_0\n");
            break;
        case GLFW_KEY_KP_1:
            printf("GLFW_KEY_KP_1\n");
            break;
        case GLFW_KEY_KP_2:
            printf("GLFW_KEY_KP_2\n");
            break;
        case GLFW_KEY_KP_3:
            printf("GLFW_KEY_KP_3\n");
            break;
        case GLFW_KEY_KP_4:
            printf("GLFW_KEY_KP_4\n");
            break;
        case GLFW_KEY_KP_5:
            printf("GLFW_KEY_KP_5\n");
            break;
        case GLFW_KEY_KP_6:
            printf("GLFW_KEY_KP_6\n");
            break;
        case GLFW_KEY_KP_7:
            printf("GLFW_KEY_KP_7\n");
            break;
        case GLFW_KEY_KP_8:
            printf("GLFW_KEY_KP_8\n");
            break;
        case GLFW_KEY_KP_9:
            printf("GLFW_KEY_KP_9\n");
            break;
        case GLFW_KEY_KP_DECIMAL:
            printf("GLFW_KEY_KP_DECIMAL\n");
            break;
        case GLFW_KEY_KP_EQUAL:
            printf("GLFW_KEY_KP_EQUAL\n");
            break;
        case GLFW_KEY_KP_ENTER:
            printf("GLFW_KEY_KP_ENTER\n");
            break;
        case GLFW_KEY_WORLD_2:
            printf("GLFW_KEY_WORLD_2\n");
            break;
        }
}
