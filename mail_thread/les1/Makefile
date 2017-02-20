bild: task.cpp
	g++ -std=c++11 -o task task.cpp
test: task
	echo x^2+x | ./task | fgrep "2*x+1"
	echo 2*x^100+100*x^2 | ./task | fgrep "200*x^99+200*x"
	echo x^10000+x+1 | ./task | fgrep "10000*x^9999+1"
	echo -x^2-x^3 | ./task | fgrep "-3*x^2-2*x"
	echo x+x+x+x+x+x+x+x+x+x | ./task | fgrep "10"
	
