GCC = gcc
MDIR = code/bin
BDIR = code/bruteForce/bin
BSRC = code/bruteForce/src
TREESRC = code/tree/src
SIMINC = -Icode/tree/include -Icode/include -Icode/bruteForce/include
LIBS = -lm
TREEFLAGS =  -g  -std=c99 -O3 -Wall -Werror $(SIMINC)
TREEOBJ = code/tree/bin
MAIN = code/src
MDIR = code/bin
_CTREE = tree.o  #Core C++ files being used
CTREE = $(patsubst %,$(TREEOBJ)/%,$(_CTREE))

_CMAIN = dynamics.o particle.o  #Core C++ files being used
CMAIN = $(patsubst %,$(MDIR)/%,$(_CMAIN))

_CBRUTE = io.o  #Core C++ files being used
CBRUTE = $(patsubst %,$(BDIR)/%,$(_CBRUTE))

#_CMESH = test.o staticTree.o  #Core C++ files being used
#CMESH = $(patsubst %,$(TREEOBJ)/%,$(_CMESH))

$(TREEOBJ)/%.o:  $(TREESRC)/%.c #Compile instructions for individual C++ source files
	$(GCC) $(TREEFLAGS) -c -o $@ $^ $(LIBS)

$(BDIR)/%.o:  $(BSRC)/%.c #Compile instructions for individual C++ source files
	$(GCC) $(TREEFLAGS) -c -o $@ $^ $(LIBS)

$(MDIR)/%.o:  $(MAIN)/%.c #Compile instructions for individual C++ source files
	$(GCC) $(TREEFLAGS) -c -o $@ $^ $(LIBS)

treesim: $(CTREE) $(CMAIN)# $(CBRUTE) #Program compile
	$(GCC) $(TREEFLAGS) -o $@ $^ $(LIBS)

.phony: clean

#removes all object and dependency files, must be run when a change is made to .h files
clean:
	rm -f $(TREEOBJ)/*.o *~ core $(INCDIR)/*~
	rm -f $(MDIR)/*.o *~ core $(INCDIR)/*~
	rm -f $(BDIR)/*.o *~ core $(INCDIR)/*~
	rm -f $(ODIR)/*.d *~ core $(INCDIR)/*~

.phony: reset

reset:
	make clean
	make

.phony: run

run:
	make
	./treesim
