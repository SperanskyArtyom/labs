#include <stdio.h>
#include <math.h>

int triangle(float, float, float, float &, float &);
int factorial(int x);
void birthProbability(int, int, float &, float &);

int main()
{
    float a, b, c, P, S, pd, pm;
    int m, n;
    printf("Task 1\n\nInput a, b, c: ");
    scanf("%f%f%f", &a, &b, &c);
    if (triangle(a, b, c, P, S))
        printf("The perimetr is: %.2f, the area is: %.2f\n", P, S);
    else
        printf("Such a triangle is impossible\n");

    printf("\nTask 2\nInput n, m: ");
    scanf("%d%d", &n, &m);
    birthProbability(n, m, pd, pm);
    printf("The probability that among %d children there will be\n %d girls: %.3f\t%d boys: %.3f\n", n, m, pd, m, pm);

    return 0;
}

int triangle(float a, float b, float c, float &p, float &s)
{
    if (a + b <= c || a + c <= b || b + c <= a)
        return 0;
    p = a + b + c;
    s = sqrt(p / 2 * (p / 2 - a) * (p / 2 - b) * (p / 2 - c));
    return 1;
}

int factorial(int x)
{
    int fact = 1;
    for (int i = 1; i <= x; i++)
        fact *= i;
    return fact;
}

void birthProbability(int n, int m, float &pd, float &pm)
{
    float p = 0.45, q = 1 - p, c;
    c = factorial(n) / (factorial(m) * factorial(n - m));
    pd = c * powf(p, m) * powf(q, n - m);
    pm = c * powf(q, m) * powf(p, n - m);
}
