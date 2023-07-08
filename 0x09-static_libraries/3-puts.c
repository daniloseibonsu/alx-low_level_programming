#include "main.h"
/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
#include<stdio.h>
void _puts(char *str)
{
	int a;

	for (a = 0; str[a] != '\0'; a++)
	{
		_putchar(str[a]);
	}
	_putchar('\n');
}
