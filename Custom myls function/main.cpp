/*
CODE BY: KIRK SAECHAO
CS570 ASSIGNMENT #1 PART II
SAN DIEGO STATE UNIVERSITY
*/

#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

using namespace std;

//subroutine prototypes
int noArgs(int h);
int multipleArgs(int h,int numDir, char  *argList[]);

int main(int argc, char *argv[])
{
    int hFlag = 0;

    //checks for h flag
    if (argc >= 2 && strcmp(argv[1],"-h") == 0)
        hFlag = 1;

    //no additional directories specified. access present directory.
    if (argc == 1)
        noArgs(hFlag);

    //no additional directories specified, but -h parsed
    else if (hFlag == 1 && argc == 2)
        noArgs(hFlag);

    //multiple directories specified
    else
        multipleArgs(hFlag, argc, argv);

    return 0;
}

//if no additional directories specified, use this.
int noArgs(int h)
{
    DIR *currentDir;
    struct dirent *dirPointer;
    //open present working directory
    currentDir = opendir(".");
    if (currentDir == NULL)
    {
        cout << "Cannot access current directory." << endl;
    }
        //h flag detected
        else if (h == 1)
        {
            //loop to print out contents
            while ((dirPointer = readdir(currentDir)) != NULL)
            {
                cout << dirPointer->d_name << endl;
            }
        }
        else //h flag not detected
        {
            while ((dirPointer = readdir(currentDir)) != NULL )
            {
                //if first character in filename is not a dot
                if (dirPointer->d_name[0] != '.')
                {
                    cout << dirPointer->d_name << endl;
                }
            }
        }
    //printing finished, close active directory
    closedir(currentDir);
    return 0;
}

//multipleArgs - If multiple directories were specified, use this.
int multipleArgs(int h, int numDir, char *argList[])
{
    DIR *currentDir;
    struct dirent *dirPointer;
    //cycling thru num of specified directories
    for (int dirCounter = 1; dirCounter < numDir; dirCounter++)
    {
        //checking if opendir is successful
        currentDir = opendir(argList[dirCounter+h]);
        if (currentDir == NULL)
        {
            cout << "Cannot access specified directory" << endl;
            closedir(currentDir);
        }
        //h flag detected
        else if (h == 1)
        {
                while ((dirPointer = readdir(currentDir)) != NULL)
                {
                    cout << dirPointer->d_name << endl;
                }
                closedir(currentDir);
        }
        //h flag not detected
        else
        {
                while ((dirPointer = readdir(currentDir)) != NULL )
                {
                    if (dirPointer->d_name[0] != '.')
                    {
                        cout << dirPointer->d_name << endl;
                    }
                }
                closedir(currentDir);
        }
    }

    return 0;
}
