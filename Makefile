CC := clang
OBJCOPY := llvm-objcopy
CPPFLAGS := -DNDEBUG
CFLAGS := -std=c99 -Wall -Wextra -Werror -pedantic -x c
LDFLAGS :=

-include include.local.mk

all: ./out/hello.package

clean:
	rm -rf ./obj ./exe ./out

./out/%.package: ./exe/package ./out/%.module | ./out
	$^
./out/%.module: ./exe/module ./out/%.component | ./out
	$^
./out/%.component: ./exe/component src/%.txt ./obj/%.export.section ./obj/%.init.section ./obj/%.fini.section ./src/%.deps | ./out
	$^

./obj/%.export.section: ./obj/%.o | ./obj
	$(OBJCOPY) --dump-section .text,export=$@ $<
./obj/%.init.section: ./obj/%.o | ./obj
	$(OBJCOPY) --dump-section .text,init=$@ $<
./obj/%.fini.section: ./obj/%.o | ./obj
	$(OBJCOPY) --dump-section .text,fini=$@ $<

./obj/%.o: ./src/%.c | ./obj
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

./exe/%: ./obj/%_cli.o ./obj/%.o ./obj/util.o | ./exe
	$(CC) $(LDFLAGS) -o $@ $^

./exe ./obj ./out:
	mkdir $@
