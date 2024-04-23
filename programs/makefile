#run:	viewupback loginback signupback fileupback viewupback
#	./loginback.cgi&
#	./signupback.cgi&
#	./fuploadback.cgi&
#	./viewupback.cgi&
#	./fuploadback.ccgi&

remove: front back
	rm *.o

front:
	./compile.sh viewup
	./compile.sh fupload
	./compile.sh upload
	./compile.sh signup
	./compile.sh login

back:
	./2comp.sh loginback
	./2comp.sh signupback
	./2comp.sh viewupback
	./2comp.sh fuploadback
