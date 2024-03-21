CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic -Werror -g
COMMON_OBJECTS := controllers.o user_io.o image_output.o image_drawing.o Image.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o

#ALL
all: hello questions_3 ascii_image image_file inquisitor simple_squares_ascii flag_romania ppm_menu

#HELLO
hello: hello.o
	g++ $(CXXFLAGS) -o $@ $^
hello.o: hello.cpp
	g++ $(CXXFLAGS) -c $<

#QUESTIONS_3
questions_3: questions_3.o $(COMMON_OBJECTS)
	g++ $(CXXFLAGS) -o $@ $^

questions_3.o: questions_3.cpp image_menu.h
	g++ $(CXXFLAGS) -c $<
controllers.o: controllers.cpp image_menu.h ActionData.h ComplexFractal.h JuliaSet.h
	g++ $(CXXFLAGS) -c $<
user_io.o: user_io.cpp image_menu.h ActionData.h
	g++ $(CXXFLAGS) -c $<

#ASCII_IMAGE
ascii_image: ascii_image.o $(COMMON_OBJECTS)
	g++ $(CXXFLAGS) -o $@ $^

ascii_image.o: ascii_image.cpp image_menu.h Image.h
	g++ $(CXXFLAGS) -c $<
image_output.o: image_output.cpp image_menu.h PPM.h
	g++ $(CXXFLAGS) -c $<
image_drawing.o: image_drawing.cpp image_menu.h PPM.h JuliaSet.h
	g++ $(CXXFLAGS) -c $<
Image.o: Image.cpp Image.h
	g++ $(CXXFLAGS) -c $<

#IMAGE_FILE
image_file: image_file.o $(COMMON_OBJECTS)
	g++ -std=c++11 -o $@ $^

PPM.o: PPM.cpp PPM.h Image.h
	g++ $(CXXFLAGS) -c $<
image_file.o: image_file.cpp image_menu.h
	g++ $(CXXFLAGS) -c $<

# PRACTICE EXAM 9/13/2023: inquisitor
#INQUISITOR
inquisitor: inquisitor.o $(COMMON_OBJECTS)
	g++ $(CXXFLAGS) -o $@ $^

inquisitor.o: inquisitor.cpp image_menu.h
	g++ $(CXXFLAGS) -c $<

#SIMPLE_SQUARES_ASCII
simple_squares_ascii: simple_squares_ascii.o $(COMMON_OBJECTS)
	g++ $(CXXFLAGS) -o $@ $^

simple_squares_ascii.o: simple_squares_ascii.cpp image_menu.h
	g++ $(CXXFLAGS) -c $<

# EXAM 9/15/2023: flag_romania
#FLAG_ROMANIA
flag_romania: flag_romania.o $(COMMON_OBJECTS)
	g++ $(CXXFLAGS) -o $@ $^

flag_romania.o: flag_romania.cpp image_menu.h
	g++ $(CXXFLAGS) -c $<

# Assignment 4: Continuing Assignments
#PPM_MENU
ppm_menu: ppm_menu.o $(COMMON_OBJECTS)
	g++ $(CXXFLAGS) -o $@ $^

ppm_menu.o: ppm_menu.cpp image_menu.h
	g++ $(CXXFLAGS) -c $<

ActionData.o: ActionData.cpp ActionData.h PPM.h ColorTable.h
	g++ $(CXXFLAGS) -c $<

MenuData.o: MenuData.cpp MenuData.h
	g++ $(CXXFLAGS) -c $<

image_filters.o: image_filters.cpp image_menu.h ActionData.h
	g++ $(CXXFLAGS) -c $<

# ./unit-test.bash 09

NumberGrid.o: NumberGrid.cpp NumberGrid.h PPM.h ColorTable.h ComplexFractal.h
	g++ $(CXXFLAGS) -c $<

ColorTable.o: ColorTable.cpp ColorTable.h
	g++ $(CXXFLAGS) -c $<

ComplexFractal.o: ComplexFractal.cpp ComplexFractal.h NumberGrid.h
	g++ $(CXXFLAGS) -c $<

JuliaSet.o: JuliaSet.cpp JuliaSet.h
	g++ $(CXXFLAGS) -c $<

MandelbrotSet.o: MandelbrotSet.cpp MandelbrotSet.h
	g++ $(CXXFLAGS) -c $<

ThreadedGrid.o: ThreadedGrid.cpp ThreadedGrid.h
	g++ $(CXXFLAGS) -c $<

clean:
	-rm -f *.o calc *~

# only 14 people here today?