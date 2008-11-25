CXX = c++
CXXFLAGS = -Wall -O3 -funroll-loops -fomit-frame-pointer -fexpensive-optimizations

BOARD_FILES = \
	drawing/BoardLib/Board.o \
	drawing/BoardLib/Color.o \
	drawing/BoardLib/Rect.cpp \
	drawing/BoardLib/ShapeList.o \
	drawing/BoardLib/Shapes.o \
	drawing/BoardLib/Transforms.o

DRAWING_FILES = \
	drawing/crc.o \
	drawing/triang.o \
	drawing/drawing.o \
	$(BOARD_FILES)

GRAPH_FILES = \
   Graph.o

all: graph drawing test #libplanargraph.so

graph: $(GRAPH_FILES)

drawing: $(DRAWING_FILES)

test: graph drawing tests/test.o
	$(CXX) $(CXXFLAGS) -o tests/test tests/test.o $(DRAWING_FILES) $(GRAPH_FILES)

libplanargraph.so: graph drawing
	$(CXX) $(CXXFLAGS) -fPIC -shared -o libplanargraph.so $(GRAPH_FILES) $(DRAWING_FILES)

clean: 
	rm -f *.o
	rm -f drawing/BoardLib/*.o
	rm -f drawing/*.o
	rm -f tests/*.o
