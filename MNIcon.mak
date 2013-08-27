class = MNIcon
# cflags = /c /Q /Ge- /Gd- /Se /Re /ss /Ms /Gm+
cflags =/Ss /Q /Rn /Ge- /Gs /Ms /C .\$*.c
lflags = /NOI /NOL /ALIGN:16 /M /PACKCODE /PACKDATA /EXEPACK
dll_libs = os2386.lib som.lib
map = NUL
subobjs =

.SUFFIXES:
.SUFFIXES: .c .obj .dll .csc .sc .h .ih .ph .psc .rc .res .def

.csc.ih:
    sc -r $*.csc

.csc.c:
    sc -r $*.csc

.c.obj:
    icc $(cflags) $*.c

.rc.res:
    rc -r $*.rc $*.res

all: $(class).dll

$(class).ih: $(class).csc
$(class).obj: $(class).c $(class).ih $(class).h $(class).sc
$(class).dll: $(class).obj $(subobjs)
    LINK386 $(lflags) $* $(subobjs), $*.dll, $(map), $(dll_libs), $*.def;
