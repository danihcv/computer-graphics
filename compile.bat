cls
del test.exe
g++ %1 -o test.o -c -std=c++11
g++ test.o -o test.exe -lglu32 -lopengl32 -lfreeglut -std=c++11
del test.o