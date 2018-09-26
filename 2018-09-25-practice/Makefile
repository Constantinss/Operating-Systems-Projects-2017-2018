all:
		gcc -Wall -g --std=c99 -Werror xargs.c -o xargs
		gcc -Wall -g --std=c99 -Werror -pthread banker.c -o banker
		gcc -Wall -g --std=c99 -Werror statements.c -o statements
		gcc -Wall -g --std=c99 -Werror -pthread banks.c -o banks
		gcc -Wall -g --std=c99 -Werror -D_DEFAULT_SOURCE findbig.c -o findbig
