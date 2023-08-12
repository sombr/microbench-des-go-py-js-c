all:
	cd c-baseline && make
	cd golang && make
	cd java && make

run: all
	perl run.pl | tee results.txt
