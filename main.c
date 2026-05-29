#include <stdio.h>
#include <unistd.h>
#include "monitor.h"

int main(int argc, char* argv[]) {
    const char* target_dir = argv[1];
    int fd, wd;
    inizializza_monitor(target_dir, &fd, &wd);
    printf("[INFO] Monitoraggio avviato sulla cartella: %s\n\n", target_dir);
    while (1) {
        analizza_eventi(fd, target_dir);
    }
    inotify_rm_watch(fd, wd);
    close(fd);

    return 0;
}