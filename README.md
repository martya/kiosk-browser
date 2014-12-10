This is a minimal WebKit based browser.
It's intended use is to display a single web resource non-interactively,
while being highly portable, especially to the arm11 architecture (used for the Raspberry Pi), and supporting Javascript and HTML5 Websockets for dynamic content updates.

# CONTEXT
This branch it's a custom to make an Raspberry Pi Kiosk project...
 - unmaximize is disabled
 - GTK_VERSION 3.0 & WEBKITGTK 3.0
 - scrolledWindow is optional (--scrolled)
 - url is optional (--url="")

# COMPILING
    apt-get install libwebkitgtk-3.0-dev
    make

# INSTALLING
No special steps are required for installation. Just execute `browser`.
This program was designed to be started via inittab on boot like this:

    1:2345:respawn:/usr/bin/startx -e /usr/bin/browser --url="http://10.0.0.5/zfs/monitor" tty1 </dev/tty1 >/dev/tty1 2>&1

# USAGE
	browser 
    browser --url="<URL>"
	browser --url="<URL>" --scrolled
	
This will launch the browser in fullscreen mode and load the resource at `URL`.
`URL` can be anything that WebKit supports, including `file://`-URLs for local webpages and documents.
Omitting `URL` shows the default page, this README.

`scrolled' add to the window scroll bar

The following keybindings exist:
  - `F5` for reloading the current page

These action are also implemented as signal handlers:
  - `HUP` for reload
  
# THANKS

Thanks to Florian Fischer And Peter Schultz.
