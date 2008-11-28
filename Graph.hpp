// 
//  Graph.hpp
//  confluence
//  
//  Created by David Howden on 2007-06-11.
//  Copyright 2007 David Howden. All rights reserved.
// 

#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <iterator>
#include <fstream>
#include <utility>
#include <list>
#include <map>
#include <set>

using namespace std;

class IGraph;

namespace PlanarGraph {
   class Graph;
}

void drawGraph(PlanarGraph::Graph &g, int *boundary, char *filename, bool drawCircles);

namespace PlanarGraph
{

class Graph
{
public:
   friend class ::IGraph;
   friend void ::drawGraph(Graph &g, int *boundary, char *filename, bool drawCircles);
   
   /*
      Empty constructor
   */
   Graph ();

	/*
		Creates a new Graph object instance using the data from the
		given filename
	*/
   Graph (char *filename);

   /*
      Creates a Graph object of an 'n' vertex.
   */
   Graph (int n);

   /*
      Constructor that takes all params to setup Graph
   */
   Graph (int nB, int nE, set<int> nI, map<int,int> nc, map<int,int> ne) : B(nB), E(nE), N(nB+nE), I(nI), c(nc), e(ne) {}
   
   /*
      Constructor that takes B and E params to setup basic Graph
   */
   Graph (int nB, int nE) : B(nB), E(nE), N(nB+nE) {}
	
	/*
      Constructs the Graph of an 'n' sided polygon.
	*/
   static Graph createPolygon (int n);

   /* Destructor */
   ~Graph();
	
	/*
	   Saves the Graph to a file given by filename.
	*/
   void save (char *filename);
	
	/*
	   Rotates the current graph
	*/
   void rotate (int k);
	
	/*
	   Renumbers the points according to the permutation int *p	
	*/
   void renumber (int *p);	
	
	/*
		Intermediate function for Graph::glue(Graph &g, int n) below.
		Glues g1 and g2 together at n points.
	*/
   static Graph glue(Graph g1, Graph &g2, int n);
	
	/*
		Glues another Graph g to this one at n points
	*/
   void glue(Graph &g, int n);
	
	
	/*
		Tests if the Graph g is isomorphic to this one.
	*/
   bool isomorphic(Graph &g);
	
	/*
	   Computes the normal form of the given graph, and returns the result.
	   Uses normalForm().
	*/
   static Graph normalForm(Graph g);
	
	/*
		Converts the graph into the normal form.
	*/
   void normalForm();	
	
	/*
		Computes the closure of the given graph g and returns the result.
		Uses Graph.closure()
	*/
   static Graph closure(Graph g);
	
	/*
		Converts the current Graph object to its normal form
	*/
   void closure();
   void removeLoops();
	
	/*
		Performs verification that the maps c and e are valid (to a point).
		
		These are only simple tests, but help to easily determine if something
		has gone wrong somewhere along the way.
		
		In particular, it checks that e in an involution, and c i a bijection.
	*/
   bool checkMaps();
	
	/*
	   Produces a human-readable output of the Graph structure
	*/
   ostream &output(ostream &os);
	
	/*
	   Calls output(ostream &os) and passes the result to cout. Also
	   calls checkMaps() to ensure that the Graph object is still valid.
	*/
   void output();
	
	/*
		Outputs the permutation p (assumed to be for this Graph object and so
		is of length N), to stdout
	*/
   void output(int *p);
	
	/*
		Appends the raw text representation of this graph object
		The format is as follows:
		|B| |E| |I|
		{ i \in I }
		{ c(i) 0 <= i < N }
		{ e(i) 0 <= i < N }
	*/
   ofstream &raw_output(ofstream &os);
	
   // template<class F>
   // LinComb<Graph, F> searchReplace(const Graph &needle, const LinComb<Graph, F> &replacement);
		
private:
	/*
	   Locates the Graph g in the current (this) Graph.
	*/
   pair<int*, bool> locate(Graph &g);
	
	/*
		Removes the points x and y from I and alteres the object accordingly
	*/
   void removePoints(int x, int y);
	
	int B, E, N;
	set<int> I;
	map<int, int> c, e, label;
};

}

ostream &operator<<(ostream &os, PlanarGraph::Graph &g);
ofstream &operator<<(ofstream &os, PlanarGraph::Graph &g);

template<class T>
ofstream& operator<<(ofstream &os, const set< T > &s);

template<class T>
ostream& operator<<(ostream &os, const set< T > &s);

#endif /* _GRAPH_HPP_ */
