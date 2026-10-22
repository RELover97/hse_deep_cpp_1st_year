cmake_minimum_required(VERSION 3.16)
project(scores_seminars LANGUAGES CXX)

add_executable(scores main.cpp scores.cpp)
target_compile_features(scores PRIVATE cxx_std_20)
