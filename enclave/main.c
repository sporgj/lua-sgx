#include <sgx_trts.h>
#include <stdlib.h>
#include <stdint.h>

void ecall_main_entry() {
    // TODO
}

int rand() {
    int result;
    sgx_read_rand((uint8_t *)&result, sizeof(int));
    return result;
}

void srand(unsigned int seed) { /* XXX */ }
