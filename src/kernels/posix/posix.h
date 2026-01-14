#ifndef OPIUM_LINUX_POSIX_H
#define OPIUM_LINUX_POSIX_H

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <glob.h>
#include <signal.h>
#include <sys/resource.h>
#include <sched.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/vfs.h>
#include <sys/utsname.h>
#include <sys/prctl.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/un.h>
#include <sys/eventfd.h>
#include <sys/epoll.h>

#include <malloc.h>

#include <pthread.h>
#include <semaphore.h>

#include "posix_alloc.h"
#include "posix_event.h"

#endif /* OPIUM_LINUX_POSIX_H */
