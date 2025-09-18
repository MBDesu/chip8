#include "include/cpu.h"
#include "include/decoder.h"
#include "include/globals.h"
#include "include/platform.h"

#include <chrono>
#include <iostream>

#define HZ (1.0 / CYCLES_PER_SECOND) * 1000

void run(CPU *cpu, Platform *platform, int scale, int delay) {
  opcode op = 0;
  auto cycles = 0;
  bool quit = false;
  auto lastCycleTime = std::chrono::high_resolution_clock::now();
  int videoPitch = sizeof(cpu->video[0]) * DISPLAY_WIDTH;
  do {
    quit = platform->ProcessInput(cpu->keypad);
    auto now = std::chrono::high_resolution_clock::now();
    auto delta =
        std::chrono::duration<double, std::chrono::milliseconds::period>(
            now - lastCycleTime);

    if (delta.count() > delay) {
      lastCycleTime = now;
      std::printf("%.04x    ", cpu->getPC());
      op = cpu->fetch();
      Decoder::decode(cpu, op);
      platform->Update(cpu->video, videoPitch);
    }
  } while (!quit);
}

void printUsage(std::string arg0) {
  std::cerr << "Usage: " << arg0 << " <scale> <delay> <ROM path>" << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printUsage(argv[0]);
  }
  try {
    int scale = std::stoi(argv[1]);
    int delay = std::stoi(argv[2]);
    std::string romPath = argv[3];
    Platform platform{"CHIP-8", DISPLAY_WIDTH * scale, DISPLAY_HEIGHT * scale,
                      DISPLAY_WIDTH, DISPLAY_HEIGHT};
    CPU cpu{romPath};
    // int videoPitch = sizeof(cpu.video * DISPLAY_WIDTH);
    run(&cpu, &platform, scale, delay);
  } catch (std::exception e) {
    std::printf("%s", e.what());
  }
  return 0;
}
