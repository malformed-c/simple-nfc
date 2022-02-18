all: nfc nfc.hex

nfc: *.c *.h
	avr-gcc -Ofast -mmcu=attiny85 -DF_CPU=22000000UL -lm -Wall -Wextra main.c nfcemulator.c -o nfc

nfc.hex: nfc
	avr-objcopy -j .text -j .data -Oihex nfc nfc.hex

flash: nfc.hex nfc
	micronucleus --run nfc.hex

clean:
	rm nfc nfc.hex