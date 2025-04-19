#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int xd = 0;
void *routine()
{
    for (int i = 0; i < 100; i++)
    {
        xd++;
    }
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2, t3, t4, t5;
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);
    pthread_create(&t3, NULL, &routine, NULL);
    pthread_create(&t4, NULL, &routine, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    printf("xd = %d\n", xd);
    return 0;
}