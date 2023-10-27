#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define INF 9999


typedef int** WeightedAdjecencyMatrix;

typedef struct QNode {
    int value;
    struct QNode *next;
} Qnode;

typedef struct Queue {
    struct QNode *head;
    struct QNode *tail;
    int qlen;
} Queue;

struct node* createNode(int);

typedef struct Graph {
    int num_vertices;
    int **edges;
} Graph;

struct Queue* queue_create();
int queue_is_empty(struct Queue *queue);
int queue_peek(struct Queue *queue);
int queue_dequeue(struct Queue* queue);
int queue_enqueue(struct Queue *queue, int newval);
void free_queue(struct Queue *queue);

Graph* graph_create(int num_nodes);
void graph_destroy(Graph *graph);
void graph_print(Graph *graph);
int graph_edge_add(Graph * graph, int from_node, int to_node, int weight);
int graph_edge_has(Graph * graph, int from_node, int to_node);

void dijkstra(Graph* graph, int source);


int bfs(Graph *graph, int source, int needle);

int main()
{
    Graph *g1 = graph_create(5);
    graph_edge_add(g1, 0, 1, 1);
    graph_edge_add(g1, 1, 0, 1);
    graph_edge_add(g1, 0, 2, 4);
    graph_edge_add(g1, 0, 3, 5);
    graph_edge_add(g1, 3, 4, 5);
    graph_edge_add(g1, 2, 3, 2);
    graph_print(g1);

    int source = 1;
    int needle = 4;
    int found = bfs(g1, source, needle);

    if (found)
    {
        printf("Needle %d found starting from vertex %d\n", needle, source);
    }
    else
    {
        printf("Needle %d not found starting from vertex %d\n", needle, source);
    }

    dijkstra(g1, 1);
    graph_destroy(g1);
}

int bfs(Graph *graph, int source, int needle)
{
    // array to keep track of visited vertices
    int *visited = (int *)calloc(graph->num_vertices, sizeof(int));

    // queue for BFS
    Queue *queue = queue_create();

    // mark the source vertex as visited and enqueue it
    visited[source] = 1;
    queue_enqueue(queue, source);

    while (!queue_is_empty(queue))
    {
        // dequeue a vertex from the queue
        int current = queue_dequeue(queue);
        printf("Debug: visited %d\n", current);

        // check if current vertex matches the needle
        if (current == needle)
        {
            printf("Found the needle %d\n", needle);
            free(visited);
            free_queue(queue);
            return 1;
        }

        // visit all adjacent vertices of the current vertex
        for (int i = 0; i < graph->num_vertices; i++)
        {
            if (graph->edges[current][i] && !visited[i])
            {
                visited[i] = 1;
                queue_enqueue(queue, i);
            }
        }
    }

    printf("Needle %d not found\n", needle);
    free(visited);
    free_queue(queue);
    return 0;
}


struct Queue* queue_create()
{
    struct Queue *queue = (struct Queue*)malloc(sizeof(struct Queue));
    if(!queue)
    {
        printf("Memory allocation failed for the queue.\n");
        return NULL;
    }
    queue->head = queue->tail = NULL;
    queue->qlen = 0;
    return queue;

}

int queue_is_empty(struct Queue *queue)
{
    return queue->qlen == 0;
}

int queue_peek(struct Queue *queue)
{
    if (queue_is_empty(queue))
    {
        printf("Queue is empty.\n");
        return -1;
    }
    return queue->head->value;
}

int queue_dequeue(struct Queue* queue)
{
    if (queue_is_empty(queue))
    {
        printf("Queue is empty.\n");
        return -1;
    }

    queue->qlen--;
    int value = queue->head->value;
    struct QNode *temp = queue->head;
    queue->head = temp->next;
    free(temp);
    return value;
}

int queue_enqueue(struct Queue *queue, int newval)
{
    struct QNode *node = (struct QNode*)malloc(sizeof(*node));
    if (!node)
    {
        printf("Memory allocation failed for a new node.\n");
        return -1;
    }
    node -> value = newval;
    node->next = NULL;

    if (queue_is_empty(queue))
    {
        queue->head = queue->tail = node;
    }
    else
    {
        queue->tail->next = node;
        queue->tail = node;
    }
    queue->qlen++;

    return 0;
}

void free_queue(struct Queue *queue)
{
    while (!queue_is_empty(queue))
    {
        queue_dequeue(queue);
    }
    free(queue);
}


Graph* graph_create(int num_vertices)
{
    Graph *graph = malloc(sizeof(*graph));
    if (graph == NULL)
    {
        return NULL;
    }
    graph->num_vertices = num_vertices;

    // allocate matrix
    graph->edges = calloc(sizeof(int*), graph->num_vertices);
    if (graph->edges == NULL)
    {
        free(graph);
        return NULL;
    }

    for (int i = 0; i < graph->num_vertices; i++)
    {
        graph->edges[i] = calloc(sizeof(int), graph->num_vertices);
        if (graph->edges[i] == NULL)
        {
            graph_destroy(graph);
            return NULL;
        }
    }
    return graph;
}

void graph_destroy(Graph *graph)
{
    if (graph->edges == NULL)
    {
        return;
    }

    for (int i = 0; i < graph->num_vertices; i++)
    {
        if (graph->edges[i] != NULL)
        {
            free(graph->edges[i]);
        }
    }
    free(graph->edges);
    free(graph);
}

void graph_print(Graph *graph)
{
    printf("digraph weighted {\n");
    for (int from = 0; from < graph->num_vertices; from++)
    {
        for (int to = 0; to < graph->num_vertices; to++)
        {
            if (graph->edges[from][to] != 0)
            {
                printf("%d -> %d [weight=%i, label=\"%i\"];\n", from, to, graph->edges[from][to], graph->edges[from][to]);
            }
        }
    }
    printf("}\n");
}

int graph_edge_add(Graph * graph, int from_node, int to_node, int weight)
{
    assert(graph != NULL);
    assert(from_node < graph->num_vertices);
    assert(to_node < graph->num_vertices);
    if (graph_edge_has(graph, from_node, to_node))
    {
        return -1;
    }

    graph->edges[from_node][to_node] = weight;
    return 0;
}

int graph_edge_has(Graph *graph, int from_node, int to_node)
{
    assert(graph != NULL);
    assert(from_node < graph->num_vertices);
    assert(to_node < graph->num_vertices);

    return graph->edges[from_node][to_node];
}

void dijkstra(Graph* graph, int source)
{
    int **cost = malloc(graph->num_vertices * sizeof(int*));
    int *distance = malloc(graph->num_vertices * sizeof(int*));
    int *pred = malloc(graph->num_vertices * sizeof(int*));
    int *visited = malloc(graph->num_vertices * sizeof(int*));
    int count, min_dist, next_node;

    for (int i = 0; i < graph->num_vertices; i++)
    {
        cost[i] = malloc(graph->num_vertices * sizeof(int));
    }

    // creating a cost matrix
    for (int i = 0; i < graph->num_vertices; i++)
    {
        for (int j = 0; j < graph->num_vertices; j++)
        {
            if (graph->edges[i][j] == 0)
            {
                cost[i][j] = INF;
            }
            else
            {
                cost[i][j] = graph->edges[i][j];
            }
        }
    }

    for (int i = 0; i < graph->num_vertices; i++)
    {
        distance[i] = cost[source][i];
        pred[i] = source;
        visited[i] = 0;
    }

    distance[source] = 0;
    visited[source] = 1;
    count = 1;

    while (count < graph->num_vertices-1)
    {
        min_dist = INF;

        for (int i = 0; i < graph->num_vertices; i++)
        {
            if(distance[i] < min_dist && !visited[i])
            {
                min_dist = distance[i];
                next_node = i;
            }
        }

        visited[next_node] = 1;
        for (int i = 0; i < graph->num_vertices; i++)
        {
            if (!visited[i])
            {
                if (min_dist + cost[next_node][i] < distance[i])
                {
                    distance[i] = min_dist + cost[next_node][i];
                    pred[i] = next_node;
                }
            }
        }
        count++;
    }
    for (int i = 0; i < graph->num_vertices; i ++)
    {
        if (i != source)
        {
            printf("\nDistance from %d to %d: %d",source, i, distance[i]);
        }
    }
    printf("\n");
}
