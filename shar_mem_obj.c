#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int main() {
    //Open shared memory object
    const char *shm_name = "/shm_object";
    shm_unlink(shm_name);

    size_t p_size = getpagesize();

    int shm_fd = shm_open(shm_name, O_RDWR | O_CREAT, 0666);

    // Resize the shared memory object
    if (ftruncate(shm_fd, p_size) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Allocate a shared memory region
    int *kuz_shared_memory = mmap(0, p_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (kuz_shared_memory == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    close(shm_fd);

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("Child: Writing to shared memory\n");
        *kuz_shared_memory = 42;
        printf("Child: Wrote %d to shared memory\n", *kuz_shared_memory);
    } else {
        // Parent process
        sleep(1); // Ensure child writes first
        printf("Parent: Read from shared memory\n");
        printf("Parent: Read %d from shared memory\n", *kuz_shared_memory);
    }

    wait(NULL);

    // Clean up
    if (munmap(kuz_shared_memory, p_size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Close shared memory object
    shm_unlink(shm_name);

    return 0;
}
