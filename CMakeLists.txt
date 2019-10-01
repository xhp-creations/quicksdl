cmake_minimum_required(VERSION 3.2)
#-DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/wut/share/wut.toolchain.cmake
#set(CMAKE_TOOLCHAIN_FILE $ENV{DEVKITPRO}/wut/share/wut.toolchain.cmake)

set(PROJECT_NAME
    examplegame_sdl)

project(${PROJECT_NAME})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
# for some reason all these deps are needed when linking statically
if (WIIU)
    find_package(Freetype)
    find_package(MPG123)
    find_package(PNG)
    find_package(BZip2)
endif()

set(INCLUDES
    ${SDL2_TTF_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR}
    QuickSDL
    ExampleGame
)

set(LINK_NAMES
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES})

if (WIIU)
    if (FREETYPE_FOUND)
        list(APPEND LINK_NAMES Freetype::Freetype)
    endif()
    if (MPG123_FOUND)
        list(APPEND LINK_NAMES ${MPG123_LIBRARIES})
    endif()
    if (PNG_FOUND)
        list(APPEND LINK_NAMES PNG::PNG)
    endif()
    if (TARGET BZip2::BZip2)
        list(APPEND LINK_NAMES BZip2::BZip2)
    endif()
endif()

if (TARGET SDL2::SDL2)
    list(APPEND LINK_NAMES SDL2::SDL2)
elseif (TARGET SDL2::SDL2-static)
    list(APPEND LINK_NAMES SDL2::SDL2-static)
else()
    list(APPEND LINK_NAMES ${SDL2_LIBRARIES})
    list(APPEND INCLUDES ${SDL2_INCLUDE_DIR})
endif()

file(GLOB SRCS
    ExampleGame/*.c*
    ExampleGame/*.h*
    QuickSDL/*.c*
    QuickSDL/*.h*
)

if (WIIU)
    include("${WUT_ROOT}/share/wut.cmake" REQUIRED)
    include("/opt/devkitpro/portlibs/wiiu/share/romfs-wiiu.cmake" REQUIRED)
endif()

add_executable(${PROJECT_NAME}
    ${SRCS}
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -O2 -ffast-math )

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
target_link_libraries(${PROJECT_NAME} ${LINK_NAMES})

if (WIIU)
    romfs_add(${PROJECT_NAME} "romfs")
    wut_create_rpx(${PROJECT_NAME}.rpx ${PROJECT_NAME})
endif()
