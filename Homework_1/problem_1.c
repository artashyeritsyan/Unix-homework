#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>

float getInput() {
    float input;
    do {
        if (scanf("%f", &input) != 1 || input < 1) {
            printf("\tInvalid input. Enter again");
        }
    } while (input <= 0);
    return input;
}

float calculateRectangleArea(float length, float width) {
    float area = length * width;

    return area;
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
    } 
    else {
        int status = 0;
        waitpid(pid, &status, 0);

        if (status == 1) {
            perror("The Child process terminates with error \n");
        }

        float length;
        float width;

        printf("Input the params for Rectangle` \n");
        printf("\tEnter length: ");
        length = getInput();

        printf("\tEnter width: ");
        width = getInput();

        float area = calculateRectangleArea(length, width);
        printf("\tRectangle Area: %.2f\n", area);

    }

    return 0;
}
