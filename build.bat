@Echo off

Echo Build for Windows 32
gcc -m32 -g -O2 -flto -Wall -o bin/NeraMath_unpacked.exe  scr/main.c

::Echo Gen asm file
::gcc -m32 -g -O2 -flto -Wall -S -o bin/NeraMath_unpacked.asm  scr/main.c

Echo Build for Windows 64
gcc -m64 -g -O2 -flto -Wall -o bin/NeraMath_unpacked64.exe  scr/main.c

Echo Build for KolibriOS
kos32-tcc -g -O3 -flto -Wall -o bin/NeraMath_unpacked scr/main.c -lck -I ./libc/include
::kos32-tcc -O3 -flto -Wall -I./include -o bin/NeraMath_unpacked scr/main.c lib/crt0.o -nostdlib 
::kos32-tcc -O3 -flto -Wall -Ilibc.obj/include -o bin/NeraMath_unpacked scr/main.c -nostdlib 

Echo pack NeraMath_unpacked.exe
cd bin
del NeraMath.exe
upx --ultra-brute --no-backup NeraMath_unpacked.exe -o NeraMath.exe

Echo pack NeraMath_unpacked 
kpack NeraMath_unpacked NeraMath.kex

Echo Garbage collection
::del NeraMath_unpacked.exe
del NeraMath_unpacked

cd ..

@Echo on
pause