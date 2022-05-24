
UNIWAMEIGame: main.o Engine.o Potter.o Gnome.o Traal.o Moving.o Renderer.o HiScore.o SharedGameUtils.o
	g++ $(CFLAGS) -o UNIWAMEIGame main.o Engine.o Potter.o Gnome.o Traal.o Moving.o Renderer.o HiScore.o SharedGameUtils.o -lncurses
main.o: main.cpp Engine.h
	g++ $(CFLAGS) -c main.cpp
Engine.o: Engine.cpp Engine.h Potter.h Gnome.h Traal.h Moving.h Renderer.h HiScore.h SharedGameUtils.h
	g++ $(CFLAGS) -c Engine.cpp
Potter.o: Potter.cpp Potter.h Moving.h SharedGameUtils.h
	g++ $(CFLAGS) -c Potter.cpp
Gnome.o: Gnome.cpp Gnome.h Moving.h SharedGameUtils.h
	g++ $(CFLAGS) -c Gnome.cpp
Traal.o: Traal.cpp Traal.h Moving.h SharedGameUtils.h
	g++ $(CFLAGS) -c Traal.cpp
Moving.o: Moving.cpp Moving.h SharedGameUtils.h
	g++ $(CFLAGS) -c Moving.cpp
Renderer.o: Renderer.cpp Renderer.h SharedGameUtils.h
	g++ $(CFLAGS) -c Renderer.cpp
HiScore.o: HiScore.cpp HiScore.h SharedGameUtils.h
	g++ $(CFLAGS) -c HiScore.cpp
SharedGameUtils.o: SharedGameUtils.cpp SharedGameUtils.h
	g++ $(CFLAGS) -c SharedGameUtils.cpp
clean:
	rm UNIWAMEIGame *.o
