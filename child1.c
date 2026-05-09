#include <stdio.h>
#include "storage.h"

void child1_function(int param) {
    if (param == 1) {
        printf("Child1: Parametre %d - Calisiyorum!\n", param);
        // Child1 ozel islemleri buraya
    } else {
        printf("Child1: Parametre %d - Calismiyorum (sadece 1 kabul edilir)\n", param);
    }
}
