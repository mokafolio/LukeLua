find_package(OpenGL REQUIRED)
find_package(Lua 5.2 REQUIRED)
find_package(SDL2 REQUIRED)

include_directories (${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})
add_executable (LukeLuaPlayground LukeLuaPlayground.cpp)
set_target_properties(LukeLuaPlayground PROPERTIES COMPILE_FLAGS "-fsanitize=address")
set_target_properties(LukeLuaPlayground PROPERTIES LINK_FLAGS "-fsanitize=address")
target_link_libraries(LukeLuaPlayground Luke Stick ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${LUA_LIBRARIES})