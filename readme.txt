NewSlide by Afrothunder.
Version 2
---
Changelog:
-Checks for Memory Stick condition(would not activate if one was inserted before)
---

Released under a BSD license (see LICENSE.txt)

NewSlide is a plugin that allows one to replace the slide
function of his or her PSPgo unit. Upon closing the screen
NewSlide will automatically start an EBOOT from the location
ef0:/NEWSLIDE/EBOOT.PBP. NewSlide ships with a default
launch EBOOT that utilizes the PSP's web browser to show a
custom clock. The web browser has a settings.ini file that
allows the user to change some settings, such as the page
that is loaded. This web browser will by default exit back
to the XMB when the screen is opened, but this may be changed.

Installation:
1) Copy NewSlide.prx from /bin/SEPLUGINS to the plugins
directory for your HEN/CFW and enable it in vsh.txt.

2) Copy /bin/NEWSLIDE to the root of your System Storage.

3) Restart the VSH and slide your screen to the closed position.

NOTES & TIPS:
- You can change widgets.htm in the NEWSLIDE folder to change
  the custom clock.
- You can change settings.ini in the NEWSLIDE folder to change
  browser settings. This allows you to load pages from the
  internet when you close your screen.
- You can replace the EBOOT.PBP file in the NEWSLIDE folder to
  load any program you want when you close your screen.
- Shameless plug: Try HomebrewStore! http://hbstore.screeze.com

This Homebrew is an entry for the PSP Genesis competition 2011,
sponsored by npt, psp-hacks.com, pspgen.com, pspslimhacks.com,
exophase.com, pspcustomfirmware.com, daxhordes.org, gamegaz.jp,
and wololo.net