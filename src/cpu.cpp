#include "../include/cpu.h"

CPU::CPU(std::string filepath) {
  this->memory = std::vector<uint8_t>(0x1000, 0);
  this->V = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  this->PC = 0;
  this->soundTimer = 0;
  this->delayTimer = 0;

  std::copy(FONT_DATA.begin(), FONT_DATA.end(),
            this->memory.begin() + FONT_OFFSET);

  std::ifstream file;
  file.open(filepath, std::ios_base::binary);
  if (file.good()) {
    std::vector<uint8_t> program((std::istreambuf_iterator<char>(file)),
                                 (std::istreambuf_iterator<char>()));
    std::copy(program.begin(), program.end(),
              this->memory.begin() + PROGRAM_START);
    this->dump(PROGRAM_START, program.size());
  }
  file.close();
  this->PC = PROGRAM_START;
}

void CPU::dump(uint16_t addr, size_t n) {
  std::printf("      00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n\n");
  for (auto i = addr; i < addr + n; i += 0x10) {
    std::printf("%.04x  ", i);
    for (auto j = 0; j < 0x10; j++) {
      std::printf("%.02x ", this->memory[i + j]);
    }
    std::printf("\n");
  }
  std::printf("\n");
}

uint16_t CPU::fetch() {
  uint8_t pch = this->read(this->PC++);
  uint8_t pcl = this->read(this->PC++);
  return (pch << 8) + pcl;
}

uint8_t CPU::read(uint16_t address) { return this->memory[address]; }

std::vector<uint8_t> CPU::read(uint16_t address, size_t n) {
  return std::vector<uint8_t>(this->memory.begin() + address,
                              this->memory.begin() + address + n);
}

uint16_t CPU::getPC() { return this->PC; }

void CPU::setPC(uint16_t address) { this->PC = address; }

void CPU::push(uint16_t addr) { this->stack.push(addr); }

uint16_t CPU::peek() { return this->stack.top(); }

void CPU::pop() { this->stack.pop(); }

void CPU::set(int vx, uint16_t value) { this->V[vx] = value; }

void CPU::write(uint16_t addr, uint8_t value) { this->memory[addr] = value; }
