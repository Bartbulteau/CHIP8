#ifndef CPU_HPP
#define CPU_HPP

#include <iostream>
#include <vector>

typedef unsigned char BYTE;
typedef unsigned short int WORD;



class CPU {
public:
    CPU();
    virtual ~CPU();

    void loadGame(const char* filename);
private:

    // Memory
    BYTE m_GameMemory[0xFFF] ; // 0xFFF bytes of memory
    BYTE m_Registers[16] ; // 16 registers, 1 byte each
    WORD m_AddressI ; // the 16-bit address register I
    WORD m_ProgramCounter ; // the 16-bit program counter
    std::vector<WORD> m_Stack; // the 16-bit stack

    BYTE m_ScreenData[64][32];

    void reset();

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
    void Execute0x8XY3(int reg_number1, int reg_number2);
    void Execute0x8XY4(int reg_number1, int reg_number2);
    void Execute0x8XY5(int reg_number1, int reg_number2);
    void Execute0x8XY6(int reg_number1);
    void Execute0x8XY7(int reg_number1, int reg_number2);
    void Execute0x8XYE(int reg_number1);
};

#endif