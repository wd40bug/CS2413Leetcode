#include <stdlib.h>
struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode *removeElements(struct ListNode *head, int val) {
  struct ListNode *elem = head;
  struct ListNode *prev = NULL;
  while (elem != NULL) {
    struct ListNode *next = elem->next;
    if (elem->val == val && prev == NULL) {
      head = elem->next;
      elem = NULL;
    } else if (elem->val == val) {
      prev->next = elem->next;
      elem = prev;
    }
    prev = elem;
    elem = next;
  }
  return head;
}

struct ListNode *reverseList(struct ListNode *head) {
  struct ListNode *prev = NULL;
  struct ListNode *elem = head;
  while (elem != NULL) {
    struct ListNode *next = elem->next;
    elem->next = prev;

    prev = elem;
    elem = next;
  }
  return prev;
}
