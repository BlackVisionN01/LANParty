build:
	gcc *.c -o lanParty -g
run:
	./lanParty c.in d.in r.out
clean:
	rm -f lanParty
