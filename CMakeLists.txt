cmake_minimum_required (VERSION 2.8.11)
project (LukeLua)
set(CMAKE_CXX_FLAGS "-std=c++11 -fno-exceptions")

find_package(Lua 5.2 REQUIRED)
include_directories (${CMAKE_CURRENT_SOURCE_DIR} /usr/local/include  ${LUA_INCLUDE_DIR})
link_directories(/usr/local/lib)

set (LUKELUADEPS Stick pthread ${LUA_LIBRARIES})

set (LUKELUAINC
LukeLua/LukeLua.hpp
)

install (FILES ${LUKELUAINC} DESTINATION /usr/local/include/LukeLua)
add_subdirectory (Playground)
