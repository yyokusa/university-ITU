#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

#define SEMKEY 7
#define SEMKEY_2 8

int nr_register_time = 0;
int semaphore_set_identifier; // interviewers 
int semaphore_set_identifier_2; // applicants 
int processed = 0;
int applicants_line_index;
int applicants_line_waiting_time_list[256];
int applicants_count = 0;


void semsignal(int semaphore_set_identifier, int val){
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = val;
    semaphore.sem_flg = 1;
    semop(semaphore_set_identifier, &semaphore, 1) ;
}


void semwait(int semaphore_set_identifier, int val){
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = (-1*val);
    semaphore.sem_flg = 1;
    semop (semaphore_set_identifier, &semaphore, 1) ;
}


void* interview(void* interviewer_id_param){
    int interviewer_id = (long int) interviewer_id_param;
    int counter = 0;
    while(applicants_count > counter++){
        semwait(semaphore_set_identifier_2, 1);
        semwait(semaphore_set_identifier, 1);
        applicants_line_index++;
        semsignal(semaphore_set_identifier, 1);
        int applicant = applicants_line_index - 1;

        printf("Interviewer %d started interview with Applicant %d\n", interviewer_id, applicant+1);
        sleep(applicants_line_waiting_time_list[applicant]);
        printf("Interviewer %d finished interview with Applicant %d\n", interviewer_id, applicant+1);
        processed++;
    }
    return NULL;
}

void* register_applicants(void* applicant_index_param){
    int applicant_index = (long int) applicant_index_param;
    for (int i = 0; i < applicant_index; i++){
        sleep(nr_register_time);
        printf("Applicant %d’s registeration is done\n", i + 1);
        semsignal(semaphore_set_identifier_2, 1);
    }

    while(applicant_index > processed){;}
    // It returns from start_routine().  This is equivalent to calling
        //  pthread_exit(3) with the value supplied in the return
        //  statement.
    return NULL;
}

int main(int argc, const char * argv[]){
    nr_register_time = atoi(argv[2]);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


    //    int semget(key_t key, int nsems, int semflg);
    //    The semget() system call returns the System V semaphore set
    //    identifier associated with the argument key.
    // A new set of nsems semaphores is created if key has the value IPC_PRIVATE
    semaphore_set_identifier = semget(SEMKEY, 0, 0); 
    semaphore_set_identifier_2 = semget(SEMKEY_2, 0, 0);


    // int semctl(int semid, int semnum, int cmd, ...);
    // semctl() performs the control operation specified by cmd on the
    //    System V semaphore set identified by semid

    // SETVAL Set the semaphore value (semval) to arg.val for the
    //           semnum-th semaphore of the set
    semctl(semaphore_set_identifier, 0 , SETVAL, 1);
    semctl(semaphore_set_identifier_2, 0 , SETVAL, 0);
    applicants_line_index = 0;

    // interviewer threads
    pthread_t interviewer1;
    pthread_t interviewer2;
    pthread_t interviewer3;
    
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Could not open file\n");
        exit(EXIT_FAILURE);
    }
    char *line = NULL;
    size_t len = 0;

    int number = 0;
    int applicant_index = 0;
    while(getline(&line, &len, fp) != -1) {
        number = atoi(line);
        applicants_line_waiting_time_list[applicant_index] = number;
        printf("Applicant %d applied to the receptionist\n", (applicant_index + 1));
        applicant_index++;
    }
    fclose(fp);
    applicants_count = applicant_index;


    pthread_t receptionist;
    pthread_create(&receptionist, &attr, register_applicants, (void *)(long int)applicant_index); // to get rid of warning-> first cast to long int then void *
    pthread_create(&interviewer1, NULL, interview, (void *)1);
    pthread_create(&interviewer2, NULL, interview, (void *)2);
    pthread_create(&interviewer3, NULL, interview, (void *)3);
    

    pthread_join(receptionist, NULL);
    semctl(semaphore_set_identifier, 0, IPC_RMID, 0);
    printf("All applicants have interviewed successfully.\n");
    return 0;
}
