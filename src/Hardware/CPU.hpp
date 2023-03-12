#ifndef CPU_HPP
#define CPU_HPP

#include <iostream>
#include <vector>
#include "Params.hpp"

typedef unsigned char BYTE;
typedef unsigned short int WORD;

const BYTE fonts[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


class CPU {
public:
    CPU();
    virtual ~CPU();

    // Public variables


    // Public functions
    void loadGame(const char* filename);
    void cycle();

    // Peripheric related functions
    bool isPixelActivated(int i, int j);
    void setKeyState(int i, bool keystate);

private:

    // Memory
    BYTE m_GameMemory[0xFFF] ;  // 0xFFF bytes of memory
    BYTE m_Registers[16] ;      // 16 registers, 1 byte each
    WORD m_AddressI ;           // the 16-bit address register I
    WORD m_ProgramCounter ;     // the 16-bit program counter
    BYTE m_DelayTimer;
    BYTE m_SoundTimer;
    std::vector<WORD> m_Stack;  // the 16-bit stack

    // Peripheric components
    bool ScreenData[SCREEN_WIDTH][SCREEN_HIGHT];
    bool Keys[KEYS_NUMBER];

    // Memory related functions
    void reset();
    void loadFonts();

    // Peripheric related functions
    int keyPressedValue();
    void beep();

    // Opcode related functions
    // error handling
    void unknownOpcode(WORD opcode);
    // get next opcode
    WORD getNextOpcode();
    // execute it
    void executeNextOpcode();
    // decode cases
    void DecodeOpcode0(WORD opcode);
    void DecodeOpcode1(WORD opcode);
    void DecodeOpcode2(WORD opcode);
    void DecodeOpcode3(WORD opcode);
    void DecodeOpcode4(WORD opcode);
    void DecodeOpcode5(WORD opcode);
    void DecodeOpcode6(WORD opcode);
    void DecodeOpcode7(WORD opcode);
    void DecodeOpcode8(WORD opcode);
    void DecodeOpcode9(WORD opcode);
    void DecodeOpcodeA(WORD opcode);
    void DecodeOpcodeB(WORD opcode);
    void DecodeOpcodeC(WORD opcode);
    void DecodeOpcodeD(WORD opcode);
    void DecodeOpcodeE(WORD opcode);
    void DecodeOpcodeF(WORD opcode);

    // execution of each instruction
    void Execute0x00E0();
    void Execute0x00EE();

    void Execute0x1NNN(WORD adrr);

    void Execute0x2NNN(WORD adrr);

    void Execute0x3XNN(int reg_number, int nn);

    void Execute0x4XNN(int reg_number, int nn);

    void Execute0x5XY0(int reg_number1, int reg_number2);

    void Execute0x6XNN(int reg_number, int nn);

    void Execute0x7XNN(int reg_number, int nn);

    void Execute0x8XY0(int reg_number1, int reg_number2);
    void Execute0x8XY1(int reg_number1, int reg_number2);
    void Execute0x8XY2(int reg_number1, int reg_number2);
    void Execute0x8XY3(int reg_number1, int reg_number2);
    void Execute0x8XY4(int reg_number1, int reg_number2);
    void Execute0x8XY5(int reg_number1, int reg_number2);
    void Execute0x8XY6(int reg_number1, int reg_number2);
    void Execute0x8XY7(int reg_number1, int reg_number2);
    void Execute0x8XYE(int reg_number1, int reg_number2);

    void Execute0x9XY0(int reg_number1, int reg_number2);

    void Execute0xANNN(int nnn);
    
    void Execute0xBNNN(int nnn);

    void Execute0xCXNN(int reg_number1, int nn);

    void Execute0xDXYN(int reg_number1, int reg_number2, int n);

    void Execute0xEX9E(int reg_number1);
    void Execute0xEXA1(int reg_number1);

    void Execute0xFX07(int reg_number1);
    void Execute0xFX0A(int reg_number1);
    void Execute0xFX15(int reg_number1);
    void Execute0xFX18(int reg_number1);
    void Execute0xFX1E(int reg_number1);
    void Execute0xFX29(int reg_number1);
    void Execute0xFX33(int reg_number1);
    void Execute0xFX55(int reg_number1);
    void Execute0xFX65(int reg_number1);
};

#endif