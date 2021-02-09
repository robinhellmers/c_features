#include <stdio.h>
#include <dirent.h>
#include <string.h>


#define DIR_PATH "/home/hellmers/code/git/c_features/list_directories"

void list_directories(char* dir_path);


int main(void)
{
    list_directories(DIR_PATH);

    return 0;
}


void list_directories(char* dir_path)
{
    char dirs_buffer[1000];
    DIR* d;
    struct dirent* dir;


    memset(dirs_buffer, 0, sizeof dirs_buffer);

    d = opendir(DIR_PATH);

    // readdir scans the next directory within the opened directory
    while ((dir = readdir(d)) != NULL) {
        if(dir->d_type == DT_DIR) // DT_DIR = directory
        {
            printf("%s\n", dir->d_name);

            /**
             * Also add to some buffer
             */
            strncat(dirs_buffer, dir->d_name, (size_t)strlen(dir->d_name));
            strcat(dirs_buffer, "\n");
        }  
    }

    printf("\n%s\n\n", dirs_buffer);
}