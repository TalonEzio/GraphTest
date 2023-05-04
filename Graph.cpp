#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;
#define OO 1000
typedef struct Graph
{
public:
	int n;
	int** a;
	void input(string fileName)
	{
		fstream f(fileName);
		if (f.is_open())
		{
			f >> this->n;

			a = new int* [n];
			for (int i = 0; i < n; ++i)a[i] = new int[n];

			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					f >> a[i][j];
				}
			}
		}
		else
		{
			cout << "Can't open file!";
		}
	}
	void output()
	{
		cout << n << endl;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				cout << a[i][j] << " ";
			}
			cout << endl;
		}
	}
	void BFS(int start, int end)
	{
		if (start == end)return;
		queue<int> open;
		open.push(start);

		bool* visited = new bool[n];
		fill(visited, visited + n, false);

		int* trace = new int[n];
		fill(trace, trace + n, -1);

		bool result = false;

		while (!open.empty())
		{
			int u = open.front();
			if (u == end)
			{
				result = true;
				break;
			}
			open.pop();

			for (int v = 0; v < n; ++v)
			{
				if (a[u][v] > 0)
				{
					if (a[u][v] > 0 && visited[v] == false)
					{
						visited[v] = true;
						trace[v] = u;
						open.push(v);
					}
				}
			}
		}
		if (result)
		{
			int temp = end;
			while (temp != start)
			{
				cout << temp << "<==";
				temp = trace[temp];
			}
			cout << start << endl;
		}
		else
		{
			cout << "No Result!" << endl;
		}
	}
	void DFS(int start, int end)
	{
		if (start == end)return;
		stack<int> open;
		open.push(start);

		bool* visited = new bool[n];
		fill(visited, visited + n, false);
		visited[start] = true;

		int* trace = new int[n];
		fill(trace, trace + n, -1);

		bool result = false;

		while (!open.empty())
		{
			int u = open.top();
			if (u == end)
			{
				result = true;
				break;
			}
			open.pop();

			for (int v = n - 1; v >= 0; --v)
			{
				if (a[u][v] > 0 && visited[v] == false)
				{
					visited[v] = true;
					trace[v] = u;
					open.push(v);
				}
			}
		}
		if (result)
		{
			int temp = end;
			while (temp != start)
			{
				cout << temp << "<==";
				temp = trace[temp];
			}
			cout << start << endl;
		}
		else
		{
			cout << "No Result!" << endl;
		}
	}
	void Dijkstra(int start, int end)
	{
		bool* visited = new bool[n];
		fill(visited, visited + n, false);

		int* trace = new int[n];
		fill(trace, trace + n, -1);

		int* d = new int[n];
		fill(d, d + n, OO);

		d[start] = 0;

		int current = start;
		while (current != end)
		{
			visited[current] = true;

			for (int i = 0; i < n; ++i)
			{
				if (a[current][i] > 0 && !visited[i])
				{
					int new_dist = d[current] + a[current][i];
					if (new_dist < d[i])
					{
						d[i] = new_dist;
						trace[i] = current;
					}
				}
			}
			int min_dist = OO;
			for (int i = 0; i < n; ++i)
			{
				if (d[i] < min_dist && !visited[i])
				{
					min_dist = d[i];
					current = i;
				}
			}

			if (min_dist == OO)
			{
				cout << "Not found!" << endl;
				return;
			}
		}

		cout << "Shortest distance from " << start << " to " << end << ": " << d[end] << endl;
		cout << "Path: " << end;
		while (trace[end] != -1)
		{
			cout << " <- " << trace[end];
			end = trace[end];
		}
		cout << endl;
	}

}Graph;


int main()
{
	Graph g;
	g.input("graph.inp");
	g.output();

	cout << "BFS: ";
	g.BFS(0, 5);

	cout << "DFS: ";
	g.DFS(0, 5);


	g.input("dijkstra.inp");
	g.Dijkstra(0, 5);

	system("pause");
	return 0;
}