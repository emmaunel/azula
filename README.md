# Azula
Freebsd rootkit 

# Tested on
Freebsd 12.1-RELEASE

# Why another freebsd rootkit
Well, the rootkits out ther are outdated and they do they same thing(syshook hooking). that's good but I wanted to take it further. Reptile has been a big influence on this rootkit mainly the file tampering feature. Now it's on Freebsd


# Features
* Hide files and directories
* File content tampering --> <azula> </azula>
* Hide processes

# Install
```
git clone https://github.com/emmaunel/azula.git
cd azula
make
kldload ./azula.ko
```

# Uninstall

# Usage

# References


# Misc

* Look into graphical install menu(bsdconfig)
* find what syscall is called when passwd uses
* freebsd saves compiled binary /usr/obj/root/src
