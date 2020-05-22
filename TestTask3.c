#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>


#define   S_IFSOCK   0140000   
#define   S_IFLNK    0120000  
#define   S_ISUID    0004000   
#define   S_ISGID    0002000   
#define   S_ISVTX    0001000    
#define   S_IRWXG    00070     
#define   S_IRGRP    00040    
#define   S_IWGRP    00020    
#define   S_IXGRP    00010     
#define   S_IRWXO    00007     
#define   S_IROTH    00004     
#define   S_IWOTH    00002    
#define   S_IXOTH    00001     


typedef struct fileInfo{
	char *mode;
	char *files;
	char *size;
	char *owner;
	char *group;
	char *date;
	char *name;
}info; 




char* permissions(char *file){
    struct stat st;
    char *modeval = malloc(sizeof(char) * 9 + 1);
    if(stat(file, &st) == 0){
        mode_t perm = st.st_mode;
        modeval[0] = (perm & S_IRUSR) ? 'r' : '-';
        modeval[1] = (perm & S_IWUSR) ? 'w' : '-';
        modeval[2] = (perm & S_IXUSR) ? 'x' : '-';
        modeval[3] = (perm & S_IRGRP) ? 'r' : '-';
        modeval[4] = (perm & S_IWGRP) ? 'w' : '-';
        modeval[5] = (perm & S_IXGRP) ? 'x' : '-';
        modeval[6] = (perm & S_IROTH) ? 'r' : '-';
        modeval[7] = (perm & S_IWOTH) ? 'w' : '-';
        modeval[8] = (perm & S_IXOTH) ? 'x' : '-';
        modeval[9] = '\0';
        return modeval;     
    }
    else{
        return strerror(errno);
    }   
}

char* checkDir (char * directory){
	DIR* dir = opendir(directory);
	int file_count = 0;
	char *result;
	if (dir) {
		struct dirent  *entry;
		while ((entry = readdir(dir)) != NULL) {
        file_count++;
    	}
    	result = malloc(sizeof(char)*sizeof(file_count));
    	sprintf(result, "%d", file_count);
    	closedir(dir);
    	return result;
	    
	} else {
		result = malloc(sizeof(char));
		result = "1";
		return result;
	}
}

char* sizeInChar (int sizeInt) {
	char *sizeChar = malloc(sizeof(char)*sizeof(sizeInt));
	sprintf(sizeChar, "%d", sizeInt);
	return sizeChar;
}

char* formatTime (struct tm *time) {
	char *output;
	output = asctime(time);
	output[strlen(output)-1] = '\0';
    return output;
}

char* getUser(uid_t uid)
{
    struct passwd *pws;
    pws = getpwuid(uid);
    return pws->pw_name;
}

char* getGroup(gid_t gid)
{
    struct group *grp;
    grp = getgrgid(gid);
    return grp->gr_name;
} 




int main()
{	
	setlocale(LC_ALL, "");
	int ret;
    DIR            *dptr;
    struct dirent  *ds;
    struct stat buf;
    struct fileInfo *info;
    dptr = opendir(".");
    info = (struct fileInfo*)malloc(sizeof(struct fileInfo));
    while ((ds = readdir(dptr)) != 0) {
    	if ((ret = stat(ds->d_name, &buf))!=0)	{
    	fprintf(stderr, "stat failure error .%d", ret);
    	abort();
  		}
	info->name = ds->d_name;
	info->mode = permissions(ds->d_name);
	info->files = checkDir(ds->d_name);
	info->size = sizeInChar(buf.st_size);
	info->date = formatTime(localtime(&buf.st_ctime));
	info->owner = getUser(buf.st_uid);
	info->group = getGroup(buf.st_gid);
	printf("%s %s %s %s %s %s %s\n", info->mode, info->files, info->owner, info->group, info->size, info->date, info->name);
    }
    free(info);
    closedir(dptr);
    return 0;
}





