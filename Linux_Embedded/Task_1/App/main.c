#include <stdio.h>

#include "../Inc/addition.h"
#include "../Inc/subtraction.h"
#include "../Inc/multiplication.h"
#include "../Inc/division.h"
#include "../Inc/modulus.h"


int main()
{


	double Num_1 , Num_2;
	char Operation;

	printf("Enter first number: ");
	

	scanf(" %lf",&Num_1);

	// Clear input buffer
	while ((Operation = getchar()) != '\n' && Operation != EOF);

	printf("Enter operation: ");
	Operation = getchar();	
		
	printf("Enter second number: ");
	scanf(" %lf",&Num_2);
		
	switch(Operation)
	{
		case '+':
			printf("%f + %f = %f\n", Num_1, Num_2 ,Add(Num_1 ,Num_2));
			break;
		case '-':
			printf("%f - %f = %f\n", Num_1, Num_2 ,Subtract(Num_1 ,Num_2));
			break;
		case '*':
			printf("%f * %f = %f\n", Num_1, Num_2 ,Multiply(Num_1,Num_2));
			break;
		case '/':
			printf("%f / %f = %f\n", Num_1, Num_2 ,Divide(Num_1,Num_2));
			break;
		case '%':
			printf("%f %% %f = %f\n", Num_1, Num_2 ,Mod(Num_1,Num_2));
			break;
		default:
			printf("Wrong operation !\n");									
	}
		
	return 0;
}

