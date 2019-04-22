#include <c2ba/window_manager/window_manager.hpp>

#include <c2ba/window_manager/glfw.hpp>
#include <c2ba/glutils/debug_output.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <fmt/format.h>
#include <stdexcept>

namespace c2ba
{

WindowManager::WindowManager(uint16_t width, uint16_t height, const char * title)
{
	if (!glfwInit()) 
	{
		const auto what = "Unable to init GLFW.\n";
		fmt::print(stderr, what);
		throw std::runtime_error(what);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	m_pWindow = glfwCreateWindow(int(width), int(height), title, nullptr, nullptr);
	if (!m_pWindow) 
	{
		const auto what = "Unable to open window.\n";
		fmt::print(stderr, what);
		throw std::runtime_error(what);
	}

	glfwMakeContextCurrent(m_pWindow);

	glfwSwapInterval(0); // No VSync

	if (!gladLoadGL()) 
	{
		const auto what = "Unable to init OpenGL.\n";
		fmt::print(stderr, what);
		throw std::runtime_error(what);
	}

	c2ba::initGLDebugOutput();

	// Setup ImGui
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);
}

WindowManager::~WindowManager()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

bool WindowManager::shouldClose() const
{
	return glfwWindowShouldClose(m_pWindow);
}

glm::ivec2 WindowManager::framebufferSize() const
{
	int displayWidth, displayHeight;
	glfwGetFramebufferSize(m_pWindow, &displayWidth, &displayHeight);
	return glm::ivec2(displayWidth, displayHeight);
}

void WindowManager::swapBuffers() const
{
	glfwSwapBuffers(m_pWindow);
}

void pollEvents()
{
	glfwPollEvents();
}

double getSeconds()
{
	return glfwGetTime();
}

void imguiNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void imguiRenderFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}