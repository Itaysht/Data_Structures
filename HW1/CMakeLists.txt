cmake_minimum_required(VERSION 3.23)
project(ex1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

#add_executable(ex1 main23a1.cpp wet1util.h worldcup23a1.cpp worldcup23a1.h Team.cpp Team.h Player.cpp Player.h
#        Dictionary.h)

add_executable(Dictionary.h Player.h Player.cpp worldcup23a1.cpp worldcup23a1.h Team.cpp Team.h Player.cpp Player.h Mytests.cpp)

