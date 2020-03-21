#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define REPORT_FILE "packages_report.txt"
#define MAX_STR_LEN 500
#define ARR_MAX_SIZE 100
// IF the value of total packages surpases the limit, feel free to increment this value
#define PACKAGES_MAX_NUMBER 1000


// This is the struct that is used for the array of package data
struct package {
    char *name;
    char *installDate;
    char *updateDate;
    int updates;
    char *removedDate;
    int removed;
};


// This function reads a line and returns and array of 4 strings
// The first one is the date, se second one is the name of the bundle, 
// the third one is the action and the fourth one is the name of the package
char ** readLine(int fl) {
    char **arr;
    arr = malloc(sizeof(char*) * ARR_MAX_SIZE);
    for(int i = 0; i < ARR_MAX_SIZE; i++) {
        arr[i] = malloc(sizeof(int*) * ARR_MAX_SIZE);
    }
    char bff[1];
    int section = 0;
    int pointer = 0;
    int spaces = 0;
    while (read(fl,bff,1) == 1) {
        if (bff[0] == ' ') {
            spaces++;
            if (spaces>1) {
                for (int i = pointer; i < ARR_MAX_SIZE-pointer; i++)
                {
                    arr[section][i] = '\0';
                }
                pointer = 0;
                section++;
            } 
        }
        if (spaces<5) {
            if ((bff[0] != ' ') || (spaces == 1)) {
                arr[section][pointer] = bff[0];
                pointer++;
            }
        }
        if (bff[0] == '\n') {
            return arr;
        }
    }
}


// This function checks if a package is already installed
int package_installed(char* name, int installed, struct package* packages) {
    for (int i = 0; i < installed; i++) {
        if (strcmp(name,packages[i].name) == 0) {
            return i;
        }
    }
    return -1;
}


// This function checks if a package is already removed
int package_removed(char* name, int installed, struct package* packages) {
    for (int i = 0; i < installed; i++) {
        if (strcmp(name,packages[i].name) == 0) {
            if (packages[i].removed == 1) {
                return i;
            }
            return -1;
        }
    }
    return -1;
}


// This function erases the brackets of the date
char* trimDate(char* date) {
    int i;
	for(i=1;i<strlen(date)-1;i++) {
		date[i-1]=date[i];
	}
	date[i-1]='\0';
    return date;
}


void analizeLog(char *logFile, char *report);


int main(int argc, char **argv) {

    if (argc < 2) {
	printf("Usage:./pacman-analizer.o pacman.log\n");
	return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

// Function that analyzes the log file and generates a new file
void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    // Opens logFile
    int fl = 0;
    if((fl = open(logFile, O_RDONLY)) == -1) {
        printf("File not found\n");
        return;
    }

    char **line;
    int index = 0;
    int installed_packages = 0;
    int removed_packages = 0;
    int upgraded_packages = 0;
    int current_installed = 0;
    struct package packages[PACKAGES_MAX_NUMBER];

    // Reads line by line of the log file
    while (line = readLine(fl))
    {
        line[0] = trimDate(line[0]);
        // If action is install
        if (strcmp(line[2],"installed") == 0) {
            // If the package is not installed
            if (package_installed(line[3],installed_packages,packages) < 0) {
                // Adds installation of package
                installed_packages++;
                current_installed++;
                packages[index].name = line[3];
                packages[index].installDate = line[0];
                packages[index].removed = 0;
                packages[index].removedDate = "-";
                packages[index].updates = 0;
                packages[index].updateDate = "-";
                index++;
            }
        // If action is remove
        } else if (strcmp(line[2],"removed") == 0) {
            // Check if package is installed
            int installed = package_installed(line[3],installed_packages,packages);
            if (installed >= 0) {
                // Adds the removal data of the package
                removed_packages++;
                current_installed--;
                packages[installed].removed = 1;
                packages[installed].removedDate = line[0];
            }
        // If action is update
        } else if (strcmp(line[2],"upgraded") == 0) {
            // If the package is installed and has not being removed
            int installed = package_installed(line[3],installed_packages,packages);
            int removed = package_removed(line[3],installed_packages,packages);
            if ((installed >= 0) && (removed == -1)) {
                // Adds update data into the package information
                upgraded_packages++;
                packages[installed].updates++;
                packages[installed].updateDate = line[0];
            }
        }   
    }

    // After the package has been analyzed, the file is closed and the file for writting the results is openned
    close(fl);
    int wFile = open("packages_report.txt", O_WRONLY | O_CREAT, 0640);

    char text[MAX_STR_LEN];
    
    // This section writes on the file the four main values of the analysis
    char* title = "Pacman Packages Report\n----------------------\n";
    write(wFile, title, strlen(title));
    sprintf(text, "%s%d\n", "- Installed packages : ", installed_packages);
    write(wFile, text, strlen(text));
    sprintf(text, "%s%d\n", "- Removed packages : ", removed_packages);
    write(wFile, text, strlen(text));
    sprintf(text, "%s%d\n", "- Upgraded packages : ", upgraded_packages);
    write(wFile, text, strlen(text));
    sprintf(text, "%s%d\n", "- Current installed : ", current_installed);
    write(wFile, text, strlen(text));
    char* secTitle = "\nList of packages\n----------------\n";
    write(wFile, secTitle, strlen(secTitle));

    // For each package, its data is written in the file
    for (int i = 0; i < installed_packages; i++) {
        sprintf(text, "%s%s\n", "- Package Name : ", packages[i].name);
        write(wFile,text,strlen(text));
        sprintf(text, "%s%s\n", "     - Install date : ", packages[i].installDate);
        write(wFile,text,strlen(text));
        sprintf(text, "%s%s\n", "     - Last update date : ", packages[i].updateDate);
        write(wFile,text,strlen(text));
        sprintf(text, "%s%d\n", "     - How many updates : ", packages[i].updates);
        write(wFile,text,strlen(text));
        sprintf(text, "%s%s\n", "     - Removal date : ", packages[i].removedDate);
        write(wFile,text,strlen(text));
    }
    
    close(wFile);

    printf("Report is generated at: [%s]\n", report);
}