all:
	lemon parser.y
	ragel -o calculator.c calculator.rl

test: all
	gcc -o calculator test.c calculator.c parser.c -lm
	echo '1+1' | ./calculator; echo ''
	echo '-1+1' | ./calculator; echo ''
	echo '.1+1' | ./calculator; echo ''
	echo '1-1' | ./calculator; echo ''
	echo '1*2' | ./calculator; echo ''
	echo '9/3' | ./calculator; echo ''
	echo '0/0' | ./calculator; echo ''
	echo '1/0' | ./calculator; echo ''
	echo '2^0' | ./calculator; echo ''
	echo '2^10' | ./calculator; echo ''
	echo '2*2^10' | ./calculator; echo ''
	echo '2^10*2' | ./calculator; echo ''

clean:
	rm -f *.o *.h *.out *.cpp calculator calculator.c parser.c
