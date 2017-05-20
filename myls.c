/* This was done in Spring 2016 */
/* This program is an attempt to recreate Unix's ls command */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void recursedir(char* cwd, char* filename, char* pathname);

int main(int argc, char *argv[])
{
	/* Start by getting the current directory */
	char cwd[512];
	/* Error check */
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("getcwd() failed!\n");
		return 0;
	}
	if (argc == 1)
	{
		/* myls */
		/* Initialize needed variables */
		DIR *durr = opendir(cwd); //current directory
		struct dirent *durrent; //directory entry structure
		/* Error check */
		if (durr == NULL)
		{
			printf("Cannot open %s\n", cwd);
			return 0;
		}
		/* Create variable for filename */
		char* filename;
		/* Read directory */
		while ((durrent = readdir(durr)) != NULL)
		{
			/* List files and directories besides . and .. */
			filename = durrent->d_name;
			if (strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0)
			{
				/* Print file name */
				printf("%s  ", durrent->d_name);
			}
		}
		/* Print a newline to make it look pretty */
		printf("\n");
		/* Cleanup; close directory */
		closedir(durr);
	}
	//
	else if (argc == 2)
	{
		if (strcmp(argv[1], "-i") == 0)
		{
			/* ./myls -i */
			/* Initialize needed variables */
			DIR *durr = opendir(cwd); //current directory
			struct dirent *durrent; //directory entry structure
			struct stat *filestat = malloc(sizeof(struct stat)); // file stat structure
			/* Error check */
			if (durr == NULL)
			{
				printf("Cannot open %s\n", cwd);
				return 0;
			}
			/* Create needed variables */
			char* filename;
			int inode;
			/* Read directory */
			while ((durrent = readdir(durr)) != NULL)
			{
				/* List files and directories besides . and .. */
				filename = durrent->d_name;
				if (strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0)
				{
					/* Get file inode and list it alongside file name */
					stat(filename, filestat);
					inode = filestat->st_ino;
					printf("%d %s  ", inode, filename);
				}
			}
			/* Print a newline to make it look clean */
			printf("\n");
			/* Clean up; close directory and free filestat */
			closedir(durr);
			free(filestat);
		}
		else if (strcmp(argv[1], "-l") == 0)
		{
			/* ./myls -l */
			/* Initialize needed variables */
			DIR *durr = opendir(cwd); //current directory
			struct dirent *durrent; //directory entry structure
			struct stat *filestat = malloc(sizeof(struct stat)); // file stat structure
			/* Error check */
			if (durr == NULL)
			{
				printf("Cannot open %s\n", cwd);
				return 0;
			}
			/* Create needed variables */
			char* filename;
			int permissions;
			char permarray[11] = "----------";
			int links;
			int user;
			struct passwd *pwd;
			int group;
			struct group *grp; 
			int filesize;
			time_t lastmod;
			struct tm lastmoddate;
			char timestring[200];
			int blockcount = 0;
			/* Read directory */
			while ((durrent = readdir(durr)) != NULL)
			{
				filename = durrent->d_name;
				if (strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0)
				{
					stat(filename, filestat);
					blockcount += filestat->st_blocks;
				}
			}
			blockcount = blockcount/2;
			printf("total %d\n", blockcount);
			rewinddir(durr);
			while ((durrent = readdir(durr)) != NULL)
			{
				/* List files and directories besides . and .. */
				filename = durrent->d_name;
				if (strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0)
				{
					/* Get file inode and list it alongside file name */
					stat(filename, filestat);
					/* Build permissions array */
					permissions = filestat->st_mode;
					if (S_ISDIR(permissions))
					{
						permarray[0] = 'd';
					}
					else
					{
						permarray[0] = '-';
					}
					if (permissions & S_IRUSR)
					{
						permarray[1] = 'r';
					}
					else
					{
						permarray[1] = '-';
					}
					if (permissions & S_IWUSR)
					{
						permarray[2] = 'w';
					}
					else
					{
						permarray[2] = '-';
					}
					if (permissions & S_IXUSR)
					{
						permarray[3] = 'x';
					}
					else
					{
						permarray[3] = '-';
					}
					if (permissions & S_IRGRP)
					{
						permarray[4] = 'r';
					}
					else
					{
						permarray[4] = '-';
					}
					if (permissions & S_IWGRP)
					{
						permarray[5] = 'w';
					}
					else
					{
						permarray[5] = '-';
					}
					if (permissions & S_IXGRP)
					{
						permarray[6] = 'x';
					}
					else
					{
						permarray[6] = '-';
					}
					if (permissions & S_IROTH)
					{
						permarray[7] = 'r';
					}
					else
					{
						permarray[7] = '-';
					}
					if (permissions & S_IWOTH)
					{
						permarray[8] = 'w';
					}
					else
					{
						permarray[8] = '-';
					}
					if (permissions & S_IXOTH)
					{
						permarray[9] = 'x';
					}
					else
					{
						permarray[9] = '-';
					}
					/* Number of hard links */
					links = filestat->st_nlink;
					/* Build username */
					user = filestat->st_uid;
					pwd = getpwuid(user);
					/* Build group name */
					group = filestat->st_gid;
					grp = getgrgid(group);
					/* Size of file in bytes */
					filesize = filestat->st_size;
					/* Build last modification date */
					lastmod = filestat->st_mtime;
					localtime_r(&lastmod, &lastmoddate);
					strftime(timestring, sizeof(timestring), "%b %d %H:%M", &lastmoddate);
					/* Print file information */
					printf("%s %d %6s %8s %7d %s %s\n", permarray, links, pwd->pw_name, grp->gr_name, filesize, timestring, filename);
				}
			}
			/* Clean up */
			closedir(durr);
			free(filestat);
		}
		else if (strcmp(argv[1], "-R") == 0)
                {
			/* ./myls -R */
			/* Initialize needed variables */
			DIR *durr = opendir(cwd); //current directory
			struct dirent *durrent; //directory entry structure
			struct stat *filestat = malloc(sizeof(struct stat)); // file stat structure
			/* Error check */
			if (durr == NULL)
			{
				printf("Cannot open %s\n", cwd);
				return 0;
			}
			/* Create needed variables */
			char* filename;
			/* Read directory */
			printf(".:\n");
			while ((durrent = readdir(durr)) != NULL)
			{
				/* List files and directories besides . and .. */
				filename = durrent->d_name;
				if (strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0)
				{
					/* Get file inode and list it alongside file name */
					printf("%s  ", filename);
				}
			}
			/* Recurse over directories in current working directory */
			rewinddir(durr);
			int permissions;
			char* pathname = "./";
			while ((durrent = readdir(durr)) != NULL)
			{
				/* Find directories and recurse over them */
				filename = durrent->d_name;
				if (strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0)
				{
					/* Recurse over directory */
					stat(filename, filestat);
					permissions = filestat->st_mode;
					if (S_ISDIR(permissions))
					{
						recursedir(cwd, filename, pathname);
					}
				}
			}
			/* Print a newline character to make it look clean */
			printf("\n");
			/* Clean up; close directory and free filestat */
			closedir(durr);
			free(filestat);
		}
		/* Invalid command */
		else
		{
			printf("Invalid command.\n");
			return 0;
		}
	}
	else
	{
		/* If we're here, we have too many arguments */
		printf("Invalid number of arguments.\n");
	}
	return 0;
}

/* Directory recursion function */
/* Works even on files that aren't directories */
/* If the file is not a directory, the function will realize this and return */
void recursedir(char* cwd, char* filename, char* pathname)
{
	/* Get new pathname */
	/* Allocate space for new pathname */
	char* newpathname;
	if ((newpathname = malloc(strlen(pathname) + strlen(filename) + 2)) != NULL)
	{
		/* Build new pathname from pathname and filename */
		newpathname[0] = '\0'; // This keeps the memory clean
		strcat(newpathname, pathname);
		strcat(newpathname, filename);
	}
	/* Error check */
	else
	{
		printf("Memory allocation failure\n");
		return;
	}
	/* Get new cwd */
	/* Allocate space for new cwd */
	char* newcwd;
	if ((newcwd = malloc(strlen(cwd) + strlen(filename) + 2)) != NULL)
	{
		/* Build new cwd from cwd and filename */
		newcwd[0] = '\0'; // This keeps the memory clean
		strcat(newcwd, cwd);
		strcat(newcwd, "/");
		strcat(newcwd, filename);
	}
	/* Error check */
	else
	{
		printf("Memory allocation failure\n");
		free(newpathname);
		return;
	}
	/* Start listing directory entries */
	/* Create needed variables */
	DIR *derr = opendir(newcwd); //current directory
	struct dirent *derrent; //directory entry structure
	/* Error check */
	/* This will see if what we're trying to open is actually a directory */
	if (derr == NULL)
	{
		free(newpathname);
		free(newcwd);
		return;
	}
	/* If we're here, we know that we're in a directory that can be opened */
	printf("\n\n");
	printf("%s\n", newpathname);
	strcat(newpathname, "/");
	char* newfilename;
	/* Read directory */
	while ((derrent = readdir(derr)) != NULL)
	{
		newfilename = derrent->d_name;
		/* List files and directories besides . and .. */
		if (strcmp(newfilename, ".") != 0 && strcmp(newfilename, "..") != 0)
		{	
			/* Print filename */
			printf("%s  ", newfilename);
		}
	}
	rewinddir(derr);
	/* Recurse over directories */
	while ((derrent = readdir(derr)) != NULL)
	{
		newfilename = derrent->d_name;
		if (strcmp(newfilename, ".") != 0 && strcmp(newfilename, "..") != 0)
		{
			/* Attempt to recurse over file, even if it's not a directory */
			recursedir(newcwd, newfilename, newpathname);
		}
	}
	/* Cleanup */
	closedir(derr);
	free(newpathname);
	free(newcwd);
	return;
}
