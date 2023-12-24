#include "gl.h"
#include "gui.h"
#include "CubeObject.h"
#include <cstdio>

static int screen_width = 1024;
static int screen_height = 768;

CubeObject cube;
static bool isShowingFaceColors = cube.isDrawingFaceColors();
static float scale = cube.getScale();

static void MainTick(){
    // Clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();
    ImGuiIO& io = ImGui::GetIO();

    // ImGui window
    ImGui::Begin("Cube Scale");
    if (ImGui::SliderFloat("Scale", &scale, 0.1, 2, "%f"))
        cube.setScale(scale);
    if (ImGui::Checkbox("Face Colors", &isShowingFaceColors))
        cube.setDrawFaceColors(isShowingFaceColors);
    if (isShowingFaceColors){
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(204, 0.819f, 0.541f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(204, 0.824f, 0.4f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(203, 0.711f, 0.298f));
        ImGui::Button("Toggle Random Face Colors");
        if (ImGui::IsItemClicked(0))
        {
            cube.randomizeFaceColors();
        }
        ImGui::PopStyleColor(3);
    }
    ImGui::End();

    // Screen projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)screen_width / (GLfloat)screen_height, 0.1, 100.0);

    // Camera position
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Cube rotation
    static float angle = 0.0f;
    glRotatef(angle, 0.5f, 1.0f, 0.75f);
    angle += 0.5f;

    // Draw cube
    cube.draw();

    // Render ImGui frame
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers
    glutSwapBuffers();

    // Redraw
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(screen_width, screen_height);
    glutInitWindowPosition(0, 0);
    int win_cr = glutCreateWindow("OpenGL_Proj");
    if (win_cr < 1) {
        fprintf(stderr, "Error: %s\n", "Failed to create window");
        return 1;
    }
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(MainTick);

    // Initialize GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGLUT_InstallFuncs();

    // Enter main loop
    glutMainLoop();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
