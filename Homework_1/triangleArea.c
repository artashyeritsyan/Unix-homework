#include <stdio.h>
#include <stdlib.h>

float getInput() {
    float input;
    do {
        if (scanf("%f", &input) != 1 || input < 1) {
            printf("\tInvalid input. Enter again");
        }
    } while (input <= 0);
    return input;
}

float triangleArea(float base, float height) {
    float area = 0.5 * base * height;

    return area;
}


int main() {
    float base;
    float height;
    
    printf("Input the params for Triangle` \n");
    printf("\tEnter base size: ");
    base = getInput();

    printf("\tEnter height: ");
    height = getInput();

    float area = triangleArea(base, height);
    printf("\tTriangle Area: %.2f\n", area);
    
    return 0;
}
