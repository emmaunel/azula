#!/usr/bin/python3

import os
from cmd import Cmd
import socket

name = "Azula client"
author = "Written by: PabloPotat0"
logo = """
 ▄▄▄      ▒███████▒ █    ██  ██▓    ▄▄▄      
▒████▄    ▒ ▒ ▒ ▄▀░ ██  ▓██▒▓██▒   ▒████▄    
▒██  ▀█▄  ░ ▒ ▄▀▒░ ▓██  ▒██░▒██░   ▒██  ▀█▄  
░██▄▄▄▄██   ▄▀▒   ░▓▓█  ░██░▒██░   ░██▄▄▄▄██ 
 ▓█   ▓██▒▒███████▒▒▒█████▓ ░██████▒▓█   ▓██▒
 ▒▒   ▓▒█░░▒▒ ▓░▒░▒░▒▓▒ ▒ ▒ ░ ▒░▓  ░▒▒   ▓▒█░
  ▒   ▒▒ ░░░▒ ▒ ░ ▒░░▒░ ░ ░ ░ ░ ▒  ░ ▒   ▒▒ ░
  ░   ▒   ░ ░ ░ ░ ░ ░░░ ░ ░   ░ ░    ░   ▒   
      ░  ░  ░ ░       ░         ░  ░     ░  ░
          ░                                  
"""


class Terminal(Cmd):
    prompt = "azula-client> "
    lhost = ""
    lport = ""
    rhost = ""
    rport = ""

    def __init__(self):
        Cmd.__init__(self)

    def do_exit(self, args):
        "Exit this shell"
        print("Always be on the lookout")
        exit(0)

    def do_clear(self, args):
        os.system("clear")

    def do_set(self, args):
        "set value to a variable\nset <variable> <value>\nExample: set LHOST 192.168.213.5"
        
        arg = args.split()
        if arg[0] == "RHOST":
            print("[+] RHOST --> " + arg[1])
            self.rhost = arg[1]
        elif arg[0] == "RPORT":
            print("[+] RPORT --> " + arg[1])
            self.rport = arg[1]
        elif arg[0] == "LHOST":
            print("[+] LHOST --> " + arg[1])
            self.lhost = arg[1]
        elif arg[0] == "LPORT":
            print("[+] LPORT --> " + arg[1])
            self.lport = arg[1]


    def do_unset(self, args):
        "unset value to a variable\nunset <variable>\nExample: unset LHOST "

        arg = args.split()
        if arg[0] == "RHOST":
            self.rhost = ""
        elif arg[0] == "RPORT":
            self.rport = ""
        elif arg[0] == "LHOST":
            self.lhost = ""
        elif arg[0] == "LPORT":
            self.lport = ""

    def do_show(self, args):
        "show the current configuration"
        print("VAR          VALUE         DESCRIPTION")
        print("LHOST " + self.lhost + " Local host to receive the shell")
        print("LPORT " + self.lport + " Local port to receive the shell")
        print("RHOST " + self.rhost + " Remote host")
        print("RPORT " + self.rport + " Remote port")


    def do_run(self, args):
        "run the listener and send the magic packet"

    

def main():
    print(name)
    print(author)
    print(logo)

    terminal = Terminal()
    terminal.cmdloop()


if __name__ == "__main__":
    main()