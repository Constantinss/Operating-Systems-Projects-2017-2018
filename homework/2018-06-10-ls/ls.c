#include <sys/stat.h> 
#include <sys/types.h>
#include <dirent.h>
#include <getopt.h>
#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sysexits.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h> 

//--------------------------------------------
//NAME: Konstantin Mihaylov       
//CLASS: XIb
//NUMBER: 13
//PROBLEM: realization of ls
//FILE NAME: ls.c MakeFile
//FILE PURPOSE: How to implements ls 
//  -alR -Rla -a -l
// source: https://codereview.stackexchange.com/questions/
// 114479/implementation-of-the-ls-command-with-several-options 
// 
// source: https://github.com/coreutils/coreutils/blob/master/src/ls.c
//                ...
//--------------------------------------------

#define BUFSIZE 1024

struct Options get_options(int count, char* args[]);

//getopt(3) linux man page
struct Options{
	bool using_a; //all
	bool using_d; //directory
    bool using_l; //list
    bool using_R; //reverse 
    bool using_g; 
    bool using_h; 
    bool using_o;
    bool using_q;
    bool using_p;
}options_st;

static void SetOptions(struct Options* option){
	option->using_a = false;
	option->using_d = false;
	option->using_l = false;
	option->using_R = false;
	option->using_o = false;
	option->using_h = false;
	option->using_g = false;
	option->using_q = false;
    option->using_p = false;
}

void ShowPermissions(mode_t mode)
{
    putchar((mode & S_IRUSR) ? 'r' : '-');
    putchar((mode & S_IWUSR) ? 'w' : '-');
    putchar((mode & S_IXUSR) ? 'x' : '-');
    putchar((mode & S_IRGRP) ? 'r' : '-');
    putchar((mode & S_IWGRP) ? 'w' : '-');
    putchar((mode & S_IXGRP) ? 'x' : '-');
    putchar((mode & S_IROTH) ? 'r' : '-');
    putchar((mode & S_IWOTH) ? 'w' : '-');
    putchar((mode & S_IXOTH) ? 'x' : '-');
}

void ShowFiletype(mode_t mode)
{
    switch (mode & S_IFMT)
    {
        case S_IFREG:  putchar('-'); break;
        case S_IFDIR:  putchar('d'); break;
        case S_IFLNK:  putchar('l'); break;
        case S_IFCHR:  putchar('c'); break;
        case S_IFBLK:  putchar('b'); break;
        case S_IFSOCK: putchar('s'); break;
        case S_IFIFO:  putchar('p'); break;
    }
}

void ShowFilesize(off_t size){

    const char* units[] = { "", "K", "M", "G", "T"};
    int i;

    for (int i = 0; size > 1024; ++i, size /= 1024);

    char FilesizeBuf[1024];

    snprintf(FilesizeBuf, sizeof(FilesizeBuf), "%*jd%s ", i, (intmax_t)size, units[i]);
    printf(" %8s", FilesizeBuf);

}

void GetOptions(int count, char* args[]){
	SetOptions(&options_st);

    static struct option long_opts[] = {
        { "all",             optional_argument, NULL, 'a' },
        { "directory",       optional_argument, NULL, 'd' },
        { "list",                optional_argument, NULL, 'l' },
        { "reverse",         optional_argument, NULL, 'R' },
        { "owner",                optional_argument, NULL, 'o' },
        { "group",                optional_argument, NULL, 'g' },
        { NULL,              0,                 NULL,  0  }
    };

	int opt;
	while ((opt = getopt(count, args, "aAlRghoQ")) != -1){
		switch (opt){
			case 'a': options_st.using_a = true;
					 break;
            case 'A': options_st.using_a = true;
                     break;
			case 'l': options_st.using_l = true;
					 break;
			case 'R': options_st.using_R = true;
					 break;
			case 'g': options_st.using_g = true;
					 break;
            case 'h': options_st.using_h = true;
            		 break;
            case 'o': options_st.using_o = true;
            		 break;
           	case 'Q': options_st.using_q = true;
            		 break;
			default: 
					 break;
		}
	}
}

struct stat GetStats(const char* filename, const char* dir){
	
    char PathBuf[BUFSIZE];

	const int WrittenBytes = snprintf(PathBuf, sizeof(PathBuf), "%s/%s", dir, filename);

	if(WrittenBytes <= 0){
		exit(EX_IOERR);
	}

	struct stat CurrentStatus;

	if(lstat(PathBuf, &CurrentStatus) < 0){
		perror(PathBuf);
		exit(EX_IOERR);
	}

	return CurrentStatus;
}

void ShowTime(time_t timeMode){
	// get current time with year
	time_t CurrentTime;
	time(&CurrentTime);
	struct tm* myTime = localtime(&CurrentTime);
	const int CurrentMonth = myTime->tm_mon;
	const int CurrentYear = 1970 + myTime->tm_year;

	// get modified time and year
    myTime = localtime(&timeMode);
    const int ModifiedMonth = myTime->tm_mon;
    const int ModifiedYear = 1970 + myTime->tm_year;

    // determine format based on modification time
    // (past six months)
    const char* format = (ModifiedYear == CurrentYear) && (ModifiedMonth >= (CurrentMonth - 6)) ? "%b %e %H:%M" : "%b %e  %Y";
    
    char TimeBuf[BUFSIZE];

    const size_t WrittenBytes = strftime(TimeBuf, sizeof(TimeBuf), format, myTime);

    if (WrittenBytes <= 0)exit(-1);
    printf("%s", TimeBuf);
}

int IsDir(const char* filename){
    struct stat Stat = GetStats(filename, ".");

    if(lstat(filename, &Stat) < 0){
        perror(filename);
        exit(EX_IOERR);
    }

    return Stat.st_mode & S_IFDIR;
}

void ShowName(const char* filename)
{
    if (options_st.using_q)
    {
        printf(" \"%s\"", filename);
    }else{
        printf(" %s", filename);
    }

    if (options_st.using_p && IsDir(filename))
    {
        putchar('/');
    }

    putchar('\n');
}

void StructureDirEntries(DIR* dir, char** entries, size_t* entries_count)
{
    struct dirent* index = readdir(dir);
    *entries_count = 0;

    while (index)
    {
        const bool omit_hidden = !options_st.using_a && index->d_name[0] == '.';

        if (!omit_hidden)
        {
            if (*entries_count >= BUFSIZE)
            {
                entries = realloc(entries, sizeof(entries) * BUFSIZE);
                if (!entries)
                {
                    perror("realloc");
                    abort();
                }
            }
            entries[*entries_count] = index->d_name;
            ++(*entries_count);
        }
        index = readdir(dir);
    }
}

bool IsInDir(const char* dir, const char* filename){
	DIR* d = opendir(dir);

	if(!d){
		perror(dir);
		exit(EX_IOERR);
	}

	struct dirent* dirp = readdir(d);
	while(dirp){
		if(strcmp(filename, dirp->d_name) == 0){
			closedir(d);
			return true;
		}
		dirp = readdir(d);
	}
	closedir(d);
	return false;
}

void DisplayStats(const char* dir, const char* filename){
	if(!IsInDir(dir, filename))return;

    struct stat sb = GetStats(filename, dir);

	if(!options_st.using_l && !options_st.using_o && !options_st.using_g){
            ShowFiletype(sb.st_mode);
            printf(" %s\n", filename);
        //using return statement, because I can't break here;
        return;
    }
    // show filetype
	ShowFiletype(sb.st_mode);
    // show permissions
	ShowPermissions(sb.st_mode);
    // number after wrx permissions
    if(sb.st_nlink > 9)
    printf(" %jd ", (intmax_t)sb.st_nlink);
    else
    printf("  %jd ", (intmax_t)sb.st_nlink);
	// print owner
	if(!options_st.using_g)
	 printf("%4s ", getpwuid(sb.st_uid)->pw_name );
    // print group
	if(!options_st.using_o)
	 printf("%4s", getgrgid(sb.st_gid)->gr_name);
	// print file size
	if(options_st.using_h){
		ShowFilesize(sb.st_size);
	}else{
		printf("%8jd ", (intmax_t)sb.st_size);
	}
	// print time
	ShowTime(sb.st_mtime);
    // print filename
    ShowName(filename);
}

void DisplayDirArgs(int argc, char* argv[]){
    //TO DO total
    if((argc - optind) == 0)
	 DisplayStats(".",".");	

	for (int i = optind; i < argc; ++i)
	{
		DisplayStats(".", argv[i]);
	}
}

void DisplayDirEntries(const char* dir)
{
    char** entries = malloc(BUFSIZE * sizeof(char*));
    if (!entries)
    {
        perror("malloc");
        abort();
    }

    DIR* dfd = opendir(dir);

    size_t entries_count;

    StructureDirEntries(dfd, entries, &entries_count);

    for (size_t i = 0; i < entries_count; ++i)
    {
        DisplayStats(dir, entries[i]);
    }

    closedir(dfd);

    free(entries);
}

void MultipleDirs(const char *name){
    DIR *dir;
    struct dirent *entry;
    
    if(!(dir = opendir(name)))return;

    while((entry = readdir(dir)) != NULL){
        if(entry->d_type == DT_DIR){
            char dirPath[BUFSIZE];
            if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(dirPath, sizeof(dirPath), "%s%s", name, entry->d_name);
            printf("d %s\n", entry->d_name);
        }else{
            if(entry->d_name[0] != '.'){
                struct stat sb = GetStats(entry->d_name, name);
                ShowFiletype(sb.st_mode);
                printf(" %s\n",entry->d_name);
            }
        }
    }
    closedir(dir);
}

void ScanDirEntries(int argc, char* argv[])
{
    for (int i = optind; i < argc; ++i)
    {        
        if (!IsDir(argv[i]))
        {
            DisplayStats(".", argv[i]);
            continue;
        }else{
            if(i != 1)printf("\n%s:\n",argv[i]);
            MultipleDirs(argv[i]);
            continue;
        }

        if (!IsInDir(".", argv[i]))
        {
            continue;
        }       
        DisplayDirEntries(argv[i]);
    }
}

int main(int argc, char *argv[])
{
    GetOptions(argc, argv);
    if(options_st.using_d)
    {
        DisplayDirArgs(argc, argv);
        return EX_OK;
    }else{
        if(optind == argc){
            DisplayDirEntries(".");
            return EX_OK;
        }
        ScanDirEntries(argc, argv);
    }
}