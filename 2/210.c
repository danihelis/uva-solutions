/* 210
 * Concurrency Simulator
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_OPS             5
#define MAX_PROGRAMS        12
#define MAX_INSTRUCTIONS    30
#define MAX_VARIABLES       26
#define MAX_QUEUE           (MAX_PROGRAMS + 2)
#define MAX_STRING          100

typedef enum {
    ASSIGN = 0,
    PRINT = 1,
    LOCK = 2,
    UNLOCK = 3,
    END = 4
} optype_t;

int cycles[MAX_OPS], quantum;

typedef struct {
    optype_t type;
    int value, param;
} inst_t, *inst_p;

typedef struct {
    inst_t instruction[MAX_INSTRUCTIONS];
    int index, num_insts, cp;
} program_t, *program_p;

program_t program[MAX_PROGRAMS];
int num_programs;

typedef struct {
    program_p queue[MAX_QUEUE];
    int front, rear;
} queue_t, *queue_p;

queue_t ready, blocked;
int variable[MAX_VARIABLES];

/* Read a program from stdin */
void read_program(int index) {
    char line[MAX_STRING], arg;
    program_p p = &program[index];
    p->index = index, p->num_insts = 0;
    while (scanf(" %[^\n]", line) != EOF) {
        inst_p inst = &p->instruction[p->num_insts++];
        if (strncmp(line, "lo", 2) == 0) {
            inst->type = LOCK;
        }
        else if (strncmp(line, "un", 2) == 0) {
            inst->type = UNLOCK;
        }
        else if (strncmp(line, "en", 2) == 0) {
            inst->type = END;
            return;
        }
        else if (strncmp(line, "pr", 2) == 0) {
            inst->type = PRINT;
            assert(sscanf(line, "print %c", &arg) == 1);
            inst->param = arg - 'a';
        }
        else {
            inst->type = ASSIGN;
            assert(sscanf(line, "%c = %d", &arg, &inst->value) == 2);
            inst->param = arg - 'a';
        }
    }
    p->instruction[p->num_insts++].type = END;
}

/* Enqueue a program */
void enqueue(queue_p queue, program_p p) {
    queue->queue[queue->rear] = p;
    queue->rear = (queue->rear + 1) % MAX_QUEUE;
}

/* Enqueue at front */
void enqueue_ahead(queue_p queue, program_p p) {
    queue->front = (MAX_QUEUE + queue->front - 1) % MAX_QUEUE;
    queue->queue[queue->front] = p;
}

/* Dequeue a program */
program_p dequeue(queue_p queue) {
    int index = queue->front;
    if (index == queue->rear) {
        return NULL;
    }
    queue->front = (index + 1) % MAX_QUEUE;
    return queue->queue[index];    
}

/* Simulate the machine */
void simulate_machine() {
    int i, locked;
    program_p current, shift;

    ready.front = 0, ready.rear = 0;
    blocked.front = 0, blocked.rear = 0;
    memset(variable, 0, MAX_VARIABLES * sizeof (int));
    locked = 0;
    for (i = 0; i < num_programs; i++) {
        enqueue(&ready, &program[i]);
        program[i].cp = 0;
    }

    while ((current = dequeue(&ready)) != NULL) {
        int time = 0, stop = 0;
        while (time < quantum && !stop) {
            inst_p inst = &current->instruction[current->cp++];
            time += cycles[(int) inst->type];
            switch (inst->type) {
                case ASSIGN:
                    variable[inst->param] = inst->value;
                    break;
                case PRINT:
                    printf("%d: %d\n", current->index + 1, variable[inst->param]);
                    break;
                case LOCK:
                    if (!locked) {
                        locked = 1;
                    }
                    else {
                        current->cp--;
                        enqueue(&blocked, current);
                        stop = 1;
                    }
                    break;
                case UNLOCK:
                    locked = 0;
                    shift = dequeue(&blocked);
                    if (shift != NULL) {
                        enqueue_ahead(&ready, shift);
                    }
                    break;
                case END:
                    stop = 1;
                    break;
            }
        }
        if (!stop) {
            enqueue(&ready, current);
        }
    }
}

/* Main function */
int main() {
    int num_tests;
    assert(scanf("%d", &num_tests) != EOF);
    for (; num_tests > 0; num_tests--) {
        int i;
        assert(scanf("%d", &num_programs) != EOF);
        for (i = 0; i < MAX_OPS; i++) {
            assert(scanf("%d", &cycles[i]) != EOF);
        }
        assert(scanf("%d", &quantum) != EOF);
        for (i = 0; i < num_programs; i++) {
            read_program(i);
        }
        simulate_machine();
        if (num_tests > 1) {
            printf("\n");
        }
    }
    return 0;
}
