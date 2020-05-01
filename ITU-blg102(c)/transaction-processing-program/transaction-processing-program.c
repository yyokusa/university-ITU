// compile using gcc -std=c99 -Wall -Werror transaction-processing-program.c -o [output_name]
#include <stdio.h>

typedef struct ClientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[10];
    double balance;
}ClientData;
void createBlankData();
void textFile(FILE* fptr);
void updateRecord(FILE* fptr);
void newRecord(FILE* fptr);
void deleteRecord(FILE* fptr);
unsigned int enterChoice(void);
void showRecords(FILE * fptr);
int main() {
    
    // createBlankData() call this function one time to create a credit.dat file
    FILE* fptr;

    unsigned int choice; 

    if ((fptr = fopen("credit.dat", "rb+")) == NULL) { // rb+ bak
        puts("Could not open file");
    } //end if
    else {
        while ((choice = enterChoice()) != 6) {
            switch (choice)
            {
            case 1:
                textFile(fptr);
                break;
            case 2:
                updateRecord(fptr);
                break;
            case 3:
                newRecord(fptr);
                break;
            case 4:
                deleteRecord(fptr);
                break;
            case 5:
                showRecords(fptr);
                break;
            default:
            puts("Incorrect choice");
                break;
            }
        } //end while
        fclose(fptr);
    }//end else 

    return 0;
}//end main

void createBlankData() {
    ClientData blank_client = {0, "", "", 0.0};
    FILE * fptr;
    if((fptr = fopen("credit.dat", "wb")) == NULL) {
        puts("could not open file");
        return;
    } else {
        for (int  i = 0; i < 100; i++) {
            fwrite(&blank_client,sizeof(ClientData), 1, fptr);
        }
        fclose(fptr);
    }
}

unsigned int enterChoice() {
    unsigned int menu_choice;
    printf("%s", "\nEnter your choice\n"
        "1 - Store a formatted text file of accounts\n"
        "   called \"accounts.txt\" for printing\n"
        "2 - Update an account\n"
        "3 - Add an account\n"
        "4 - Delete an account\n"
        "5 - Show all\n"
        "6 - End program\n");
    scanf("%u", &menu_choice);
    return menu_choice;
}
void textFile(FILE* read_ptr) {
    FILE *write_ptr;
    int result; // used to read if fread read any bytes

    ClientData client = {0, "", "", 0.0};
    if ((write_ptr = fopen("accounts.txt", "w")) == NULL) {
        puts("Could not open file");
    } //end if
    else {
        rewind(read_ptr);
        //print content in file instead of stdout console
        fprintf(write_ptr, "%-6s%-16s%-11s%-10s\n",
            "Acct","Last name","First name","Balance");
        // read all record s until eof
        while (!feof(read_ptr)) {
            result = fread(&client, sizeof(ClientData), 1, read_ptr);
            // write single record to text file
            if (result != 0 && client.acctNum != 0) {
                fprintf(write_ptr, "%-6d%-16s%-11s%-10.2lf\n",
                    client.acctNum, client.lastName, client.firstName, client.balance);
            }// end if
        } //end while
        fclose(write_ptr);
    }//end else 
}
//OK
void updateRecord(FILE* fptr) {
    ClientData client = {0, "", "", 0.0};
    double transaction_amount = 0.0;
    unsigned int account = 0;
    

    printf("Enter account to update (1 to 100): ");
    scanf("%d", &account);
    // find record
    fseek(fptr, (account - 1) * sizeof(ClientData), SEEK_SET);
    //read record
    fread(&client, sizeof(ClientData), 1, fptr);
    if (client.acctNum == 0) {
        printf("Account %d has no information \n", client.acctNum);
        return;
    } 
    else { // update record
        printf("%-6d%-16s%-11s%-10.2lf",
            client.acctNum, client.lastName, client.firstName, client.balance);
        //request transaction amount
        printf("%s","Enter charge ( + ) or payment ( - ): ");
        scanf("%lf", &transaction_amount);
        client.balance += transaction_amount;
        printf("%-6d%-16s%-11s%-10.2lf",
            client.acctNum, client.lastName, client.firstName, client.balance);
        //move fptr to correct record in file
        fseek(fptr, (account - 1) * sizeof(ClientData), SEEK_SET);
        //write updated record over old record in file
        fwrite(&client, sizeof(ClientData), 1, fptr);
    }
}
void newRecord(FILE* fptr) {
    ClientData client = {0, "" , "", 0.0};
    unsigned int account_num;

    printf("%s","Enter account number"
        " (1 to 100, 0 to end input)\n? ");
    scanf("%d", &account_num);
    fseek(fptr, (account_num - 1) * sizeof(ClientData), SEEK_SET);
    fread(&client, sizeof(ClientData), 1, fptr);    
    //user enter info which copied into file
    if (client.acctNum != 0) {
        printf("Account %d already have info", client.acctNum);
        return;
    } else {
        printf("%s","Enter lastname, firstname, balance\n? ");
        //set record
        fscanf(stdin, "%14s%9s%lf", client.lastName, client.firstName, &client.balance);
        client.acctNum = account_num;
        //seek position in file for the record
        fseek(fptr, (account_num - 1) * sizeof(ClientData), SEEK_SET);
        //write user-specified info in file
        fwrite(&client, sizeof(ClientData), 1, fptr);
    }
}
        
void deleteRecord(FILE* fptr) {
    ClientData client;
    ClientData blank_client = {0, "", "", 0.0};
    unsigned int account_num;
    printf("%s","account num to delete (1 to 100) ");
    scanf("%d", &account_num);
    // find record
    fseek(fptr, sizeof(ClientData) * (account_num - 1), SEEK_SET);
    //read record
    fread(&client, sizeof(ClientData), 1, fptr);
    if (client.acctNum == 0) {
        printf("Account %d does not exist\n", account_num);
        return;
    } 
    else {
        // find record
        fseek(fptr, sizeof(ClientData) * (account_num - 1), SEEK_SET);
        //set record
        fwrite(&blank_client, sizeof(ClientData), 1, fptr);
        // return to record start
        //fseek(fptr, (-1) * sizeof(ClientData), SEEK_CUR); // check if it is same as above
    }
}


void showRecords(FILE * fptr) {
    rewind(fptr);
    ClientData client = {0,"","",0.0};
    while(!feof(fptr)) {
        fread(&client, sizeof(ClientData), 1, fptr);
        printf("%d %s %s %lf\n", client.acctNum,client.lastName,client.firstName,client.balance);
    }
}



/*
from man fseek:
int
    fseek(FILE *stream, long offset, int whence);

from GeeksForGeeks
int fseek(FILE *pointer, long int offset, int position)

pointer: pointer to a FILE object that identifies the stream.
offset: number of bytes to offset from position
position: position from where offset is added.

returns:
zero if successful, or else it returns a non-zero value

position defines the point with respect to which the file pointer needs to be moved. It has three values:
SEEK_END : It denotes end of the file.
SEEK_SET : It denotes starting of the file.
SEEK_CUR : It denotes file pointer’s current position.
*/

/*
ftell(FILE *stream);
The ftell() function obtains the current value of the file position indicator for the stream pointed to by stream.
*/