all:
	lemon parser.y
	ragel -o calculator.c calculator.rl
	ragel -Vp calculator.rl -o calculator.dot

test: all
	gcc -o calculator test.c calculator.c parser.c -lm
	#basic arithmetic tests
	echo '1+1' | ./calculator | jq --exit-status 'select(.==2.0)'
	echo '.1+1' | ./calculator | jq --exit-status 'select(.==1.1)'
	echo '1-1' | ./calculator | jq --exit-status 'select(.==0.0)'
	echo '1*2' | ./calculator | jq --exit-status 'select(.==2.0)'
	echo '9/3' | ./calculator | jq --exit-status 'select(.==3.0)'
	#power tests
	echo '2^0' | ./calculator | jq --exit-status 'select(.==1)'
	echo '2^10' | ./calculator | jq --exit-status 'select(.==1024)'
	echo '2^-1' | ./calculator | jq --exit-status 'select(.==1.0/2.0)'
	echo '-10^2' | ./calculator | jq --exit-status 'select(.==-100)'
	#precedence tests
	echo '1+1*2' | ./calculator | jq --exit-status 'select(.==3.0)'
	echo '2*1+1' | ./calculator | jq --exit-status 'select(.==3.0)'
	echo '1+1/2' | ./calculator | jq --exit-status 'select(.==1.5)'
	echo '1/2+1' | ./calculator | jq --exit-status 'select(.==1.5)'
	echo '(1+1)/2' | ./calculator | jq --exit-status 'select(.==1.0)'
	#float tests
	echo '0/0' | ./calculator | jq --exit-status --raw-input 'select(.=="NaN")'
	echo '1/0' | ./calculator | jq --exit-status --raw-input 'select(.=="inf")'
	echo '2*2^10' | ./calculator | jq --exit-status 'select(.==2048)'
	echo '2^10*2' | ./calculator | jq --exit-status 'select(.==2048)'
	echo '2^(10*2)' | ./calculator | jq --exit-status 'select(.==1048576)'
	#starting sign tests
	echo '-1+1' | ./calculator | jq --exit-status 'select(.==0.0)'
	echo '+1+1' | ./calculator | jq --exit-status 'select(.==2.0)'
	echo '*1+1' | ./calculator | jq --exit-status --raw-input 'select(. | startswith("Error"))'

clean:
	rm -f *.o *.h *.out *.cpp calculator calculator.c parser.c
