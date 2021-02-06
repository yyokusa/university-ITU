#include "fileoperations.h"
#include "phone_tree.h"

using namespace std;

void testphonebook();
void insert_test(Phone_Tree&, const char *, const char *);
void search_test(Phone_Tree&, const char *);
void update_test(Phone_Tree&, const char *, const char *, const char *);
void delete_test(Phone_Tree&, const char *);
void clear_test(Phone_Tree&);
void multi_read_test(Phone_Tree&, int);
void randomfill(Phone_Tree&, int);
void randstr(char[], int, int, int);