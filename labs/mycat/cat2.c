#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>


/* filecopy:  copy file ifp to file ofp */
void filecopy(int fl)
{
    char bff[1];

    if (fl == -1) {
        int c;
        while ((c = getchar()) != EOF) {
            printf("%c",c);
        }
    } else {
        while ((read(fl,bff,1)) == 1) {
            printf("%c",bff[0]);
        }
    }
}

/* cat:  concatenate files, version 2 */
int main(int argc, char *argv[])
{
    clock_t start = clock();
    int fl = 0;
    char *prog = argv[0];   /* program name for errors */

    if (argc == 1) {
        filecopy(-1);
    } else {
        while (--argc > 0) {
            if((fl = open(*++argv, O_RDONLY)) == -1) {
                printf("Error: Cannot open '%s'\n", *argv);
                return 0;
            } else {
                filecopy(fl);
                close(fl);
            }
        }
    }
    clock_t end = clock();
    double total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("-----\nEXECUTION CLOCK TIME = %f\n-----\n", total);
    return 0;
}
