This is the README for Quick SDL

Current version is 0.9.1

LEGAL
=====

Quick SDL is 
(C) 2019 XHP Creations (xhpcreations(at)att.net)
https://gitlab.com/xhp-creations

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not see <http://www.gnu.org/licenses/>.

COMPILE
=======

The source code is hosted on GitLab.
https://gitlab.com/xhp-creations/quicksdl

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
ckame .. <br/>
make<br/>

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

https://gitlab.com/xhp-creations/quicksdl : source repository for Quick SDL<br/>
https://gitlab.com/xhp-creations          : XHP Creations homepage<br/>
https://gitlab.com/4TU                    : 4TU (For The Users)
