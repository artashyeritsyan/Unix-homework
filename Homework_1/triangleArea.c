#include <stdio.h>
#include <stdlib.h>

void triangleArea() {
    float base;
    float height;
    printf("Input the params for Triangle` \n");
    printf("\tEnter base size: ");
    scanf("%f", &base);

    printf("\tEnter height: ");
    scanf("%f", &height);

    float area = 0.5 * base * height;
    printf("\ttriangle Area: %.2f\n", area);
}

int main() {
    triangleArea();
    return 0;
}
