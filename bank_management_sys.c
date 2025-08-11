#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_account();
void deposit();
void withdraw();
void check_balance();
void account_details();
void all_acc_details();
void update_acc();

typedef struct{
    char name[70];
    int acc_num;
    float bal;
} Account;


int main(){

    while(1){
        int choice;
        printf("\n### Bank Management System ###\n");
        printf("1. Create an account\n");
        printf("2. Deposit money\n");
        printf("3. Withdraw money\n");
        printf("4. Check balance\n");
        printf("5. View account details\n");
        printf("6. View all account details\n");
        printf("7. Update account details\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                create_account();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                check_balance();
                break;
            case 5:
                account_details();
                break;
            case 6:
                all_acc_details();
                break;
            case 7:
                update_acc();
                break;
            case 8:
                printf("Thanks for visiting.\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please choose a valid option.\n");
                break;
        }
    }

}

void create_account(){
    Account acc;
    FILE *file=fopen("account.dat","ab+");
    if(file==NULL){
        printf("Error opening file.\n");
        return;
    }
    getchar();
    printf("Enter your name: ");
    fgets(acc.name,sizeof(acc.name),stdin);
    int ind=strcspn(acc.name,"\n");
    acc.name[ind]='\0';
    printf("Enter your account number: ");
    scanf("%d",&acc.acc_num);
    acc.bal=0;

    fwrite(&acc,sizeof(acc),1,file);
    fclose(file);
    printf("Account created successfully.\n");
}
void deposit(){
    FILE *file=fopen("account.dat","rb+");
    if(file==NULL){
        printf("Error opening file.\n");
        return;
    }

    int acc_no;
    float amt;
    Account acc;
    printf("Enter your account number: ");
    scanf("%d",&acc_no);
    printf("Enter the amount to deposit: ");
    scanf("%f",&amt);
    if(amt<0){
        printf("Negative amount cannot be deposited.\n");
        return;
    }

    while(fread(&acc,sizeof(Account),1,file)==1){
        if(acc.acc_num==acc_no){
            acc.bal+=amt;
            fseek(file,-sizeof(Account),SEEK_CUR);
            fwrite(&acc,sizeof(Account),1,file);
            fclose(file);
            printf("Successfully deposited %.2f. Your new balance is %.2f.\n",amt,acc.bal);
            return;
        }
    }

    fclose(file);
    printf("Money could not be deposited as account was not found.\n");
}
void withdraw(){
    FILE *file=fopen("account.dat","rb+");
    if(file==NULL){
        printf("Error opening file.\n");
        return;
    }

    int acc_no;
    float amt;
    Account acc;
    printf("Enter your account number: ");
    scanf("%d",&acc_no);
    printf("Enter the amount to withdraw: ");
    scanf("%f",&amt);

    while(fread(&acc,sizeof(Account),1,file)==1){
        if(acc.acc_num==acc_no){
            if(acc.bal>=amt){
                acc.bal-=amt;
                fseek(file,-sizeof(Account),SEEK_CUR);
                fwrite(&acc,sizeof(Account),1,file);
                printf("Successfully withdrawed %.2f. Your new balance is %.2f.\n",amt,acc.bal);
            }
            else{
                printf("Insufficient balance.\n");
            }
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("Account was not found.\n");
}
void check_balance(){
    FILE *file=fopen("account.dat","rb");
    if(file==NULL){
        printf("Error opening file.\n");
        return;
    }

    int acc_no;
    Account acc;
    printf("Enter your account number: ");
    scanf("%d",&acc_no);
    
    while(fread(&acc,sizeof(Account),1,file)==1){
        if(acc.acc_num==acc_no){
            printf("Your current balance is Rs.%.2f\n", acc.bal);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("Account was not found.\n");
}

void account_details(){
    FILE *file=fopen("account.dat","rb");
    if(file==NULL){
        printf("Error opening file.\n");
        return;
    }

    int acc_no;
    Account acc;
    printf("Enter your account number: ");
    scanf("%d",&acc_no);
    
    while(fread(&acc,sizeof(Account),1,file)==1){
        if(acc.acc_num==acc_no){
            printf("Account Number: %d\n", acc.acc_num);
            printf("Name  : %s\n", acc.name);
            printf("Balance: %.2f\n", acc.bal);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("Account was not found.\n");
}

void update_acc(){
    FILE *file=fopen("account.dat","rb+");
    if(file==NULL){
        printf("Error opening file.\n");
        return;
    }

    int acc_no;
    Account acc;
    printf("Enter your account number: ");
    scanf("%d",&acc_no);
    getchar();
    while(fread(&acc,sizeof(Account),1,file)==1){
        if(acc.acc_num==acc_no){
            printf("Your current name is %s\n", acc.name);
            printf("Enter your new name: ");
            fgets(acc.name,sizeof(acc.name),stdin);
            int ind=strcspn(acc.name,"\n");
            acc.name[ind]='\0';
            fseek(file,-sizeof(Account),SEEK_CUR);
            fwrite(&acc,sizeof(Account),1,file);
            fclose(file);
            printf("Successfully updated the account details.\n");
            return;
        }
    }
    fclose(file);
    printf("Account was not found.\n");
}

void all_acc_details(){
    FILE *file=fopen("account.dat","rb");
    if(file==NULL){
        printf("Error opening file.\n");
        return;
    }
    Account acc;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size == 0) {
        printf("No accounts found.\n");
        fclose(file);
        return;
    }
    rewind(file);
    while(fread(&acc,sizeof(Account),1,file)==1){
        printf("Account Number: %d\n", acc.acc_num);
        printf("Name  : %s\n", acc.name);
        printf("Balance: %.2f\n\n", acc.bal);
    }
    fclose(file);
}