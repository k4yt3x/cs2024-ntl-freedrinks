.PHONY: static dynamic debug clean test

SRCDIR=src
BINDIR=bin

build:
	mkdir -p $(BINDIR)
	#movcc -Wf--no-mov-extern -static $(SRCDIR)/freedrinks.c -s -o $(BINDIR)/freedrinks
	movcc $(SRCDIR)/freedrinks.c -o $(BINDIR)/freedrinks
	mv $(BINDIR)/freedrinks% $(BINDIR)/freedrinks
	strip -s $(BINDIR)/freedrinks
	objcopy \
		--remove-section .eh_frame \
		--remove-section .hash \
		--remove-section .gnu.hash \
		--remove-section .note.gnu.property \
		--remove-section .shstrtab \
		bin/freedrinks bin/temp
	mv bin/temp bin/freedrinks

debug:
	mkdir -p $(BINDIR)
	gcc -Wall -I$(SRCDIR) -g -DDEBUG $(SRCDIR)/freedrinks.c -o $(BINDIR)/freedrinks

clean:
	rm -f $(SRCDIR)/*.o $(BINDIR)/freedrinks

