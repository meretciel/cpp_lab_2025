
#include <stdio.h>
#include <string>

#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <GLFW/glfw3.h>  // Will drag system OpenGL headers

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

static GLFWwindow* imgui_create_host_window(const std::string& window_name, int width, int height)
{
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());  // Valid on GLFW 3.3+ only
    GLFWwindow* window =
        glfwCreateWindow((int)(width * main_scale), (int)(height * main_scale), window_name.c_str(), nullptr, nullptr);
    if (window == nullptr)
    {
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);  // Bake a fixed style scale. (until we have a solution for
                                      // dynamic style scaling, changing this requires resetting
                                      // Style + calling this again)
    style.FontScaleDpi = main_scale;  // Set initial font scale. (using
                                      // io.ConfigDpiScaleFonts=true makes this unnecessary. We
                                      // leave both here for documentation purpose)

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return window;
}

static void imgui_render(GLFWwindow* window, ImVec4 clear_color)
{
    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

static void imgui_clean_up(GLFWwindow* window)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

static void imgui_draw_components(ImVec4 clear_color, bool show_demo_window, bool show_another_window)
{
    ImGuiIO& io = ImGui::GetIO();

    
    // 1. Show the big demo window (Most of the sample code is in
    // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
    // ImGui!).
    if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair
    // to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");  // Create a window called "Hello,
                                        // world!" and append into it.

        ImGui::Text("This is some useful text.");  // Display some text (you can
                                                   // use a format strings too)
        ImGui::Checkbox("Demo Window",
                        &show_demo_window);  // Edit bools storing our window
                                             // open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f,
                           1.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*) &clear_color);  // Edit 3 floats representing a color

        if (ImGui::Button("Button"))  // Buttons return true when clicked (most
                                      // widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window",
                     &show_another_window);  // Pass a pointer to our bool variable (the
                                             // window will have a closing button that
                                             // will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me")) show_another_window = false;
        ImGui::End();
    }
};

/**
 * Poll events and start new frame if needed.
 *
 * @return True if the main loop should continue the execute
 *         (i.e. draw ImGui components and render it.)
 *         False if the main loop should skip the current iteration.
 */
static bool imgui_poll_events_and_start_new_frame(GLFWwindow* window)
{
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to
    // tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data
    // to your main application, or clear/overwrite your copy of the mouse
    // data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input
    // data to your main application, or clear/overwrite your copy of the
    // keyboard data. Generally you may always pass all inputs to dear
    // imgui, and hide them from your application based on those two flags.
    glfwPollEvents();
    if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
    {
        ImGui_ImplGlfw_Sleep(10);
        return false;
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    return true;
};


int main(int argc, char* argv[])
{
    // Prepare ImGui before the main loop.
    // The main purpose of this preparation code is to create the host window
    // and some state varaible.
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
        return 1;
    }

    int host_window_width = 1200;
    int host_window_height = 800;
    GLFWwindow* window = imgui_create_host_window("My First ImGui Window (Main)", host_window_width, host_window_height);
    if (window == nullptr)
    {
        return 1;
    }
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Our state
    bool show_demo_window = true;
    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // -----------------------------------------------------------------------
        // Game code and other code go here
        //
        //        ┈┈┈╲┈┈┈┈╱
        //        ┈┈┈╱▔▔▔▔╲
        //        ┈┈┃┈▇┈┈▇┈┃
        //        ╭╮┣━━━━━━┫╭╮
        //        ┃┃┃┈┈┈┈┈┈┃┃┃
        //        ╰╯┃┈┈┈┈┈┈┃╰╯
        //        ┈┈╰┓┏━━┓┏╯
        //        ┈┈┈╰╯┈┈╰╯
        //
        // -----------------------------------------------------------------------

        // -----------------------------------------------------------------------
        //                     ImGui Code Section
        // -----------------------------------------------------------------------

        // The ImGui code is placed at the end of the main loop.

        if (imgui_poll_events_and_start_new_frame(window))
        {
            imgui_draw_components(clear_color, show_demo_window, show_another_window);  // The GUI logic goes here.
            imgui_render(window, clear_color);
        }
    }

    imgui_clean_up(window);
    return 0;
}
