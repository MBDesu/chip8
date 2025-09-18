#pragma once

#include "cpu.h"
#include "decoder.h"

class Opcode {
public:
  static void cls(Instruction *inst);   // 00e0; cls
  static void ret(Instruction *inst);   // 00ee; ret
  static void jp(Instruction *inst);    // 1NNN; jp NNN
  static void call(Instruction *inst);  // 2NNN; call NNN
  static void se(Instruction *inst);    // 3XNN; se VX,NN
  static void sne(Instruction *inst);   // 4XNN; sne VX,NN
  static void xye(Instruction *inst);   // 5XY0; se VX,Vy
  static void ldi(Instruction *inst);   // 6XNN; ld VX,NN
  static void add(Instruction *inst);   // 7XNN; add VX,NN
  static void ldxy(Instruction *inst);  // 8XY0; ld VX,VY
  static void Or(Instruction *inst);    // 8XY1; or VX,VY
  static void aNd(Instruction *inst);   // 8XY2; and VX,VY
  static void xOr(Instruction *inst);   // 8XY3; xor VX,VY
  static void addxy(Instruction *inst); // 8XY4; add VX,VY
  static void sub(Instruction *inst);   // 8XY5; sub VX,VY
  static void shr(Instruction *inst);   // 8XY6; shr VX
  static void subn(Instruction *inst);  // 8XY7; subn VX,VY
  static void shl(Instruction *inst);   // 8XYE; shl VX
  static void xyne(Instruction *inst);  // 9XY0; sne VX,VY
  static void ldI(Instruction *inst);   // ANNN; ld I,NNN
  static void jpr(Instruction *inst);   // BNNN; jp V0,NNN
  static void draw(Instruction *inst);  // DXYN; draw
  static void skp(Instruction *inst);   // EX9E; skp VX
  static void sknp(Instruction *inst);  // EXA1; sknp VX
  static void ldt(Instruction *inst);   // FX07; ld VX,DT
  static void ldk(Instruction *inst);   // FX0A; ld VX,K
  static void lds(Instruction *inst);   // FX18; ld ST,VX
  static void addi(Instruction *inst);  // FX1E; add I,VX
  static void ldf(Instruction *inst);   // FX29; ld F,VX
  static void ldb(Instruction *inst);   // FX33; ld B,VX
  static void ldix(Instruction *inst);  // FX55; ld [I],VX
  static void ldxi(Instruction *inst);  // FX65; ld VX,[I]
};
