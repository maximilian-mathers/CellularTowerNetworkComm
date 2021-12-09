#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>
#include <map>
#include <time.h>

using namespace std;

ofstream fout1, fout2;

class G1
{
	int V;

	list<int>* adj;
public:
	G1(int V);

	void addEdge(int v, int w);

	void BFS(int s);
};

G1::G1(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void G1::addEdge(int v, int w)
{
	adj[v].push_back(w);
}

void G1::BFS(int s)
{
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	list<int> queue;

	visited[s] = true;
	queue.push_back(s);

	list<int>::iterator i;

	while (!queue.empty())
	{
		s = queue.front();
		fout1 << s << "\n";
		queue.pop_front();

		for (i = adj[s].begin(); i != adj[s].end(); ++i)
		{
			if (!visited[*i])
			{
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
}

class G2 {
public:
	map<int, bool> visited;
	map<int, list<int> > adj;

	void addEdge(int v, int w);

	void DFS(int v);
};

void G2::addEdge(int v, int w)
{
	adj[v].push_back(w);
}

void G2::DFS(int v)
{
	visited[v] = true;
	fout2 << v << "\n";

	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFS(*i);
}



int main() {

	fout1.open("BFS.txt");
	fout2.open("DFS.txt");

	//string name;
	//name.resize(4);
	//vector<string> towers;


	//char c1, c2, c3, c4;
	//c1 = c2 = c3 = c4 = 'A';

	//fout.open("Alp.txt");

	int i, j, k, u;
	//	for (i = 0; i < 26; i++) for (j = 0; j < 26; j++) for (k = 0; k < 26; k++) for (u = 0; u < 6; u++) { name[0] = char(c1 + i), name[1] = char(c2 + j), name[2] = char(c3 + k), name[3] = char(c4 + u); towers.push_back(name); }

	//	while give stack overflow at 10000
	int v = 4000;

	G1 g_1(v);
	G2 g_2;
	int start_vertex = 724;

	for (i = 0; i < v; i++) {
		int random = 2 + (rand() % 3);
		for (j = 0; j < random; j++) {
		L1:
			int random2 = rand() % v; 
			if (random2 == v) 
				goto L1;
			g_1.addEdge(i, random2);
			g_1.addEdge(random2, i);
			g_2.addEdge(i, random2);
			g_2.addEdge(random2, i);
		}
	}
	
	//cout << "***********************************" << endl;
	cout << "Cellular Tower Network Communicator" << endl;
	cout << "***********************************" << endl;
	cout << endl;
	bool repeat = true;
	while (repeat)
	{
		cout << "Enter a Tower number to find associated towers in the network: " << endl;

		cin >> start_vertex;
		if (start_vertex > 4001)
		{
			cout << "Tower does not exist, please enter a valid Tower number: " << endl;
			cin >> start_vertex;
			while (start_vertex > 4001)
			{
				cout << "Tower does not exist, please enter a valid Tower number: " << endl;
				cin >> start_vertex;
			}
		}

		int goTwice = 0;
		string track = "";

		string txtUser = "";
		while (goTwice < 2 && track == "")
		{
			cout << "Type BFS to receive the Breadth First Search results." << endl;
			cout << "Type DFS to receive the Depth First Search results." << endl;
			cin >> txtUser;

			if (txtUser == "BFS")
			{
				clock_t tStart1 = clock();
				fout1 << "The following is the Breadth First Traversal (starting from Tower " << start_vertex << ")" << endl;;
				g_1.BFS(start_vertex);
				cout << "Time taken for BFS: " << (double)(clock() - tStart1) / CLOCKS_PER_SEC << " seconds" << endl;
				goTwice++;
			}

			if (txtUser == "DFS")
			{
				clock_t tStart2 = clock();
				fout2 << "The following is the Depth First Traversal (starting from Tower " << start_vertex << ")" << endl;
				g_2.DFS(start_vertex);
				cout << "Time taken for DFS: " << (double)(clock() - tStart2) / CLOCKS_PER_SEC << " seconds" << endl;
				goTwice++;
			}
		}
		
		string userRepeat = "";
		cout << "Enter " << "'Y' to find other connected Towers on the network: " << endl;
		cout << "Enter 'N' to exit." << endl;
		cin >> userRepeat;
		if (userRepeat == "Y")
		{
			cout << "Results are available in the outputted BFS and DFS text files." << endl;
			cout << endl;
			continue;
		}
		if (userRepeat == "N")
			break;
	}

	fout1.close();
	fout2.close();

	return 0;
}
