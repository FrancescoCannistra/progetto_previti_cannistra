#include "monitor.h"
#include <unistd.h>

void inizializza_monitor(const char* target_dir, int* fd, int* wd) {
    *fd = inotify_init();
    *wd = inotify_add_watch(*fd, target_dir, MONITOR_MASK);
}

void analizza_eventi(int fd, const char* target_dir) {
    char buffer[BUF_LEN];
    int length = read(fd, buffer, BUF_LEN);

    int i = 0;
    while (i < length) {
        struct inotify_event* event = (struct inotify_event*)&buffer[i];
        if (event->len) {
            int is_dir = event->mask & IN_ISDIR;
            if (event->mask & IN_CREATE) {
                if (is_dir) {
                    printf("IN_ISDIR | IN_CREATE: Creata la directory %s/%s\n", target_dir, event->name);
                } else {
                    printf("IN_CREATE: Creato il file %s/%s\n", target_dir, event->name);
                }
            } 
            else if (event->mask & IN_DELETE) {
                if (is_dir) {
                    printf("IN_ISDIR | IN_DELETE: Rimossa la directory %s/%s\n", target_dir, event->name);
                } else {
                    printf("IN_DELETE: Rimosso il file %s/%s\n", target_dir, event->name);
                }
            }
            else if (event->mask & IN_MOVED_FROM) {
                if (is_dir) {
                    printf("IN_ISDIR | IN_MOVED_FROM: Directory spostata o rinominata da %s/%s\n", target_dir, event->name);
                } else {
                    printf("IN_MOVED_FROM: File spostato o rinominato da %s/%s\n", target_dir, event->name);
                }
            }
            else if (event->mask & IN_MOVED_TO) {
                if (is_dir) {
                    printf("IN_ISDIR | IN_MOVED_TO: Directory spostata o rinominata in %s/%s\n", target_dir, event->name);
                } else {
                    printf("IN_MOVED_TO: File spostato o rinominato in %s/%s\n", target_dir, event->name);
                }
            }
        }
        i += EVENT_SIZE + event->len;
    }
}