/*
 * 10033
 * Interpreter
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* Useful macros */
#define COMMAND(x) ((x) / 100)
#define REGISTER(x) (((x) / 10) % 10)
#define PARAM(x) ((x) % 10)


#define REG_MOD 1000
int ram[REG_MOD];


/* Emulate a program and return the number of interations */
#define NUM_REG 10
int emulator() {
    static int reg[NUM_REG];
    int emulation_steps = 0;
    int pointer = 0;
    int halt = 0;
    
    memset(reg, 0, NUM_REG * sizeof (int));
    while (!halt) {
        int inst = ram[pointer];
        switch(COMMAND(inst)) {
            /* Halt emulation */
            case 1:
                halt = 1;
                break;
            /* Set register value to a number */
            case 2:
                reg[REGISTER(inst)] = PARAM(inst);
                break;
            /* Add to register value a number */
            case 3:
                reg[REGISTER(inst)] = (reg[REGISTER(inst)] + PARAM(inst)) % REG_MOD;
                break;
            /* Multiply register value by a number */
            case 4:
                reg[REGISTER(inst)] = (reg[REGISTER(inst)] * PARAM(inst)) % REG_MOD;
                break;
            /* Set register value to another register value */
            case 5:
                reg[REGISTER(inst)] = reg[PARAM(inst)];
                break;
            /* Add to register value another register value */
            case 6:
                reg[REGISTER(inst)] = (reg[REGISTER(inst)] + reg[PARAM(inst)]) % REG_MOD;
                break;
            /* Multiply register value by another register value */
            case 7:
                reg[REGISTER(inst)] = (reg[REGISTER(inst)] * reg[PARAM(inst)]) % REG_MOD;
                break;
            /* Set register value to a value from a ram address */
            case 8:
                reg[REGISTER(inst)] = ram[reg[PARAM(inst)]];
                break;
            /* Set value of a ram address to a register value */
            case 9:
                ram[reg[PARAM(inst)]] = reg[REGISTER(inst)];
                break;
            /* Set program pointer to register value unless another register is null */
            case 0:
                if (reg[PARAM(inst)] != 0) {
                    pointer = reg[REGISTER(inst)] - 1;
                }
                break;
        }        
        pointer++;
        emulation_steps++;
    }

    return emulation_steps;
}


/* Main function */
#define INPUT_SIZE 50
int main() {
    int number_programs, program, i;
    char input[INPUT_SIZE];

    assert(fgets(input, INPUT_SIZE, stdin) != NULL);
    assert(sscanf(input, "%d", &number_programs) != EOF);

    for (program = 0; program < number_programs; program++) {
        if (program == 0) {
            assert(fgets(input, INPUT_SIZE, stdin) != NULL);
            assert(input[0] == '\n');
        }
        else {
            printf("\n");
        }

        memset(ram, 0, REG_MOD * sizeof(int));
        for (i = 0; ; i++) {
            if (fgets(input, INPUT_SIZE, stdin) == NULL || i >= REG_MOD 
                    || sscanf(input, "%d", &ram[i]) == EOF) {
                break;
            }
        }
        printf("%d\n", emulator());
    }

    return 0;
}
