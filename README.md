This is the README for Quick SDL

Current version is 0.9.1

COMPILE
=======

The source code is hosted on GitHub.
https://github.com/xhp-creations/quicksdl

The project compiles and creates an example game, to add more screens,
or change the starting screen, modify the ScreenManager Class, or employ
your own classes to manage them.

Windows
-------

Make sure you install either the Visual Studio or the Mingw version
of the SDL development library. You can use either compiler
targeting 32 as well as 64-bit binary builds.

Setup instructions are not covered here, just make sure to include the
SDL include directories and link to the SDL library as needed.

Wii U
-----

Before compiling, set up your environment for development on Wii U.
If you do not have Devkitpro, install it from here:
https://www.devkitpro.org
Follow instructions for setting it up and setting up the package manager.
Once you have the package manager installed, begin by installing each of
the WUT packages, as well as all the SDL for Wii U packages.
Complete instructions for setup can be found here:
https://github.com/yawut/ProgrammingOnTheU

The Wii U version uses CMake to ensure you have your environment setup to
compile the project.

To compile:<br/>
mkdir build<br/>
cd build<br/>
cmake -DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/wut/share/wut.toolchain.cmake .. <br/>
make<br/>

The command -DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/wut/share/wut.toolchain.cmake is commented in the CMakeLists.txt file
to easily copy and paste, or you may uncomment the 3rd line in the CMakeLists.txt file that reads as follows:
#set(CMAKE_TOOLCHAIN_FILE $ENV{DEVKITPRO}/wut/share/wut.toolchain.cmake)

FEATURES
========

Quick SDL features:

- Easy to setup game engine
- Most functions are fully commented and straight-forward
- Designed for use on the Wii U, but can also be used on other SDL platforms
- Fully implemented timer, for timer based movement, that is not frame dependent.
- Textures that support sprite sheets, animations, and TTF fonts for text
- Easy Music and SFX use
- Fully managed resources, so resources are only loaded once
- W3C Color definitions included
- Single joystick support (more can be added easily)
- Keeps the state of the joystick, including buttons, axises, and hat.
- Wii U Gamepad and XINPUT button, axis, and hat defines.
- Uses SDL built-in Keyboard states for use on PC, Wii U support may be added later
- A useful and powerful Math Helper

LINKS
=====

https://github.com/xhp-creations/quicksdl : source repository for Quick SDL<br/>
https://github.com/xhp-creations          : XHP Creations homepage<br/>
https://github.com/fortheusers            : 4TU (For The Users)
