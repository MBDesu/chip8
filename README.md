# chip8
A simple CHIP-8 emulator in C++ for education purposes.

## Building

### macOS
Unfortunately, for now, this only compiles on macOS due to using Homebrew, though you could easily modify `CMakeLists.txt` for other platforms. I'm just too lazy/don't care.

In the root of the project, run:

`cmake -Bbuild .`

`cd build`

`make -j`

## Running
Wherever you placed the executable, run `./mbdchip8 <scale> <delay> <ROM path>`, where scale is the scale of the video and delay is the delay (in milliseconds) between CPU cycles. A value of 40 or so is good for most games.

## Tests

### Corax+
![Corax](./img/corax.png)

### Flags
![Flags](./img/flags.png)
