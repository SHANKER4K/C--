#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int fd[2];
    int id = fork();

    if (id == 0)
    {
        close(fd[0]);
        string str = "Assalam";
        wait(NULL);
        write(fd[1], str.c_str(), sizeof(str));
        close(fd[1]);
    }
    else
    {
        close(fd[0]);
        char y[100];
        read(fd[0], &y, sizeof(y)) ; 
        close(fd[0]);
        cout << y;
    }

    return 0;
}