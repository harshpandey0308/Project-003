#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    struct stat st;
    if(stat("har.txt" , &st) == -1){
        perror("stat failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Device ID : %ju.\n",st.st_dev);
    printf("INODE : %ju.\n",st.st_ino);
    printf("Mode : %o\n",st.st_mode);
    printf("N-Links : %ju.\n",st.st_nlink);
    printf("UID : %u.\n" , st.st_uid);
    printf("GID : %u.\n" , st.st_gid);
    printf("the total size of the file (in bytes) : %ld.\n",st.st_size);

    printf("Owner read : %s\n",(st.st_mode & S_IRUSR)? "YES" : "NO");
    printf("Owner Write : %s\n" , (st.st_mode & S_IWUSR)? "YES":"NO");
    printf("Owner execute : %s\n" , (st.st_mode & S_IXUSR)? "YES":"NO");

    if(S_ISREG(st.st_mode)){
       printf("REGULAR FILE.\n");
    }
    else if(S_ISDIR(st.st_mode)){
        printf("DIRECTORY.\n");
    }
    else if(S_ISLNK(st.st_mode)){
        printf("SYMBOLIC LINK.\n");
    }

    return 0;
}