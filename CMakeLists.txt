cmake_minimum_required(VERSION 3.15.1)
set(TARGET_NAME SmartiesTransformer)
set(TARGET_VERSION 0.1)
project(${TARGET_NAME} VERSION ${TARGET_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(OpenCV REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(${TARGET_NAME}   src/main.cpp
                                src/config/config.cpp
                                src/image/image.cpp
                                src/analyzer/analyzer.cpp
                                src/draw/draw.cpp
                                src/calibrator/calibrator.cpp
                                src/utilities/utilities.cpp)

target_include_directories(${TARGET_NAME} PRIVATE ${Boost_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS} nlohmann_json::nlohmann_json)

target_include_directories(${TARGET_NAME} PUBLIC        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src/config
                                                        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src/image
                                                        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src/analyzer
                                                        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src/draw
                                                        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src/calibrator
                                                        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src/utilities
)

target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${OpenCV_LIBS})

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

