(head -n 5 /usr/include/stdio.h | tail -n 3  ; tail -n 4 /usr/include/stdio.h | cut -b -3 ) | (read A; read B; echo ciao; echo kelvin ; read RIGA &> /dev/null; while read RIGA; do echo 0; done)
