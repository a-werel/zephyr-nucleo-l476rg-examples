cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(app_tmp_sensor)

add_library(temp_sensor STATIC src/temp_sensor.cpp)
add_library(lcd_display STATIC src/tft_display.cpp)


target_include_directories(temp_sensor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(lcd_display PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(temp_sensor PRIVATE ${PROJECT_NAME})
target_link_libraries(lcd_display PRIVATE ${PROJECT_NAME})

target_sources(app PRIVATE src/main.cpp)