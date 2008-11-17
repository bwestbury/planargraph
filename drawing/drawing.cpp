/*
	Graph drawing code

	Written by Sebastian Jörn.
	Seperated by David Howden.
 */

#include "drawing.hpp"

using namespace PlanarGraph;

void drawGraph(Graph &g, int *boundary, char *filename, bool drawCircles)
{
	//Configure with boundary:
	Graph gnew = IGraph::configure(g, boundary);

	//Index the configured Graph:
	IGraph ig(gnew, g.N);
	ig.info();

	//Find the neighbours of each IGCombPoint in the Graph:
	int **neighbours;
	int *neighboursizes;
	ig.getallneighbours(neighbours, neighboursizes);

	//Now create a labeled complex:
	LComplex lc(ig, neighbours, neighboursizes);

	//Finally, perform circle packing and layout:
	lc.make_packing();
	lc.layout(filename, drawCircles);
}
