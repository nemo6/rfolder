#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int num = 0;

int fsize(char *filename) {
    
    struct stat st;

    if ( stat(filename, &st) == 0)
    
    	return st.st_size;
}

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;
	char path[1024];
	char blabla[1024];

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {

        sprintf(blabla, "%s/%s", name, entry->d_name);
		
        if (entry->d_type == DT_DIR || isDirectory(blabla) ) {

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            listdir(path, indent + 2);

        } else {
			
			num++;
            printf("%d %*s size: [%d] %s\n\n", num, indent, "", fsize(blabla), entry->d_name);
        }
    }
    closedir(dir);
}

int main(void) {
	
    listdir(".", 0);
	system("PAUSE");
}