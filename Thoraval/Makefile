# MODIFICATIONS : #=====#

# program

NOM_PROGRAMME=impression_max4

# bibliotheque amble

#=====# A MODIFIER 
LIB_AMBLE=~/pour_les_tp_de_parallelisme_septembre_2011/amble_CIE/

# native code compiling

NATIVE_LIBS=unix.cmxa threads.cmxa amble.cmxa
OCAMLOPT=ocamlopt
#=====# n'a pas ete compile par l'administrateur #=====#OCAMLOPT=ocamlopt.opt

OCAMLOPTFLAGS=-thread -I $(LIB_AMBLE)


# bytecode compiling

BYTECODE_LIBS=unix.cma threads.cma amble.cma
OCAMLC=ocamlc
OCAMLCFLAGS=-thread -I $(LIB_AMBLE)



all: bytecode native

bytecode: $(NOM_PROGRAMME).cmo
	$(OCAMLC) $(OCAMLCFLAGS) $(BYTECODE_LIBS) \
           $(NOM_PROGRAMME).cmo -o $(NOM_PROGRAMME).b

native:	$(NOM_PROGRAMME).cmx
	$(OCAMLOPT) $(OCAMLOPTFLAGS) $(NATIVE_LIBS) \
           $(NOM_PROGRAMME).cmx -o $(NOM_PROGRAMME)

clean:
	rm -f *.cm* *.o $(NOM_PROGRAMME) $(NOM_PROGRAMME).b


.SUFFIXES: .ml .mli .cmi .cmo .cmx

.mli.cmi:
	$(OCAMLC) $(OCAMLCFLAGS) -c $<

.ml.cmo:
	$(OCAMLC) $(OCAMLCFLAGS) -c $<

.ml.cmx:
	$(OCAMLOPT) $(OCAMLOPTFLAGS) -c $<

