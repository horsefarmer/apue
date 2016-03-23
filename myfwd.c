#include "apue.h"
#include <fcntl.h>
#include <dirent.h>

int 
main(int argc, char *argv[])
{

	ftw(argv[1]);
	exit(0);
}

int ftw(char *path)
{
	struct stat statbuf;
	if(path == NULL)
		return 0;

	//printf("stat file:%s\n", path);
	if(stat(path, &statbuf) < 0)
	{
		err_ret("%s :stat error!\n", path);
		return 1;
	}

	if(S_ISDIR(statbuf.st_mode))
	{
		DIR *pdir;
		struct dirent *pdirent;

		if((pdir = opendir(path)) < 0)
		{
			err_ret("%s: opendir error!\n", path);
			closedir(pdir);
			return 1;
		}
		while((pdirent = readdir(pdir)) != NULL)
		{
			if((strcmp(pdirent->d_name, ".") == 0)||
			   (strcmp(pdirent->d_name, "..") == 0))
			{
				continue;
			}
			else
			{
				int size = strlen(path) + 255;
				char *newpath = (char*)malloc(size);
				int offset = 0;
				memset(newpath, 0, size);
				memcpy(newpath+offset, path, strlen(path));
				offset = strlen(path);
				if(path[offset-1] != '/')
					newpath[offset++] = '/';
				memcpy(newpath+offset, pdirent->d_name, strlen(pdirent->d_name));
				ftw(newpath);
				free(newpath);
			}
		}
		closedir(pdir);
		return 0;
		
	}
	if(S_ISREG(statbuf.st_mode))
	{
		printf("%s :reg file!\n", path);
	}
	if(S_ISCHR(statbuf.st_mode))
	{
		printf("%s : char file!\n", path);
	}
	if(S_ISBLK(statbuf.st_mode))
		printf("%s : block file!\n",path);
	if(S_ISFIFO(statbuf.st_mode))
		printf("%s : fifo file!\n", path);
	if(S_ISLNK(statbuf.st_mode))
		printf("%s : file symlink!\n", path);
	if(S_ISSOCK(statbuf.st_mode))
		printf("%s : file socket!\n", path);
	
	return 0;
}

