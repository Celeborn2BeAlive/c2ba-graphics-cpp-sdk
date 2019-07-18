#include <c2ba/utils/filesystem.hpp>
#include <c2ba/window_manager/glfw.hpp>
#include <c2ba/window_manager/window_manager.hpp>
#include <chrono>
#include <cxxopts.hpp>
#include <fmt/format.h>
#include <imgui.h>

namespace chrono = std::chrono;
using hr_clock = chrono::high_resolution_clock;

struct Application
{
    static cxxopts::Options getOptions()
    {
        cxxopts::Options options{ "samples-app", "One line description of sample app" };
        options.add_options()("w,width", "Width of the window", cxxopts::value<uint16_t>()->default_value("1280"))("h,help", "Show help");
        return options;
    }

    cxxopts::ParseResult m_InputArgs;

    const c2ba::fs::path m_AppPath;
    const std::string m_AppName;
    const std::string m_ImGuiIniFilename;
    const c2ba::fs::path m_ShadersRootPath;

    const uint16_t m_nWindowWidth = 1280;
    const uint16_t m_nWindowHeight = 720;
    c2ba::WindowManager m_WindowManager{ m_nWindowWidth, m_nWindowHeight, "Template" };

    Application(int argc, char ** argv, cxxopts::ParseResult inputArgs):
        m_InputArgs{ inputArgs }, m_AppPath{ c2ba::fs::path{ argv[0] } }, m_AppName{ m_AppPath.stem().string() }, m_ImGuiIniFilename{ m_AppName + ".imgui.ini" },
        m_ShadersRootPath{ m_AppPath.parent_path() / "shaders" }, m_nWindowWidth{ m_InputArgs["width"].as<uint16_t>() }, m_nWindowHeight{ (uint16_t)(m_nWindowWidth * 9.f / 16) }
    {
        ImGui::GetIO().IniFilename = m_ImGuiIniFilename.c_str(); // At exit, ImGUI will store its windows positions in this file

        glfwSetWindowUserPointer(m_WindowManager.window(), this);
        glfwSetWindowRefreshCallback(m_WindowManager.window(), onWindowRefresh);
    }

    int run()
    {
        // Loop until the user closes the window
        for (auto iterationCount = 0u; !m_WindowManager.shouldClose(); ++iterationCount)
        {
            c2ba::pollEvents();

            auto guiHasFocus = ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
            if (!guiHasFocus)
            {
                // Put here code to handle user interactions
            }

            render();
        }

        return 0;
    }

    void render()
    {
        const auto start = hr_clock::now();

        // Put here rendering code
        const auto fbSize = m_WindowManager.framebufferSize();
        glViewport(0, 0, fbSize.x, fbSize.y);
        glClear(GL_COLOR_BUFFER_BIT);

        // GUI code:
        c2ba::imguiNewFrame();

        {
            ImGui::Begin("GUI");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        c2ba::imguiRenderFrame();

        m_WindowManager.swapBuffers();

        const auto ellapsedSeconds = std::chrono::duration<float>(hr_clock::now() - start).count();
    }

    static void onWindowRefresh(GLFWwindow * window)
    {
        auto app = (Application *) glfwGetWindowUserPointer(window);
        app->render();
    }
};

int main(int argc, char ** argv)
{
    auto options = Application::getOptions();
    const auto inputArgs = options.parse(argc, argv);

    if (inputArgs.count("help") > 0)
    {
        fmt::print("{}", options.help());
        return 0;
    }

    Application app{ argc, argv, inputArgs };
    return app.run();
}
