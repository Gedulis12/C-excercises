#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAZE_ROWS 20
#define MAZE_COLS 20

const int dir[][2] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
};

typedef struct {
    int x;
    int y;
} Point;

bool walk(char maze[MAZE_ROWS][MAZE_COLS], char wall, Point curr, Point end, bool seen[MAZE_ROWS][MAZE_COLS], Point path[], int maze_rows, int maze_cols, int step);

int main()
{
    int maze_rows = MAZE_ROWS;
    int maze_cols = MAZE_COLS;

    char maze[MAZE_ROWS][MAZE_COLS] = {
"####################",
"#S              #  #",
"#  ## #  ### ### # #",
"#       #  #   #   #",
"### # ###  ### # ###",
"#     #    #   #   #",
"# ### #  # ### # # #",
"#   # #  #     #   #",
"# ### #### ### ### #",
"#     #    #       #",
"### ### ## ### #####",
"#   #   # #    #   #",
"# ### # # ### ## # #",
"#     # #   #  #   #",
"# ### ##### ## # ###",
"# #   #      # #   #",
"# # ### ## ### ### #",
"# #     #  #       #",
"#                  #",
"##################E#"
};


    bool seen[MAZE_ROWS][MAZE_COLS] = {false, false};

    Point start = {1, 1};
    Point end = {18, 19};
    Point path[maze_rows * maze_cols];

    for (int i = 0; i < maze_rows * maze_cols; i++) 
    {
        path[i].x = -1;  // Initialize the path array
        path[i].y = -1;
    }

    if (walk(maze, '#', start, end, seen, path, maze_rows, maze_cols, 0))
    {
        printf("Path found: \n");
        int i = 0;
        while (path[i].x != end.x || path[i].y != end.y)
        {
            printf("(%d, %d) -> ", path[i].x, path[i].y);
            i++;
        }
        printf("(%d, %d)\n", end.x, end.y);
    }
    else {
        printf("No path found.\n");
    }

    return 0;
}


bool walk(char maze[MAZE_ROWS][MAZE_COLS], char wall, Point curr, Point end, bool seen[MAZE_ROWS][MAZE_COLS], Point path[], int maze_rows, int maze_cols, int step)
{
    //printf("Current position: (%d, %d), Step: %d\n", curr.x, curr.y, step);
    // 1. Base case - off the map
    if (curr.x < 0 || curr.x >= maze_cols ||
        curr.y < 0 || curr.y >= maze_rows)
    {
        //printf("DEBUG: off the map\n");
        return false;
    }

    // 2. on a wall
    if (maze[curr.y][curr.x] == wall)
    {
        //printf("DEBUG: on a wall\n");
        return false;
    }

    // 3. at the end
    if (curr.x == end.x && curr.y == end.y)
    {
        //printf("DEBUG: found the end!\n");
        path[step] = end;
        return true;
    }

    // 4. seen
    if (seen[curr.y][curr.x])
    {
        //printf("DEBUG: already seen\n");
        return false;
    }

    // pre
    path[step] = curr;
    seen[curr.y][curr.x] = true;

    // recurse
    for (int i = 0; i < 4; i++)
    {
        int x = dir[i][0];
        int y = dir[i][1];
        if (walk(maze, wall, (Point){curr.x + x, curr.y + y}, end, seen, path, maze_rows, maze_cols, step + 1))
        {
            return true;
        }
    }

    // post
    path[step].x = -1;
    path[step].y = -1;
    seen[curr.y][curr.x] = false;

    //printf("Backtrack from: (%d, %d), Step: %d\n", curr.x, curr.y, step);

    return false;

}

