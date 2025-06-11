cmake_minimum_required(VERSION 3.10)
project(metrics_library)

set(CMAKE_CXX_STANDARD 20)

add_library(metrics_library STATIC
    metric.hpp
    typed_metric.hpp
    metrics_collector.hpp
    metrics_collector.cpp
)

add_executable(metrics_example main.cpp)
target_link_libraries(metrics_example metrics_library)
