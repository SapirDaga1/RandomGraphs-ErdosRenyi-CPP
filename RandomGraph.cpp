

#include<iostream>
#include<vector>
#include<cstdlib>
#include <Bits.h>
#include <StlLock.h>
#include <ctime>
#include <cstdio>
#include <climits>
#include <queue>
#include <fstream>

using namespace std;
using std::vector;
using std::queue;
#define V 1000 // default num of vertices
#define INF INT_MAX 

// declaration of functions
vector<vector<int>> build_random_graph(float p, int v);
vector<int> bfs(int u, vector<vector<int>> vec, vector<int> distances);
int connectivity(vector<vector<int>> vec, vector<int> distances, int isolated_result);
int is_Isolated(vector<vector<int>> vector);
int diameter(int v, const vector<vector<int>> graph, int isolated_result);
void printGraph(vector<vector<int>> graph);


// simulation functions
void attribute1(double a[]);
void attribute2(double b[]);
void attribute3(double a[]);


// creating an undirected random graph
vector<vector<int>> build_random_graph(float p, int v) {
	vector<vector<int>> vec(V);
	for (int i = 0; i < v; i++) {
		for (int j = i; j < v; j++) {
			double r = (double)rand() / (RAND_MAX); // a number between 0-1
			if (r <= p && i != j) { // here we create the edge
				vec[i].push_back(j);
				vec[j].push_back(i);
				// we execute these two commands because it's an undirected graph.
			}
		}
	}
	return vec;
}

// printing the graph
void printGraph(vector<vector<int>> graph)
{
	for (int i = 0; i < V; ++i)
	{
		cout << "\n Adjacency list of vertex "
			<< i << "\n head ";

		for (auto x : graph[i]) // iterator
			cout << "-> " << x;

		cout << "\n";
	}
}

// checking the connectivity of the graph
int connectivity(vector<vector<int>> vec, vector<int> distances, int isolated_result) {
	

	if (isolated_result == 1) // if there is an isolated vertex in the graph 
		return 0;

	distances = bfs(0, vec, distances); // update the distances array

	for (int i = 0; i < vec.size(); i++)
	{
		if (distances[i] == INF) {
			return 0;
		}
	}
	return 1;
}


int is_Isolated(vector<vector<int>> vec) {

	for (int i = 0; i < V; ++i) {
		if (vec[i].size() == 0) // TRUE, there is an isolated vertex in the graph 
			return 1;
	}
	return 0; // FALSE, there isn't isolated vertex in the graph. (there isn't any vertex without neighbors)
}

vector<int> bfs(int u, vector<vector<int>> vec, vector<int> d) // u = vertex number
{
	queue<int> q;
	vector<bool> visited(V, false); // A vector of distances from current u vertex iniitalized to FALSE.

	q.push(u);
	visited[u] = true;
	d[u] = 0;

	for (auto i : vec[u]) // Here we initialize N(u) to 1 
		d[i] = 1;

	while (!q.empty())
	{
		u = q.front();
		q.pop();

		for (auto i : vec[u]) { // in this for loop we iterate through the vector and update the distances.
			if (!visited[i])
			{
				visited[i] = true;
				d[i] = d[u] + 1;
				q.push(i);
			}
		}
	}
	return d;
}

int diameter(int v, const vector< vector<int> > vec, int isolated_result) // This function finds the diameter of the graph

{
	int max = 0; // contains the diameter value
	vector<int>distances(V, INF);

	int isConnected = connectivity(vec, distances, isolated_result);
	if (isConnected == 0) // graph isn't connected thus diameter equals INF.
		return -1;

	else {
		for (int i = 0; i < vec.size(); i++)
		{
			distances = bfs(i, vec, distances);
			if (*max_element(distances.begin(), distances.end()) > max)
			{
				max = *max_element(distances.begin(), distances.end());
			}
		}
	}
	return max;
}

void attribute1(double a[])
{
	double estimate = 0.0;
	int c_connectivity = 0, isolated_result = 0; //c_connectivity is a counter.
	ofstream myFile;
	myFile.open("Att1_results.csv");  // file for attribute 1
	myFile << "TH_1 = 0.0069" << "," << "Probability" << "," << "Num of Connected graphs" << "," << "Probability estimation" << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			vector <int> distances(V);
			vector<vector<int>> vec;
			vec = build_random_graph(a[i], V);// build a random graph of V vertices with probability of p
			isolated_result = is_Isolated(vec);
			c_connectivity += connectivity(vec, distances, isolated_result); // amount of connectivity graphs from whole 500 

		}
		estimate = double(c_connectivity) / 500;
		myFile << "," << a[i] << "," << c_connectivity << "," << estimate <<  endl;
		c_connectivity = 0, isolated_result = 0;
	}
	myFile.close();
}
void attribute2(double b[])
{
	double estimate = 0.0;
	int c_diam = 0, diam = 0, isolated_result = 0; // c_diam is a counter.
	ofstream myFile;
	myFile.open("Att2_results.csv");  // file for attribute 2
	myFile << "TH_2 = 0.11753" << "," << "Probability" << "," << "Number of diameter = 2" << "," << "Probability estimation" << endl;
	for (int i = 0; i < 10; i++)
	{

		for (int j = 0; j < 500; j++)
		{
			vector <int> distances(V);
			vector<vector<int>> vec;
			vec = build_random_graph(b[i], V); // build a random graph of V vertices with probability of p
			isolated_result = is_Isolated(vec);
			diam = diameter(0, vec, isolated_result);
			if (diam >= 2)
				c_diam++; // amount of graphs from whole 500 
		}
		estimate= double(c_diam) / 500;
		myFile << "," << b[i] << "," << c_diam << "," << estimate << endl;
		c_diam = 0;
	}
	myFile.close();
}
void attribute3(double a[])
{
	double estimate = 0.0;
	int c_isolated = 0, isolated_result = 0; // c_isolates is a counter.
	ofstream myFile;
	myFile.open("Att3_results.csv");  // resultsFile = name of our file

	myFile << "TH_3 = 0.0069" << "," << "Probability" << "," << "Number of isolated graphs" << "," << "Probability estimation" << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			vector <int> distances(V);
			vector<vector<int>> vec;
			vec = build_random_graph(a[i], V);// build a random graph of V vertices with probability of p
			isolated_result +=is_Isolated(vec);// amount of graphs with isolated vertex from whole 500 
		}
		estimate = double(isolated_result) / 500;
		myFile << "," << a[i] << "," << isolated_result << "," << estimate << endl;
		c_isolated = 0, isolated_result = 0;
	}
	myFile.close();
}

// main function
int main() {
	srand(time(NULL));
	double a[10] = { 0.002,  0.003, 0.004 ,0.005, 0.006, 0.007, 0.0075, 0.0078,0.008, 0.009 },
		b[10] = { 0.007,0.008, 0.009, 0.101 ,0.11, 0.12, 0.13, 0.135, 0.14, 0.15 };
	attribute1(a);
	attribute2(b);
	attribute3(a);
	return 0;
}
