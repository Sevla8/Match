#include <stdio.h>
#include <stdlib.h>

int strlength(char* string, int length){
	if (string[0] == '\0')
		return length;
	return strlength(string+1, length+1);
}

int match(char* string, char* star) {
	if (string[0] == '\0' && star[0] == '\0')
		return 1;
	else if (star[0] == '*')
		return match(string, star+1);
	else if (string[0] == '\0')
		return 0;
	else if (string[0] == star[0]){
		if (star[-1] == '*') {
			if (!match(string+1, star+1))
				return match(string+1, star);
		}
		return match(string+1, star+1);
	}
	else if (string[0] != star[0] && star[-1] == '*')
		return match(string+1, star);
	else if (string[0] != star[0] && star[-1] != '*')
		return 0;
}

int count_match(char* string, char* star, int count) {
	if (!match(string, star))
		return 0;
}

int main(int argc, char *argv[]) {

	if (argc == 3) {

		int l1 = strlength(argv[1], 0);
		char* string = (char*) malloc(sizeof(char)*(l1+1));
		for (int i = 0; i < l1; i += 1)
			string[i] = argv[1][i];
		string[l1] = '\0';

		int l2 = strlength(argv[2], 0);
		char* star = (char*) malloc(sizeof(char)*(l2+1));
		for (int i = 0; i < l2; i = i+1)
			star[i] = argv[2][i];
		star[l2] = '\0';

		if (star[0] != '*' && string[0] != star[0])
			printf("%d\n", 0);
		else if (star[0] == '*')
				printf("%d\n", match(string, star+1));
		else if (string[0] == star[0])
				printf("%d\n", match(string+1, star+1));

		free(string); free(star);
	}

	if (argc == 4) {

		int l1 = strlength(argv[1], 0);
		char* string = (char*) malloc(sizeof(char)*(l1+1));
		for (int i = 0; i < l1; i += 1)
			string[i] = argv[1][i];
		string[l1] = '\0';

		int l2 = strlength(argv[2], 0);
		char* star = (char*) malloc(sizeof(char)*(l2+1));
		for (int i = 0; i < l2; i += 1)
			star[i] = argv[2][i];
		star[l2] = '\0';

		int l3 = strlength(argv[3], 0);
		char* option = (char*) malloc(sizeof(char)*(l3+1));
		for (int i = 0; i < l3; i += 1)
			option[i] = argv[3][i];
		option[l3] = '\0';

		if (option[0] == '-' && option[1] == 'c' && option[3] == '\0') {
			if (star[0] != '*' && string[0] != star[0])
				printf("%d\n", 0);
			else if (star[0] == '*')
				printf("%d\n", count_match(string, star+1, 0));
			else if (string[0] == star[0])
				printf("%d\n", count_match(string+1, star+1, 0));
		}

		free(string); free(star); free(option);
	}

	return 0;
}