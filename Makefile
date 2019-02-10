CFLAGS += -Werror=implicit-function-declaration
CFLAGS += -Werror=missing-prototypes
CFLAGS += -Werror=return-type
CFLAGS += -Werror=incompatible-pointer-types
CFLAGS += -Werror=undef

use-test: use-test.o lib.o

lib.o: lib.c egl_trie.h

egl_trie.h: egl_entrypoints.txt
	python gen_lib.py --entrypoints $^ --prefix egl --header $@

.INTERMEDIATE: egl_trie.h use-test.o lib.o

test:: use-test
	python order_check.py egl_entrypoints.txt
	./use-test

clean::
	rm -f egl_trie.h use-test *.o