assembling:
	cd assembler && make all && make clean

#stack:
#	cd stack1 && make all && make clean

processing:
	cd processor && make all && make clean

run.assm:
	cd assembler && ./assembler

run.proc:
	cd processor && ./processor

clean.assm:
	cd assembler && make clean

clean.proc:
	cd processor && make clean
