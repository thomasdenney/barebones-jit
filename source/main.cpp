#include "MicroBit.h"

#include <cstdint>
#include <vector>

MicroBit uBit;

typedef void (*f_void)(void);

void basic_jit()
{
    static const uint16_t instrs[] = { /*(0b0100 0111 0111 0000),*/ 0x4770 };
    asm("DSB");
    asm("ISB");
    f_void fp = (f_void)((unsigned)instrs | 0x1);
    fp();
}

void basic_jit_heap()
{
    uint16_t* instrs = (uint16_t*)calloc(1, sizeof(uint16_t));
    instrs[0] = 0x4770;
    asm("DSB");
    asm("ISB");
    f_void fp = (f_void)((unsigned)instrs | 0x1);
    fp();
    free(instrs);
}


typedef int (*f_int_int_int_int_int)(int, int, int, int);

void jit_int_sum(unsigned int n)
{
    std::vector<uint16_t> instrs;
    if (n == 0) {
        // MOV   Rd  Value
        // 00100 000 00000000
        // 2   0     0   0
        instrs.push_back(0x2000);
    } else {
        for (unsigned k = 1; k != n; ++k) {
            // Rd := Rn + Rm
            // Add     Rm  Rn  Rd
            // 0001100 000 xxx 000
            // 1   8    0    0
            instrs.push_back(0x1800 | (k << 3));
        }
    }
    instrs.push_back(0x4770);

    asm("DSB");
    asm("ISB");
    auto fp = (f_int_int_int_int_int)((unsigned)instrs.data() | 0x1);
    int result = fp(1, 2, 3, 4);

    if (n == 0 && result != 0) {
        uBit.display.scroll("0");
    } else if (n == 1 && result != 1) {
        uBit.display.scroll("1");
    } else if (n == 2 && result != 3) {
        uBit.display.scroll("2");
    } else if (n == 3 && result != 6) {
        uBit.display.scroll("3");
    } else if (n == 4 && result != 10) {
        uBit.display.scroll("4");
    }
}

int main()
{
    uBit.init();
    basic_jit();
    basic_jit_heap();
    jit_int_sum(0);
    jit_int_sum(1);
    jit_int_sum(2);
    jit_int_sum(3);
    jit_int_sum(4);
    uBit.display.scroll("!");
    release_fiber();
}
