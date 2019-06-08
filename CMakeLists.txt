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
        liballegro.so.5.2.6
        liballegro_acodec.so.5.2.6
        liballegro_audio.so.5.2.6
        liballegro_color.so.5.2.6
        liballegro_dialog.so.5.2.6
        liballegro_font.so.5.2.6
        liballegro_image.so.5.2.6
        liballegro_main.so.5.2.6
        liballegro_memfile.so.5.2.6
        liballegro_primitives.so.5.2.6
        liballegro_ttf.so.5.2.6

        archive
        pthread
        )
