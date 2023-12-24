cmake_minimum_required(VERSION 3.27)
project(OpenGL_Proj)

set(CMAKE_CXX_STANDARD 23)
set(GLEW_VERSION 2.1.0)
set(GLUT_VERSION 3.4.0)

# ADD LIBRARY PATHS
set(GLUT_DIR "${CMAKE_SOURCE_DIR}/lib/freeglut-${GLUT_VERSION}")
set(GLEW_DIR "${CMAKE_SOURCE_DIR}/lib/glew-${GLEW_VERSION}")
set(VEC3D_DIR "${CMAKE_SOURCE_DIR}/lib/Vector3D")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/lib/imgui")

# ADD INCLUDE PATHS
include_directories(
        "${GLEW_DIR}/include"
        "${GLUT_DIR}/include"
        "${VEC3D_DIR}"
        "${IMGUI_DIR}"
)

add_executable(OpenGL_Proj
        main.cpp
        CubeObject.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glut.cpp
)

# MOVE DLLs TO BUILD DIRECTORY
add_custom_command(TARGET OpenGL_Proj POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GLUT_DIR}/bin/Release/freeglut.dll" $<TARGET_FILE_DIR:OpenGL_Proj>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GLEW_DIR}/bin/Release/x64/glew32.dll" $<TARGET_FILE_DIR:OpenGL_Proj>)

# LINK LIBRARIES
target_link_libraries(OpenGL_Proj OpenGL32 glu32)
target_link_libraries(OpenGL_Proj ${GLUT_DIR}/lib/Release/freeglut.lib)
target_link_libraries(OpenGL_Proj ${GLEW_DIR}/lib/Release/x64/glew32.lib)

