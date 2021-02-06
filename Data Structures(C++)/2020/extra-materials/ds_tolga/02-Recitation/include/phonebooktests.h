#include "fileoperations.h"

using namespace std;

void testphonebook();
void add_test(PhonebookFile&, const char *, const char *);
void search_test(PhonebookFile&, const char *);
void update_test(PhonebookFile&, int, const char *, const char *);
void delete_test(PhonebookFile&, int);
void multi_read_test(PhonebookFile&, int);
void randomfill(PhonebookFile&, int);
void randstr(char[], int, int, int);