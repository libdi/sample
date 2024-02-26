CC = clang
OBJCOPY = llvm-objcopy

all: ./hello.package

clean:
	rm -f ./package ./module ./component ./*.section ./*.o

hello.package: ./package ./hello.module
	$@

./hello.module: ./module ./hello.component
	$@

./%.component: ./component src/%.txt ./%.export.section ./%.init.section ./%.fini.section
	$@

./%.export.section: ./%.o
	$(OBJCOPY) --dump-section .text,export=$@ $<
./%.init.section: ./%.o
	$(OBJCOPY) --dump-section .text,init=$@ $<
./%.fini.section: ./%.o
	$(OBJCOPY) --dump-section .text,fini=$@ $<

./%.o: ./src/%.c
	$(CC) -c -o $@ $<

./package: src/package.c
	$(CC) -o $@ $<
./module: src/module.c
	$(CC) -o $@ $<
./component: src/component.c
	$(CC) -o $@ $<
