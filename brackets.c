#include <stdio.h>
#define MAX_INPUT_LENGTH		10000

char opening_symbol(char symbol)
{
	if (symbol == ')')
		return '(';
	else if (symbol == ']')
		return '[';
	else if (symbol == '}')
		return '{';
	else
		return '\0';
}

int is_valid_closing(char symbol, char nests[], int nest_index)
{
	return nest_index > 0 && nests[nest_index-1] == opening_symbol(symbol);
}

int main(int argc, char *argv[]){
	if (!argc){
		printf("No arguments in command line");
		return 1;
	}

	char		*s_fileName = argv[1];
	FILE		*p_file = fopen(s_fileName, "r");

	if (!p_file) {
		printf("Can't open the file: %s\n", s_fileName);
		return 1;
	}

	char		nests[MAX_INPUT_LENGTH] = { '\0' };
	int			nest_index = 0;
	char		input;
	char		symbol = '\0';

	int line = 1, column = 0;

	while ((input = fgetc(p_file)) != EOF) {
		column++;
		symbol = input;

		if (symbol == '\n') {
			line++;
			column = 0;
		} 
		if (symbol == '(' || symbol == '[' || symbol == '{') {
			nests[nest_index++] = symbol;
		}
		if (symbol == ')' || symbol == ']' || symbol == '}') {
			if (is_valid_closing(symbol, nests, nest_index)) {
				nests[--nest_index] = '\0';
			} 
			else {
				printf("Unexpected '%c' at line %d, column %d\n", symbol, line, column);
				return 1;
			}
		}
	}

	if (nest_index > 0) {
		printf("Unbalanced '%c'", nests[0]);
		for (int i = 1; i < nest_index; i++) {
			printf(", '%c'", nests[i]);
		}
		printf("\n");
		return 1;
	} else {
		printf("Balanced\n");
	}
return 0;
}
