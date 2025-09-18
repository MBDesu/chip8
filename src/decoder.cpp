#include "../include/decoder.h"
#include "../include/opcode.h"

Instruction Decoder::decode(CPU *cpu, uint16_t instruction) {
  Instruction inst = {
      .cpu = cpu,
      .X = X(instruction),     // is a register pointer
      .Y = Y(instruction),     // is a register pointer
      .N = N(instruction),     // is an immediate
      .NN = NN(instruction),   // is an immediate
      .NNN = NNN(instruction), // is an immediate
      .OP = OP(instruction),
      .raw = instruction,
      .mnemonic = "",
  };

  switch (inst.OP) {
  case 0x0:
    switch (inst.NN) {
    case 0xe0:
      Opcode::cls(&inst);
      break;
    case 0xee:
      Opcode::ret(&inst);
      break;
    }
    break;
  case 0x1:
    Opcode::jp(&inst);
    break;
  case 0x2:
    Opcode::call(&inst);
    break;
  case 0x3:
    Opcode::se(&inst);
    break;
  case 0x4:
    Opcode::sne(&inst);
    break;
  case 0x5:
    Opcode::xye(&inst);
    break;
  case 0x6:
    Opcode::ldi(&inst);
    break;
  case 0x7:
    Opcode::add(&inst);
    break;
  case 0x8:
    switch (inst.N) {
    case 0x0:
      Opcode::ldxy(&inst);
      break;
    case 0x1:
      Opcode::Or(&inst);
      break;
    case 0x2:
      Opcode::aNd(&inst);
      break;
    case 0x3:
      Opcode::xOr(&inst);
      break;
    case 0x4:
      Opcode::addxy(&inst);
      break;
    case 0x5:
      Opcode::sub(&inst);
      break;
    case 0x6:
      Opcode::shr(&inst);
      break;
    case 0x7:
      Opcode::subn(&inst);
      break;
    case 0xe:
      Opcode::shl(&inst);
      break;
    default:
      break;
    }
    break;
  case 0x9:
    Opcode::xyne(&inst);
    break;
  case 0xa:
    Opcode::ldI(&inst);
    break;
  case 0xb:
    Opcode::jpr(&inst);
    break;
  case 0xc:
    // TODO: rnd
    break;
  case 0xd:
    Opcode::draw(&inst);
    break;
  case 0xe:
    switch (inst.NN) {
    case 0x9e:
      Opcode::skp(&inst);
      break;
    case 0xa1:
      Opcode::sknp(&inst);
      break;
    }
    break;
  case 0xf:
    switch (inst.NN) {
    case 0x7:
      Opcode::ldt(&inst);
      break;
    case 0xa:
      Opcode::ldk(&inst);
      break;
    case 0x18:
      Opcode::lds(&inst);
      break;
    case 0x1e:
      Opcode::addi(&inst);
      break;
    case 0x29:
      Opcode::ldf(&inst);
    case 0x33:
      Opcode::ldb(&inst);
      break;
    case 0x55:
      Opcode::ldix(&inst);
      break;
    case 0x65:
      Opcode::ldxi(&inst);
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
  if (inst.mnemonic.empty()) {
    std::printf("INSTRUCTION NOT IMPLEMENTED: %.04x (%.02x)\n", inst.raw,
                inst.OP);
  } else {
    if (inst.cpu->delayTimer > 0) {
      --inst.cpu->delayTimer;
    }
    if (inst.cpu->soundTimer > 0) {
      --inst.cpu->soundTimer;
    }
    std::printf("%.04x\t%s\n", inst.raw, inst.mnemonic.c_str());
  }
  return inst;
}
