.PHONY: clean, init, compile

F := lals
D := $(shell pwd)

clean:
	rm -rf vial-qmk/keyboards/${F}
	cd vial-qmk; qmk clean

init:
	make clean
	git submodule update --remote
	git submodule update --init --recursive
	ln -s ${D}/${F} vial-qmk/keyboards/${F}
	rm -rf build/*

compile:
	cd vial-qmk; qmk compile -j 4 -kb ${F} -km vial
	cp vial-qmk/.build/${F}* build/

