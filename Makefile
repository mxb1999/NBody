GCC = gcc
LIB =
TREESRC = tree/src
TREEINC = tree/include
TREEFLAGS = -Wall -Werror -Og -g -std=c99 -I$(TREEINC)
TREEOBJ = tree/bin

_COBJ = test.o staticTree.o  #Core C++ files being used
COBJ = $(patsubst %,$(TREEOBJ)/%,$(_COBJ))

$(TREEOBJ)/%.o:  $(TREESRC)/%.c#Compile instructions for individual C++ source files
	$(GCC) $(TREEFLAGS) -c -o $@ $^


treesim: $(COBJ)  #Program compile
	$(GCC) $(TREEFLAGS) -o $@ $^

.phony: clean

#removes all object and dependency files, must be run when a change is made to .h files
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm -f $(ODIR)/*.d *~ core $(INCDIR)/*~

.phony: reset

reset:
	make clean
	make
