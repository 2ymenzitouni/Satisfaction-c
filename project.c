#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

int main(){

    /*==variables===*/
    int choix;
    char firstname[50], lastname[50], username[50], email[50], occupation[50], password[50];
    char login_username [50],login_password [50];
    char register_first_name[50],register_last_name [50],register_username[50],register_email[50],register_occupation[50],register_password[50];
    char line[1024];
    int answer=0;
    int total=0;
    /*==variables===*/

    /*==goto===*/
    home:
        printf("==========================================Home==========================================\n");
        printf(" 1.Login \n 2.Register \n 3.Use web \n 4.Quit");
        printf("\n========================================================================================\n");
        printf("Choix: ");
        scanf("%d",&choix);
    /*==goto===*/

    /*===choix 1===*/
    if (choix == 1){
        printf("\n==========================================Login==========================================\n");
        //get the username
        printf("Username: ");
        scanf("%s",&login_username);

        //get the password
        printf("Password: ");
        scanf("%s",&login_password);

        // if superadmin is logged in
        if(strcmp(login_username ,"superadmin")==0 && strcmp(login_password ,"admin")==0){
            printf("\n==================\Welcome %s===================\n" , login_username);
        /*=====if user is logged in as superadmin=====*/
            printf("1.View All Answers \n 2.View All users \n 3.Quit");
            printf("\n================================================\n");
            scanf("%d",&choix);
            if (choix == 1){
                printf("satisfaction");
            }
            else if (choix ==2){
                FILE *file = fopen("users.csv", "r");
                printf("name    first_name  last_name   username    password \n\n");
                while (fgets(line, sizeof(line), file)) {
                    printf("%s\n", line);
                }
                fclose(file);
            }
            else if(choix==3){
                goto home;
            }
        }
        //if normal user
        else{

            FILE *file = fopen("users.csv", "r");
            if (file == NULL) {
                perror("Error opening file");
                return 1;
            }
            while (fgets(line, sizeof(line), file)) {
                line[strcspn(line, "\n")] = '\0';
                char *firstName = strtok(line, ";");
                char *lastName = strtok(NULL, ";");
                char *username = strtok(NULL, ";");
                char *email = strtok(NULL, ";");
                char *occupation = strtok(NULL, ";");
                char *password = strtok(NULL, ";");
                //check
                if(strcmp(login_username,username)==0 && strcmp(login_password,password)){
                    printf("\n==========You have been Sucessfully Logged In==========\n");
                    printf("\n\n==================\Welcome %s===================\n" , login_username);
                    /*=====if user is logged in as superadmin=====*/
                    printf("\n 1.Answer the Satisfaction \n 2.My Answers \n 3.Quit");
                    printf("\n================================================\n");
                    scanf("%d",&choix);
                    if (choix == 1){
                        FILE *file = fopen("student.csv", "r");
                        if (file == NULL) {
                        perror("Error opening file");
                        return 1;
                        }
                        while (fgets(line, sizeof(line), file)) {
                            line[strcspn(line, "\n")] = '\0';
                            printf("\n%s\n\n",line);
                            printf("\n1 - Very Dissatisfied \n2 - Dissatisfied \n3 - Neutral \n4 - Satisfied \n5 - Very Satisfied \n\nAnswer:");
                            scanf("%d",&answer);
                            total += answer;
                        }
                        if(total/5 == 1){
                            printf("\n===================================Result===================================\n");
                            printf("Your Satisfaction Score is %d  ==> you are Very Dissatisfied ",total/5);
                            printf("\n============================================================================\n");
                        }
                        else if(total/answer == 2){
                            printf("\n===================================Result===================================\n");
                            printf("Your Satisfaction Score is %d  ==> you are Dissatisfied ",total/5);
                            printf("\n============================================================================\n");
                        }
                        else if(total/5 == 3){
                            printf("\n===================================Result===================================\n");
                            printf("Your Satisfaction Score is %d  ==> you are Neutral ",total/5);
                            printf("\n============================================================================\n");
                        }
                        else if(total/5 == 4){
                            printf("\n===================================Result===================================\n");
                            printf("Your Satisfaction Score is %d  ==> you are Satisfied ",total/5);
                            printf("\n===================================Result===================================\n");
                        }
                        else{
                            printf("\n===================================Result===================================\n");
                            printf("Your Satisfaction Score is %d  ==> you are Vert Satisfied ",total/5);
                            printf("\n===================================Result===================================\n");
                        }

                    }
                    else if(choix ==2){
                        printf("satisfaction");
                    }
                    else if(choix ==3){
                        goto home;
                    }
                }
            }

            fclose(file);
        }
    }
    /*===choix 2===*/
    else if(choix==2){
        printf("\n======Regiser======\n");
        printf("first name: ");
        scanf("%s" , &register_first_name);

        printf("last name: ");
        scanf("%s" , &register_last_name);

        printf("username: ");
        scanf("%s" , &register_username);

        printf("email: ");
        scanf("%s",&register_email);

        printf("occupation: ");
        scanf("%s", &register_occupation);

        printf("password: ");
        scanf("%s", &register_password);
        printf("\n=====================your account has been successfully created.=====================\n");
        /*=====save information in a csv file=====*/
        FILE *file = fopen("users.csv", "a");
        if (file == NULL) {
            printf("Erreur lors de l'ouverture du fichier.\n");
        }
        fprintf(file, "%s;%s;%s;%s;%s;%s \n",register_first_name,register_last_name ,register_username,register_email,register_occupation,register_password);
        fclose(file);
        //should go login
    }
    else if(choix==3){
        system("start form.html");
    }
}






























