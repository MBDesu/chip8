#pragma once

#include "SDL2/SDL_render.h"
#include "globals.h"

#include <fstream>
#include <stack>
#include <stdint.h>
#include <vector>

typedef uint16_t opcode;

const std::vector<uint8_t> FONT_DATA = {
    0xf0, 0x90, 0x90, 0x90, 0xf0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xf0, 0x10, 0xf0, 0x80, 0xf0, // 2
    0xf0, 0x10, 0xf0, 0x10, 0xf0, // 3
    0x90, 0x90, 0xf0, 0x10, 0x10, // 4
    0xf0, 0x80, 0xf0, 0x10, 0xf0, // 5
    0xf0, 0x80, 0xf0, 0x90, 0xf0, // 6
    0xf0, 0x10, 0x20, 0x40, 0x40, // 7
    0xf0, 0x90, 0xf0, 0x90, 0xf0, // 8
    0xf0, 0x90, 0xf0, 0x10, 0xf0, // 9
    0xf0, 0x90, 0xf0, 0x90, 0x90, // a
    0xe0, 0x90, 0xe0, 0x90, 0xe0, // b
    0xf0, 0x80, 0x80, 0x80, 0xf0, // c
    0xe0, 0x90, 0x90, 0x90, 0xe0, // d
    0xf0, 0x80, 0xf0, 0x80, 0xf0, // e
    0xf0, 0x80, 0xf0, 0x80, 0x80  // f
};

class CPU {
public:
  CPU(std::string filepath);
  opcode fetch();
  uint8_t read(uint16_t addr);
  std::vector<uint8_t> read(uint16_t address, size_t n);
  uint16_t getPC();
  void setPC(uint16_t addr);
  uint16_t peek();
  void draw(std::vector<std::vector<bool>> *pixelData);
  void push(uint16_t addr);
  void pop();
  void set(int vx, uint16_t value);
  void dump(uint16_t addr, size_t n);
  void write(uint16_t addr, uint8_t value);

  std::vector<uint8_t> V{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint16_t I{0};
  uint16_t PC{0};
  uint8_t delayTimer{0};
  uint8_t keypad[16]{};
  uint8_t soundTimer{0};
  uint32_t video[DISPLAY_WIDTH * DISPLAY_HEIGHT];

private:
  std::vector<uint8_t> memory = std::vector<uint8_t>(0x1000, 0);
  std::stack<uint16_t> stack{};
  SDL_Renderer *renderer;
};
