all:
	cd src && qmake && make -j8
doxygen:
	cd src && doxygen Doxyfile
pack:
	zip -r xfeket00-xperin11.zip ./src/* ./examples/* ./doc/ ./README.txt ./Makefile
clean:
	cd src && make clean && rm -f icp && rm -f Makefile
run: all
	cd src && ./icp