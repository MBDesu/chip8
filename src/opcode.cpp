#include "../include/opcode.h"
#include "../include/decoder.h"
#include "../include/globals.h"

#include <format>

void Opcode::cls(Instruction *inst) {
  inst->mnemonic = "cls";
  memset(inst->cpu->video, 0, sizeof(inst->cpu->video));
}

void Opcode::jp(Instruction *inst) {
  inst->mnemonic = std::format("jp 0x{:02x}", inst->NNN);
  inst->cpu->setPC(inst->NNN);
}

void Opcode::ret(Instruction *inst) {
  inst->mnemonic = "ret";
  inst->cpu->setPC(inst->cpu->peek());
  inst->cpu->pop();
}
void Opcode::ldi(Instruction *inst) {
  inst->mnemonic = std::format("ld V{:1x},0x{:01x}", inst->X, inst->NN);
  inst->cpu->V[inst->X] = inst->NN;
}

void Opcode::add(Instruction *inst) {
  inst->mnemonic = std::format("add V{:1x},0x{:01x}", inst->X, inst->NN);
  inst->cpu->V[inst->X] += inst->NN;
}

void Opcode::addxy(Instruction *inst) {
  inst->mnemonic = std::format("add V{:1x},V{:1x}", inst->X, inst->Y);
  uint16_t sum = inst->cpu->V[inst->X] + inst->cpu->V[inst->Y];
  inst->cpu->V[inst->X] = sum & 0xff;
  inst->cpu->V[0xf] = sum > 0xff;
}

void Opcode::sub(Instruction *inst) {
  inst->mnemonic = std::format("sub V{:1x},V{:1x}", inst->X, inst->Y);
  auto x = inst->cpu->V[inst->X];
  auto y = inst->cpu->V[inst->Y];
  inst->cpu->V[inst->X] = x - y;
  inst->cpu->V[0xf] = x >= y;
}

void Opcode::shr(Instruction *inst) {
  inst->mnemonic = std::format("shr V{:1x}", inst->X);
  auto x = inst->cpu->V[inst->X];
  inst->cpu->V[inst->X] >>= 1;
  inst->cpu->V[0xf] = x & 0x1;
}

void Opcode::subn(Instruction *inst) {
  inst->mnemonic = std::format("subn V{:1x},V{:1x}", inst->X, inst->Y);
  auto x = inst->cpu->V[inst->X];
  auto y = inst->cpu->V[inst->Y];
  inst->cpu->V[inst->X] = inst->cpu->V[inst->Y] - inst->cpu->V[inst->X];
  inst->cpu->V[0xf] = y >= x;
}

void Opcode::shl(Instruction *inst) {
  inst->mnemonic = std::format("shl V{:1x}", inst->X);
  auto x = inst->cpu->V[inst->X];
  inst->cpu->V[inst->X] <<= 1;
  inst->cpu->V[0xf] = (x & 0x80) >> 0x7;
}

void Opcode::ldxy(Instruction *inst) {
  inst->mnemonic = std::format("ld V{:1x},V{:1x}", inst->X, inst->Y);
  inst->cpu->V[inst->X] = inst->cpu->V[inst->Y];
}

void Opcode::ldI(Instruction *inst) {
  inst->mnemonic = std::format("ld I,0x{:02x}", inst->NNN);
  inst->cpu->I = inst->NNN;
}

void Opcode::draw(Instruction *inst) {
  inst->mnemonic = "draw";
  uint8_t xPos = inst->cpu->V[inst->X] % DISPLAY_WIDTH;
  uint8_t yPos = inst->cpu->V[inst->Y] % DISPLAY_HEIGHT;

  inst->cpu->V[0xf] = 0;

  for (auto row = 0; row < inst->N; ++row) {
    uint8_t spriteByte = inst->cpu->read(inst->cpu->I + row);

    for (auto col = 0; col < 8; ++col) {
      uint8_t spritePixel = spriteByte & (0x80 >> col);
      uint32_t *screenPixel =
          &(inst->cpu->video[(yPos + row) * DISPLAY_WIDTH + (xPos + col)]);

      if (spritePixel) {
        if (*screenPixel == 0xffffffff) {
          inst->cpu->V[0xf] = 1;
        }
        *screenPixel ^= 0xffffffff;
      }
    }
  }
}

void Opcode::call(Instruction *inst) {
  inst->mnemonic = std::format("call 0x{:03x}", inst->NNN);
  inst->cpu->push(inst->cpu->getPC());
  inst->cpu->setPC(inst->NNN);
}

void Opcode::se(Instruction *inst) {
  inst->mnemonic = std::format("se V{:1x},0x{:01x}", inst->X, inst->NN);
  if (inst->cpu->V[inst->X] == inst->NN)
    inst->cpu->setPC(inst->cpu->getPC() + 2);
}

void Opcode::sne(Instruction *inst) {
  inst->mnemonic = std::format("jne V{:1x},0x{:01x}", inst->X, inst->NN);
  if (inst->cpu->V[inst->X] != inst->NN)
    inst->cpu->setPC(inst->cpu->getPC() + 2);
}

void Opcode::xye(Instruction *inst) {
  inst->mnemonic = std::format("se V{:1x},V{:1x}", inst->X, inst->Y);
  if (inst->cpu->V[inst->X] == inst->cpu->V[inst->Y])
    inst->cpu->setPC(inst->cpu->getPC() + 2);
}

void Opcode::xyne(Instruction *inst) {
  inst->mnemonic = std::format("sne V{:1x},V{:1x}", inst->X, inst->Y);
  if (inst->cpu->V[inst->X] != inst->cpu->V[inst->Y])
    inst->cpu->setPC(inst->cpu->getPC() + 2);
}

void Opcode::xOr(Instruction *inst) {
  inst->mnemonic = std::format("xor V{:1x},V{:1x}", inst->X, inst->Y);
  inst->cpu->V[inst->X] ^= inst->cpu->V[inst->Y];
}

void Opcode::aNd(Instruction *inst) {
  inst->mnemonic = std::format("and V{:1x},V{:1x}", inst->X, inst->Y);
  inst->cpu->V[inst->X] &= inst->cpu->V[inst->Y];
}

void Opcode::Or(Instruction *inst) {
  inst->mnemonic = std::format("or V{:1x},V{:1x}", inst->X, inst->Y);
  inst->cpu->V[inst->X] |= inst->cpu->V[inst->Y];
}

void Opcode::jpr(Instruction *inst) {
  inst->mnemonic = std::format("jp V0,0x{:02x}", inst->NNN);
  inst->cpu->setPC(inst->cpu->V[0] + inst->NNN);
}

void Opcode::skp(Instruction *inst) {
  inst->mnemonic = std::format("skp V{:1x}", inst->X);
  uint8_t key = inst->cpu->V[inst->X];
  if (inst->cpu->keypad[key]) {
    inst->cpu->PC += 2;
  }
}

void Opcode::sknp(Instruction *inst) {
  inst->mnemonic = std::format("sknp V{:1x}", inst->X);
  if (!inst->cpu->keypad[inst->cpu->V[inst->X]]) {
    inst->cpu->PC += 2;
  }
}

void Opcode::ldt(Instruction *inst) {
  inst->mnemonic = std::format("ld V{:1x},DT", inst->X);
  inst->cpu->V[inst->X] = inst->cpu->delayTimer;
}

void Opcode::ldk(Instruction *inst) {
  inst->mnemonic = std::format("ld V{:1x},K", inst->X);

  if (inst->cpu->keypad[0])
    inst->cpu->V[inst->X] = 0;
  else if (inst->cpu->keypad[0x1])
    inst->cpu->V[inst->X] = 1;
  else if (inst->cpu->keypad[0x2])
    inst->cpu->V[inst->X] = 2;
  else if (inst->cpu->keypad[0x3])
    inst->cpu->V[inst->X] = 3;
  else if (inst->cpu->keypad[0x4])
    inst->cpu->V[inst->X] = 4;
  else if (inst->cpu->keypad[0x5])
    inst->cpu->V[inst->X] = 5;
  else if (inst->cpu->keypad[0x6])
    inst->cpu->V[inst->X] = 6;
  else if (inst->cpu->keypad[0x7])
    inst->cpu->V[inst->X] = 7;
  else if (inst->cpu->keypad[0x8])
    inst->cpu->V[inst->X] = 8;
  else if (inst->cpu->keypad[0x9])
    inst->cpu->V[inst->X] = 9;
  else if (inst->cpu->keypad[0xa])
    inst->cpu->V[inst->X] = 10;
  else if (inst->cpu->keypad[0xb])
    inst->cpu->V[inst->X] = 11;
  else if (inst->cpu->keypad[0xc])
    inst->cpu->V[inst->X] = 12;
  else if (inst->cpu->keypad[0xd])
    inst->cpu->V[inst->X] = 13;
  else if (inst->cpu->keypad[0xe])
    inst->cpu->V[inst->X] = 14;
  else if (inst->cpu->keypad[0xf])
    inst->cpu->V[inst->X] = 15;
  else
    inst->cpu->PC -= 2;
}

void Opcode::lds(Instruction *inst) {
  inst->mnemonic = std::format("ld ST,V{:1x}", inst->X);
  inst->cpu->soundTimer = inst->cpu->V[inst->X];
}

void Opcode::addi(Instruction *inst) {
  inst->mnemonic = std::format("ld I,V{:1x}", inst->X);
  inst->cpu->I += inst->cpu->V[inst->X];
}

void Opcode::ldf(Instruction *inst) {
  inst->mnemonic = std::format("ld F,V{:1x}", inst->X);
  inst->cpu->I = FONT_OFFSET + (5 * inst->cpu->V[inst->X]);
}

void Opcode::ldb(Instruction *inst) {
  inst->mnemonic = std::format("ld B,V{:1x}", inst->X);
  uint8_t value = inst->cpu->V[inst->X];
  auto index = inst->cpu->I;
  inst->cpu->write(index + 2, value % 10);
  value /= 10;
  inst->cpu->write(index + 1, value % 10);
  value /= 10;
  inst->cpu->write(index, value % 10);
}

void Opcode::ldix(Instruction *inst) {
  inst->mnemonic = std::format("ld [I],V{:1x}", inst->X);
  for (auto i = 0; i <= inst->X; ++i) {
    inst->cpu->write(inst->cpu->I + i, inst->cpu->V[i]);
  }
}

void Opcode::ldxi(Instruction *inst) {
  inst->mnemonic = std::format("ld V{:1x},[I]", inst->X);
  for (auto i = 0; i <= inst->X; ++i) {
    inst->cpu->V[i] = inst->cpu->read(inst->cpu->I + i);
  }
}
