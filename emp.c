#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
struct employee
{
    int empID;
    int empSalary;
    char empName[20];
    long long empPhone;
    char empPost[10];
    int isPaid;
};

int authenticate();
void newEmployee();
void updateEmp();
void empDetails();
void empList();
void fireEmployee();
void getEmpSalary();
void promoteEmp();
void paySalary();
void isSalaryPaid();

int main()
{
    if(authenticate() != 1) {
        printf("Exitting...\n");
        exit(0);
    } 
    while (1)
    {
        system("cls");
        printf("\t\tChoose Action\t\t\n\n");
        printf("1. New Employee\n2. Update Employee Details\n3. Employee Details\n4. Employee List\n5. Fire Employee\n6. Employee salary\n7. Promote Employee\n8. Pay Salary\n9. Salary status\n10. Exit\n");
        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            newEmployee();
            break;

        case 2:
            updateEmp();
            break;

        case 3:
            empDetails();
            break;

        case 4:
            empList();
            break;

        case 5:
            fireEmployee();
            break;

        case 6:
            getEmpSalary();
            break;

        case 7:
            promoteEmp();
            break;

        case 8:
            paySalary();
            break;

        case 9:
            isSalaryPaid();
            break;

        case 10:
            exit(0);
            break;
        default:
            printf("Invalid Choice!!\n");
        }
        printf("\nMENU: 0\n");
        int menu = 0;
        scanf("%d", &menu);
        if (menu != 0)
        {
            printf("INVALID CHOICE!!\n\nEXITING.....\n");
            exit(0);
        }
    }
}
int authenticate()
{
    //Incomplete, need to implement file system for storing and hiding login details
    //Only for demonstrating login functionality
    system("cls");
    int flag = 1;
    char loginID[] = "admin";
    char password[] = "Admin@123";
    char pass[11];
    char login[10];
    printf("****************Welcome to employee manager*****************\n\n");
    printf("\tLogin:\n\n");
    printf("Enter login ID: ");
    scanf("%s", login);
    printf("Enter password: ");
    scanf("%s", pass);
    if (strcmp(loginID, login) != 0)
    {
        flag = 0;
    }
    if (strcmp(password, pass) != 0)
    {
        flag = 0;
    }
    if (!flag)
    {
        printf("Wrong credentials...Try again\n");
        return 0;
    }
    else
    {
        return 1;
    }
}
void newEmployee()
{
    int num;
    FILE *NEW;
    struct employee emp;
    printf("Enter Employee ID\n");
    scanf("%d", &num);
    NEW = fopen("EMP.txt", "ab+");
    if (NEW == NULL)
    {
        printf("ERROR!!\n");
        fclose(NEW);
        return;
    }
    while (fread(&emp, sizeof(emp), 1, NEW))
    {
        if (num == emp.empID)
        {
            printf("Employee already exists!");
            return;
        }
    }
    emp.empID = num;
    printf("Enter Employee's Name\n");
    fflush(stdin);
    scanf("%[^\n]s", &emp.empName);

    printf("Enter Employee's Phone No.\n");
    scanf("%lld", &emp.empPhone);

    printf("Enter Employee's Salary\n");
    scanf("%d", &emp.empSalary);

    emp.isPaid = 0;
    printf("Enter Employee's Post\n");
    scanf("%s", &emp.empPost);

    fwrite(&emp, sizeof(emp), 1, NEW);
    printf("Employee added successsfully!!\n");
    fclose(NEW);
}
void updateEmp()
{
    FILE *upd;
    FILE *temp;
    char c;
    struct employee emp;
    int num;

    printf("Enter Employee ID TO Update Details: \n");
    scanf("%d", &num);

    upd = fopen("EMP.txt", "rb");
    if (!upd)
    {
        printf("ERRROR!\n");
        exit(1);
    }

    temp = fopen("TMP.TXT", "wb");
    if (!temp)
    {
        printf("ERROR!\n");
        exit(1);
    }
    while (fread(&emp, sizeof(emp), 1, upd))
    {
        if (num == emp.empID)
        {
            printf("Enter Employee's ID\n");
            scanf("%d", &emp.empID);

            printf("Enter Employee's Name\n");
            fflush(stdin);
            scanf("%[^\n]s", &emp.empName);

            printf("Enter Employee's Phone No.\n");
            scanf("%lld", &emp.empPhone);

            printf("Enter Employee's Post\n");
            scanf("%s", &emp.empPost);

            printf("Enter Employee's Salary\n");
            scanf("%d", &emp.empSalary);

            printf("Details updated successsfully!!\n");

            fwrite(&emp, sizeof(emp), 1, temp);
        }
        else
            fwrite(&emp, sizeof(emp), 1, temp);
    }

    fclose(upd);
    fclose(temp);

    remove("EMP.txt");
    rename("TMP.txt", "EMP.txt");
}
void empDetails()
{
    int NUM;
    FILE *view;
    struct employee emp;
    printf("Enter Employee Number!\n");
    scanf("%d", &NUM);
    view = fopen("EMP.txt", "rb");
    if (view == NULL)
    {
        printf("ERROR!!\n");
        return;
    }
    else
    {
        printf("EMP.NO. \tNAME\t\tPHONE  \t\tPOST\n");
        printf("___________________________________________________________\n");
        while (fread(&emp, sizeof(emp), 1, view))
        {
            if (NUM == emp.empID)
            {
                printf(" %d \t\t%s \t\t%lld \t%s", emp.empID, emp.empName, emp.empPhone, emp.empPost);
            }
        }
    }
    fclose(view);
}
void empList()
{
    FILE *disp;
    struct employee emp;

    disp = fopen("EMP.txt", "rb");
    if (disp == NULL)
    {
        printf("ERROR!!\n");
        return;
    }
    else
    {
        printf("EMP.NO. \tNAME\n");
        printf("_________________________________\n");
        while (fread(&emp, sizeof(emp), 1, disp))
            printf(" %d \t\t%s\n", emp.empID, emp.empName);
    }
    fclose(disp);
}
void getEmpSalary()
{
    int NUM;
    FILE *view;
    struct employee emp;
    printf("Enter Employee Number!\n");
    scanf("%d", &NUM);
    view = fopen("EMP.txt", "rb");
    if (view == NULL)
    {
        printf("ERROR!!\n");
        return;
    }
    else
    {
        printf("EMP.NO. \tNAME\t\tSALARY\tisPAID\n");
        printf("___________________________________________________________\n");
        while (fread(&emp, sizeof(emp), 1, view))
        {
            if (NUM == emp.empID)
            {
                printf(" %d \t\t%s \t\t%d \t%d", emp.empID, emp.empName, emp.empSalary, emp.isPaid);
            }
        }
    }
    fclose(view);
}
void fireEmployee()
{
    int num, fired;
    struct employee emp;
    FILE *list;
    FILE *temp;

    printf("Enter Employee Number to fire!\n");
    scanf("%d", &num);

    list = fopen("EMP.txt", "rb");
    if (!list)
    {
        printf("ERRROR!\n");
        exit(1);
    }
    temp = fopen("TMP.TXT", "wb");
    if (!temp)
    {
        printf("ERROR!\n");
        exit(1);
    }
    while (fread(&emp, sizeof(emp), 1, list))
    {
        if (num == emp.empID)
        {
            printf("Employee Fired!!\n");
            fired = 1;
        }
        else
            fwrite(&emp, sizeof(emp), 1, temp);
    }
    if (!fired)
        printf("No Employee with Employee Number %d", num);

    fclose(list);
    fclose(temp);

    remove("EMP.txt");
    rename("TMP.txt", "EMP.txt");
}
void promoteEmp()
{
    FILE *upd;
    FILE *temp;
    struct employee emp;
    int num;

    printf("Enter Employee ID To Promote: \n");
    scanf("%d", &num);

    upd = fopen("EMP.txt", "rb");
    if (!upd)
    {
        printf("ERRROR!\n");
        exit(1);
    }

    temp = fopen("TMP.TXT", "wb");
    if (!temp)
    {
        printf("ERROR!\n");
        exit(1);
    }
    while (fread(&emp, sizeof(emp), 1, upd))
    {
        if (num == emp.empID)
        {
            printf("Enter Employee's Post\n");
            scanf("%s", &emp.empPost);

            printf("Enter Employee's Salary\n");
            scanf("%d", &emp.empSalary);

            fwrite(&emp, sizeof(emp), 1, temp);
        }
        else
            fwrite(&emp, sizeof(emp), 1, temp);
    }
    printf("Employee promoted sucessfully\n");
    fclose(upd);
    fclose(temp);

    remove("EMP.txt");
    rename("TMP.txt", "EMP.txt");
}
void paySalary()
{
    FILE *upd;
    FILE *temp;
    struct employee emp;
    int num;

    printf("Enter Employee ID To Promote: \n");
    scanf("%d", &num);

    upd = fopen("EMP.txt", "rb");
    if (!upd)
    {
        printf("ERRROR!\n");
        exit(1);
    }

    temp = fopen("TMP.TXT", "wb");
    if (!temp)
    {
        printf("ERROR!\n");
        exit(1);
    }
    while (fread(&emp, sizeof(emp), 1, upd))
    {
        if (num == emp.empID)
        {
            if (num == emp.empID)
            {
                if (emp.isPaid == 1)
                {
                    printf("Salary is already paid\n");
                }
                else
                {
                    printf("Salary sucessfully paid\n");
                    emp.isPaid = 0;
                    fwrite(&emp, sizeof(emp), 1, temp);
                }
            }
        }
        else
            fwrite(&emp, sizeof(emp), 1, temp);
    }
    fclose(upd);
    fclose(temp);

    remove("EMP.txt");
    rename("TMP.txt", "EMP.txt");
}
void isSalaryPaid()
{
    int NUM;
    FILE *view;
    struct employee emp;
    printf("Enter Employee ID\n");
    scanf("%d", &NUM);
    view = fopen("EMP.txt", "rb");
    if (view == NULL)
    {
        printf("ERROR!!\n");
        return;
    }
    else
    {
        while (fread(&emp, sizeof(emp), 1, view))
        {
            if (NUM == emp.empID)
            {
                if (emp.isPaid == 1)
                {
                    printf("Salary is already paid\n");
                }
                else
                {
                    printf("Salary is not paid\n");
                }
            }
        }
    }
    fclose(view);
}
