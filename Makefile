.PHONY: static dynamic debug clean test

SRCDIR=src
BINDIR=bin

build:
	mkdir -p $(BINDIR)
	#movcc -Wf--no-mov-extern -static $(SRCDIR)/freedrink.c -s -o $(BINDIR)/freedrink
	movcc $(SRCDIR)/freedrink.c -o $(BINDIR)/freedrink
	mv $(BINDIR)/freedrink% $(BINDIR)/freedrink
	strip -s $(BINDIR)/freedrink
	objcopy \
		--remove-section .eh_frame \
		--remove-section .hash \
		--remove-section .gnu.hash \
		--remove-section .note.gnu.property \
		--remove-section .shstrtab \
		bin/freedrink bin/temp
	mv bin/temp bin/freedrink

debug:
	mkdir -p $(BINDIR)
	gcc -Wall -I$(SRCDIR) -g -DDEBUG $(SRCDIR)/freedrink.c -o $(BINDIR)/freedrink

clean:
	rm -f $(SRCDIR)/*.o $(BINDIR)/freedrink

