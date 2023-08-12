all:
	cd c-baseline && make
	cd golang && make
	cd java && make

run: all
	perl run.pl | tee results.txt

csv: results.txt
	echo "cmd,duration (ms)" > results.csv
	cat results.txt | perl -lne 'chomp; m{^\d+:\s+(\S+)\s+.*?runtime:\s+([\.\d]+)\s+ms} and print "$$1,$$2";' >> results.csv
