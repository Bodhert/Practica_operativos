#! /bin/bash
make
rm /dev/shm/mem
./controlewe -n mem src/ficheros_entrada/mews/entrada_bigendian.mew 
xxd /dev/shm/mem > mem.txt
nano mem.txt
./interewe -n mem src/ficheros_entrada/bews/mac.bew
xxd /dev/shm/mem > memModificada.txt
nano memModificada.txt
diff mem.txt memModificada.txt  > cambios.txt
nano cambios.txt
make clean
rm mem.txt memModificada.txt cambios.txt

