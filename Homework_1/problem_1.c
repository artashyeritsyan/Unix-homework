#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>

void calculateRectangleArea() {
    float length;
    float width;
    printf("Input the params for Rectangle` \n");
    printf("\tEnter length: ");
    scanf("%f", &length);

    printf("\tEnter width: ");
    scanf("%f", &width);

    float area = length * width;
    printf("\tRectangle Area: %.2f\n", area);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error \n");
        return 1;
    } 
    else if (pid == 0) {
        execl("./triangleArea", "triangleArea", NULL);
        perror("Exec failed\n");
        return 1;
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (status == 1) {
            perror("The Child process terminates with error \n");
        }

        calculateRectangleArea();
    }

    return 0;
}
