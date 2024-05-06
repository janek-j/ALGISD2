#include <iostream>
#include <vector>

template<typename T>
class Iterator {
public:
    virtual ~Iterator() {;}
    Iterator() {;}
    virtual bool IsDone() = 0;
    virtual T & operator * () = 0;
    virtual T & operator ++ () = 0;
};

//wierzcholek
class Vertex {
    int number;
public:
    int weight; std::string label;
    Vertex(int n) : number(n), weight(0) {}
    int Number() const { return number; }
};

//krawedz
class Edge {
protected:
    Vertex* v0;
    Vertex* v1;
public:
    int weight;
    std::string label;
    Edge (Vertex *V0, Vertex* V1) : v0(V0), v1(V1) {}
    Vertex* V0 (){ return v0; };
    Vertex* V1 (){ return v1; };
    Vertex* Mate (Vertex *v) { return (v == v0) ? v1 : v0; }
};

class GraphAsMatrix {
    std::vector<Vertex *> vertices;
    std::vector<std::vector<Edge *> > adjacencyMatrix;
    int numberOfVertices;
    int numberOfEdges = 0;
    bool isDirected;
    std::vector<bool> visited;
public:
    GraphAsMatrix(int n, bool b);

    int NumberOfVertices() { return numberOfVertices; }

    bool IsDirected() { return isDirected; }

    int NumberOfEdges() { return numberOfEdges; }

    bool IsEdge(int u, int v);

    void MakeNull();

    void AddEdge(int u, int v);

    Edge *SelectEdge(int u, int v);

    Vertex *SelectVertex(int v);

    void DFS();

    void DFSVisit(Vertex *v);

    class AllEdgesIter : public Iterator<Edge> {
        GraphAsMatrix &owner;
        int row;
        int col;
    public:
        AllEdgesIter(GraphAsMatrix &g) : owner(g), row(0), col(-1) {
            next();
        }
        void next() {
            if (row >= owner.numberOfVertices) return; // Already done

            do {
                col++;
                if (col >= owner.numberOfVertices) {
                    col = 0;
                    row++;
                }
                if (row >= owner.numberOfVertices) {
                    break; // Completed all rows
                }
            } while (owner.adjacencyMatrix[row][col] == nullptr);
        }

        bool IsDone() override {
            return row >= owner.numberOfVertices;
        }

        Edge &operator*() override {
            return *owner.adjacencyMatrix[row][col];
        }

        Edge &operator++() override {
            if (IsDone()) {
                throw std::out_of_range("Iterator out of range");
            }
            next();
            return **this; //zwraca referencje do current edga
        }
    };
};
GraphAsMatrix::GraphAsMatrix(int n, bool b) {
    isDirected = b;
    numberOfVertices = n;
    vertices.resize(n);
    for (int i = 0; i < n; i++) {
        vertices[i] = new Vertex(i);
    }
    adjacencyMatrix.resize(n);
    for (auto &row: adjacencyMatrix) {
        row.resize(n, nullptr);
    }
    visited.resize(n);
}

bool GraphAsMatrix::IsEdge(int u, int v) {
    if (u >= 0 && u < numberOfVertices && v >= 0 && v < numberOfVertices)
        return adjacencyMatrix[u][v] != nullptr;
    return false;
}

void GraphAsMatrix::AddEdge(int u, int v) {
    if (u < 0 || u >= numberOfVertices || v < 0 || v >= numberOfVertices) return;
    if (adjacencyMatrix[u][v] == nullptr) {
        Edge* newEdge = new Edge(vertices[u], vertices[v]);
        adjacencyMatrix[u][v] = newEdge;
        if (!isDirected)
            adjacencyMatrix[v][u] = newEdge;
        numberOfEdges++;
    }
}

Edge *GraphAsMatrix::SelectEdge(int u, int v) {
    if (u >= 0 && u < numberOfVertices && v >= 0 && v < numberOfVertices)
        return adjacencyMatrix[u][v];
    return nullptr;
}

Vertex* GraphAsMatrix::SelectVertex(int v) {
    if (v >= 0 && v < numberOfVertices)
        return vertices[v];
    return nullptr;
}

void GraphAsMatrix::MakeNull() {
    for(int i = 0; i < numberOfVertices; i++) {
        for(int j = 0; j < numberOfEdges; j++) {
            if(adjacencyMatrix[i][j] != nullptr) {
                delete adjacencyMatrix[i][j];
            }
            if(!isDirected) {
                adjacencyMatrix[i][j] = nullptr;
            }
        }
    }
    numberOfEdges = 0;
}

void GraphAsMatrix::DFS() {
    std::fill(visited.begin(), visited.end(), false);
    for (int v = 0; v < numberOfVertices; v++) {
        if (!visited[v]) {
            DFSVisit(vertices[v]);
            std::cout << "Completed component starting from vertex: " << v << std::endl;
        }
    }
}

void GraphAsMatrix::DFSVisit(Vertex *v) {
    int vIndex = v->Number();
    visited[vIndex] = true;
    std::cout << "Visit na: " << vIndex << std::endl;
    for(int i = 0; i < numberOfVertices; i++) {
        if (adjacencyMatrix[vIndex][i] != nullptr && !visited[i]) {
            DFSVisit(vertices[i]);
        }
    }
}

void przetestujDFS() {
    GraphAsMatrix *graph = new GraphAsMatrix(10, false);
    graph->AddEdge(0,1);
    graph->AddEdge(1,2);
    graph->AddEdge(2,3);
    graph->AddEdge(3,4);
    graph->AddEdge(3,7);
    graph->AddEdge(4,5);
    graph->AddEdge(5,9);
    graph->AddEdge(9,9);

    graph->AddEdge(6,8);
    graph->AddEdge(8,6);
    graph->DFS();

    std::cout << "Skonczylem testowac nieskierowany" << std::endl;
    std::cout << std::endl << "Teraz skierowany." << std::endl;
    GraphAsMatrix *graph1 = new GraphAsMatrix(10, true);
    graph1->AddEdge(0,1);
    graph1->AddEdge(1,2);
    graph1->AddEdge(2,3);
    graph1->AddEdge(3,4);
    graph1->AddEdge(3,7);
    graph1->AddEdge(4,5);
    graph1->AddEdge(5,9);
    graph1->AddEdge(9,9);

    graph1->AddEdge(6,8);
    graph1->AddEdge(8,6);
    graph1->DFS();
    int counted = graph1->NumberOfVertices();
    std::cout << "Liczba wierzcholkow:" << counted << std::endl;

}

void przetestujWizytator() {

}

//test 1 dziala
void test1(GraphAsMatrix &graf) {
    std::cout << "Liczba krawedzi " << graf.NumberOfEdges() << std::endl;
    std::cout << "Liczba wierzcholkow " << graf.NumberOfVertices() << std::endl;
    Vertex *v = graf.SelectVertex(2);
    if (v) {
        std::cout << "Unikalny numer v: " << v->Number() << std::endl;
        v->weight = v->Number() * v->Number();
        std::cout << "Waga v: " << v->weight << std::endl;
    }

    graf.AddEdge(1, 2);
    graf.AddEdge(1, 2);
    graf.AddEdge(2, 3);
    graf.AddEdge(3, 4);
    graf.AddEdge(9, 9);

    std::cout << "Liczba wierzcholkow po dodaniu krawedzi: " << graf.NumberOfVertices() << std::endl;
    std::cout << "Liczba krawedzi po dodaniu krawedzi: " << graf.NumberOfEdges() << std::endl;

    std::cout << "Czy istnieje krawedz (1,1): " << graf.IsEdge(1, 1) << std::endl;
    std::cout << "Czy istnieje krawedz (1,2): " << graf.IsEdge(1, 2) << std::endl;
    std::cout << "Czy istnieje krawedz (2,1): " << graf.IsEdge(2, 1) << std::endl;

    Edge* e;
    std::vector<std::pair<int,int>> edgesToTest = {{1,2}, {2,3}, {3,4}, {9,9}};
    for(auto &edgePair: edgesToTest) {
        e = graf.SelectEdge(edgePair.first, edgePair.second);
        if (e) {
            std::cout << "V0 dla e: " << e->V0()->Number() << std::endl;
            std::cout << "V1 dla e: " << e->V1()->Number() << std::endl;
            std::cout << "Sasiad V0 dla e: " << e->Mate(e->V0())->Number() << std::endl;
            std::cout << "Sasiad V1 dla e: " << e->Mate(e->V1())->Number() << std::endl;
            e->weight = e->V0()->Number() + e->V1()->Number();
            std::cout << "Waga krawedzi e: " << e->weight << std::endl;
        } else {
            std::cout << "Krawedz (" << edgePair.first << ", " << edgePair.second << ") nie istnieje w grafie. " << std::endl;
        }
    }
}

void test2(GraphAsMatrix &graf) {
    std::cout << "Liczba krawedzi " << graf.NumberOfEdges() << std::endl;
    std::cout << "Liczba wierzcholkow " << graf.NumberOfVertices() << std::endl;
    Vertex *v = graf.SelectVertex(2);
    if (v) {
        std::cout << "Unikalny numer v: " << v->Number() << std::endl;
        v->weight = v->Number() * v->Number();
        std::cout << "Waga v: " << v->weight << std::endl;
    }

    graf.AddEdge(1, 2);
    graf.AddEdge(1, 2);
    graf.AddEdge(2, 3);
    graf.AddEdge(3, 4);
    graf.AddEdge(9, 9);

    std::cout << "Liczba wierzcholkow po dodaniu krawedzi: " << graf.NumberOfVertices() << std::endl;
    std::cout << "Liczba krawedzi po dodaniu krawedzi: " << graf.NumberOfEdges() << std::endl;

    std::cout << "Czy istnieje krawedz (1,1): " << graf.IsEdge(1, 1) << std::endl;
    std::cout << "Czy istnieje krawedz (1,2): " << graf.IsEdge(1, 2) << std::endl;
    std::cout << "Czy istnieje krawedz (2,1): " << graf.IsEdge(2, 1) << std::endl;

    Edge* e;
    std::vector<std::pair<int,int>> edgesToTest = {{1,2}, {2,3}, {3,4}, {9,9}};
    for(auto &edgePair: edgesToTest) {
        e = graf.SelectEdge(edgePair.first, edgePair.second);
        if (e) {
            std::cout << "V0 dla e: " << e->V0()->Number() << std::endl;
            std::cout << "V1 dla e: " << e->V1()->Number() << std::endl;
            std::cout << "Sasiad V0 dla e: " << e->Mate(e->V0())->Number() << std::endl;
            std::cout << "Sasiad V1 dla e: " << e->Mate(e->V1())->Number() << std::endl;
            e->weight = e->V0()->Number() + e->V1()->Number();
            std::cout << "Waga krawedzi e: " << e->weight << std::endl;
        } else {
            std::cout << "Krawedz (" << edgePair.first << ", " << edgePair.second << ") nie istnieje w grafie. " << std::endl;
        }
    }
    graf.AddEdge(3,5);
    graf.AddEdge(8,3);
    graf.AddEdge(5,2);

    // Wypisanie wszystkich krawedzi
    std::cout << "\nWypisanie wszystkich krawedzi:\n";
    GraphAsMatrix::AllEdgesIter allEdgesIter(graf);
    for (; !allEdgesIter.IsDone(); ++allEdgesIter) {
        Edge &e = *allEdgesIter;
        std::cout << "Edge from " << e.V0()->Number() << " to " << e.V1()->Number() << std::endl;
    }

    std::cout << "\nKrawedzie dochodzace do wierzcholka 2:\n";
    GraphAsMatrix::AllEdgesIter itIn(graf);
    for (; !itIn.IsDone(); ++itIn) {
        Edge &e = *itIn;
        if (e.V1()->Number() == 2) { // filtrujemy krawędzie, które dochodzą do wierzchołka o numerze 2
            std::cout << "Edge from " << e.V0()->Number() << " to " << e.V1()->Number() << std::endl;
        }
    }

    std::cout << "\nKrawedzie wychodzace z wierzcholka 3:\n";
    GraphAsMatrix::AllEdgesIter itOut(graf);
    for (; !itOut.IsDone(); ++itOut) {
        Edge &e = *itOut;
        if (e.V0()->Number() == 3) { // filtrujemy krawędzie, które wychodzą z wierzchołka o numerze 3
            std::cout << "Edge from " << e.V0()->Number() << " to " << e.V1()->Number() << std::endl;
        }
    }
}

void zadanie1() {
    GraphAsMatrix skierowany(10, true);
    GraphAsMatrix nieskierowany(10, false);

    std::cout << "Test dla skierowanego: " << std::endl;
    test1(skierowany);
    std::cout << "Koniec testu dla skierowanego" << std::endl;
    std::cout << std::endl;

    std::cout << "Test dla nieskierowanego: " << std::endl;
    test1(nieskierowany);
    std::cout << "Koniec testu dla nieskierowanego" << std::endl;
}

//Zadanie drugie nie dziala, musze zrobic na nowo, bo wywala segfault core dumped xp
void zadanie2() {
    GraphAsMatrix skierowany(10, true);
    GraphAsMatrix nieskierowany(10, false);

    std::cout << "Test dla skierowanego: " << std::endl;
    test2(skierowany);
    std::cout << "Koniec testu dla skierowanego" << std::endl;
    std::cout << std::endl;

    std::cout << "Test dla nieskierowanego: " << std::endl;
    test2(nieskierowany);
    std::cout << "Koniec testu dla nieskierowanego" << std::endl;
}

int main(int args, char* argv[]) {
    zadanie1();
    return 0;
}