project(net)

cmake_minimum_required(VERSION 3.10)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0 -g)

aux_source_directory(src/ls/net SRC)

include_directories(include)

link_directories(/usr/local/lib)

add_library(lsnet SHARED ${SRC})

add_executable(server sample/server.cpp ${SRC})

add_executable(client sample/client.cpp ${SRC})

target_link_libraries(server lsbuffer lsepoll  lsio lsexception)

target_link_libraries(client lsbuffer lsio lsexception)

install(TARGETS lsnet DESTINATION lib)
install(DIRECTORY include/ls/net DESTINATION include/ls)
