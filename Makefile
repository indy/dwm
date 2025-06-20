# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

##########################################################
#
# (isg) One time installation for lightdm on ubuntu with:
# $ sudo make indy-system-install
#
# then further installs are:
# $ make install
#
##########################################################

include config.mk

SRC = drw.c dwm.c util.c
OBJ = ${SRC:.c=.o}

all: options dwm

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

dwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f dwm ${OBJ} dwm-${VERSION}.tar.gz

dist: clean
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		dwm.1 drw.h util.h ${SRC} dwm.png transient.c dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf dwm-${VERSION}

install: all
	mkdir -p ${PREFIX}/bin
	cp -f dwm ${PREFIX}/bin
	chmod 755 ${PREFIX}/bin/dwm
	mkdir -p ${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dwm.1 > ${MANPREFIX}/man1/dwm.1
	chmod 644 ${MANPREFIX}/man1/dwm.1
	cp scripts/user/* ${PREFIX}/bin

uninstall:
	rm -f ${PREFIX}/bin/dwm\
		${MANPREFIX}/man1/dwm.1

# invoke once as sudo to setup lightdm with a dwm session option
indy-system-install:
	cp scripts/system/dwm.desktop /usr/share/xsessions/.
	cp scripts/system/dwmstart /usr/local/bin/.
	chmod 755 /usr/local/bin/dwmstart

.PHONY: all options clean dist install uninstall indy-system-install
