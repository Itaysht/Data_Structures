cmake_minimum_required(VERSION 3.23)
project(Wet2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(worldcup23a2.h worldcup23a2.cpp wet2util.h Uptrees.cpp Uptrees.h RankedTree.h RankedTree.cpp Team.h Team.cpp Player.h Player.cpp RankedTree.cpp main23a2.cpp)