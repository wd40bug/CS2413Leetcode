#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
  struct Node *next;
  int data;
} Node;

typedef struct Stack {
  Node *top;
} Stack;

void push(Stack *stack, int data) {
  Node *new = (Node *)malloc(sizeof(Node));
  new->data = data;
  new->next = stack->top;
  stack->top = new;
}

int pop(Stack *stack) {
  assert(stack->top !=
         NULL); // Just error if empty stack. Not a production ready solution
  Node *n = stack->top;
  stack->top = stack->top->next;
  int ret = n->data;
  free(n);
  return ret;
}

typedef struct {
  Stack *stack_in;
  Stack *stack_out;
} MyQueue;

MyQueue *myQueueCreate() {
  MyQueue *queue = (MyQueue *)malloc(sizeof(MyQueue));
  queue->stack_in = (Stack *)malloc(sizeof(Stack));
  queue->stack_in->top = NULL;
  queue->stack_out = (Stack *)malloc(sizeof(Stack));
  queue->stack_out->top = NULL;
  return queue;
}

void myQueuePush(MyQueue *obj, int x) { push(obj->stack_in, x); }

int myQueuePop(MyQueue *obj) {
  if (obj->stack_out->top == NULL) {
    while (obj->stack_in->top != NULL) {
      push(obj->stack_out, pop(obj->stack_in));
    }
  }

  return pop(obj->stack_out); // This will error if queue empty
}

bool myQueueEmpty(MyQueue *obj) {
  return obj->stack_out->top == NULL && obj->stack_in->top == NULL;
}

int myQueuePeek(MyQueue *obj) {
  if (obj->stack_out->top == NULL) {
    while (obj->stack_in->top != NULL) {
      push(obj->stack_out, pop(obj->stack_in));
    }
  }

  assert(!myQueueEmpty(obj));
  return obj->stack_out->top->data;
}

void myQueueFree(MyQueue *obj) {
  while (!myQueueEmpty(obj)) {
    myQueuePop(obj);
  }
  free(obj->stack_in);
  free(obj->stack_out);
  free(obj);
}
