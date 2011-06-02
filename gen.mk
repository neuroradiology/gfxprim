#
# This is makefile rule for generating C sources from python generators
#
ifndef LIBNAME
$(error LIBNAME not defined, fix your library Makefile)
endif

ifndef GENHEADERS
GENHEADERS=
endif

ifndef GENSOURCES
GENSOURCES=
endif

#
# Headers goes into include/core/
#
INCLUDE_PREFIX=$(TOPDIR)/include/$(LIBNAME)/
RGENHEADERS=$(addprefix $(INCLUDE_PREFIX),$(GENHEADERS))

#
# Generate genfiles for generated sources
#
CSOURCES+=$(GENSOURCES)

#
# Make the genrated headers actually build
#
all: $(RGENHEADERS)

$(CSOURCES): $(RGENHEADERS)

#
# And clean them
#
CLEAN+=$(GENSOURCES) $(RGENHEADERS)

#
# Currently, just depend on all python files
#
GENERATORS=$(PYTHON_FILES)

#
# Generated files depend on python generators and libs
#
%.gen.c %.gen.h: $(GENERATORS)
ifdef VERBOSE
	${PYTHON} ${TOPDIR}/pylib/bin/generate_file.py "$@"
else
	@echo "GEN  $@"
	@${PYTHON} ${TOPDIR}/pylib/bin/generate_file.py "$@"
endif

