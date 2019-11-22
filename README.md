# EMU-LATER
A NES emulator written by a handful of goons.

This emulator is designed to run on Windows, Linux, and MacOSX. 
It is written in C with SDL2 and a light-weight SDL2 wrapper for GUI widgets [see [https://github.com/actsl/kiss_sdl2](https://github.com/actsl/kiss_sdl2)]

All software is provided "as-is" under the GNU Public License and can be freely used, modified, and distributed provided that the original license is maintained and this README file is also packaged.

# Dependencies

- The following libraries need to be installed on your machine (i.e. through "apt-get" on Linux, or "brew install" on Mac-OSX, etc)

  - OSX 
	> #brew install SDL2 SDL2_image SDL2_tff
   - Arch Linux
		> #pacman -S sdl2 sdl2_image sdl2_tff
  

# Building and Running
 - With dependencies installed run "make"
   - This will build the following:
     - cpu-test: runs dummy instructions to test implemented instructions.
     - rom-test: loads a given rom and parses the header and provides basic information.
     - emu-later: core build, currently doesn't run anything besides loading rom, but will build whole core to ensure it builds.
     - emu_gui: sdl gui frontend.