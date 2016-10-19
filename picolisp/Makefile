PICOLISP = miniPicoLisp
WORK_DIR = $(PICOLISP)
TARFILE = $(PICOLISP).tgz

PATCHFILES = $(sort $(wildcard patches/*.patch))

PATCH_CMD = \
        for f in $(PATCHFILES); do\
            echo $$f; \
            patch -s -d $(WORK_DIR) -p1 -b -z .original < $$f; \
        done

all:
	tar zxf $(TARFILE)
	$(PATCH_CMD)
	#cd files; tar -c -f - * | (cd ../$(WORK_DIR) ; tar xfp -)
	make -C $(WORK_DIR)/src libpicolisp.a 

clean:
	-rm -rf $(WORK_DIR)
