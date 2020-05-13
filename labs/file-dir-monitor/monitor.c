#define _XOPEN_SOURCE 500
#define BUFFER_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

#include <ftw.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/inotify.h>

#include "logger.h"

int inotify_fd;
int wd;

//Function from https://linux.die.net/man/3/nftw
static int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf) {
    if(tflag == FTW_D){
         wd = inotify_add_watch(inotify_fd, fpath, IN_CREATE | IN_DELETE | IN_MOVE);
        if (wd == -1) {
            errorf("Error while adding watch to inotify");
        }
    }
    return 0; 
}

//Function from inotify/demo_inotify.c
static void displayInotifyEvent(struct inotify_event *i) {
    if (i->mask & IN_CREATE)        infof("CREATED %s\n",i->name);
    if (i->mask & IN_DELETE)        infof("DELETED %s\n",i->name);
    if (i->mask & IN_MOVED_FROM)    infof("RENAMING %s ",i->name);
    if (i->mask & IN_MOVED_TO)      infof("TO %s\n", i->name);
}


int main(int argc, char *argv[]) {
    
    int flags = 0;
    char buffer[BUFFER_LEN] __attribute__ ((aligned(8)));
    char *c;
    size_t rValue;
    struct inotify_event *event;

    inotify_fd = inotify_init();
    if (inotify_fd == -1) {
        errorf("Error with initialization of inotify");
    }

    if (argc > 2 && strchr(argv[2], 'd') != NULL) {
        flags |= FTW_DEPTH;
    }

    if (argc > 2 && strchr(argv[2], 'p') != NULL) {
        flags |= FTW_PHYS;
    }

    if (nftw((argc < 2) ? "." : argv[1], display_info, 20, flags) == -1) {
        errorf("Error on nftw usage");
        exit(EXIT_FAILURE);
    }

    while (1) { 

        rValue = read(inotify_fd, buffer, BUFFER_LEN);

        if (rValue == -1) {
            errorf("Error while reading");
        }

        if (rValue == 0) {
            errorf("Returned 0 from read (inotify_fd)");
        }

        for (c = buffer; c < buffer + rValue; ) {
            event = (struct inotify_event *) c;
            displayInotifyEvent(event);

            c += sizeof(struct inotify_event) + event->len;
        }
    }

    exit(EXIT_SUCCESS);
}
