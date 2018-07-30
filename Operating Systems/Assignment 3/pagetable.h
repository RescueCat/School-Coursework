#define v 1
#define i 0
#define NONE -1

int** initializeTable(int*** table, int size);
int** pointPage(int*** table, int virtpage, int physframe);
void freeTable(int*** table, int size);
