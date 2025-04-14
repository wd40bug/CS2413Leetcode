#include <stdlib.h>
#include <string.h>
struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

int *preorderTraversal(struct TreeNode *root, int *returnSize) {
  if (root == NULL) {
    *returnSize = 0;
    return NULL;
  }
  int left_size = 0;
  int *left_preorder = preorderTraversal(root->left, &left_size);
  int right_size = 0;
  int *right_preorder = preorderTraversal(root->right, &right_size);
  *returnSize = left_size + right_size + 1;
  int *ret = (int *)malloc(sizeof(int) * *returnSize);
  ret[0] = root->val;
  if (left_size != 0) {
    memcpy(ret + 1, left_preorder, left_size * sizeof(int));
  }
  if (right_size != 0) {
    memcpy(ret + 1 + left_size, right_preorder, right_size * sizeof(int));
  }
  free(left_preorder);
  free(right_preorder);

  return ret;
}

int *inorderTraversal(struct TreeNode *root, int *returnSize) {
  if (root == NULL) {
    *returnSize = 0;
    return NULL;
  }
  int left_size = 0;
  int *left_preorder = inorderTraversal(root->left, &left_size);
  int right_size = 0;
  int *right_preorder = inorderTraversal(root->right, &right_size);
  *returnSize = left_size + right_size + 1;
  int *ret = (int *)malloc(sizeof(int) * *returnSize);
  if (left_size != 0) {
    memcpy(ret, left_preorder, left_size * sizeof(int));
  }
  ret[left_size] = root->val;
  if (right_size != 0) {
    memcpy(ret + 1 + left_size, right_preorder, right_size * sizeof(int));
  }
  free(left_preorder);
  free(right_preorder);

  return ret;
}
