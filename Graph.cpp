// 
//  Graph.cpp
//  planargraph
//  
//  Created by David Howden on 2008-11-15.
//  Copyright 2008 David Howden. All rights reserved.
// 

#include "Graph.hpp"

using namespace std;

namespace PlanarGraph {

/*
   Empty constructor
*/
Graph::Graph () {}


/*
	Creates a new Graph object instance using the data from the
	given filename
*/
Graph::Graph (char *filename) {
	ifstream fin(filename, ifstream::in);

	fin >> B;
	fin >> E;
	int nI;
	fin >> nI;

	N = B + E;
	
	int temp;
	
	for (int i = 0; i < nI; i++) {
		fin >> temp;
		I.insert(temp);
	}

	for (int i = 0; i < N; i++) {
		fin >> temp;
		c[i] = temp;
	}

	for (int i = 0; i < N; i++) {
		fin >> temp;
		e[i] = temp;
	}
	
	fin.close();
}


/*
   Creates a Graph object of an 'n' vertex.
*/
Graph::Graph (int n) {
	
	if (n < 3) {
		cerr << "Error: n must be >= 3" << endl;
		//return NULL;
	}
	
	B = n;
	//I = 0;
	E = 0;
	for (int i = 0; i < n; i++) {
		c[i] = i+1;
		e[i] = -1;
	}
	c[n-1] = 0;
	
	N = B + E;
}

/*
   Constructs the Graph of an 'n' sided polygon.
*/
Graph
Graph::createPolygon (int n) {
	Graph g;
	g.B = n;
	g.E = 2*n;
	
	g.N = g.B + g.E;
	
	for (int i = 0; i < n; i++) {
		g.c[i] = n + i ;
		g.c[n+i] = 2*n + i;
		g.c[2*n + i] = i;
		g.e[i] = -1;
		g.e[n + i] = 2*n + i + 1;
		g.e[2*n + i + 1] = n + i;
	}
	
	g.e[2*n - 1] = 2*n;
	g.e[2*n] = 2*n - 1;
	
	return g;
}

/* Destructor */
Graph::~Graph () {};

/*
   Saves the Graph to a file given by filename.
*/
void
Graph::save (char *filename) {
	ofstream fout(filename, ios::out);
	raw_output(fout);
	fout.close();
}


void
Graph::rotate (int k) {
	if(0 < k && k < B) {
		int *p = new int[N];
		
		for(int i = 0; i < k; i++) {
			p[i] = B - k + i;
		}
		
		for(int i = 0; i < (B - k); i++) {
			p[k+i] = i;
		}
		
		for(int i = B; i < N; i++) {
			p[i] = i;
		}
		//output(p);
		renumber(p);
		delete p;
	} else {
		cerr << "rotate(" << k << ") called with B = " << B << endl;
	}
}


/*
   Renumbers the points according to the permutation int *p	
*/
void
Graph::renumber (int *p)
{	
	map<int, int> cc, ec;
	
	for(int i = 0; i < N; i++) {
		cc[p[i]] = p[c[i]];
		if(e[i] == -1) {
			ec[p[i]] = -1;
		} else {
			ec[p[i]] = p[e[i]];
		}
		//label.insert(p[i], p[label[i]]);
	}
	int temp;
	
	set<int> nI;
	for(set<int>::iterator iter = I.begin(); iter != I.end(); ++iter) {
		temp = (*iter);
		//if(p[temp] != temp) {
		nI.insert(p[temp]);
		//}
	}
	I = nI;
	
	c = cc;
	e = ec;
}


/*
	Intermediate function for Graph::glue(Graph &g, int n) below.
	
	Glues g1 and g2 together at n points.
*/
Graph
Graph::glue(Graph g1, Graph &g2, int n) {
	g1.glue(g2, n);
	return g1;
}


/*
	Glues another Graph g to this one at n points
*/
void
Graph::glue(Graph &g, int n) {
	
	int i;
	int nB = B + g.B - 2*n;
	int nE = E + g.E + 4*n;
	int nN = nB + nE;
	int X = nN - 2*n;
	//int nI = I + g.I;
	
	for(i = 0; i < g.N; i++) {
		c[N+i] = N + g.c[i];
		if(g.e[i] == -1) {
			e[N+i] = -1;
		} else {
			e[N+i] = N + g.e[i];
		}
		//label.put(N+i, g.label(i));
	}
	
	for(i = 0; i < n; i++) {
		e[B - n + i] = X +i;
		e[X+i] = B - n + i;
		
		e[N + n - i - 1] = X + n + i;
		e[X + n + i] = N + n - i - 1;
		
		c[X + i] = X + n + i;
		c[X + n + i] = X + i;
	}
	
	// ====================
	// = Sort out the I's =
	// ====================
	for(set<int>::iterator iter = g.I.begin(); iter != g.I.end(); iter++) {
		I.insert((*iter)+N);
	}
	
	for(i = X; i < (X+2*n); i++) {
		I.insert(i);
	}
	
	
	// ==========================
	// = Create the permutation =
	// ==========================
	int *p = new int[nN];
	
	for(i = 0; i < (B - n); i++) {
		p[i] = i;
	}
	
	
	for(i = 0; i < (g.B - n); i++) {
		p[N + i + n] = B - n + i;
	}
			
	for(i = 0; i < E; i++) {
		p[B + i] = nB + i;
	}
	
	for(i = 0; i < g.E; i++) {
		p[N + g.B + i] = N + g.B - 2*n + i;
	}
	
	for(i = 0; i < n; i++) {
		p[B - n + i] = X - 2*n + i;
		p[N + i] = X - n + i;
	}
	
	for(i = X; i < (X + 2*n); i++) {
		p[i] = i;
	}
	
	N = nN;
	
	//output();
	
	renumber(p);

	delete p;
	
	B = nB;
	E = nE;
	//I = nI;
}


/*
	Tests if the Graph g is isomorphic to this one.
*/
bool
Graph::isomorphic(Graph &g) {
	if(B == 0) {
		cerr << "Need nonempty boundary." << endl;
		return false;
	}
	
	// check that B, E and I are the same
	if(B != g.B || E != g.E || I.size() != g.I.size()) {
		cout << "F1" << endl;
		return false;
	}
	
	for(int i = 0; i < B; i++) {
		if(c[i] < B) {
			if(c[i] != g.c[i]) {
				return false;
			}
		}
	}
	
	int *p = new int[N];
	// ****  assumes there is a boundary ****
	for(int i = 0; i < B; i++) {
		p[i] = i;
	}
	
	for(int i = B; i < N; i++) {
		p[i] = -1;
	}
	
	bool flag = true;
	
	while(flag) {
		flag = false;
		for(int i = B; i < N; i++) {
			//cout << i << endl;
			if(p[i] != -1) {
				if(p[c[i]] != -1) {
					if(p[c[i]] != g.c[p[i]]) {
						return false;
						cout << "F2" << endl;
					}// else {
					//	return false;
					//}
				} else {
					p[c[i]] = g.c[p[i]];
					flag = true;
				}
				
				if(p[e[i]] != -1) {
					if(p[e[i]] != g.e[p[i]]) {
						cout << "F3 : " << i << endl;
						return false;
					} //else {
					//	return false;
					//}
				} else {
					p[e[i]] = g.e[p[i]];
					flag = true;
				}
			}
		}			
	}
	
	return true;
}

bool
Graph::operator== (Graph &g) {
	return isomorphic(g);
}

/*
   Computes the normal form of the given graph, and returns the result.
   Uses normalForm().
*/
Graph
Graph::normalForm(Graph g) {
   g.normalForm();
   return g;
}

/*
	Converts the graph into the normal form.
*/
void
Graph::normalForm() {
	int x, y, z;

	bool flag = true;
	while(flag) {
		flag = false;
		for(set<int>::iterator iter = I.begin(); iter != I.end(); iter++) {
			x = (*iter);
			// e[x] == -1 <=> x < B
			if(x >= B) {
				y = c[x];
				z = e[x];
				if(y == z) {
					if(y != -1) {
						// loop
						// flag = true;
						// break;
					}
				} else {
					// need to remove x and y...
					set<int>::iterator iter = I.find(y);
					if(iter == I.end()) {
						cerr << "Error: y value " << y << " is not in I: ";
                  cerr << I;
						//output_set(cerr, I);
						cerr << endl;
					}
					
					
					if(y < B) {

						int temp = z;
						
						do {
							temp = c[temp];
						} while(c[temp] != z);
						
						c[temp] = y;
						c[y] = c[z];
						
						removePoints(x,z);
					} else {
						e[z] = e[y];
						e[e[y]] = z;
						removePoints(x,y);
					}
					output();
					flag = true;
					break;
				}
			}
		}
	}
}


/*
	Computes the closure of the given graph g and returns the result.
	Uses Graph.closure()
*/
Graph
Graph::closure(Graph g) {
     g.closure();
     return g;
}

/*
	Converts the current Graph object to its normal form
*/
void
Graph::closure() {
     int B3 = 3*B;
     int B2 = 2*B;
     
     map<int, int> c_old, e_old;
     c_old = c;
     e_old = e;

     for(int i = 0; i < N; i++) {
         c[B3+i] = B3 + c_old[i];
         e[B3+i] = B3 + e_old[i];
     }
     
     for(int i = 0; i < B; i++) {
         e[B3 + i] = i;
         e[i] = B3 + i;
         c[i] = B+i;
         c[B+i] = B2 + i;
         c[B2+i] = i;
     }
     
     for(int i = 0; i < (B-1); i++) {
         e[B + i] = B2 + i + 1;
         e[B2 + i + 1] = B + i;
     }
     
     e[B2 - 1] = B2;
     e[B2] = B2 - 1;
     
     E = 4*B + E;
     B = 0;
     N = B + E;
}

/*
   Removes loops from Graph
*/
void
Graph::removeLoops()
{
	int x;

	bool flag = true;
	while(flag) {
		flag = false;
		for(set<int>::iterator iter = I.begin(); iter != I.end(); iter++) {
			x = (*iter);

			// e[x] == -1 <=> x < B
			if(x >= B) {
				if(c[x] != -1 && c[x] == e[x]) {
					// we have a loop
					cout << "WE HAVE A LOOP!!!!!" << endl;
					removePoints(x, c[x]);
					flag = true;
					break;
				}
			}
		}
	}
}


/*
	Performs verification that the maps c and e are valid (to a point).
	
	These are only simple tests, but help to easily determine if something
	has gone wrong somewhere along the way.
	
	In particular, it checks that e in an involution, and c i a bijection.
*/
bool
Graph::checkMaps() {
	for(int i = 0; i < B; i++) {
		if(e[i] != -1) {
			cerr << "Error: e fails on boundary, e(" << i << ") = " << e[i] << endl;
			return false;
		}
	}
	
	for(int i = B; i < N; i++) {
		if(e[i] != -1) {
			if(e[e[i]] != i) {
				cerr << "Error: e fails on " << i << "(must be an involution on E)" << endl;
				return false;
			}
		} else {
			cerr << "Error: e fails on " << i << " (must be defined on E)" << endl;
		}
	}
	
	bool *checked = new bool[N];
	for(int i = 0; i < N; i++) {
		checked[i] = false;
	}
	
	for(int i = 0; i < N; i++) {
		if(checked[c[i]]) {
			cerr << "Error: c fails on " << i << endl;
			return false;
		}
		checked[c[i]] = true;
	}
	
	for(set<int>::iterator iter = I.begin(); iter != I.end(); iter++) {
		if(c[(*iter)] != -1 && I.find(c[(*iter)]) == I.end()) {
			cerr << "Error: c fails on I, c(" << (*iter) << ") = " << c[(*iter)] << " is not in I" << endl;
		}
	}
   return true;
}


/*
   Produces a human-readable output of the Graph structure
*/
ostream&
Graph::output(ostream &os) {
	os << "GRAPH (B = " << B << ", E = " << E << ", I = " << I << ")" << endl;
	
	int i;
	
	for(i = 0; i < N; i++) {
		os << "c(" << i << ") = " << c[i] << endl;
	}
	
	for(i = 0; i < N; i++) {
		cout << "e(" << i << ") = " << e[i] << endl;
	}
	
	os << endl;
	return os;
}

/*
   Calls output(ostream &os) and passes the result to cout. Also
   calls checkMaps() to ensure that the Graph object is still valid.
*/
void
Graph::output() {
	output(cout);
	checkMaps();
}


/*
	Outputs the permutation p (assumed to be for this Graph object and so
	is of length N), to stdout
*/
void
Graph::output(int *p) {
	cout << "Permutation:" << endl;
	cout << "  i   ";
	for(int i = 0; i < N; i++) {
		cout << "\t" << i;
	}
	
	cout << endl << " p(i) ";
	
	for(int i = 0; i < N; i++) {
		cout << "\t" << p[i];
	}
	cout << endl;
}


/*
	Appends the raw text representation of this graph object
	The format is as follows:
	|B| |E| |I|
	{ i \in I }
	{ c(i) 0 <= i < N }
	{ e(i) 0 <= i < N }
*/
ofstream&
Graph::raw_output(ofstream &os) {
	os << B << " " << E << " " << I.size() << endl << I << endl;
	for(int i = 0; i < N; i++) {
		os << c[i] << " ";
	}
	os << endl;
	for(int i = 0; i < N; i++) {
		os << e[i] << " ";
	}
	os << endl;
	return os;
}

 // template<class F>
 // LinComb<Graph, F> searchReplace(const Graph &needle, const LinComb<Graph, F> &replacement) 
 // {
 //  LinComb<Graph, F> result;
 //  
 //  int *p = locate(needle);
 // 
 //  return NULL;
 // }
	
/*
   Locates a Graph g within the current Graph object, and returns a pair<int * p, bool found>
   where p is a permutation specifing the mapping from g to Graph and found indicates if g
   was found in the Graph
*/
pair<int*, bool>
Graph::locate(Graph &g)
{
   int *p = new int[g.N];
  
   bool flag;
   bool done;
   bool break_again = false;

   for(int r = 0; r < N; r++) {
       // should this be p[0] = r??????
       for(int i = 1; i < g.N; i++) {
           p[i] = -1;
       }
       p[0] = r;

       flag = true;
       while(flag) {
           flag = false;
   		done = false;
           for(int i = 0; i < g.N; i++) {
               if(p[g.c[i]] == -1) {
                   // check label
                   p[g.c[i]] = c[p[i]];
                   flag = true;
               } else if(p[g.c[i]] != c[p[i]]) {
                   break_again = true;
                   break;
               }
   			if (i >= g.B) {
   				int g_e_i = g.e[i];
   				if(p[g_e_i] == -1) {
   	                // check label
   	                p[g_e_i] = e[p[i]];
   	                flag = true;
   	            } else if(p[g_e_i] != e[p[i]]) {
   	                break_again = true;
   	                break;
   	            }
   			}
   			if ((i+1) == g.N) {
   				pair<int *, bool> win(p, true);
   				return win;
   			}
           }
           if(break_again) {
               break_again = false;
               break;
           }
       }
   }
   pair< int *, bool> fail(NULL, false);
   return fail;
}


/*
	Removes the points x and y from I and alters the object accordingly
*/
void
Graph::removePoints(int x, int y)
{
	int min, max;
	
	cout << "Erasing x=" << x << " and y=" << y << " from I" << endl;
	
	I.erase(x);
	I.erase(y);

	if(x <= y) {
		min = x;
		max = y;
	} else {
		min = y;
		max = x;
	}
	
	//cout << "min: " << min << "  max: " << max << endl;
	
	int *p = new int[N];
	
	for(int i = 0; i < min; i++) {
		p[i] = i;
	}
	
	for(int i = (min+1); i < max; i++) {
		p[i] = i-1;
	}
	
	for(int i = (max+1); i < N; i++) {
		p[i] = i-2;
	}
	
	p[min] = N - 2;
	p[max] = N - 1;
	
	cout << "Renumber to fill gaps" << endl;
	renumber(p);
	
	delete p;
	
	N-=2;
	E-=2;
}

} /* PlanarGraph */

ostream &operator<<(ostream &os, PlanarGraph::Graph &g) {
   return g.output(os);
}

ofstream &operator<<(ofstream &os, PlanarGraph::Graph &g) {
   return g.raw_output(os);
}

template<class T>
ofstream& operator<<(ofstream &os, const set< T > &s) {
	copy(s.begin(), s.end(), ostream_iterator<T>(os, " "));
	return os;
}

template<class T>
ostream& operator<<(ostream &os, const set< T > &s) {
	os << "{";
	copy(s.begin(), s.end(), ostream_iterator<T>(os, ", "));
	os << "}";
	return os;
}
