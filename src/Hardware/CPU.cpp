#include <iostream>
#include <vector>
#include "Params.hpp"

#include "CPU.hpp"

CPU::CPU() {
    this->reset();
}

CPU::~CPU() {
    
}

// Public functions

void CPU::loadGame(const char* filename) {
    this->reset();
    FILE *in;
    in = fopen(filename, "rb" );
    fread( &m_GameMemory[0x200], 0xfff, 1, in);
    fclose(in);
}

void CPU::cycle() {
    for(int i = 0; i < CYCLES_PER_FRAME; i++) {
        this->executeNextOpcode();
        if(this->m_DelayTimer > 0) this->m_DelayTimer--;
        if(this->m_SoundTimer > 0) this->m_SoundTimer--;
        if(this->m_SoundTimer > 0) this->beep();
    }
}

// Peripheric related functions
bool CPU::isPixelActivated(int i, int j) {
    return this->ScreenData[i][j];
}
void CPU::setKeyState(int i, bool keystate) {
    this->Keys[i] = keystate;
}

// Private functions

// Memory related functions
void CPU::reset() {
    m_AddressI = 0;
    m_ProgramCounter = 0x200;

    memset(m_Registers,0,sizeof(m_Registers));      // set registers to 0
    memset(m_GameMemory,0,sizeof(m_GameMemory));    // set gamememory to 0

    
    for(int i = 0; i < SCREEN_WIDTH; i++) {         // reset screen
        for(int j = 0; j < SCREEN_HIGHT; j++) {
            this->ScreenData[i][j] = false;
        }
    }
    for(int i = 0; i < KEYS_NUMBER; i++) {          // reset keys
        this->Keys[i] = false;
    }

    m_DelayTimer = 0;
    m_SoundTimer = 0;
}

// Peripheric related functions
int CPU::keyPressedValue() {
    for(int i = 0; i < KEYS_NUMBER; i++) {
        if(this->Keys[i]) return i;
    }
    return -1;
} 

void CPU::beep() {
    //std::cout << "beep" << std::endl;
}

// Opcode related

void CPU::unknownOpcode(WORD opcode) {
    std::cout << "Error unknown opcode " << opcode << std::endl;
}

WORD CPU::getNextOpcode() {
    WORD res = 0;
    res = m_GameMemory[m_ProgramCounter]; 
    res <<= 8;
    res |= m_GameMemory[m_ProgramCounter+1];
    m_ProgramCounter+=2 ;
    return res;
}

void CPU::executeNextOpcode() {
    WORD opcode = this->getNextOpcode();
    switch(opcode & 0xF000) {
        case 0x0000: this->DecodeOpcode0(opcode); break;
        case 0x1000: this->DecodeOpcode1(opcode); break;
        case 0x2000: this->DecodeOpcode2(opcode); break;
        case 0x3000: this->DecodeOpcode3(opcode); break;
        case 0x4000: this->DecodeOpcode4(opcode); break;
        case 0x5000: this->DecodeOpcode5(opcode); break;
        case 0x6000: this->DecodeOpcode6(opcode); break;
        case 0x7000: this->DecodeOpcode7(opcode); break;
        case 0x8000: this->DecodeOpcode8(opcode); break;
        case 0x9000: this->DecodeOpcode9(opcode); break;
        case 0xA000: this->DecodeOpcodeA(opcode); break;
        case 0xB000: this->DecodeOpcodeB(opcode); break;
        case 0xC000: this->DecodeOpcodeC(opcode); break;
        case 0xD000: this->DecodeOpcodeD(opcode); break;
        case 0xE000: this->DecodeOpcodeE(opcode); break;
        case 0xF000: this->DecodeOpcodeF(opcode); break;
        default: this->unknownOpcode(opcode); break;
    }
}

// 0x0000 opcodes

void CPU::DecodeOpcode0(WORD opcode) {
    switch(opcode) {
        case 0x00E0: this->Execute0x00E0(); break; // CLS
        case 0x00EE: this->Execute0x00EE(); break; // RET
        default: this->unknownOpcode(opcode); break;
    }
}

void CPU::Execute0x00E0() {
    for(int i = 0; i < SCREEN_WIDTH; i++) {
        for(int j = 0; j < SCREEN_HIGHT; j++) {
            this->ScreenData[i][j] = false;
        }
    }
}

void CPU::Execute0x00EE() {
    this->m_ProgramCounter = this->m_Stack.back();
    this->m_Stack.pop_back();
}

// Ox1000 opcodes

void CPU::DecodeOpcode1(WORD opcode) {
    this->Execute0x1NNN(opcode & 0x0FFF);
}

void CPU::Execute0x1NNN(WORD adrr) {
    this->m_ProgramCounter = adrr;
}

// 0x2000 opcodes

void CPU::DecodeOpcode2(WORD opcode) {
    this->Execute0x2NNN(opcode & 0x0FFF);
}

void CPU::Execute0x2NNN(WORD adrr) {
    this->m_Stack.push_back(this->m_ProgramCounter);
    this->m_ProgramCounter = adrr;
}

// 0x3000 opcodes

void CPU::DecodeOpcode3(WORD opcode) {
    int nn = opcode & 0x00FF;
    int reg_number = (opcode & 0x0F00);
    reg_number >>= 8;
    this->Execute0x3XNN(reg_number, nn);
}

void CPU::Execute0x3XNN(int reg_number, int nn) {
    if(this->m_Registers[reg_number] == nn) this->m_ProgramCounter += 2;
}

// 0x4000 opcodes

void CPU::DecodeOpcode4(WORD opcode) {
    int nn = opcode & 0x00FF;
    int reg_number = opcode & 0x0F00;
    reg_number >>= 8;
    this->Execute0x4XNN(reg_number, nn);
}

void CPU::Execute0x4XNN(int reg_number, int nn) {
    if(this->m_Registers[reg_number] != nn) this->m_ProgramCounter += 2;
}

// 0x5000 opcodes

void CPU::DecodeOpcode5(WORD opcode) {
    if((opcode & 0x000F) == 0x0000) {
        int regx = opcode & 0x0F00;
        regx >>= 8;
        int regy = opcode & 0x00F0;
        regy >>= 8;
        this->Execute0x5XY0(regx, regy);
    } else {
        this->unknownOpcode(opcode);
    }
}

void CPU::Execute0x5XY0(int reg_number1, int reg_number2) {
    if(this->m_Registers[reg_number1] == this->m_Registers[reg_number2]) this->m_ProgramCounter += 2;
}

// 0x6000 opcodes

void CPU::DecodeOpcode6(WORD opcode) {
    int nn = opcode & 0x00FF;
    int regx = opcode & 0x0F00;
    regx >>= 8;
    this->Execute0x6XNN(regx, nn);
}

void CPU::Execute0x6XNN(int reg_number, int nn) {
    this->m_Registers[reg_number] = nn;
}

// 0x7000 opcodes

void CPU::DecodeOpcode7(WORD opcode) {
    int nn = opcode & 0x0FF;
    int regx = opcode & 0x0F00;
    regx >>= 8;
    this->Execute0x7XNN(regx, nn);
}

void CPU::Execute0x7XNN(int reg_number, int nn) {
    this->m_Registers[reg_number] = this->m_Registers[reg_number] + nn;
}

// 0x8000 opcodes

void CPU::DecodeOpcode8(WORD opcode) {
    int regx = opcode & 0x0F00;
    regx >>= 8;
    int regy = opcode & 0x00F0;
    regy >>= 4;
    switch(opcode & 0x000F) {
        case 0x0000: this->Execute0x8XY0(regx, regy); break;
        case 0x0001: this->Execute0x8XY1(regx, regy); break;
        case 0x0002: this->Execute0x8XY2(regx, regy); break;
        case 0x0003: this->Execute0x8XY3(regx, regy); break;
        case 0x0004: this->Execute0x8XY4(regx, regy); break;
        case 0x0005: this->Execute0x8XY5(regx, regy); break;
        case 0x0006: this->Execute0x8XY6(regx); break;
        case 0x0007: this->Execute0x8XY7(regx, regy); break;
        case 0x000E: this->Execute0x8XYE(regx); break;
        default: this->unknownOpcode(opcode); break;
    }
}

void CPU::Execute0x8XY0(int reg_number1, int reg_number2) {
    this->m_Registers[reg_number1] = this->m_Registers[reg_number2];
}

void CPU::Execute0x8XY1(int reg_number1, int reg_number2) {
    this->m_Registers[reg_number1] = this->m_Registers[reg_number1] | this->m_Registers[reg_number2];
}

void CPU::Execute0x8XY2(int reg_number1, int reg_number2) {
    this->m_Registers[reg_number1] = this->m_Registers[reg_number1] & this->m_Registers[reg_number2];
}

void CPU::Execute0x8XY3(int reg_number1, int reg_number2) {
    this->m_Registers[reg_number1] = this->m_Registers[reg_number1] ^ this->m_Registers[reg_number2];
}

void CPU::Execute0x8XY4(int reg_number1, int reg_number2) {
    int value = this->m_Registers[reg_number1] + this->m_Registers[reg_number2];
    if(value > 255) this->m_Registers[0xF] = 1;

    this->m_Registers[reg_number1] = this->m_Registers[reg_number1] + this->m_Registers[reg_number2];
}

void CPU::Execute0x8XY5(int reg_number1, int reg_number2) {
    if(this->m_Registers[reg_number1] > this->m_Registers[reg_number2]) this->m_Registers[0xF] = 1;
    else this->m_Registers[0xF] = 0;

    this->m_Registers[reg_number1] = this->m_Registers[reg_number1] - this->m_Registers[reg_number2];
}

void CPU::Execute0x8XY6(int reg_number1) {
	this->m_Registers[0xF] = this->m_Registers[reg_number1] & 0x1 ;
	this->m_Registers[reg_number1] >>= 1 ;
}

void CPU::Execute0x8XY7(int reg_number1, int reg_number2) {
    if (this->m_Registers[reg_number2] < this->m_Registers[reg_number1]) this->m_Registers[0xF] = 0;
    else this->m_Registers[0xF] = 1;
	this->m_Registers[reg_number1] = this->m_Registers[reg_number2] - this->m_Registers[reg_number1] ;
}

void CPU::Execute0x8XYE(int reg_number1) {
    this->m_Registers[0xF] = this->m_Registers[reg_number1] >> 7 ;
	this->m_Registers[reg_number1] <<= 1 ;
}

// 0x9000 opcodes

void CPU::DecodeOpcode9(WORD opcode) {
    int regx = opcode & 0x0F00;
    regx >>= 8;
    int regy = opcode & 0x00F0;
    regy >>= 4;
    switch(opcode & 0x000F) {
        case 0x0000: this->Execute0x9XY0(regx, regy); break;
        default: this->unknownOpcode(opcode); break;
    }
}

void CPU::Execute0x9XY0(int reg_number1, int reg_number2) {
    if(this->m_Registers[reg_number1] != this->m_Registers[reg_number2]) this->m_ProgramCounter += 2;
}

// 0xA000 opcodes

void CPU::DecodeOpcodeA(WORD opcode) {
    int nnn = opcode & 0x0FFF;
    this->Execute0xANNN(nnn);
}

void CPU::Execute0xANNN(int nnn) {
    this->m_AddressI = nnn;
}

// 0xB000 opcodes

void CPU::DecodeOpcodeB(WORD opcode) {
    int nnn = opcode & 0x0FFF;
    this->Execute0xBNNN(nnn);
}

void CPU::Execute0xBNNN(int nnn) {
    this->m_ProgramCounter = this->m_Registers[0] + nnn;
}

// 0xC000 opcodes

void CPU::DecodeOpcodeC(WORD opcode) {
    int regx = opcode & 0x0F00;
    regx >>= 8;
    int nn = opcode & 0x00FF;
    this->Execute0xCXNN(regx, nn);
}

void CPU::Execute0xCXNN(int reg_number1, int nn) {
    this->m_Registers[reg_number1] = rand() & nn;
}

// 0xD000 opcodes

void CPU::DecodeOpcodeD(WORD opcode) {
    int regx = opcode & 0x0F00;
    regx >>= 8;
    int regy = opcode & 0x00F0;
    regy >>= 4;
    int n = opcode & 0x000F;
    this->Execute0xDXYN(regx, regy, n);
}

void CPU::Execute0xDXYN(int reg_number1, int reg_number2, int n) {
    int coordx = (this->m_Registers[reg_number1])%SCREEN_WIDTH;
    int coordy = (this->m_Registers[reg_number2])%SCREEN_HIGHT;
    this->m_Registers[0xF] = 0;

    int x, y;

    for (int j = 0; j < n; j++) {

        y = coordy+j;

        BYTE line = this->m_GameMemory[this->m_AddressI+j]; // get line to draw from memory

        bool line_pixels[8];                                // convert to an array bool depending on each expected pixel state
        for(int k = 0; k < 8; k++) {
            line_pixels[k] = bool(line & (0x80 >> k));
        }

        for(int i = 0; i < 8; i++) {                        // apply following the rule
            x = coordx+i;
            if(x >= SCREEN_WIDTH) break;
            bool tmp = this->ScreenData[x][y];
            this->ScreenData[x][y] = (line_pixels[i] != this->ScreenData[x][y]);
            if(this->ScreenData[x][y] != tmp) this->m_Registers[0xF] = 1;
        }

    }
}

// 0xE000 opcodes
void CPU::DecodeOpcodeE(WORD opcode) {
    int regx = opcode & 0x0F00;
    regx >>= 8;
    switch(opcode & 0x0FF) {
        case 0x009E: this->Execute0xEX9E(regx); break;
        case 0x00A1: this->Execute0xEXA1(regx); break;
        default: this->unknownOpcode(opcode); break;
    }
}

void CPU::Execute0xEX9E(int reg_number1) {
    if(this->Keys[reg_number1]) this->m_ProgramCounter += 2;
}

void CPU::Execute0xEXA1(int reg_number1) {
    if(!this->Keys[reg_number1]) this->m_ProgramCounter += 2;
}

// 0xF000 opcodes
void CPU::DecodeOpcodeF(WORD opcode) {
    int regx = opcode & 0x0F00;
    regx >>= 8;
    switch(opcode & 0x0FF) {
        case 0x0007: this->Execute0xFX07(regx); break;
        case 0x000A: this->Execute0xFX0A(regx); break;
        case 0x0015: this->Execute0xFX15(regx); break;
        case 0x0018: this->Execute0xFX18(regx); break;
        case 0x001E: this->Execute0xFX1E(regx); break;
        case 0x0029: this->Execute0xFX29(regx); break;
        case 0x0033: this->Execute0xFX33(regx); break;
        case 0x0055: this->Execute0xFX55(regx); break;
        case 0x0065: this->Execute0xFX65(regx); break;
        default: this->unknownOpcode(opcode); break;
    }
}

void CPU::Execute0xFX07(int reg_number1) {
    this->m_Registers[reg_number1] = this->m_DelayTimer;
}

void CPU::Execute0xFX0A(int reg_number1) {
    int key = this->keyPressedValue();
    if(key == -1) this->m_ProgramCounter -= 2;  // loop while no key is pressed
    else this->m_Registers[reg_number1] = key;  // store once key is pressed
}

void CPU::Execute0xFX15(int reg_number1) {
    this->m_DelayTimer = this->m_Registers[reg_number1];
}

void CPU::Execute0xFX18(int reg_number1) {
    this->m_SoundTimer = this->m_Registers[reg_number1];
}

void CPU::Execute0xFX1E(int reg_number1) {
    this->m_AddressI += this->m_Registers[reg_number1];
}

void CPU::Execute0xFX29(int reg_number1) {
    this->m_AddressI = this->m_Registers[reg_number1]*5;
}

void CPU::Execute0xFX33(int reg_number1) {
    int value = this->m_Registers[reg_number1] ;

	int hundreds = value / 100 ;
	int tens = (value / 10) % 10 ;
	int units = value % 10 ;

	this->m_GameMemory[m_AddressI] = hundreds ;
	this->m_GameMemory[m_AddressI+1] = tens ;
	this->m_GameMemory[m_AddressI+2] = units ;
}

void CPU::Execute0xFX55(int reg_number1) {
    for (int i = 0 ; i <= reg_number1; i++) {
		this->m_GameMemory[this->m_AddressI + i] = this->m_Registers[i];
	}
	this->m_AddressI += (reg_number1 + 1);
}

void CPU::Execute0xFX65(int reg_number1) {
    for (int i = 0 ; i <= reg_number1; i++) {
		this->m_Registers[i] = this->m_GameMemory[this->m_AddressI + i];
	}
	this->m_AddressI += (reg_number1 + 1);
}