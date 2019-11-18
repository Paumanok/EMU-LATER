# EMU-LATER

A NES emulator written by a handful of goons.

This emulator is designed to run on Windows, Linux, and MacOSX. 
It is written in C with SDL2 and a light-weight SDL2 wrapper for GUI widgets [see [https://github.com/actsl/kiss_sdl2](https://github.com/actsl/kiss_sdl2)]

All software is provided "as-is" under the GNU Public License and can be freely used, modified, and distributed provided that the original license is maintained and this README file is also packaged.

# Dependencies

- The following libraries need to be installed on your machine (i.e. through "apt-get" on Linux, or "brew install" on Mac-OSX, etc)

	> SDL2

	> SDL2_image

	> SDL2_tff

  

# Building and Running

- There are a couple options to build the project depending on how your operating system has installed the dependencies with its package manager.

	> 1) make

	> 2) ./setup.sh

	> 3) manual gcc build
