SHELL=/bin/bash
all: tutto.txt

tutto.txt: B1.txt B2.txt
	cat B1.txt B2.txt > tutto.txt

B1.txt: A1.txt
	cat A1.txt > B1.txt
	date >> B1.txt

B2.txt: A2.txt
	date > B2.txt
	cat A2.txt >> B2.txt

A1.txt:
	[[ -f A1.txt ]] || echo "AAAA" > A1.txt

A2.txt:
	[[ -f A2.txt ]] || echo "ZZZZ" > A2.txt

.PHONY: clean touch

clean:
	-rm A1.txt A2.txt

touch:
	if [[ -e B1.txt ]]; then touch B1.txt; fi;

# Nella soluzione del prof i file A1 e A2, vengono ricreati anche quando
# vengono modificati, non solo quando non esistono
# ho problemi con il touch
# Comando che avevo messo io: [[ -f B1.txt ]] && touch B1.txt
