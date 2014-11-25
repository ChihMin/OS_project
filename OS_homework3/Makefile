vm:main.o file.o
	nvcc -arch=sm_30 main.o file.o -rdc=true -o vm

main.o:main.cu
	nvcc -arch=sm_30 main.cu -rdc=true -c

file.o:file.cu
	nvcc -arch=sm_30 file.cu -rdc=true -c

clean:
	rm vm file.o main.o
	

