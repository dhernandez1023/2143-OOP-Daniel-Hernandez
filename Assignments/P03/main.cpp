/************************************************************************
 *
 *  Author:           Daniel Hernandez
 *  Email:            dhernandez1023@my.msutexas.edu
 *  Label:            Program 03
 *  Title:            Graphviz Class
 *  Course:           CMPS-2143
 *  Semester:         Spring 2023
 *
 *  Description:
 *        This program will recreate certain parts of the
 *        graphviz online tool. Using this program, you can
 *        create graphs for a linked list, double linked list,
 *        and a binary search tree that will work in graphviz.
 *
 *
 *  Files:
 *      main.cpp    : driver program
 *      output.txt  : output file
 ************************************************************************/
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

/**
 * Attribute
 *
 * Description:
 *      This class allows for the creation of an attribute map.
 *
 *
 * Public Methods:
 *      Attribute()
 *      void addAttribute(string key, string val)
 *      void addAttributes(map<string, string> atts)
 *
 * Usage:
 *      map<string, string> Name;
 *
 */
class Attribute {
protected:
  map<string, string> att; // attributes

public:
  Attribute() {}

  /**
   * Update an edge attribute. Assumes key is valid.
   */
  void addAttribute(string key, string val) { att[key] = val; }

  /**
   * Takes a map of attributes. Loops over them and saves them
   * locally.
   */
  void addAttributes(map<string, string> atts) {
    for (auto const &x : atts) {
      att[x.first] = x.second;
    }
  }

  /**
   * Use our basic print to dump this class out.
   */
  friend ostream &operator<<(ostream &os, Attribute &e) {

    os << "[";

    int i = 0;
    for (auto const &x : e.att) {
      os << x.first << "="
         << "\"" << x.second << "\"";

      if (i < e.att.size() - 1) {
        os << ", ";
      }
      i++;
    }
    os << "]";

    return os;
  }
};

/**
 * Edge
 *
 * Description:
 *      This class allows for the creation of a default and
 *      overloaded edge. It also prints out the edge section
 *      of the graph using an overloaded << operator.
 *
 * Public Methods:
 *      Edge()
 *      Edge(string color, string arrow, string arrowtail,
 *           string direction, string tailclip)
 *      Edge(int start, int end)
 *
 * Private Methods:
 *      int   eid
 *      int   start
 *      int   end
 *
 */
class Edge : public Attribute {
protected:
  int eid;
  int start;
  int end;

public:
  Edge() {
    att["color"] = "black";   // default color
    att["arrowhead"] = "vee"; // default arrowhead shape
    att["arrowtail"] = "vee"; // default arrowtail shape
    att["dir"] = "one";       // default direction
  }

  Edge(string color, string arrow, string arrowtail, string direction) {
    att["color"] = color;         // overloading color
    att["arrowhead"] = arrow;     // overloading arrowhead
    att["arrowtail"] = arrowtail; // overloading arrowtail
    att["dir"] = direction;       // overloading direction
  }
  Edge(int start, int end) {
    this->start = start;
    this->end = end;
  }

  friend ostream &operator<<(ostream &os, Edge &e) {
    os << e.start << " -> " << e.end << " ";
    os << "[";

    int i = 0;
    for (auto const &x : e.att) {
      os << x.first << "="
         << "\"" << x.second << "\"";

      if (i < e.att.size() - 1) {
        os << ", ";
      }
      i++;
    }
    os << "]";

    return os;
  }
};

/**
 * Node
 *
 * Description:
 *      This class creates a default node and overloaded node
 *      with attributes.
 *
 * Public Methods:
 *      Node()
 *      Node(map<string, string> atts)
 *
 * Private Methods:
 *      int    nid
 *
 */
class Node : public Attribute {
  int nid;

public:
  Node() {
    att["color"] = "black";  // default color
    att["shape"] = "record"; // default node shape
  }

  Node(map<string, string> atts) {
    for (auto const &x : atts) {
      att[x.first] = x.second;
    }
  }
};

/**
 * GraphViz
 *
 * Description:
 *      This class does almost all the work in the program.
 *      You can create an instance of graphviz, add and edit
 *      nodes. Will also add and edit edges and print the nodes
 *      portion of the graph.
 *
 *
 * Public Methods:
 *      GraphViz()
 *      GraphViz(string graph_name, string graph_shape)
 *      int addNode()
 *      int addNode(map<string, string> atts)
 *      void editNode(int id, string key, string value)
 *      void addEdge(int start, int end)
 *      void addEdge(int start, int end, map<string, string> att)
 *      void editEdge(int id, string key, string value)
 *
 *
 * Private Methods:
 *        int           edgeId;
 *        int           nodeId;
 *        vector<Edge>  Edges;
 *        vector<Node>  Nodes;
 *        string        graphName;
 *        string        graphShape;
 *
 * Usage:
 *        GraphViz G()
 *        GraphViz G(string, string)
 *        G.addNode()
 *        G.addNode(att)
 *        G.editNode(num, string, string)
 *        G.addEdge(num, num)
 *        G.addEdge(num, num, att)
 *        G.editEdge(num, string, string)
 *
 */
class GraphViz {
  int edgeId;
  int nodeId;
  vector<Edge> Edges;
  vector<Node> Nodes;
  string graphName;
  string graphShape;

public:
  GraphViz() {
    edgeId = 0;
    nodeId = 0;
    graphName = "foo";
  }

  GraphViz(string graph_name, string graph_shape) {
    edgeId = 0;
    nodeId = 0;
    graphName = graph_name;
    graphShape = graph_shape;
  }

  int addNode() {
    Nodes.push_back(Node());
    return Nodes.size() - 1;
  }

  int addNode(map<string, string> atts) {
    Nodes.push_back(Node(atts));

    return Nodes.size() - 1;
  }

  void editNode(int id, string key, string value) {
    Nodes[id].addAttribute(key, value);
  }

  void addEdge(int start, int end) { Edges.push_back(Edge(start, end)); }

  void addEdge(int start, int end, map<string, string> att) {

    Edges.push_back(Edge(start, end));
    Edges[Edges.size() - 1].addAttributes(att);
  }

  void editEdge(int id, string key, string value) {
    Edges[id].addAttribute(key, value);
  }

  friend ostream &operator<<(ostream &os, GraphViz &g) {
    os << "digraph " << g.graphShape << " {\n";
    if (g.graphShape == "BST") {
      os << "rankdir=\"TD\"" << endl;
    } else {
      os << "rankdir=\"LR\"" << endl;
      ;
    }
    for (int i = 0; i < g.Nodes.size(); i++) {
      os << i << " " << g.Nodes[i] << endl;
    }
    for (int i = 0; i < g.Edges.size(); i++) {
      os << g.Edges[i] << endl;
    }
    os << "}\n";

    return os;
  }
};

int main() {
  ofstream fout;
  fout.open("output.txt");

  // Headings
  cout << "Daniel Hernandez\n";
  cout << "3/8/2023\n";
  cout << "Spring 2143\n\n";
  fout << "Daniel Hernandez\n";
  fout << "3/8/2023\n";
  fout << "Spring 2143\n\n";

  // Create graphviz instances with specific shapes
  GraphViz G("LinkedList", "LL");
  GraphViz D("DoublyLinkedList", "DLL");
  GraphViz B("BinarySearchTree", "BST");

  // Default node and edge attributes
  map<string, string> defNode;
  map<string, string> defEdge;
  // Attribute that gets a map of attributes and
  // adds them to "A"
  Attribute A;
  defNode["shape"] = "record";
  defNode["color"] = "black";
  A.addAttributes(defNode);

  defEdge["color"] = "black";
  defEdge["arrowhead"] = "vee";
  A.addAttributes(defEdge);

  // making the linked list nodes
  // and putting in attributes
  int nodeId = G.addNode(defNode);
  nodeId = G.addNode();
  G.editNode(1, "shape", "circle");
  G.editNode(1, "color", "red");
  G.editNode(1, "label", "4");
  nodeId = G.addNode();
  G.editNode(2, "shape", "diamond");
  G.editNode(2, "color", "purple");
  G.editNode(2, "style", "filled");
  nodeId = G.addNode();
  G.editNode(3, "shape", "octagon");
  G.editNode(3, "color", "green");
  G.editNode(3, "style", "filled");
  nodeId = G.addNode(defNode);
  G.editNode(4, "label", "{ <data> 56 | <next> }");
  nodeId = G.addNode(defNode);
  G.editNode(5, "color", "white");
  G.editNode(5, "label", "{ <data> null }");

  // making the linked list edges
  // and putting in attributes
  G.addEdge(0, 1, defEdge);
  G.editEdge(0, "color", "red");
  G.editEdge(0, "arrowhead", "crow");
  G.editEdge(0, "arrowtail", "dot");
  G.editEdge(0, "dir", "both");
  G.addEdge(1, 2, defEdge);
  G.editEdge(1, "color", "green");
  G.editEdge(1, "arrowhead", "curve");
  G.addEdge(2, 3, defEdge);
  G.editEdge(2, "color", "pink");
  G.editEdge(2, "arrowhead", "dot");
  G.editEdge(2, "arrowtail", "box");
  G.editEdge(2, "dir", "both");
  G.addEdge(3, 4, defEdge);
  G.editEdge(3, "color", "brown");
  G.editEdge(3, "dir", "none");
  G.addEdge(4, 5, defEdge);
  G.editEdge(4, "color", "brown");
  G.editEdge(4, "dir", "one");

  // making the doubly linked list nodes
  // and putting in attributes
  nodeId = D.addNode(defNode);
  D.editNode(0, "color", "gray");
  D.editNode(0, "label", "{ <data> 5 | <next> }");
  nodeId = D.addNode();
  D.editNode(1, "shape", "star");
  D.editNode(1, "color", "yellow");
  D.editNode(1, "style", "filled");
  nodeId = D.addNode();
  D.editNode(2, "shape", "triangle");
  D.editNode(2, "color", "blue");
  nodeId = D.addNode(defNode);
  D.editNode(3, "shape", "egg");
  D.editNode(3, "color", "deepskyblue");
  D.editNode(3, "label", "14");
  D.editNode(3, "style", "filled");
  nodeId = D.addNode(defNode);
  D.editNode(4, "shape", "house");
  D.editNode(4, "color", "purple");

  // making the doubly linked list edges
  // and putting in attributes
  D.addEdge(0, 1, defEdge);
  D.editEdge(0, "color", "blue");
  D.editEdge(0, "arrowhead", "icurve");
  D.addEdge(1, 0, defEdge);
  D.editEdge(1, "color", "blue");
  D.editEdge(1, "arrowhead", "tee");
  D.editEdge(1, "dir", "one");
  D.addEdge(1, 2, defEdge);
  D.editEdge(2, "color", "pink");
  D.editEdge(2, "arrowhead", "none");
  D.addEdge(2, 1, defEdge);
  D.editEdge(3, "color", "red");
  D.editEdge(3, "arrowhead", "inv");
  D.editEdge(3, "arrowtail", "icurve");
  D.editEdge(3, "dir", "both");
  D.addEdge(2, 3, defEdge);
  D.editEdge(4, "color", "purple");
  D.addEdge(3, 2, defEdge);
  D.editEdge(5, "color", "gray");
  D.editEdge(5, "dir", "none");
  D.addEdge(3, 4, defEdge);
  D.editEdge(6, "arrowhead", "icurve");
  D.addEdge(4, 3, defEdge);
  D.editEdge(7, "color", "yellow");

  // Making the binary search tree nodes
  // and putting in attributes
  nodeId = B.addNode(defNode);
  B.editNode(0, "color", "purple");
  nodeId = B.addNode(defNode);
  B.editNode(1, "shape", "egg");
  B.editNode(1, "color", "aquamarine");
  B.editNode(1, "label", "5");
  B.editNode(1, "style", "filled");
  nodeId = B.addNode(defNode);
  B.editNode(2, "shape", "folder");
  nodeId = B.addNode(defNode);
  B.editNode(3, "shape", "invtriangle");
  B.editNode(3, "color", "darkseagreen");
  B.editNode(3, "style", "filled");
  nodeId = B.addNode(defNode);
  B.editNode(4, "shape", "star");
  B.editNode(4, "label", "37");
  nodeId = B.addNode(defNode);
  B.editNode(5, "shape", "octagon");
  B.editNode(5, "color", "cyan");
  B.editNode(5, "style", "filled");
  nodeId = B.addNode(defNode);
  B.editNode(6, "shape", "hexagon");
  B.editNode(6, "color", "forestgreen");
  B.editNode(6, "label", "93");

  // making the binary search tree edges
  // and putting in attributes
  B.addEdge(0, 1, defEdge);
  B.editEdge(0, "color", "pink");
  B.editEdge(0, "arrowhead", "tee");
  B.addEdge(0, 2, defEdge);
  B.editEdge(1, "color", "green");
  B.editEdge(1, "arrowhead", "inv");
  B.editEdge(1, "dir", "none");
  B.addEdge(1, 3, defEdge);
  B.editEdge(2, "color", "red");
  B.editEdge(2, "arrowhead", "icurve");
  B.addEdge(1, 4, defEdge);
  B.editEdge(3, "color", "crimson");
  B.editEdge(3, "arrowhead", "normal");
  B.addEdge(2, 5, defEdge);
  B.editEdge(4, "color", "chocolate");
  B.editEdge(4, "arrowhead", "diamond");
  B.editEdge(4, "dir", "one");
  B.addEdge(2, 6, defEdge);
  B.editEdge(5, "color", "deeppink");
  B.editEdge(5, "arrowhead", "box");
  B.editEdge(5, "arrowtail", "diamond");
  B.editEdge(5, "dir", "both");

  // Prints graphs to console and output file
  cout << G << endl;
  fout << G << endl;
  cout << D << endl;
  fout << D << endl;
  cout << B << endl;
  fout << B << endl;

  fout.close();
}