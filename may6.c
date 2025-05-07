/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


bool isMirror(struct TreeNode* left, struct TreeNode* right){
    if (left == NULL && right == NULL){
        return true;
    }else if (left == NULL && right != NULL || left != NULL && right == NULL){
        return false;
    }else if (left->val != right->val){
        return false;
    }
    // Both nodes aren't NULL and have equal values
    return isMirror(left->left, right->right) && isMirror(left->right, right->left);
}

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL){
        return true;
    }
    return isMirror(root->left, root->right);
}

int numIslands(char** grid, int gridSize, int* gridColSizes) {
    int gridColSize = gridColSizes[0];
    bool* visited = (bool*)calloc(gridSize * gridColSize, sizeof(bool));
    int island_count = 0;
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridColSize; j++){
            int index = i * gridColSize + j;
            if (visited[index] == false){
                visited[index] == true;
                if (grid[i][j] == '1'){

                    island_count++;
                    int* queue = (int*)calloc(gridSize * gridColSize * 2, sizeof(int));
                    int front = 0;
                    int len = 0;
                    queue[0] = index;
                    len++;
                    while (len > 0){
                        int square = queue[front];
                        front++;
                        len--;
                        int x = square % gridColSize;
                        int y = square / gridColSize;

                        if (visited[square] == true){
                            continue;
                        }
                        visited[square] = true;
                        if (grid[y][x] == '0'){
                            continue;
                        }
                        if (y < gridSize  - 1){
                            int index = square + gridColSize;
                            if (visited[index] == false){
                                queue[front + len] = index;
                                len++;
                            }
                        }
                        if (y > 0){
                            int index = square - gridColSize;
                            if (visited[index] == false){
                                queue[front + len] = index;
                                len++;
                            }
                        }
                        if (x < gridColSize - 1) {
                            
                            int index = square + 1;
                            if (visited[index] == false){
                                queue[front + len] = index;
                                len++;
                            }
                        }
                        if (x > 0) {
                            int index = square - 1;
                            if (visited[index] == false){
                                queue[front + len] = index;
                                len++;
                            }
                        }
                    }
                    free(queue);
                }
            }
        }
    }
    free(visited);
    return island_count;
}
