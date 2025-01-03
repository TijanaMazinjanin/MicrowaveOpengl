#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "microwave.h"
#include "resource_manager.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

const unsigned int SCREEN_WIDTH = 1200;
const unsigned int SCREEN_HEIGHT = 800;

Microwave MicrowaveProgram(SCREEN_WIDTH, SCREEN_HEIGHT);

const float targetFPS = 60.0f;
const float frameTime = 1.0f / targetFPS;


int main() {

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW! :(\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Microwave", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to initialize Window! :(\n";
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    MicrowaveProgram.Init();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        MicrowaveProgram.ProcessInput(deltaTime);

        MicrowaveProgram.Update(deltaTime);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        MicrowaveProgram.Render();

        glfwSwapBuffers(window);

        auto frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> frameDuration = frameEnd - frameStart;

        if (frameDuration.count() < frameTime) {
            std::this_thread::sleep_for(std::chrono::duration<float>(frameTime - frameDuration.count()));
        }
    }


    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            MicrowaveProgram.Keys[key] = true;
        else if (action == GLFW_RELEASE)
            MicrowaveProgram.Keys[key] = false;
    }


}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            MicrowaveProgram.ProcessMouseButtonPressed(xpos, ypos);
            
        }
        
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}