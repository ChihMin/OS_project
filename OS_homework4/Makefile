fs:main.o file.o
	nvcc -arch=sm_30 main.o file.o -rdc=true -o fs

debug:main.cu file.cu
	nvcc -arch=sm_30 main.cu file.cu -rdc=true -g -G -o debug

main.o:main.cu
	nvcc -arch=sm_30 main.cu -rdc=true -c

file.o:file.cu
	nvcc -arch=sm_30 file.cu -rdc=true -c

clean:
	rm vm file.o main.o snapshot.bin a.txt b.txt debug 
	

