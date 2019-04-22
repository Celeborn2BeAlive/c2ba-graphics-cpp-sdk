#pragma once

#include <glm/glm.hpp>

struct GLFWwindow;

namespace c2ba
{

// Class responsible for initializing GLFW, creating a window, initializing OpenGL function pointers with GLAD library and initializing ImGUI
class WindowManager
{
public:
	WindowManager(uint16_t width, uint16_t height, const char * title);
	~WindowManager();

    // Non-copyable class:
    WindowManager(const WindowManager&) = delete;
    WindowManager& operator =(const WindowManager&) = delete;

	bool shouldClose() const;

	glm::ivec2 framebufferSize() const;

	void swapBuffers() const;

    GLFWwindow* window()
    {
        return m_pWindow;
    }

private:
    GLFWwindow* m_pWindow = nullptr;
};

// To be called before calling functions from Dear ImGui in the render loop
void imguiNewFrame();

// To be called after calling functions from Dear ImGui in the render loop, before swapping buffers
void imguiRenderFrame();

void pollEvents();

// Get seconds since the window manager has been created
double getSeconds();

}