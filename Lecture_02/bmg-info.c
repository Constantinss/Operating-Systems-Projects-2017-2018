//------------------------------------------------------------------------
// NAME: Konstantin Mihaylov
// CLASS: XIb
// NUMBER: 13
// PROBLEM: #1
// FILE NAME: bmp-info
// FILE PURPOSE:
// to read bmp file and to write the information 
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> 

void *read_image( const char *filepath );

int main(int argc, char* argv[])
{
    void *img = read_image(argv[1]);
	int32_t *width = (img + 18);
	int32_t *height = (img + 22);
	printf("BMP image width: %d\nBMP image height: %d\n", *width, *height);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


void *read_image(char *path) {
        int fd = open(path, O_RDONLY);
        if (fd < 0) {
            return NULL;
        }
        size_t size = 1000;
        size_t offset = 0;
        size_t res;
        char *buff = malloc(size);

        while((res = read(fd, buff + offset, 100)) != 0) {
                offset += res;
                if (offset + 100 > size) {
                        size *= 2;
                        buff = realloc(buff, size);
                }
        }
        close(fd);
        return buff;
}
