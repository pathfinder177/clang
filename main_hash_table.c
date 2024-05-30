#include "hash_table.h"

int main() {
    install("tail", "value1");
    install("middle", "value2");
    install("head", "value3");
    undef("middle");

    return 0;
}
