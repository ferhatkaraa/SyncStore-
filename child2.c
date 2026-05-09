#include <stdio.h>
#include "storage.h"

void child2_function(int param) {
    if (param == 2) {
        printf("Child2: Parametre %d - Calisiyorum!\n", param);
        // Child2 ozel islemleri buraya
    } else {
        printf("Child2: Parametre %d - Calismiyorum (sadece 2 kabul edilir)\n", param);
    }
}
