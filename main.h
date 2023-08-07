wchar_t g_v_line = 0x2503;
wchar_t g_v_line_dashed = 0x2506;
wchar_t g_arrow = 0x2B95;

typedef struct Node Node;

typedef struct Head {
  Node *pFirstNode;
} Head;

struct Node {
  long data;
  Node *pNextNode;
};
