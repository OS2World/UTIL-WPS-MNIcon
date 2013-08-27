--- MNIcon class release 1.0 (02/21/93) by Makoto Nagata

include <wpicon.sc>

class: MNIcon,
    external stem = mnicon,
    local,
    external prefix = mnicon_,
    classprefix = mniconM_,
    major version = 1,
    minor version = 1;

parent: WPIcon;

methods:

override wpclsQueryTitle, class;

override wpDragOver;
override wpDrop;

passthru: C.ih;

#define INCL_32
#define INCL_WIN
#include <os2.h>

endpassthru:
