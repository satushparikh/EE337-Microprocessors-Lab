#include <stdio.h>

int length = 0;
int width = 0;
int area = 0;
int perimeter = 0;

void calculate_area() {
    area = length * width;
    perimeter = 2 * (length + width);
}

int main() {
    printf("Enter the length of the rectangle: ");
    scanf("%d", &length);

    printf("Enter the width of the rectangle: ");
    scanf("%d", &width);

    calculate_area();

    printf("The area of the rectangle is: %d\n", area);
    printf("The perimeter of the rectangle is: %d\n", perimeter);

    return 0;
}
