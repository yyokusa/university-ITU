#include "fileoperations.h"
#include "phone_list.h"

using namespace std;

void testphonebook();
void insert_test(Phone_List &, const char *, const char *);
void search_test(Phone_List &, const char *);
void update_test(Phone_List &, int, const char *, const char *);
void delete_test(Phone_List &, int);
void clear_test(Phone_List &);
void multi_read_test(Phone_List &, int);
void randomfill(Phone_List &, int);
void randstr(char[], int, int, int);