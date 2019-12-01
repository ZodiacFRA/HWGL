cmake_minimum_required(VERSION 3.14)
project(hwgl)

set(CMAKE_CXX_STANDARD 14)
set(SFML_DIR "/home/zodiac/Code/HW/3D/HWGL/libraries/SFML-2.5.1/lib/cmake/SFML")

set(INC_DIR "${PROJECT_SOURCE_DIR}/inc")
set(GL_INC_DIR "${PROJECT_SOURCE_DIR}/inc/GL")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(GL_SRC_DIR "${PROJECT_SOURCE_DIR}/src/GL")


set(SRC_FILES
	${SRC_DIR}/main.cpp
	${SRC_DIR}/utils.cpp
	${SRC_DIR}/Texture.cpp

	${SRC_DIR}/App/App.cpp
	${SRC_DIR}/App/AppInits.cpp
	${SRC_DIR}/App/AppControls.cpp
	${SRC_DIR}/App/AppUtils.cpp
	${SRC_DIR}/App/AppLoaders.cpp
	${SRC_DIR}/App/AppScenery.cpp
	${SRC_DIR}/App/AppPlayer.cpp
	${SRC_DIR}/App/AppText2D.cpp

	${SRC_DIR}/Obj/Obj.cpp
	${SRC_DIR}/Obj/ObjLoaders.cpp

	${SRC_DIR}/Shader/Shader.cpp
	${SRC_DIR}/Shader/ShaderLoaders.cpp

	${SRC_DIR}/SceneTree/SceneTree.cpp
	${SRC_DIR}/SceneTree/SceneTreeTransformations.cpp
)
set(GL_SRC_FILES
	${GL_SRC_DIR}/vboindexer.cpp
)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SFML 2.5 COMPONENTS audio system REQUIRED)

include_directories(
	"${PROJECT_SOURCE_DIR}/libraries/glm-0.9.9.6/glm"
	${GL_INC_DIR}
	${INC_DIR}
	${GLEW_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIRS}
	${SFML_INCLUDE_DIR}
)

set(CMAKE_CXX_FLAGS "-W -Wextra -Wall -Werror -std=c++11")

add_executable(${PROJECT_NAME} ${SRC_FILES} ${GL_SRC_FILES})

target_link_libraries(${PROJECT_NAME}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	sfml-audio
	sfml-system
	glfw
)
