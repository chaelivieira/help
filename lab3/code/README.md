# linux-kernel-module


Simple examples of Linux Kernel Modules, written as a learning exercise.

<!-- vim-markdown-toc GFM -->

* [Sample 1: Greeter](#sample-1-hello)
    * [Building the Module](#building-the-module)
    * [Installing / Uninstalling](#installing--uninstalling)
* [Sample 2: Babel](#sample-2-babel)
* [Tips](#tips)
* [Reading](#reading)

<!-- vim-markdown-toc -->

## Project 1: Hello

This sample simply takes a name as a parameter, and writes a greeting to the kernel log (`/var/log/kern.log`). `cd` into `hello/` before running any of the commands before.

### Building the Module

```sh
make
```

The module is compiled to `hello.ko`.

### Installing / Uninstalling

```sh
# Install:
sudo insmod hello.ko

# Install with parameters:
sudo insmod hello.ko name=Frodo

# Uninstall
sudo rmmod hello
```

## Project 2: qmod

`qmod` is a character driver which adds a device called
`/dev/qmod`. This device provides a shared queue for sending and
receiving messages (see qadd.c and qremove.c for example clients).

Install with:

```sh
cd qmod
make
sudo insmod qmod.ko
```

Then run the test clients, which will let you exchange messages through the `/dev/qmod` device:

```sh
sudo ./qadd your-message-here
```

```sh
sudo ./qremove
```

Uninstall with:

```sh
sudo rmmod qmod
```

Make the `/dev/qmod` device read/write accessible without super user priviledges by adding a rule. First get the Kernal and Subsystem name:

```sh
udevadm info -a -p /sys/class/qmod/qmod

# Will show something like:
#   KERNEL=="qmod"
#   SUBSYSTEM=="qmod"
```

Now create a low-priority rule to enable user access:

```sh
echo 'KERNEL=="qmod", SUBSYSTEM=="qmod", MODE="0666"' >> /etc/udev/rules.d/99-qmod.rules
```

Reload the driver and it will be accessible without superuser rights.

## Tips

Show loaded modules with:

```sh
lsmod
```

Show `menuconfig` with:

```sh
sudo make menuconfig
```

Show the kernel log with:

```sh
dmesg
```

Show info about the module:

```sh
modinfo hello.ko
```

Note: if you get the following error:

```
insmod: ERROR: could not insert module hello.ko: Invalid parameters
```

Then make sure you are not trying to install the module from a shared location (such as a shared folder on a virtual machine). Copy it to the home directory and install from there instead.

Trace module calls with:

```sh
sudo apt-get install strace
sudo strace ./qmod/qadd
sudo strace ./qmod/qremove
```

`strace` will show low-level system calls in realtime as the program makes them.

## Reading

The bulk of this code came from Dave Kerr, based in turn on these blog posts by
Derek Molloy:

http://derekmolloy.ie/writing-a-linux-kernel-module-part-1-introduction/

http://derekmolloy.ie/writing-a-linux-kernel-module-part-2-a-character-device/
