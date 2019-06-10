cmake_minimum_required(VERSION 3.13)
project(wa)

set(CMAKE_CXX_STANDARD 14)

set(G++_COVERAGE_COMPILE_FLAGS "-fpermissive")
add_definitions(${G++_COVERAGE_COMPILE_FLAGS})

add_definitions(-DCOLLECTION_FOLDER=${COLLECTION_FOLDER})
add_definitions(-DNUMBER_THREADS=${NUMBER_THREADS})

include_directories(src)

add_executable(wa

        # Game
        src/data.h
        src/drawing_functions.cpp
        src/drawing_functions.h
        src/game_functions.cpp
        src/game_functions.h
        src/graphical_values.cpp
        src/graphical_values.h
        src/init.cpp
        src/init.h
        src/main.cpp
        src/sections.cpp
        src/sections.h
        src/utilities.cpp
        src/utilities.h

        # Uncompressor
        src/archive_functions.cpp
        src/archive_functions.h
        )

target_link_libraries(wa
        liballegro.so
        liballegro_acodec.so
        liballegro_audio.so
        liballegro_color.so
        liballegro_dialog.so
        liballegro_font.so
        liballegro_image.so
        liballegro_main.so
        liballegro_memfile.so
        liballegro_primitives.so
        liballegro_ttf.so

        archive
        pthread
        )
