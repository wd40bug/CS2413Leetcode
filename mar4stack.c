#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  unsigned int max_len;
  unsigned int length;
  unsigned int front;
  int *data;
} Queue;

Queue *new_queue(unsigned int max_len) {
  assert(max_len != 0);
  int *data = (int *)malloc(sizeof(int) * max_len);
  assert(data != NULL);
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  queue->max_len = max_len;
  queue->length = 0;
  queue->data = data;
  queue->front = 0;
  return queue;
}

unsigned int queue_add(unsigned int lhs, unsigned int rhs,
                       unsigned int length) {
  return (lhs + rhs) % length;
}

bool queue_full(Queue *queue) { return queue->length == queue->max_len; }

bool queue_empty(Queue *queue) { return queue->length == 0; }

void enqueue(Queue *queue, int data) {
  assert(!queue_full(queue));
  queue->data[queue_add(queue->front, queue->length, queue->max_len)] = data;
  queue->length++;
}

int dequeue(Queue *queue) {
  assert(!queue_empty(queue));
  int data = queue->data[queue->front];
  queue->front = queue_add(queue->front, 1, queue->max_len);
  queue->length--;
  return data;
}

int queue_peek(Queue *queue) {
  assert(!queue_empty(queue));
  return queue->data[queue->front];
}

typedef struct {
  Queue *one;
  Queue *two;
} MyStack;

MyStack *myStackCreate() {
  int max_size = 20;
  Queue *one = new_queue(max_size);
  Queue *two = new_queue(max_size);
  MyStack *stack = (MyStack *)malloc(sizeof(MyStack));
  stack->one = one;
  stack->two = two;
  return stack;
}

bool stack_full(MyStack *stack) {
  return queue_full(stack->one) && queue_full(stack->two);
}

bool myStackEmpty(MyStack *stack) {
  return queue_empty(stack->one) && queue_empty(stack->two);
}

void myStackPush(MyStack *stack, int data) { enqueue(stack->one, data); }

int myStackPop(MyStack *stack) {
  assert(!myStackEmpty(stack));
  while (stack->one->length > 1) {
    int data = dequeue(stack->one);
    enqueue(stack->two, data);
  }
  int res = dequeue(stack->one);
  Queue *temp = stack->one;
  stack->one = stack->two;
  stack->two = temp;
  return res;
}

int myStackTop(MyStack *stack) {
  assert(!myStackEmpty(stack));
  while (stack->one->length > 1) {
    int data = dequeue(stack->one);
    enqueue(stack->two, data);
  }
  int res = queue_peek(stack->one);
  return res;
}

void myStackFree(MyStack *stack) {
  free(stack->one);
  free(stack->two);
  free(stack);
}
