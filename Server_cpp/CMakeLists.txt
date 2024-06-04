cmake_minimum_required(VERSION 3.22)

project(Server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(SOURCES
Src/application.cpp
Src/client.cpp
Src/clientDistributor.cpp
Src/eventDistributor.cpp
Src/handlerHelper.cpp
Src/host.cpp
Src/ihandler.cpp
Src/librarian.cpp
Src/lobby.cpp
Src/lobbyHandler.cpp
Src/lobbyInfo.cpp
Src/locator.cpp
Src/main.cpp
Src/packet.cpp
Src/packetDispatcher.cpp
)

add_executable(Server ${SOURCES})

target_include_directories(Server PRIVATE
"Include"
"Dependencies/Include"
)

target_link_directories(Server PRIVATE
"Dependencies"
)

target_link_libraries(Server
enet64.lib
winmm.lib
ws2_32.lib
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})