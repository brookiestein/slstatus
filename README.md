**slstatus - suckless status**
==========================
slstatus is a suckless status monitor for window managers that use WM_NAME
(e.g. dwm) or stdin to fill the status bar.


**Features**
--------
- Battery percentage/state/time left
- CPU usage
- CPU frequency
- Custom shell commands
- Date and time
- Disk status (free storage, percentage, total storage and used storage)
- Available entropy
- Username/GID/UID
- Hostname
- IP address (IPv4 and IPv6)
- Kernel version
- Keyboard indicators
- Keymap
- Load average
- Network speeds (RX and TX)
- Number of files in a directory (hint: Maildir)
- Memory status (free memory, percentage, total memory and used memory)
- Swap status (free swap, percentage, total swap and used swap)
- Temperature
- Uptime
- Volume percentage (OSS/ALSA)
- WiFi signal percentage and ESSID


**Requirements**
------------
Currently slstatus works on FreeBSD, Linux and OpenBSD.
In order to build slstatus you need the Xlib header files.

If you will not change nothing of this configuration, you also will need:
```
1. acpilight
2. alsa
```
ALSO, IS POSSIBLE THAT NEED CHANGE THE VALUE OF THE VARIABLE **"bat"** in case of that use a laptop and
his battery file not find in **/sys/class/power_supply/BAT0.** Generally the value of this is: **BAT0** or **BAT1.**

Installation
------------
Edit config.mk to match your local setup (slstatus is installed into the
/usr/local namespace by default).

Afterwards enter the following command to build and install slstatus (if
necessary as root):

    make clean install


Running slstatus
----------------
See the man page for details.


Configuration
-------------
slstatus can be customized by creating a custom config.h and (re)compiling the
source code. This keeps it fast, secure and simple.

Todo
----
Cleaning up the whole codebase it the goal before thinking about a release.
