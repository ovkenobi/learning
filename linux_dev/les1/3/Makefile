build: solution.c
	gcc -o solution solution.c

test: solution
	./solution -vi 2>/dev/null | grep "+"
	./solution -v 2>/dev/null | grep "+"
	./solution -i 2>/dev/null | grep "+"
	./solution -q2 2>/dev/null | grep "+"
	./solution -query 2>/dev/null | grep "+"
	./solution --version 2>/dev/null | grep "+"
	./solution --longinformationrequest 2>/dev/null | grep "+"
	./solution -viq4 2>/dev/null | grep "+"
	./solution -iv 2>/dev/null | grep "+"
	./solution -ivq 3 2>/dev/null | grep "+"
	./solution -v -i -q2 2>/dev/null | grep "+"
	./solution -vi -q 12 2>/dev/null | grep "+"
	./solution --query 2 -v 2>/dev/null | grep "+"
	./solution --query 12 -iv 2>/dev/null | grep "+"
	./solution --query t -i --version 2>/dev/null | grep "+"
	./solution -t 2>/dev/null | grep "-"
	./solution -it 2>/dev/null | grep "-"
	./solution -vt 2>/dev/null | grep "-"
	./solution --versiont 2>/dev/null | grep "-"
	./solution --version -t 2>/dev/null | grep "-"
	./solution --queryt 2>/dev/null | grep "-"
	./solution -ivt 2>/dev/null | grep "-"
	./solution --query 2>/dev/null | grep "-"
	./solution --query -t 2>/dev/null | grep "-"
	./solution --query -v 2>/dev/null | grep "-"
	./solution 2>/dev/null | grep "+"
	./solution --version --query 2>/dev/null | grep "-"
	./solution --version -q 2>/dev/null | grep "-"


clean:
	-rm solution
