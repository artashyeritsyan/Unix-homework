#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <cstdlib>

#define SIZE 256

void* createSharedMemory() {
    void* sharedMemory = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (sharedMemory == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    return sharedMemory;
}

sem_t* createSemaphore(std::string name) {
    sem_t* semaphore = sem_open(name.c_str(), O_CREAT, 0644, 0);
    if (semaphore == SEM_FAILED) {
        perror("sem_open failed");
        exit(0);
    }

    return semaphore;
}

void parentProcess(void* sharedMemory, sem_t* sem_parent, sem_t* sem_child) {
    char message[SIZE];

    while (true) {
        std::cout << "Parent: ";
        std::cin.getline(message, SIZE);
        std::strcpy(static_cast<char*>(sharedMemory), message);
        if (std::strcmp((message), "exit") == 0) {
            sem_post(sem_child);
            return;
        }

        sem_post(sem_child);
        sem_wait(sem_parent);
        
        std::strcpy(message, static_cast<char*>(sharedMemory));

        std::cout << "Parent received: " << message << std::endl;
    }
}

void childProcess(void* sharedMemory, sem_t* sem_parent, sem_t* sem_child) {
    char message[SIZE];

    while (true) {
        sem_wait(sem_child);
    
        std::strcpy(message, static_cast<char*>(sharedMemory));
        std::cout << "Child received: " << message << std::endl;

        std::cout << "Child: ";
        std::cin.getline(message, SIZE);
        std::strcpy(static_cast<char*>(sharedMemory), message);
        if (std::strcmp(message, "exit") == 0) {
            sem_post(sem_parent);
            return;
        }

        sem_post(sem_parent);
    }
}

int main() {
    std::string parentName = "/sem_parent";
    std::string childName = "/sem_child";

    void* sharedMemory = createSharedMemory();
    sem_t *sem_parent = createSemaphore(parentName);
    sem_t *sem_child = createSemaphore(childName);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
        return 1;
    } 
    else if (pid == 0) {
        childProcess(sharedMemory, sem_parent, sem_child);
    } 
    else {
        
        parentProcess(sharedMemory, sem_parent, sem_child);
        wait(NULL);
    }

    int ret = munmap(sharedMemory, SIZE);
    if (ret) {
        perror("munmap");
    }
    sem_close(sem_parent);
    sem_close(sem_child);
    sem_unlink(parentName.c_str());
    sem_unlink(childName.c_str());

    return 0;
}