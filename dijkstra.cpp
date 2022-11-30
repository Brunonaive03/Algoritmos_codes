#include <iostream>
using namespace std;

struct heap_node
{
    int tam, origem;
};

struct heap_return
{
    int raiz, distancia;
};

class minHeap
{
private:
    int heap_size, heap_capacity;
    heap_node *heap;

public:
    minHeap(int n)
    {
        heap_capacity = n;
        heap = (heap_node *)malloc(heap_capacity * sizeof(heap_node));
        heap_size = 0;
    }

    void heap_add(int t, int o)
    {
        if (heap_size == heap_capacity)
        {
            heap_double();
        }

        heap[heap_size].tam = t;
        heap[heap_size].origem = o;
        heap_size++;

        bubble_up(heap_size - 1);
    }

    void bubble_up(int i)
    {
        if (i != 0 && heap[i].tam < heap[parent(i)].tam)
        {
            heap_swap(i, parent(i));
            return bubble_up(parent(i));
        }
    }

    void bubble_down(int i)
    {
        int m = i;
        int l = child_left(i);
        int r = child_right(i);

        if (l < heap_size && heap[m].tam > heap[l].tam)
        {
            m = l;
        }

        if (r < heap_size && heap[m].tam > heap[r].tam)
        {
            m = r;
        }

        if (heap[i].tam != heap[m].tam && heap[i].origem != heap[m].origem) // se os nodes forem diferentes
        {
            heap_swap(i, m);
            return bubble_down(m);
        }
    }

    void heap_swap(int i, int j)
    {
        heap_node temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    heap_return heap_extract()
    {
        heap_return retorno;
        retorno.distancia = -1;
        retorno.raiz = -1;

        if (heap_size > 0)
        {
            heap_node temp;
            temp = heap[0];
            heap[0] = heap[heap_size - 1];
            heap[heap_size - 1] = temp;
            heap_size--;

            retorno.raiz = temp.origem;
            retorno.distancia = temp.tam;

            bubble_down(0);
        }
        return retorno;
    }

    int parent(int index) { return (index - 1) / 2; }

    int child_left(int index) { return 2 * index + 1; }

    int child_right(int index) { return 2 * index + 2; }

    void heap_double()
    {
        heap_capacity *= 2;
        heap_node *heap_velha;
        heap_node *heap_nova = (heap_node *)malloc(heap_capacity * sizeof(heap_node));
        heap_velha = heap;
        heap = heap_nova;

        for (int i; i < heap_size; i++)
        {
            heap[i] = heap_velha[i];
        }

        free(heap_velha);
    }

    void heap_destruct() { free(heap); }

    void print()
    {
        for (int i = 0; i < heap_size; i++)
        {
            cout << heap[i].tam << "(" << heap[i].origem << ") ";
        }
        cout << endl;
    }
};

struct AdjNode
{
    int vert_adj;
    double custo;
    AdjNode *next;
};

class Grafo
{
private:
    AdjNode **arestas;
    int vertices;

public:
    Grafo(int V) // V: n° de vertices
    {
        arestas = (AdjNode **)malloc(V * sizeof(AdjNode *));
        for (int v = 0; v < V; v++)
        {
            arestas[v] = new AdjNode;
            arestas[v]->next = NULL;
            arestas[v]->vert_adj = (-1);
            arestas[v]->custo = (-1);
        }
        vertices = V;
    }

    void destrutor()
    {
        AdjNode *node_temp;
        for (int v = 0; v < vertices; v++)
        {
            AdjNode *ptr = arestas[v];
            while (ptr != NULL)
            {
                node_temp = ptr;
                ptr = ptr->next;
                delete node_temp;
            }
        }
        free(arestas);
    }

    void add_nodes(int V, int E, double W)
    {
        if (arestas[V]->vert_adj == -1)
        {
            arestas[V]->vert_adj = E;
            arestas[V]->custo = W;
        }
        else
        {
            AdjNode *ptr = arestas[V];
            AdjNode *novo_node = new AdjNode;
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            ptr->next = novo_node;
            ptr->next->vert_adj = E;
            ptr->next->custo = W;
            ptr->next->next = NULL;
        }
    }

    AdjNode *return_adjlist(int i)
    {
        return arestas[i];
    }

    void imprimir()
    {
        for (int c = 0; c < vertices; c++)
        {
            cout << c << ": ";
            AdjNode *ptr = arestas[c];
            while (ptr != NULL)
            {
                cout << ptr->vert_adj << "(" << ptr->custo << ") ";
                ptr = ptr->next;
            }
            cout << endl;
        }
    }
};

struct Dijkstra_return
{
    int *distancias;
    int *precursores;
    int *hops;
};

Dijkstra_return Dijkstra(int size, Grafo G, int partida)
{
    Dijkstra_return retorno;
    int *D = (int *)malloc(size * sizeof(int));
    int *F = (int *)malloc(size * sizeof(int));
    int *Ho = (int *)malloc(size * sizeof(int));

    minHeap H(size);

    for (int i = 0; i < size; i++)
    {
        D[i] = int(1 << 20);
        F[i] = -1;
        Ho[i] = 0;
    }
    D[partida] = 0;
    H.heap_add(0, partida);

    for (int i = 0; i < size; i++)
    {
        heap_return saida_heap = H.heap_extract();
        int u = saida_heap.raiz;

        AdjNode *e = G.return_adjlist(u);

        while (e != NULL)
        {
            int v = e->vert_adj;
            int w = e->custo;

            if (D[u] + w < D[v])
            {
                D[v] = D[u] + w;
                Ho[v] = Ho[u] + 1;
                F[v] = u;
                H.heap_add(D[v], v);
                
            }
            e = e->next;
        }
    }

    retorno.distancias = D;
    retorno.precursores = F;
    retorno.hops = Ho;
    H.heap_destruct();

    return retorno;
}

int main()
{
    int K, N, DR, D, E, B, C, S, T, Z;

    cin >> K;
    for (int k = 0; k < K; k++)
    {
        cin >> N;
        cin >> DR;
        
        Grafo G(N);

        for (int n = 0; n < N; n++) // vertices
        {
            cin >> D;
            for (int d = 0; d < D; d++) // arestas
            {
                cin >> E;
                cin >> B;
                double C = (1 << 20) / B;
                G.add_nodes(n, E, C);
            }
        }

        Dijkstra_return saida = Dijkstra(N, G, DR);
        int* distancias = saida.distancias;
        int* hops = saida.hops;

        cin >> C;
        cout << "caso " << k << ":" << endl;

        for (int c = 0; c < C; c++) // vertices
        {  
            cin >> S;
            cin >> T;
            cin >> Z;

            //tamanho do caminho:
            int HH = hops[S] + hops[T];
            //soma dos custos:
            int SC = distancias[S] + distancias[T];

            int TT = int((SC*Z)/(1<<20));

            cout << HH << " " << TT << endl;
        }
        cout << endl;
        G.destrutor();
        cin.ignore();
        
    }
    return 0;
}
