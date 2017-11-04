# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <list>
# include <cstdlib>

using namespace std;


class Node {
private :
	string m_name; // a string that labels the node
	int m_id ; // a unique integer from 0 t o n−1,
			   // where n i s the t o t a l number of nodes
	int component; //component id for the node;
public :
	Node () {} ;
	Node ( const string & name, int id )
	{
		m_name = name, m_id = id ; 
	} 
		int id () const { return  m_id ; } ;
	    const string & name () const { return m_name ; } ;
} ;


class Graph {

private:
	vector<Node> m_nodes;
	vector<list<Node> > m_adjList;
  
public:

	//Construct the graph from a file of edges
	Graph( string  file)
	{
		//m_nodes.reserve(100000);
		//m_adjList.reserve(100000);
		vector<Node> m (10000);
		vector<list<Node> > l(1000);
		m_nodes = m;
		m_adjList = l;
		scan(file);
	}

	//Insert a edge (a,b) to m_adjList
	void addEdge(const Node & a, const Node & b)
	{
		m_adjList[a.id()].push_back(b);
		
	}

	//Insert a node a to m_nodes
	void addNode(const Node & a)
	{
	    
		m_nodes.at(a.id()) = a;
	}

	//Return node with id equal to i
	const Node & getNode(size_t i) const
	{
		return m_nodes[i];
	}

	//Return reference of the adjacency list of node a
	//list<Node> & getAdjNodes(const Node & a) const
	//{
	//	return m_adjList[a.id()];
	//}

	//Return constant reference to adjacency list of node a
	const list <Node> & getAdjNodes(const Node & a) const
	{
	    
		return m_adjList[a.id()];
	}
	

	//Return the total number of nodes in the graph
	size_t num_nodes () const
	{
		return m_nodes.size();
	}
	
	vector<list<Node> > getAdjList() const
	{
		return m_adjList;
	}
	
	vector<Node> getNodesList() const
	{
		return m_nodes;
	}
	
	void setAdjList(vector<list<Node> > adjList)
	{
		m_adjList = adjList;
	}
	
	void setNodes(vector<Node> nodesList)
	{
		m_nodes = nodesList;
	}
	

	//Create a graph from a tab-separated text edage list file to adjacency lists
	void scan( string  file)
	{
       ifstream inFile;
       inFile.open(file.c_str());

       int node_index = 0;
       string str1, str2;
       Node node1, node2;

       inFile>> str1 >> str2;

       while(!inFile.eof())
       {
       

       	int myNode = findNode(str1);
       	
       	if(myNode == -1)
       	{
       		Node nd1(str1, node_index);
       		addNode(nd1);
       		node1 = nd1;
       		node_index++;
       	}

       	else
       	{
       		node1 = getNode(myNode);
       	}

       	myNode = findNode(str2);

       	if(myNode == -1)
       	{
       		Node nd2(str2, node_index);
       		addNode(nd2);
       		node2 = nd2;
       		node_index++;
       	}

       	else
       	{
       		node2 = getNode(myNode);
       	}

       	addEdge(node1,node2);
	inFile >>str1 >> str2;

       }

       inFile.close();
	}

	//Save a graph from adjacency lists to a tab-seperated text edge list file
	void save ( string  file) const
	{
		ofstream outFile;
		outFile.open(file.c_str());

		for(int i =0; i< m_adjList.size(); i++)
		{
		for (list<Node>::const_iterator it=m_adjList[i].begin(); it != m_adjList[i].end(); it++)
		{
				outFile<< m_nodes[i].name()<<"\t"<<it->name()<<endl;
		}
		}
	}


	//Returns a node if it is already in m_nodes, otherwise returns null
	int findNode (string str)
	{
		if(m_nodes.size()== 0)
			return -1;

		for(int i=0; i<m_nodes.size();i++)
		{
			if(str == m_nodes[i].name())
				return i;
		}

		return -1;
	}
	
	//Reverses a directed graph
	Graph reverseGraph()
	{
		vector<list<Node> > o_adjList = g.getAdjList();
		const int listLength = o_adjList.size();
		vector<list<Node> > r_adjList(listLength);
		Graph r_graph;
		
		for(int i =0; i<listLength; i++)
		{
			for (list<Node>::const_iterator it=o_adjList[i].begin(); it != o_adjList[i].end(); it++)
			{
				r_adjList[it->id()].push_back(g.getNode(i));
			}
		}
		r_graph.setAdjList(r_adjList);
		r_graph.setNodes(g.getNodesList());
		return r_graph;
	}
	

};



void testall ()
{
	for(int i=1; i<=3; i++)
	{
		string s(1,(i +'0'));
		string inputfilename = "in_small"+s+ ".txt";
		Graph g(inputfilename);
		string outputfilename = "out_small"+s+ ".txt";
		g.save(outputfilename);
	}

   for(int i=1; i<=2; i++)
    {
    	string s(1, (i + '0'));
    	string inputfilename = "in_large"+ s+ ".txt";
    	Graph g(inputfilename);
    	string outputfilename = "out_large"+ s+ ".txt";
    	g.save(outputfilename);
    }
}

vector<size_t> find_connected_components(Graph& G)
{
	const int nodeSize = G.num_nodes();
	vector<size_t> componentId (nodeSize);
	bool visited[nodeSize];
	size_t component = 0;
	
	for(int i=0; i<nodeSize; i++)
	{
		visited[i] = false;
	}
	
	for(int i=0; i<nodeSize; i++)
	{
		if(!visited[i])
		{
			explore(G,i,visited,componentId,component);
			component++;
		}
	}
	
	
}

void explore(Graph & G, int node, bool* visited, vector<size_t> & componentId, int component)
{
	visited[node] = true;
	componentId[node] = component;
	vector<list<Node> > adjList = G.getAdjList();
	for (list<Node>::const_iterator it=adjList[node].begin(); it != adjList[node].end(); it++)
	{
		if(!visited[it->id()])
		{
			explore(G,it->id(),visited,componentId,component);
		}
	}
}


int main ()
{
	 testall();
}
