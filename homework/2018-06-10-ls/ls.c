#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

struct Options get_options(int count, char* args[]);

//getopt(3) linux man page
struct Options{
	bool using_a;
    bool using_l;
    bool using_R;
};



int main(int argc, char const *argv[])
{
	
	return 0;
}

static void set_options(struct Options* option){
	option->using_a = false;
	option->using_l = false;
	option->using_R = false;
}

struct Options get_options(int count, char* args[]){
	struct Options options;
	set_options(&options);
	int opt;

	while ((opt = getopt(count, args, "alR")) != -1){
		switch (opt){
			case 'a': options.using_a = true;
					 break;
			case 'l': options.using_l = true;
					 break;
			case 'R': options.using_R = true;
					 break;
			default: 
					 break;
		}
	}

	return options;
}

void set_dirs(int count, char* arguments[], struct Options options){
	if(options.using_R){
		//TO DO
	}
}