#pragma once

#define GLFW_INCLUDE_VULKAN // TODO ???
#include <GLFW/glfw3.h>
#include <string>

namespace lve {
class  LveWindow {
public:
    LveWindow(int w, int h, std::string name);
    ~LveWindow();

    // delete copy-constructor and copy-operator because we use use GLFWwindow pointer
    LveWindow(const LveWindow &) = delete;
    LveWindow &operator=(const LveWindow &) = delete;

    bool shouldClose() {return glfwWindowShouldClose(window); }

    void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

private:
    void initWindow();

    const int width;
    const int height;

    std::string windowName;
    GLFWwindow *window;
};
}