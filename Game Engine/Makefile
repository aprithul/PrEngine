PreEngine:  FrameRateCounter.o FrameRateRegulatorComponent.o Engine.o Component.o Input.o Matrix4x4f.o TimeComponent.o Vector2f.o Vector3f.o RendererComponent_SDL.o main.o
	g++ -std=c++11 FrameRateCounter.o FrameRateRegulatorComponent.o Engine.o Component.o Input.o Matrix4x4f.o TimeComponent.o Vector2f.o Vector3f.o RendererComponent_SDL.o main.o -o ./Build/PreEngine -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Engine.o: Engine.cpp Engine.hpp
	g++ -std=c++11 -c Engine.cpp

Component.o: Component.cpp Component.hpp
	g++ -std=c++11 -c Component.cpp

FrameRateCounter.o: FrameRateCounter.cpp FrameRateCounter.hpp
	g++ -std=c++11 -c FrameRateCounter.cpp

FrameRateRegulatorComponent.o: FrameRateRegulatorComponent.cpp FrameRateRegulatorComponent.hpp
	g++ -std=c++11 -c FrameRateRegulatorComponent.cpp

Input.o: Input.cpp Input.hpp
	g++ -std=c++11 -c Input.cpp

Matrix4x4f.o: Matrix4x4f.cpp Matrix4x4f.hpp
	g++ -std=c++11 -c Matrix4x4f.cpp

RendererComponent_SDL.o: RendererComponent_SDL.cpp RendererComponent_SDL.hpp
	g++ -std=c++11 -c RendererComponent_SDL.cpp

TimeComponent.o: TimeComponent.cpp TimeComponent.hpp
	g++ -std=c++11 -c TimeComponent.cpp

Vector2f.o: Vector2f.cpp Vector2f.hpp
	g++ -std=c++11 -c Vector2f.cpp

Vector3f.o: Vector3f.cpp Vector3f.hpp
	g++ -std=c++11 -c Vector3f.cpp

clean:
	rm -f *.o