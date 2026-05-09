#include <stdio.h>
#include "storage.h"

void child3_function(int param) {
    if (param == 3) {
        printf("Child3: Parametre %d - Calisiyorum!\n", param);
        // Child3 ozel islemleri buraya
    } else {
        printf("Child3: Parametre %d - Calismiyorum (sadece 3 kabul edilir)\n", param);
    }
}
