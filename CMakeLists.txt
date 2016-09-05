cmake_minimum_required(VERSION 3.6)
project(FFGLPlugin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTARGET_OS_MAC -std=c++11 -stdlib=libc++ -arch i386")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wno-writable-strings")

find_package(OpenGL REQUIRED)

add_subdirectory(ffgl-host)
include_directories(ffgl-host/lib/ffgl)

set(FFGL_PLUGIN_FILES
        ffgl-host/lib/ffgl/FFGL.cpp
        ffgl-host/lib/ffgl/FFGLPluginInfo.cpp
        ffgl-host/lib/ffgl/FFGLPluginInfoData.cpp
        ffgl-host/lib/ffgl/FFGLPluginManager.cpp
        ffgl-host/lib/ffgl/FFGLPluginSDK.cpp
        ffgl-host/lib/ffgl/FFGLShader.cpp
        ffgl-host/lib/ffgl/FFGLExtensions.cpp
        )

add_library(FFGLPlugin MODULE EmptyEffect.cpp MyPlugin.h ${FFGL_PLUGIN_FILES})
target_link_libraries(FFGLPlugin ${OPENGL_LIBRARIES})
set_target_properties(FFGLPlugin PROPERTIES BUNDLE true)
