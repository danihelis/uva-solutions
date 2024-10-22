/* 1061
 * Consanguine Calculations
 * By Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING  5

typedef enum {
    XX = 0x00,
    OO = 0x01,
    AO = 0x02,
    BO = 0x04,
    AA = 0x08,
    BB = 0x10,
    AB = 0x20
} type_t;

typedef enum {
    RH_NEGATIVE = 0x0,
    RH_WHATEVER = 0x1,
    RH_POSITIVE = 0x2
} rh_t;

typedef struct {
    type_t type;
    rh_t rh;    
} blood_t;

#define HAS_O(b)    ((b).type == OO || (b).type & AO || (b).type & BO)
#define IS_O(b)     ((b).type == OO)
#define IS_A(b)     ((b).type & AO || (b).type & AA || (b).type & AB)
#define IS_B(b)     ((b).type & BO || (b).type & BB || (b).type & AB)
#define IS_AB(b)    ((b).type & AB)

/* Define blood type of child */
blood_t define_child(blood_t p1, blood_t p2) {
    blood_t child;
    child.type = XX;
    child.type |= (HAS_O(p1) && HAS_O(p2)) ? OO : XX;
    child.type |= ((IS_A(p1) && HAS_O(p2)) || (IS_A(p2) && HAS_O(p1))) ? AO : XX;
    child.type |= (IS_A(p1) && IS_A(p2)) ? AA : XX;
    child.type |= ((IS_B(p1) && HAS_O(p2)) || (IS_B(p2) && HAS_O(p1))) ? BO : XX;
    child.type |= (IS_B(p1) && IS_B(p2)) ? BB : XX;
    child.type |= ((IS_A(p1) && IS_B(p2)) || (IS_A(p2) && IS_B(p1))) ? AB : XX;
    child.rh = p1.rh == RH_NEGATIVE && p2.rh == RH_NEGATIVE ? RH_NEGATIVE : RH_WHATEVER;
    return child;
}

/* Define blood type of parent */
blood_t define_parent(blood_t parent, blood_t child) {
    blood_t other;
    other.type = XX;
    if (IS_O(child)) {
        other.type = HAS_O(parent) ? OO | AO | BO : XX;
    }
    else if (IS_AB(child)) {
        other.type = IS_AB(parent) ? AO | BO | AB : IS_A(parent) ? BO | AB : 
                IS_B(parent) ? AO | AB : XX;
    }
    else if (IS_A(child)) {
        other.type = IS_A(parent) ? OO | AO | BO | AB : AO | AB;
    }
    else if (IS_B(child)) {
        other.type = IS_B(parent) ? OO | AO | BO | AB : BO | AB;
    }
    other.rh = parent.rh == RH_NEGATIVE && child.rh == RH_POSITIVE ? RH_POSITIVE : RH_WHATEVER;
    return other;
}

/* Main function */
int main() {
    char string[3][MAX_STRING];
    int test = 0;
    while (scanf("%s %s %s", string[0], string[1], string[2]) != EOF && string[0][0] != 'E') {
        blood_t blood[3];
        int i, lacking;
        for (i = 0, lacking = 0; i < 3; i++) {
            if (string[i][0] == '?') {
                lacking = i;
            }
            else {
                int length = strlen(string[i]);
                blood[i].rh = string[i][length - 1] == '+' ? RH_POSITIVE : RH_NEGATIVE;
                string[i][length - 1] = 0;
                if (strcmp(string[i], "AB") == 0) {
                    blood[i].type = AB;
                }
                else if (strcmp(string[i], "A") == 0) {
                    blood[i].type = AA | AO;
                }
                else if (strcmp(string[i], "B") == 0) {
                    blood[i].type = BB | BO;
                }
                else {
                    blood[i].type = OO;
                }
            }
        }
        blood[lacking] = lacking == 2 ? define_child(blood[0], blood[1]) :
                define_parent(blood[1 - lacking], blood[2]);

        printf("Case %d: ", ++test);
        for (i = 0; i < 3; i++) {
            blood_t b = blood[i];
            if (lacking != i) {
                printf("%s%s%s%s", IS_O(b) ? "O" : "", IS_A(b) ? "A" : "", IS_B(b) ? "B": "",
                        b.rh == RH_NEGATIVE ? "-" : "+");
            }
            else {
                if (b.type == XX) {
                    printf("IMPOSSIBLE");
                }
                else {
                    if (IS_O(b) && b.rh == RH_NEGATIVE) {
                        printf("O-");
                    }
                    else {
                        int k, rep, count;
                        printf("{");
                        for (k = 0, count = 0, rep = b.rh == RH_WHATEVER ? 2 : 1; k < rep; k++) {
                            char signal = k == 0 && b.rh != RH_POSITIVE ? '-' : '+';
                            type_t t = b.type;
                            (t & OO ? printf("%sO%c", count++ == 0 ? "" : ", ", signal) : 0);
                            ((t & AA || t & AO) ? printf("%sA%c", count++ == 0 ? "" : ", ", 
                                    signal) : 0);
                            ((t & BB || t & BO) ? printf("%sB%c", count++ == 0 ? "" : ", ", 
                                    signal) : 0);
                            (t & AB ? printf("%sAB%c", count++ == 0 ? "" : ", ", signal) : 0);
                        }
                        printf("}");
                    }
                }
            }
            printf("%s", i == 2 ? "\n" : " ");
        }
    }
    return 0;
}
