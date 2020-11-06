#!/bin/bash

#sshpass ssh -o GlobalKnownHostsFile=/dev/null -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no stanz@$1$
if [ $# -gt 2 ]; then
    ssh -i redteam -o IdentitiesOnly=yes $1@$2 "$3"
    exit 1
fi

ssh -i redteam -o IdentitiesOnly=yes $1@$2