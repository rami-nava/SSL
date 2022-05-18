run: TablasDeConversion
	./TablasDeConversion

test: ConversionTest
	./ConversionTest
	rm ConversionTest
	rm ConversionTest.o
	rm Conversion.o
	
TablasDeConversion: TablasDeConversion.o Conversion.o 
	gcc TablasDeConversion.o Conversion.o -o TablasDeConversion

TablasDeConversion.o : TablasDeConversion.c Conversion.h
	gcc -c TablasDeConversion.c -std=c18 -o TablasDeConversion.o 

Conversion.o : Conversion.c Conversion.h
	gcc -c Conversion.c -std=c18 -o Conversion.o

ConversionTest: ConversionTest.o Conversion.o
	gcc ConversionTest.o Conversion.o -o ConversionTest

ConversionTest.o: ConversionTest.c Conversion.h
	gcc -c ConversionTest.c -std=c18 -o ConversionTest.o
	
	
clean:
	rm TablasDeConversion
	rm TablasDeConversion.o
	rm Conversion.o

