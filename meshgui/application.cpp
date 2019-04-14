//
// Created by mk on 14.04.19.
//

#include "application.h"
#include<imgui.h>
#include<imgui_impl_glfw.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include<imgui_impl_opengl3.h>
#include<iostream>

static void on_glfw_error(int error, const char *description) {
    spdlog::get("logger")->error("GLFW error: [{0}] {1}", error, description);
}

application::application(const std::string &title, int width, int height) :
        m_width(width), m_height(height) {
    glfwSetErrorCallback(on_glfw_error);
    if (!glfwInit())
        throw application_exception("unable to init glfw");

    m_logger = spdlog::get("logger");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    m_window = glfwCreateWindow(1280, 720, "MeshGUI", nullptr, nullptr);

    if (m_window == nullptr)
        throw application_exception("unable to create glfw window");

    glfwSetWindowUserPointer(m_window, this);
    glfwMakeContextCurrent(m_window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);
    auto mb_events = [](GLFWwindow *w, int b, int a, int m) {
        static_cast<application *>(glfwGetWindowUserPointer(w))->on_click(w, b, a, m);
    };
    glfwSetMouseButtonCallback(m_window, mb_events);

    auto cursor_pos_callback = [](GLFWwindow *w, double x, double y) {
        static_cast<application *>(glfwGetWindowUserPointer(w))->on_move(w, x, y);
    };
    glfwSetCursorPosCallback(m_window, cursor_pos_callback);

    auto scroll_callback = [](GLFWwindow *w, double x, double y) {
        static_cast<application *>(glfwGetWindowUserPointer(w))->on_scroll(w, x, y);
    };
    glfwSetScrollCallback(m_window, scroll_callback);

    auto key_cbk = [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        static_cast<application *>(glfwGetWindowUserPointer(window))->on_key(window, key, scancode, action, mods);
    };
    glfwSetKeyCallback(m_window, key_cbk);

    auto char_cbk = [](GLFWwindow *window, unsigned int c) {
        static_cast<application *>(glfwGetWindowUserPointer(window))->on_char(window, c);
    };
    glfwSetCharCallback(m_window, char_cbk);

    auto framebuffer_size_callback = [](GLFWwindow *window, int width, int height) {
        static_cast<application *>(glfwGetWindowUserPointer(window))->on_fb_resize(window, width, height);
    };
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    m_logger->info("Using OpenGL {0}.{1}: {2}", major, minor, glGetString(GL_VERSION));
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    m_logger->info("viewport: {0}, {1}, {2}, {3}", viewport[0], viewport[1], viewport[2], viewport[3]);
}

application::~application() {
    if (m_window)
        glfwDestroyWindow(m_window);
    glfwTerminate();
}

void application::run() {
    initialize();

    ImVec4 clear_color = ImVec4(0x49 / 255.f, 0x49 / 255.f, 0x49 / 255.f, 1.00f);
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // draw the main menu
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::BeginMenu("Open")) {
                    for (auto item : get_directory_list(m_work_dir, ".ply|.stl|.obj|.xyz")) {
                        if (ImGui::MenuItem(item.c_str()))
                            m_logger->info("Picked {0}", item.c_str());
                    }
                    ImGui::EndMenu();
                }
                ImGui::MenuItem("Save");
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) {
                    glfwSetWindowShouldClose(m_window, GLFW_TRUE);
                }
                ImGui::EndMenu();

            }
        }
        ImGui::EndMainMenuBar();

        // draw the toolbox
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Mesh Toolbox");
            ImGui::Text("This is some useful text.");

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float *) &clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();

        }
        ImGui::EndFrame();
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwMakeContextCurrent(m_window);
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwMakeContextCurrent(m_window);
        glfwSwapBuffers(m_window);

    }
}

void application::load_shaders(const std::string &fragment, const std::string &vertex) {

}

void application::on_move(GLFWwindow *w, double x, double y) {
    // m_logger->info("move: {0}, {1}", x, y);

}

void application::on_click(GLFWwindow *w, int a, int b, int m) {
    m_logger->info("click: {0}, {1}, {2}", a, b, m);
}

void application::on_scroll(GLFWwindow *w, double x, double y) {
    m_logger->info("scroll: {0}, {1}", x, y);
}

void application::on_key(GLFWwindow *w, int key, int scancode, int action, int mods) {
    m_logger->info("key: {0}, {1}, {2}", key, scancode, action, mods);
}

void application::on_char(GLFWwindow *w, unsigned int c) {
    m_logger->info("char: {0}", c);
}

void application::on_fb_resize(GLFWwindow *w, int width, int height) {
    m_logger->info("move: {0}, {1}", width, height);
}

void application::initialize() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    if (!ImGui_ImplGlfw_InitForOpenGL(m_window, false)) {
        throw application_exception("Error in ImGUI InitForOpenGL");
    }
    const char *glsl_version = "#version 410";
    if (!ImGui_ImplOpenGL3_Init(glsl_version)) {
        throw application_exception("Error in ImGUI ImplOpenGL3 Init");
    }

}

glm::vec3 application::to_screen_coord(double x, double y) {
    return glm::vec3();
}




