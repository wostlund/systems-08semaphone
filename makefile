compile: controlMac.c write.c
	gcc controlMac.c -o control
	gcc write.c -o write

clear: *~
	rm *~
