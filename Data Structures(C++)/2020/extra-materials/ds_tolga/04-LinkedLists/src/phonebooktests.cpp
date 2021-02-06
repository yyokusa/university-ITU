#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h> /* time */

#include "phonebooktests.h"

void testphonebook()
{
    Phone_List phonelist;
    phonelist.create();
    read_fromfile(phonelist, "test_phonebook.dat");
    insert_test(phonelist, "Tolga", "12341234");
    insert_test(phonelist, "Duygu", "9879878");
    search_test(phonelist, "Tolga");
    search_test(phonelist, "*");
    search_test(phonelist, "Murat");
    update_test(phonelist, 1, "Murat", "000000");
    search_test(phonelist, "*");
    search_test(phonelist, "Murat");
    delete_test(phonelist, 2);
    delete_test(phonelist, 1);
    search_test(phonelist, "*");
    insert_test(phonelist, "Ozge", "93944");
    insert_test(phonelist, "Savas", "334114");
    clear_test(phonelist);
    search_test(phonelist, "*");

    srand(clock());
    randomfill(phonelist, 10000);
    multi_read_test(phonelist, 5000);

    write_tofile(phonelist, "test_phonebook.dat");
    phonelist.clear();
    remove("test_phonebook.dat");
}

void multi_read_test(Phone_List &phonelist, int trials)
{

    const short namelen = 6;
    char name[namelen];

    clock_t start = clock();
    for (int i = 0; i < trials; i++)
    {
        randstr(name, namelen, 65, 26);
        phonelist.search(name);
    }

    clock_t end = clock();

    cout << "Read time for " << trials <<" records: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << " milliseconds" << endl;

    getchar();
}

void insert_test(Phone_List &phonelist, const char *name, const char *number)
{
    Phone_Record newrecord;

    newrecord.name = new char[strlen(name) + 1];
    strcpy(newrecord.name, name);

    newrecord.phonenum = new char[strlen(number) + 1];
    strcpy(newrecord.phonenum, number);

    phonelist.insert(newrecord);
    delete[] newrecord.name;
    delete[] newrecord.phonenum;
}

void search_test(Phone_List &phonelist, const char *name)
{
    char* searchfor = new char[strlen(name)+1];
    strcpy(searchfor, name);
    phonelist.search(searchfor);
    delete[] searchfor;
}

void update_test(Phone_List &phonelist, int no, const char *name, const char *number)
{
    Phone_Record newrecord;

    newrecord.name = new char[strlen(name)+1];
    strcpy(newrecord.name, name);

    newrecord.phonenum = new char[strlen(number) + 1];
    strcpy(newrecord.phonenum, number);

    phonelist.update(no, newrecord);

    delete[] newrecord.name;
    delete[] newrecord.phonenum;
}

void delete_test(Phone_List &phonelist, int no)
{
    phonelist.remove(no);
}

void clear_test(Phone_List &phonelist)
{
    phonelist.clear();
}

void randomfill(Phone_List &phonelist, int numofrecords)
{

    const short namelen = 6;
    char name[namelen];
    const short phonelen = 8;
    char phone[phonelen];
    Phone_Record newrecord;
    newrecord.name = new char[namelen];
    newrecord.phonenum = new char[phonelen];

    clock_t start = clock();

    for (int i = 0; i < numofrecords; i++)
    {
        randstr(name, namelen, 65, 26);
        randstr(phone, phonelen, 48, 10);

        strcpy(newrecord.name, name);
        strcpy(newrecord.phonenum, phone);
        phonelist.insert(newrecord);
    }
    clock_t end = clock();

    cout << "Write time for " << numofrecords <<" records: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << " milliseconds" << endl;


    delete[] newrecord.name;
    delete[] newrecord.phonenum;
}

void randstr(char str[], int len, int start, int end)
{

    for (int i = 0; i < len - 1; i++)
        str[i] = ((char)(start + rand() % end));

    str[len - 1] = '\0';
}
