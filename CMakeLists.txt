cmake_minimum_required(VERSION 3.20)
project(8ball)

if (UNIX)
    if (NOT APPLE)
        find_package(Threads REQUIRED)
        find_package(X11 REQUIRED)
    endif()
endif()

if (WIN32)
    SET (PROGRAMS-PREFIX "c:/programs")
else()
    SET (PROGRAMS-PREFIX "~/programs")
endif()

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES src/main.cpp
        src/glad/glad.c
        src/imgui/imgui.cpp
        src/imgui/imgui_draw.cpp
        src/imgui/imgui_tables.cpp
        src/imgui/imgui_widgets.cpp
        src/imgui/imgui_demo.cpp
        src/imgui/imgui_impl_glfw.cpp
        src/imgui/imgui_impl_opengl3.cpp
        src/implot/implot.cpp
        src/implot/implot_items.cpp
        src/implot/implot_demo.cpp
        include/imgui/imgui_impl_glfw.h
        include/imgui/imgui_impl_opengl3.h
        include/imgui/imgui_impl_opengl3_loader.h
        include/imgui/imconfig.h
        include/imgui/imgui.h
        include/imgui/imgui_internal.h
        include/imgui/imstb_rectpack.h
        include/imgui/imstb_textedit.h
        include/imgui/imstb_truetype.h
        include/implot/implot.h
        include/implot/implot_internal.h src/ShaderProgram.cpp include/ShaderProgram.h)

find_package(glfw3 REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/shaders)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/imgui)
include_directories(${PROJECT_SOURCE_DIR}/include/implot)
include_directories(${PROJECT_SOURCE_DIR}/include/glm)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(8ball ${SOURCE_FILES})
add_definitions(-DVERBOSE)
target_link_libraries(8ball glfw)

if (UNIX)
    if (APPLE)
        target_link_libraries(${CMAKE_PROJECT_NAME}
                "-framework Cocoa"
                "-framework IOKit"
                "-framework CoreVideo"
                )
    else()
        target_link_libraries(${CMAKE_PROJECT_NAME}
                ${CMAKE_THREAD_LIBS_INIT}
                ${X11_LIBRARIES}
                ${CMAKE_DL_LIBS}
                )
    endif()
endif()

