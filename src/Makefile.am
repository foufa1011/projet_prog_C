## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = glade

glade_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	centre.c centre.h \
	equipement.c equipement.h \
	membre.c membre.h \
	entraineur.c entraineur.h \
	evenement.c evenement.h \
	cours.c cours.h

glade_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

