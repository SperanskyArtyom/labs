#include <stdio.h>
#include <math.h>

void easterDate(int);
float power_n(float, int);
float cosinus(float);

int main(int argc, char *argv[])
{
	int year, n;
	float x, cos1, cos2;

	printf("Task 1.\n\nEnter the year to calculate the date of Easter: ");
	scanf("%d", &year);
	easterDate(year);
	printf("\nTask 2.\n\nEnter a decimal x: ");
	scanf("%f", &x);
	printf("Enter a positive or negative integer n: ");
	scanf("%d", &n);
	printf("x to the power n = %f", power_n(x, n));
	printf("\n\nTask 3.\n\nEnter x to calculate the cosinus(x): ");
	scanf("%f", &x);
	cos1 = cosinus(x);
	cos2 = cos(x);
	printf("Cosinus calculated using Taylor series:\n%f", cos1);
	printf("\nCosinus calculated by standard function:\n%f\n", cos2);
	return 0;
}

void easterDate(int year)
{
	int a, b, c, d, e, f;

	a = year % 19;
	b = year % 4;
	c = year % 7;
	d = (19 * a + 15) % 30;
	e = (2 * b + 4 * c + 6 * d + 6) % 7;
	f = d + e;
	if (f > 26)
		printf("The Easter date is %d may.\n", f - 26);
	else
		printf("The Easter date is %d april.\n", f + 4);
}

float power_n(float x, int n)
{
	float y = 1;
	int i;

	if (n > 0)
	{
		for (i = 0; i < n; i++)
		{
			y *= x;
		}
	}
	else
	{
		for (i = 0; i < -n; i++)
		{
			y /= x;
		}
	}
	return y;
}

float cosinus(float x)
{
	float eps = 0.0001;
	float diff, result = 1.0;
	int i = 1;
	long long fact = 2;

	do
	{
		diff = result;
		result += pow(-1, i) * pow(x, 2 * i) / fact;
		fact *= (2 * i + 1) * (2 * i + 2);
		i++;
		diff -= result;
	} while (fabs(diff) > eps);
	return result;
}
