#include <stdio.h>
#include <stdlib.h>

int strlength(char* string, int length){
	if (string[0] == '\0')
		return length;
	return strlength(string+1, length+1);
}

int match(char* string, char* star) {
	// version #1
	if (string[0] == '\0' && star[0] == '\0')
		return 1;
	if (star[0] == '*')
		return match(string, star+1);
	if (string[0] == '\0')
		return 0;
	if (string[0] == star[0]){
		if (star[-1] == '*') {
			if (!match(string+1, star+1))
				return match(string+1, star);
		}
		return match(string+1, star+1);
	}
	if (string[0] != star[0] && star[-1] == '*')
		return match(string+1, star);
	return 0;

	// version #2
	// int i;
	// for (i = 0; star[i] != '\0'; i += 1) {
	// 	if (star[i] != '*') {
	// 		if (string[i] != star[i])
	// 			return 0;
	// 	} 
	// 	else {
	// 		int good = 0;
	// 		int j;
	// 		for (j = i; string[j] != '\0' && !good; j += 1)
	// 			good = match(string + j, star + i + 1);
	// 		if (!good)
	// 			good = match(string + j, star + i + 1);
	// 		return good;
	// 	}
	// }
	// return (string[i] == star[i]);
}

int count_match(char* string, char* star) {
	int i;
	for (i = 0; star[i] != '\0'; i += 1) {
		if (star[i] != '*') {
			if (string[i] != star[i])
				return 0;
		}
		else {
			int count = 0;
			int j;
			for (j = i; string[j] != '\0'; j += 1)
				count += count_match(string + j, star + i + 1);
			count += count_match(string + j, star + i + 1);
			return count;
		}
	}
	return (string[i] == star[i]);
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

		// version #1
		if (star[0] != '*' && string[0] != star[0])
			printf("%d\n", 0);
		else if (star[0] == '*')
				printf("%d\n", match(string, star+1));
		else if (string[0] == star[0])
				printf("%d\n", match(string+1, star+1));

		// version #2
		// printf("%d\n", match(string, star));

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
			printf("%d\n", count_match(string, star));
		}

		free(string); free(star); free(option);
	}

	return 0;
}