cmake_minimum_required(VERSION 2.4)

project(cetris)

file(COPY data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE SOURCE_FILES
	src/*.cpp src/*.h
)


add_executable(cetris ${SOURCE_FILES})

find_package(SDL2 REQUIRED)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2TTF   REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
find_package(OpenGL REQUIRED)

include_directories(    ${SDL2_INCLUDE_DIR} 
                        ${SDL2TTF_INCLUDE_DIR}
                        ${SDL2MIXER_INCLUDE_DIR}
                        ${OPENGL_INCLUDE_DIRS}
                    )

                target_link_libraries(cetris ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2MIXER_LIBRARY} ${OPENGL_LIBRARIES}  SDL2 SDL2_ttf SDL2_mixer)
                #SDL2main
target_compile_definitions(cetris PUBLIC D_PATH="${CMAKE_INSTALL_PREFIX}/share/cetris/")


install(TARGETS cetris RUNTIME DESTINATION bin)
install(DIRECTORY data DESTINATION share/cetris)
