//------------------------------------------------------------------------
// NAME: Konstantin Mihaylov
// CLASS: XIb
// NUMBER: 13
// PROBLEM: #2
// FILE NAME: png-info
// FILE PURPOSE:
// to read image-file
//------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>

void *read_image(char *path);
int is_contain(char *argv[]);
int main(int argc, char *argv[])
{

  if(read_image(argv[1]) != NULL && is_contain(argv) != 0){
          if(is_contain(argv)){
              if(read_image(argv[1]) == NULL){printf("Unable to open file"); return 0;}
          void *img = read_image(argv[1]);
          uint32_t *width = (img + 16);
          uint32_t *height = (img + 20);

          printf("PNG image width: %d\nPNG image height: %d\n", ntohl(*width), ntohl(*height));
          int i = 0;
          uint32_t *img_size = (img + i);

          for(i = 1;ntohl(*img_size) != '\0'; i++, img_size = (img + i));
          printf("PNG file size: %d\n", i + 12);
          
        }else printf("Unable to parse file");
        
	}else if(read_image(argv[1]) == NULL && is_contain(argv) == 0)
  
    printf("Unable to parse file");
  else if(read_image(argv[1]) != NULL && is_contain(argv) == 0)
  
    printf("Unable to parse file");
	else 
  
    printf("Unable to open file");	
	return 0;
}

int is_contain(char *argv[])
{
	char extn[] = {'.','p','n','g'};
	int size_of_extn = 0;
	for(int i = 0; i < strlen(argv[1]); i++)
	{
	    
	    if(extn[size_of_extn] == *(argv[1] + i))
	    {
	    
		    size_of_extn++;
		    if(size_of_extn == 4 && i == strlen(argv[1]) - 1){return 1;
	    	}
		}else size_of_extn = 0;
	}
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
