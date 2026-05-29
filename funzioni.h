#ifndef MONITOR_H
#define MONITOR_H

#include <stdio.h>
#include <sys/inotify.h>
#include <limits.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + NAME_MAX + 1 ) )
#define MONITOR_MASK ( IN_CREATE | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO )

void inizializza_monitor(const char* target_dir, int* fd, int* wd);
void analizza_eventi(int fd, const char* target_dir);
#endif