#include<stdio.h>
#include<stdlib.h>

struct EMP
{
int Emp_no;
char Name[20];
long long Phone;
char Post[10];

};
void Emp_List(void);
void New_emp(void);
void Emp_det(void);
void Upd_emp(void);
void Fire(void);
int main()
{
    int choice,M_E=0;
    while(M_E==0)
{
    system("cls");
    printf("\t\tChoose Action\t\t\n\n");
    printf("1.Employee List\n2.Employee Details\n3.New Employee\n4.Update Employee Details\n5.Fire Employee\n---------------------------------------------\n");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:Emp_List();
        break;

        case 2:Emp_det();
        break;

        case 3:New_emp();
        break;

        case 4:Upd_emp();
        break;

        case 5:Fire();
        break;

        default:
        printf("Invalid Choice!!\n");
    }
    printf("\nMENU:0----EXIT:1\n");
    scanf("%d",&M_E);
    if(M_E!=0 && M_E!=1)
    {
    printf("INVALID CHOICE!!\n\nEXITING.....\n");
    exit(1);
    }
}
}

void Emp_List(void)
{
    FILE * disp;
    struct EMP E;

    disp = fopen("EMP.txt","rb");
    if(disp==NULL)
    {
        printf("No employee to display\n");
        return;
    }
    else
    {
        printf(" EMP.NO.\t\tNAME\n");
        printf("_____________________________\n\n");
        while(fread(&E,sizeof(E),1,disp))
        printf(" %d \t\t\t%s\n",E.Emp_no,E.Name);
    }
    fclose(disp);
}
void Emp_det(void)
{
    int NUM;
    FILE * view;
    struct EMP E;
    printf("Enter Employee Number!\n");
    scanf("%d",&NUM);
    view = fopen("EMP.txt","rb");
    if(view==NULL)
    {
        printf("No employee to display\n");
        return;
    }
    else
    {
        while(fread(&E,sizeof(E),1,view))
        {
            if(NUM == E.Emp_no)
            {
                printf("EMP.NO\tNAME\t\t\tPHONE\t\tPOST\n");
                printf("____________________________________________________\n");
                printf("%d \t%s\t\t\t%lld \t%s\n\n",E.Emp_no,E.Name,E.Phone,E.Post);
            }
        }
    }
    fclose(view);

}
void New_emp(void)
{
    int noe; //no of emp
    FILE * NEW;
    struct EMP E;
    printf("Enter Employee Number\n");
    scanf("%d",&E.Emp_no);

    printf("Enter Employee Name\n");
    scanf("%s",E.Name);

    printf("Enter Employee Phone\n");
    scanf("%lld",&E.Phone);

    printf("Enter Employee Post\n");
    scanf("%s",&E.Post);
    NEW = fopen("EMP.txt","ab");
    if(NEW==NULL)
    {
        printf("ERROR!!\n");
        fclose(NEW);
        return;
    }
    fwrite(&E,sizeof(E),1,NEW);
    fclose(NEW);

}
void Upd_emp()
{
    FILE * upd;
    FILE * temp;
    struct EMP E;
    int num,done;

    printf("Enter Employee Number TO Update Details:\n");
    scanf("%d",&num);

    upd =fopen("EMP.txt","rb");
    if(upd==NULL)
    {
        printf("ERRROR!\n");
        exit(1);
    }
    temp=fopen("TMP.TXT","wb");
    if(temp==NULL)
    {
        printf("ERROR!\n");
        exit(1);
    }
    while(fread(&E,sizeof(E),1,upd))
    {
        if(num==E.Emp_no)
        {
            printf("Enter Employee Number\n");
            scanf("%d",&E.Emp_no);

            printf("Enter Employee Name\n");
            scanf("%s",E.Name);

            printf("Enter Employee Phone\n");
            scanf("%lld",&E.Phone);

            printf("Enter Employee Post\n");
            scanf("%s",&E.Post);
        }

        fwrite(&E,sizeof(E),1,temp);

    }
    fclose(upd);
    fclose(temp);

    remove("EMP.txt");
    rename("TMP.txt","EMP.txt");

}
void Fire(void)
{
    int num,fired;
    struct EMP E;
    FILE * list;
    FILE * temp;

    printf("Enter Employee Number to fire!\n");
    scanf("%d",&num);

    list =fopen("EMP.txt","rb");
    if(!list)
    {
        printf("ERRROR!\n");
        exit(1);
    }
    temp=fopen("TMP.TXT","wb");
    if(!temp)
    {
        printf("ERROR!\n");
        exit(1);
    }
    while(fread(&E,sizeof(E),1,list))
    {
        if(num==E.Emp_no)
        {
            printf("Employee Fired!!\n");
            fired=1;
            continue;
        }
        fwrite(&E,sizeof(E),1,temp);
    }
    if(!fired)
    printf("No Employee with Employee Number %d",num);

    fclose(list);
    fclose(temp);

    remove("EMP.txt");
    rename("TMP.txt","EMP.txt");
}
