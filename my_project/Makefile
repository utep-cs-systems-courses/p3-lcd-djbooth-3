# makfile configuration
COMMON_OBJECTS = wdt_handler.o p2_interrupt_handler.o switches.o buzzer.o ../lib/libTimer.a


CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:finalprojectC.elf finalprojectA.elf

#additional rules for files
finalprojectC.elf: ${COMMON_OBJECTS} finalproject.o state_machineC.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

#additional rules for files
finalprojectA.elf: ${COMMON_OBJECTS} finalproject.o state_machineA.o 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

loadC: finalprojectC.elf
	msp430loader.sh $^

loadA: finalprojectA.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

buzzer.c: buzzer.h
finalproject.c: buzzer.h
