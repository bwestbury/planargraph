/*
   test.cpp
   planargraph
   
   Some testing for the drawing routines.
*/

#include "../PlanarGraph.hpp"

#include <iostream>

using namespace std;

/*
   Testing configuration, indexing and circle packing on premade polygons glued together.
*/
void test()
{
	cout << "Boo!";
	Graph g;
	// g = Graph::createPolygon(3);
	// Graph g1 = Graph::createPolygon(4);
	// Graph g2 = Graph::createPolygon(5);
	// Graph g3 = Graph::glue(g, g1, 1);
	// Graph g4 = Graph::glue(g3, g2, 1);
	// Graph g5 = Graph::glue(g4, g, 2);
	g = Graph::createPolygon(4);

	int boundary[4] = {1,1,1,1};

	drawGraph(g, boundary, "drawing_test.svg", false);
}

int main()
{
	test();
	return 0;
}
