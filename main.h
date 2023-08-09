#include <stddef.h>

const wchar_t kVerticalLine = 0x2503;
const wchar_t kVerticalLineDashed = 0x2506;
const wchar_t kArrow = 0x2B95;
const int kBase = 10;

enum Commands { kAdd = 1, kRemove, kInsert, kPrint, kQuit };

typedef struct NodeOptions {
  long data;
  long index;
} NodeOptions;

typedef struct Node Node;

typedef struct Head {
  Node *pFirstNode;
} Head;

struct Node {
  long data;
  Node *pNextNode;
};
