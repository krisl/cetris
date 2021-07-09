cmake_minimum_required(VERSION 3.20)

project(cetris)

file(COPY data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE SOURCE_FILES
	src/*.cpp src/*.h
)


add_executable(cetris ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
#find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_mixer REQUIRED)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2TTF   REQUIRED IMPORTED_TARGET SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED IMPORTED_TARGET SDL2_mixer>=2.0.0)

message("Woot ${OPENGL_LIBRARIES}")
message("Woot ${SDL2TTF_LIBRARIES}")
message("Woot ${SDL2TTF_LIBRARY_DIRS}")
message("Woot ${SDL2TTF_LIBDIR}")
#target_include_directories(cetris
#	PRIVATE
#  "${SDL2TTF_INCLUDE_DIRS}"
#)
include_directories(    ${SDL2_INCLUDE_DIR} 
                        ${SDL2TTF_INCLUDE_DIR}
                        ${SDL2MIXER_INCLUDE_DIR}
                        ${OPENGL_INCLUDE_DIRS}
			/opt/homebrew/include/
                    )

	    #message("sdl2ttf ${SDL2TTF_LIBRARY_DIRS}")
	    #message("sdl2ttf ${SDL2TTF_LIBRARIES}")
	    #target_link_directories(${SDL2TTF_LIBRARY_DIRS})
	    #target_link_libraries(cetris ${SDL2_LIBRARY} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARY} ${OPENGL_LIBRARIES}  SDL2::SDL2 )
                #SDL2maiN

		#target_link_directories(cetris /opt/homebrew/lib)
		#link_directories(/opt/homebrew/lib)
link_directories(${SDL2TTF_LIBDIR})
target_link_libraries(cetris
	OpenGL::GL
	SDL2::SDL2
	PkgConfig::SDL2TTF
	PkgConfig::SDL2MIXER
	#${SDL2TTF_LIBRARIES}
	#${OPENGL_LIBRARIES} 
)
target_compile_definitions(cetris PUBLIC D_PATH="${CMAKE_INSTALL_PREFIX}/share/cetris/")
#target_link_directories(cetris /usr/local/lib)

install(TARGETS cetris RUNTIME DESTINATION bin)
install(DIRECTORY data DESTINATION share/cetris)
