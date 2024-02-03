#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "LL_Queue.h"

int main(void)
{
    Queue *Q = create_queue(5);
    destroy_queue(Q);
    return 0;
}