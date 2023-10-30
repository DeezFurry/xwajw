c:
	gcc app.c -o install-dwm
removec:
	rm install-dwm
cpp:
	g++ app.cpp -lX11 -o x11progm
removecpp:
	rm x11progm