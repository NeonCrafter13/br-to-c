CFLAGS = -O3

convert: convert.c
	gcc $(CFLAGS) -o convert convert.c

output: out/output.c
	gcc $(CFLAGS) -o out/output out/output.c

test: convert
	./convert

.PHONY: test

out: output
	out/output
