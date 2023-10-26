#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int vertex;
    int weight;
    struct Node *next;
} Node;

typedef struct Graph {
    int num_vertices;
    Node **adj_lists;
} Graph;

Node* node_create(int v, int weight)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->vertex = v;
    new_node->weight = weight;
    new_node->next = NULL;

    return new_node;
}

Graph* graph_create(int num_vertices)
{
    Graph* graph = malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adj_lists = malloc(num_vertices * sizeof(Node*));

    for(int i = 0; i < num_vertices; i++)
    {
        graph->adj_lists[i] = NULL;
    }
    return graph;
}

Graph* graph_free(Graph* graph)
{
    for (int i=0; i<graph->num_vertices; i++)
    {
        Node *curr = graph->adj_lists[i];
        while (curr != NULL)
        {
            Node *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(graph->adj_lists);
    free(graph);
}

void edge_add(Graph* graph, int src, int dst, int w)
{
    Node *new_node = node_create(dst, w);
    new_node->next = graph->adj_lists[src];
    graph->adj_lists[src] = new_node;
}

void graph_print(Graph* graph)
{
    if (graph->num_vertices <= 0)
    {
        return;
    }

    for(int i=0; i<graph->num_vertices; i++)
    {
        Node *curr = graph->adj_lists[i];
        if (curr == NULL)
            continue;

        printf("Adjacency list of vertex %d: ", i);
        while(curr != NULL)
        {
            printf("(%d, %d) -> ", curr->vertex, curr->weight);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

int dfs_recursive(Graph* graph, int curr, int needle, int* seen)
{
    if (curr == needle)
    {
        return 1;
    }

    if (seen[curr])
    {
        return 0;
    }

    //pre
    seen[curr] = 1;
    //recurse
    Node *node = graph->adj_lists[curr];
    while (node != NULL)
    {
        int next = node->vertex;
        if (!seen[next])
        {
            if (dfs_recursive(graph, next, needle, seen))
            {
                return 1;
            }
        }
    }

    //post
    seen[curr] = 0;
    return 0;
}

int dfs(Graph *graph, int start, int needle) 
{
    int *seen = (int*)malloc(graph->num_vertices * sizeof(int));
    for (int i = 0; i < graph->num_vertices; i++)
    {
        seen[i] = 0;
    }

    int result = dfs_recursive(graph, start, needle, seen);

    return result;
}

int main()
{
    Graph *graph = graph_create(5);
    edge_add(graph, 0, 1, 1);
    edge_add(graph, 1, 0, 1);
    edge_add(graph, 0, 2, 4);
    edge_add(graph, 0, 3, 5);
    edge_add(graph, 3, 4, 5);
    edge_add(graph, 2, 3, 2);

    graph_print(graph);

    int res_1 = dfs(graph, 0, 4);
    int res_2 = dfs(graph, 4, 0);
    printf("TEST searching for vertice 4 starting from node 0. Expecting Found, result: %s\n", (res_1 == 1) ? "Found" : "Not found");
    printf("TEST searching for vertice 0 starting from node 4. Expecting Not Found, result: %s\n", (res_2 == 1) ? "Found" : "Not found");
    graph_free(graph);

    return 0;
}

