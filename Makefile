

all:
	make -C picolisp $@
	make -C board/st/stm32f4/mb997 $@

clean:
	make -C picolisp $@
	make -C board/st/stm32f4/mb997 $@

