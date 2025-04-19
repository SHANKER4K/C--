#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {
    const char *pipe_name = "mypipe.fifo";
    const char *message = "Hello from writer processus";
    
    //
    if (mkfifo(pipe_name, 0660) == -1) {
        perror("Erreur lors de la création du tube nommé");
        exit(EXIT_FAILURE);
    }
    
    
    int fd = open(pipe_name, O_WRONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du tube en écriture");
        unlink(pipe_name); 
        exit(EXIT_FAILURE);
    }
    
    
    if (write(fd, message, strlen(message) + 1) == -1) {
        perror("Erreur lors de l'écriture dans le tube");
        close(fd);
        unlink(pipe_name);
        exit(EXIT_FAILURE);
    }
    
    printf("Message envoyé avec succès!\n");
    
    
    close(fd);
    unlink(pipe_name);
    
    return EXIT_SUCCESS;
} 