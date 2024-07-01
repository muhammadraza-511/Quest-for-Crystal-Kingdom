#include <iostream>
#include<queue>
#include <cstdlib>
#include <ctime>
#include<algorithm>
using namespace std;
const int ROWS = 20, COLS = 20;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                               //           Global functions for Avl tree implementation

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
struct Node {
    int ID;
    Node* left;
    Node* right;
    int height;
    int count;
    int reward_score;
    char ch;
};

// Function to get the height of a node
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int getBalanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to update the height of a node
void updateHeight(Node* node) {
    if (node == nullptr)
        return;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

// Function to perform a right rotation
Node* rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Function to perform a left rotation
Node* rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Function to balance the AVL tree
Node* balance(Node* node) {
    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);

    // Left-Left case
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);

    // Right-Right case
    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);

    // Left-Right case
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right-Left case
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Function to create a new node
Node* createNode(int ID, int reward_score, char ch) {
    Node* newNode = new Node;
    newNode->ID = ID;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    newNode->count = 1;
    newNode->reward_score = reward_score;
    newNode->ch = ch;
    return newNode;
}

// Function to insert a node into the AVL tree
Node* insert(Node* root, int ID, int reward_score, char ch) {
    if (root == nullptr)
        return createNode(ID, reward_score, ch);

    if (ID < root->ID)
        root->left = insert(root->left, ID, reward_score, ch);
    else if (ID > root->ID)
        root->right = insert(root->right, ID, reward_score, ch);
    else {
        // Duplicate ID found, increment count
        root->count++;
        return root;
    }

    // Update the height of the current node
    updateHeight(root);

    // Balance the tree
    root = balance(root);

    return root;
}
// Function to generate a random item score
int generateRandomScore() {
    return std::rand() % 101; // Generates a random score from 0 to 100
}

// Function to generate a random character ('A', 'C', or 'D')
char generateRandomChar() {
    char chars[] = { 'A', 'C', 'D' };
    int randomIndex = std::rand() % 3; // Generates a random index from 0 to 2
    return chars[randomIndex];
}

// Function to display the inventory (inorder traversal of the AVL tree)
int total_score = 0;
void displayInventory(Node* root) {
    if (root == nullptr)
        return;

    displayInventory(root->left);
    cout << "ID: " << root->ID << ", Score: " << root->reward_score << "\n";
    total_score = total_score + root->reward_score;
    displayInventory(root->right);
}

// Function to search for a node with a specific ID
Node* search(Node* root, int ID) {
    if (root == nullptr || root->ID == ID)
        return root;

    if (ID < root->ID)
        return search(root->left, ID);
    else
        return search(root->right, ID);
}

// Function to get the minimum node (successor) in the subtree
Node* getSuccessor(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Function to remove a node with a specific ID from the AVL tree
Node* remove(Node* root, int ID) {
    if (root == nullptr)
        return root;

    if (ID < root->ID)
        root->left = remove(root->left, ID);
    else if (ID > root->ID)
        root->right = remove(root->right, ID);
    else {
        if (root->count > 1) {
            // If the node has more than one instance, decrement count
            root->count--;
            return root;
        }
        else {
            // If the node has only one instance, perform removal

            // Node with no child or only one child
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children
            Node* successor = getSuccessor(root->right);
            root->ID = successor->ID;
            root->reward_score = successor->reward_score;
            root->ch = successor->ch;
            root->count = successor->count;
            root->right = remove(root->right, successor->ID);
        }
    }

    // Update the height and balance the tree
    updateHeight(root);
    root = balance(root);

    return root;
}

// Function to delete an AVL tree (free memory)
void deleteAVLTree(Node* root) {
    if (root == nullptr)
        return;

    deleteAVLTree(root->left);
    deleteAVLTree(root->right);
    delete root;
}

//  


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                               //             GRAPH CLASS              //

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Graph {
public:
    char element;
    int first_index, second_index;
    int weights;
    Graph* left, * right, * upper, * down;
    Graph()
    {
        left = nullptr;
        right = nullptr;
        upper = nullptr;
        down = nullptr;
        element = '\0';
        first_index = 0;
        second_index = 0;
        weights = 1;
    }

    void union_(int* old, int Parent_of_starting_value, int Parent_of_destination_value)
    {
        old[Parent_of_destination_value] = Parent_of_starting_value;
    }
    // edge=size

    struct side {
        int src, dest, weight;
        side(int s, int d, int w)
        {
            src = s;
            dest = d;
            weight = w;
        }
    };

    //function to find the
    int dhundo(int* old, int vertex)
    {
        if (old[vertex] != vertex)
        {
            old[vertex] = dhundo(old, old[vertex]);
        }
        return old[vertex];
    }
    // comparing the weights of edges
    struct Compare {
        bool operator()(const side& EDGE_A, const side& EDGE_B)
        {
            return EDGE_A.weight > EDGE_B.weight;
        }
    };


 


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                 //            Kruskal Algorithm            //

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // kruskal function to find spanning tree
    // parameters are adjacency matrix and total size
    void kruskal(int** adj_list, int n)
    {
        // queue to store edge sorted by weight
        priority_queue<side, vector<side>, Compare>queu;


        // adding all the sides to the priority queue
        // basically pushing whole object to the queue
        for (int a = 0; a < n; a++)
        {
            for (int b = a + 1; b < n; b++)
            {
                if(adj_list[a][b] != 0)
                {
                    side e(a, b, adj_list[a][b]);
                    queu.push(e);
                }
            }
        }

        // array to store parent of vertexes
        int* father = new int[n];
        for (int z = 0; z < n; z++)
        {
            father[z] = z;
        }
        // main array to store minimum spanning tree
        int** Kruskal_MST = new int* [n];
        for (int a = 0; a < n; a++)
        {
            Kruskal_MST[a] = new int[n];
            for (int b = 0; b < n; b++)
            {
                Kruskal_MST[a][b] = 0;
            }
        }

        int Number_of_edges = 0;
        while (!queu.empty() && Number_of_edges < n - 1)
        {
            side e = queu.top();
            queu.pop();
            int src_p = dhundo(father, e.src);
            int dest_p = dhundo(father, e.dest);

            // checking the repetition 
            // if this edge cause cycle or nor
            if (src_p != dest_p)
            {
                Kruskal_MST[e.src][e.dest] = e.weight;
                Kruskal_MST[e.dest][e.src] = e.weight;
                Number_of_edges++;

                union_(father, src_p, dest_p);
            }


        }

        // printing the minimum spanning tree
        cout << "Kruskal's Minimum spanning tree :" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (Kruskal_MST[i][j] != 0)
                {
                    cout << i << " - " << j << ": " << Kruskal_MST[i][j] << endl; 
                }
            }
        }
    }



    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                               //            Prims Algorithm              //

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // prims algorithm function for spanning tree
    void prims(int** adj_list, int n)
    {
        int* father = new int[n]; // to store tree
        int* key = new int[n];   
        bool* in_mst = new bool[n];

        // initializing all the arrays with false values
        for (int i = 0; i < n; i++)  
        {
            father[i] = -1;
            // assigning initially infinity to the whole array
            key[i] = INT_MAX;
            in_mst[i] = false;
        }


        // some built in things which i can't understand
        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> queu(cmp);

        int s = 0;
        key[s] = 0;
        queu.push({ s,0 });
        while (!queu.empty())
        {
            int u = queu.top().first;
            queu.pop();
            in_mst[u] = true;

            // update key values and add adjacent vertices to the priority queue
            for (int i = 0; i < n; i++)
            {
                if (adj_list[u][i] && !in_mst[i] && adj_list[u][i] < key[i])
                {
                    father[i] = u;
                    key[i] = adj_list[u][i];
                    queu.push({ i,key[i] });
                }
            }
        }

        cout << endl << "PRIM'S MINIMUM SPANNING TREE :" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << father[i] << " - " << i << " : " << adj_list[i][father[i]] << endl;
        }
    }

};










/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                               //             floyd's shortest path function (ALGORITHM)              //

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//  function to calculate shortest path with floyds algorithm

void calculateShortestPath_Floyd(int **adjMatrix)
{
    int row_address = 0;
    int col_address = 0;

    for (int k = 0; k < ROWS * COLS; k++)
    {
        for (int i = 0; i < ROWS * COLS; i++)
        {
            for (int j = 0; j < ROWS * COLS; j++)
            {

                if (adjMatrix[i][k] != numeric_limits<int>::max() && adjMatrix[k][j] != numeric_limits<int>::max() && adjMatrix[i][j] > adjMatrix[i][k] + adjMatrix[k][j])
                {
                    adjMatrix[i][j] = adjMatrix[i][k] + adjMatrix[k][j];
                }
            }
        }
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                               //             Dijkstra shortest algorithm             //

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// function to calculate shortest path with Dijkstra
int Dijkstra(Graph** graph, int ver1, int ver2, int x, int y, int check[][2]) {
    int press, temp1, temp2;
    int distance[ROWS][COLS];

    bool visit[ROWS][COLS];
    for (int i = 0; i < ROWS; i++)
    {

        for (int j = 0; j < COLS; j++)
        {
            distance[i][j] = INT_MAX;
            visit[i][j] = false;
        }

    }
    for (int i = 0; i < ROWS * COLS; i++)
    {
        check[i][0] = -1;
        check[i][1] = -1;
    }
    do
    {
        cout << "Press 1 to start from default location\nPress 2 to start from custom location\n";
        cin >> press;
    } while (press < 1 || press>2);

    if (press == 2)
    {
        do
        {
            cout << "Enter cordinates x: ";
            cin >> temp1;
        } while (temp1 < 0 || temp1>20);
        do
        {
            cout << "Enter cordinates y: ";
            cin >> temp2;
        } while (temp2 < 0 || temp2>20);
        ver1 = temp1;
        ver2 = temp2;
    }
    //source vertices
    distance[ver1][ver2] = 0;
    int index[ROWS][COLS];

    //Main loop
    for (int count = 0; count < ROWS * COLS - 1; count++)
    {
        int min_dis = INT_MAX;
        int u_x = -1, u_y = -1;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++) {
                if (!visit[i][j] && distance[i][j] < min_dis) {
                    min_dis = distance[i][j];
                    u_x = i;
                    u_y = j;
                    check[count][0] = u_x;
                    check[count][1] = u_y;
                }
            }
        }
        if (u_x == x && u_y == y)
        {

            return distance[x][y];
        }

        visit[u_x][u_y] = true;

        Graph* output;

        output = graph[u_x * COLS + u_y];

        if (output->upper && !visit[output->upper->first_index][output->upper->second_index] && distance[u_x][u_y] + output->upper->weights < distance[output->upper->first_index][output->upper->second_index])
        {
            distance[output->upper->first_index][output->upper->second_index] = distance[u_x][u_y] + output->upper->weights;

        }
        if (output->down && !visit[output->down->first_index][output->down->second_index] && distance[u_x][u_y] + output->down->weights < distance[output->down->first_index][output->down->second_index])
        {
            distance[output->down->first_index][output->down->second_index] = distance[u_x][u_y] + output->down->weights;

        }
        if (output->left && !visit[output->left->first_index][output->left->second_index] && distance[u_x][u_y] + output->left->weights < distance[output->left->first_index][output->left->second_index])
        {
            distance[output->left->first_index][output->left->second_index] = distance[u_x][u_y] + output->left->weights;

        }

        if (output->right && !visit[output->right->first_index][output->right->second_index] && distance[u_x][u_y] + output->right->weights < distance[output->right->first_index][output->right->second_index])
        {
            distance[output->right->first_index][output->right->second_index] = distance[u_x][u_y] + output->right->weights;

        }


    }

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                               //             Converting graph to adjacent matrix            //

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  //Function to print the adjacency matrix
void char_to_AdjacencyMatrix(Graph* map[ROWS][COLS],int** adjMatrix,int n)
{
    

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            Graph* current = map[i][j];
            int currentIdx = i * COLS + j;
            if (current->upper)
            {
                int upIdx = (i - 1) * COLS + j;
                if (current->upper->element == '#')
                {
                    adjMatrix[currentIdx][upIdx] = 100;
                }
                else
                {
                    adjMatrix[currentIdx][upIdx] = 1;
                }
            }
            if (current->down)
            {
                int downIdx = (i + 1) * COLS + j;
                if (current->down->element == '#')
                {
                    adjMatrix[currentIdx][downIdx] = 100;
                }
                else
                {
                    adjMatrix[currentIdx][downIdx] = 1;
                }
            }
            if (current->left)
            {
                int leftIdx = i * COLS + (j - 1);
                if (current->left->element == '#')
                {
                    adjMatrix[currentIdx][leftIdx] = 100;
                }
                else
                {
                    adjMatrix[currentIdx][leftIdx] = 1;
                }
            }
            if (current->right)
            {
                int rightIdx = i * COLS + (j + 1);
                if (current->right->element == '#')
                {
                    adjMatrix[currentIdx][rightIdx] = 100;
                }
                else
                {
                    adjMatrix[currentIdx][rightIdx] = 1;
                }
            }
        }
    }
 
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                               //             converting character arrray of graph to linked list 
                               //             used in Dijkstra  

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// finction to convert charcter array to linked list  
void converting_chararray_to_linkedlist(Graph* graph[ROWS][COLS],char map[ROWS][COLS])
{
    // loops for making nodes of adacency list and then assigning them the value
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            graph[i][j] = new Graph;
            graph[i][j]->element = map[i][j];
            graph[i][j]->first_index = i;
            graph[i][j]->second_index = j;

        }
    }

    // lops for attaching the nodes of linked list
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // conditions for the edges
            if (i == 0 && j == 0)
            {
                graph[i][j]->right = graph[i][j + 1];
                graph[i][j]->down = graph[i + 1][j];
            }
            else if (i == 0 && j == COLS - 1)
            {
                graph[i][j]->down = graph[i + 1][j];
                graph[i][j]->left = graph[i][j - 1];
            }
            else if (i == ROWS - 1 && j == 0)
            {
                graph[i][j]->upper = graph[i - 1][j];
                graph[i][j]->right = graph[i][j + 1];
            }
            else if (i == ROWS - 1 && j == COLS - 1)
            {
                graph[i][j]->upper = graph[i - 1][j];
                graph[i][j]->left = graph[i][j - 1];
            }

            // conditions for the rows and columns with the edges

            else if (j == COLS - 1)
            {
                graph[i][j]->down = graph[i + 1][j];
                graph[i][j]->upper = graph[i - 1][j];
                graph[i][j]->left = graph[i][j - 1];

            }
            else if (i == ROWS - 1)
            {
                graph[i][j]->upper = graph[i - 1][j];
                graph[i][j]->left = graph[i][j - 1];
                graph[i][j]->right = graph[i][j + 1];
            }
            else if (j == 0)
            {
                graph[i][j]->upper = graph[i - 1][j];
                graph[i][j]->down = graph[i + 1][j];
                graph[i][j]->right = graph[i][j + 1];
            }
            else if (i == 0)
            {
                graph[i][j]->left = graph[i][j - 1];
                graph[i][j]->down = graph[i + 1][j];
                graph[i][j]->right = graph[i][j + 1];
            }
            // condition for all other points
            else {
                graph[i][j]->right = graph[i][j + 1];
                graph[i][j]->left = graph[i][j - 1];
                graph[i][j]->down = graph[i + 1][j];
                graph[i][j]->upper = graph[i - 1][j];

            }
        }

    }


    // assigning weights to the nodes of lists
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (graph[i][j]->right != nullptr && graph[i][j]->right->element == '#')
            {
                graph[i][j]->right->weights = 100;
            }
            if (graph[i][j]->left != nullptr && graph[i][j]->left->element == '#')
            {
                graph[i][j]->left->weights = 100;
            }
            if (graph[i][j]->down != nullptr && graph[i][j]->down->element == '#')
            {
                graph[i][j]->down->weights = 100;
            }
            if (graph[i][j]->upper != nullptr && graph[i][j]->upper->element == '#')
            {
                graph[i][j]->upper->weights = 100;
            }



        }
    }

}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                               //            assigning_path_of_graph_to_array 

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// function store the path covered by the algorithm in an character array
void assigning_path_of_graph_to_array(Graph* graph[ROWS][COLS], char* array,int check[ROWS*COLS][2])
{

    int c = 0;
    int z = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (check[i][0] != -1)
            {
                if (i == check[i][0] || j == check[i][1])
                {

                    array[c] = graph[i][j]->element;
                    c++;


                }
            }
            else {
                z = -1;
                break;

            }

        }
        if (z == -1)
        {
            break;
        }

    }
    array[c] = '\0';
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                               //            Main function

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main() {




    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                   //           Generating Random map

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    srand(time(nullptr)); // seed the random number generator with the current time

    char map[ROWS][COLS]; // create a 2D character array to store the map data

     //Initialize the matrix
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            map[i][j] = 'C';
        }
    }

    // Add the crystal to a random location in the matrix
    int crystal_x = rand() % ROWS, crystal_y = rand() % COLS;
    map[crystal_x][crystal_y] = '*';

    // Add 25 rewards to random locations in the matrix
    char rewards[] = { 'J', 'P', 'W' };
    for (int i = 0; i < 60; i++) {
        int reward_x = rand() % ROWS, reward_y = rand() % COLS;
        while (map[reward_x][reward_y] != 'C') {
            reward_x = rand() % ROWS;
            reward_y = rand() % COLS;
        }
        map[reward_x][reward_y] = rewards[rand() % 3];
    }

    // Add 15 death points to random locations in the matrix
    for (int i = 0; i < 15; i++) {
        int death_x = rand() % ROWS, death_y = rand() % COLS;
        while (map[death_x][death_y] != 'C') {
            death_x = rand() % ROWS;
            death_y = rand() % COLS;
        }
        map[death_x][death_y] = '%';
    }

    // Add 50 obstacles to random locations in the matrix
    for (int i = 0; i < 35; i++) {
        int obstacle_x = rand() % ROWS, obstacle_y = rand() % COLS;
        while (map[obstacle_x][obstacle_y] != 'C') {
            obstacle_x = rand() % ROWS;
            obstacle_y = rand() % COLS;
        }
        map[obstacle_x][obstacle_y] = '#';
    }
    for (int i = 0; i < 14; i++) {
        int obstacle_x = rand() % ROWS, obstacle_y = rand() % COLS;
        while (map[obstacle_x][obstacle_y] != 'C') {
            obstacle_x = rand() % ROWS;
            obstacle_y = rand() % COLS;
        }
        map[obstacle_x][obstacle_y] = '&';
    }
    for (int i = 0; i < 18; i++) {
        int obstacle_x = rand() % ROWS, obstacle_y = rand() % COLS;
        while (map[obstacle_x][obstacle_y] != 'C') {
            obstacle_x = rand() % ROWS;
            obstacle_y = rand() % COLS;
        }
        map[obstacle_x][obstacle_y] = '$';
    }
    for (int i = 0; i < 10; i++) {
        int obstacle_x = rand() % ROWS, obstacle_y = rand() % COLS;
        while (map[obstacle_x][obstacle_y] != 'C') {
            obstacle_x = rand() % ROWS;
            obstacle_y = rand() % COLS;
        }
        map[obstacle_x][obstacle_y] = '@';
    }


    

    // converint 2d array to linked list 
    // call to a function
    Graph* graph[ROWS][COLS];
    converting_chararray_to_linkedlist(graph, map);
   
    

    // making and initializing adjacency list to zero
    int n = ROWS * COLS;
    int** adjMatrix = new int* [ROWS * COLS];
    for (int i = 0; i < ROWS * COLS; i++)
    {
        adjMatrix[i] = new int[ROWS * COLS];
    }
    for (int i = 0; i < ROWS * COLS; i++)
    {
        for (int j = 0; j < ROWS * COLS; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }
    // converting linked list to adjacency matrix
    // call to function
        char_to_AdjacencyMatrix(graph, adjMatrix,n);


        // working for calculating the position of crystal for floyd's algorithm
        int src = 0;
        int desti = 0;
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (graph[i][j]->element == '*')
                {
                    cout << "Address of Crystal is: " << "[" << graph[i][j]->first_index << "]" << "[" << graph[i][j]->second_index << "]" << endl;
                    src = graph[i][j]->first_index;
                    desti = graph[i][j]->second_index;
                    break;
                }
            }
        }

       // int adjMatr[ROWS * COLS][ROWS * COLS]; 
        int** adjMatr = new int* [ROWS * COLS];
        for (int i = 0; i < ROWS * COLS; i++)
        {
            adjMatr[i] = new int[ROWS * COLS];
        }

        // initialize adjacency matrix with given data
        for (int i = 0; i < ROWS * COLS; i++)
        {
            for (int j = 0; j < ROWS * COLS; j++)
            {
                if (i == j)
                {
                    adjMatr[i][j] = 0;
                }
                else if (abs(i - j) == 1 || abs(i - j) == ROWS)
                {
                    adjMatr[i][j] = 1;
                }
                else
                {
                    adjMatr[i][j] = numeric_limits<int>::max();
                }
            }
        }

        //calculate shortest paths and shortest spanning tree
        calculateShortestPath_Floyd(adjMatr);
        //shortestspanningtree(adjMatrix);

        
        // find shortest path from default location to specific location

        Graph kela;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                cout << graph[i][j]->element<<" ";
            }
            cout << endl;
        }




        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                       //           commented work of avl tree 
                                        //          and try to calculate score

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        char* array = new char[ROWS];

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                   //          Dispalying the menu

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        int decision;
        cout << "\nPress 1 for floyd's shortest algorithm :" << endl;
        cout << "Press 2 for kruskal's spanning tree :" << endl;
        cout << "Press 3 for Prim's spanning tree :" << endl;
        cout << "Press 4 for dijkstra's algorithm :" << endl;
        cin >> decision;

        if (decision == 1)
        {

            int source_row = 0;
            int source_col = 0;
            int source = 0;

            cout << "Press 1 for Finding Shortest Path from default location(0,0): " << endl;
            cout << "Press 2 for any custom location to Crytsal Destination : " << endl;
            cin >> decision;

            if (decision == 1)
            {
                source_row = 0;
                source_col = 0;
                source = source_row * COLS + source_col;
            }
            if (decision == 2)
            {
                cout << "Enter Source Location for Rows:";
                cin >> source_row;
                cout << "Enter Source Location for Cols:";
                cin >> source_col;
                source = source_row * COLS + source_col;
            }

            int dest_row = src;
            int dest_col = desti;
            int destination = dest_row * COLS + dest_col;
            int shortestPath = adjMatr[source][destination];

            cout << "Shortest path from (" << source_row << "," << source_col << ") to (" << dest_row << "," << dest_col << ") is: " << shortestPath << endl;
        }
        else if (decision == 2)
        {
            kela.kruskal(adjMatrix, n);
        }
        else  if (decision == 3)
        {
            kela.prims(adjMatrix, n);
        }
        else if (decision == 4)
        {
             int check[ROWS * COLS][2];

             int path = Dijkstra(graph[0], 0, 0, crystal_x, crystal_y, check);
             assigning_path_of_graph_to_array(graph, array, check);

             Node* root = nullptr;
                
                 // Set the seed for random number generation
                 srand(time(nullptr));
                 int j = 0;
                 while (array[j] != '\0')
                 {
                     cout << array[j] << " ";
                     j++;
                 }
                 cout << endl;
                 // Generate the first ID as 100
                 int firstID = 100;
                int i = 0; int score = 0;

                 if (array[i] != '%')
                 {

                     if (array[i] == 'J')
                     {
                         score = 50;
                     }
                     else if (array[i]=='C')
                     {
                         score = 0;
                     }
                     else if (array[i] == 'W')
                     {
                         score = 30;
                     }
                     else if (array[i] == 'P')
                     {
                         score = 70;
                     }
                     else if (array[i] == '@')
                     {
                         score = -30;
                     }
                     else if (array[i] == '&')
                     {
                         score = -50;
                     }
                     else if (array[i] == '$')
                     {
                         score = -70;
                     }
                     // Insert the first node with ID 100
                     root = insert(root, firstID, score, array[i]);

                     i++;
                     // Generate and insert the remaining nodes
                     while (array[i] != '\0')
                     {
                         int randomID = rand() % 201; // Generate random ID from 0 to 200
                         if (array[i] != '%')
                         {

                             if (array[i] == 'C')
                             {
                                 score = 0;
                             }
                             else if (array[i] == '#')
                             {
                                 score = 0;
                             }
                             else if (array[i] == 'J')
                             {
                                 score = 50;
                             }
                             else if (array[i] == 'W')
                             {
                                 score = 30;
                             }

                             else if (array[i] == 'P')
                             {
                                 score = 70;
                             }
                             else if (array[i] == '@')
                             {
                                 score = -30;
                             }
                             else if (array[i] == '&')
                             {
                                 score = -50;
                             }
                             else if (array[i] == '$')
                             {
                                 score = -70;
                             }

                             root = insert(root, randomID, score, array[i]);
                             i++;
                         }
                         else
                         {
                             cout << " DEATH " << endl;
                             array[i] = '\0';
                             array[++i] = '\0';
                             break;

                         }

                     }



                 }
                 else
                 {
                     cout << " DEATH " << endl;

                     array[i] = '\0';
                     array[++i] = '\0';
                 }
                 // Perform operations on the AVL tree

             // Display the inventory
                cout << "Player's Inventory:\n";
                 displayInventory(root);
                 cout << "TOTAL SCORE :" << total_score << endl;
                cout << "\n";

                 // Search for a specific item
                 int searchID = 150;
                 Node* searchNode = search(root, searchID);
                 if (searchNode) {
                     cout << "Item with ID " << searchID << " found. Score: " << searchNode->reward_score << "\n";
                 }
                 else {
                     cout << "Item with ID " << searchID << " not found.\n";
                 }


            cout << "Location of crystal in the map : "<< crystal_x<<" "<< crystal_y << endl<<endl;
            cout << "Shoetest Path to reach crystal : " << path << endl;

        }



    return 0;
}






