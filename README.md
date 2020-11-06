# Azula
Freebsd rootkit 

# Tested on
Freebsd 12.1-RELEASE

# Why another freebsd rootkit
Well, the rootkits out there are outdated and they do the same thing(syscall hooking). That's good but I wanted to take it further. Reptile has been a big influence on this rootkit mainly the file tampering feature. Now it will be on Freebsd. Also instead to syscall hijacking, I will attempt inlink hooking. :)


# Features
* Hide files and directories
* File content tampering --> <azula> </azula>(WIP)
* Hide processes (WIP)

# Install
```
git clone https://github.com/emmaunel/azula.git
cd azula
make
kldload ./azula.ko
```

# Uninstall

```
kldunload azula
```

# Usage

# References


# Misc

* Look into graphical install menu(bsdconfig)
* find what syscall is called when passwd uses
* freebsd saves compiled binary /usr/obj/root/src(sometimes, weird)
