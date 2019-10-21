cmake_minimum_required(VERSION 3.14)
project(hwgl)

set(CMAKE_CXX_STANDARD 14)

set(INC_DIR "./inc")
set(GL_INC_DIR "./inc/GL")
set(SRC_DIR "./src")
set(GL_SRC_DIR "./src/GL")

set(SRC_FILES
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/App.cpp
        ${SRC_DIR}/AppInits.cpp
        ${SRC_DIR}/AppControls.cpp
        ${SRC_DIR}/utils.cpp
        ${SRC_DIR}/Obj.cpp
)

set(GL_SRC_FILES
        #${GL_SRC_DIR}/controls.cpp
        ${GL_SRC_DIR}/objloader.cpp
        #${GL_SRC_DIR}/quaternion_utils.cpp
        ${GL_SRC_DIR}/shader.cpp
        #${GL_SRC_DIR}/tangentspace.cpp
        #${GL_SRC_DIR}/text2D.cpp
        #${GL_SRC_DIR}/texture.cpp
        #${GL_SRC_DIR}/vboindexer.cpp
)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

include_directories(
        "./libraries/glm-0.9.9.6/glm"
	${GL_INC_DIR}
        ${INC_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${GL_SRC_FILES})

target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLUT_LIBRARY}
        glfw
)
