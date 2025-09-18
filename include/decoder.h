#pragma once

#include "cpu.h"

#include <cstdint>

#define OP(inst) (inst >> 12)
#define X(inst) ((inst & 0x0f00) >> 8)
#define Y(inst) ((inst & 0x00f0) >> 4)
#define N(inst) (inst & 0x000f)
#define NN(inst) (inst & 0x00ff)
#define NNN(inst) (inst & 0x0fff)

struct Instruction {
  CPU *cpu;
  int X;
  int Y;
  int N;
  int NN;
  int NNN;
  int OP;
  int raw;
  std::string mnemonic;
};

typedef void (*OpcodeFn)(Instruction *);

class Decoder {
public:
  static Instruction decode(CPU *cpu, uint16_t bytes);
};
