#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    const char *pipe_name = "mypipe.fifo";
    char buffer[BUFFER_SIZE];
    
    
    while (access(pipe_name, F_OK) == -1) {
        sleep(1);
    }
    
    
    int fd = open(pipe_name, O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du tube en lecture");
        exit(EXIT_FAILURE);
    }
    
    
    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
        perror("Erreur lors de la lecture du tube");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    buffer[bytes_read] = '\0';
    printf("Message reçu: %s\n", buffer);
    
    
    close(fd);
    
    return EXIT_SUCCESS;
} 