#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

struct package 
{ 
   char name[100];
   char installDate[100];
   char lastUpdate[100];
   int  upgrades;
   char removalDate[100];
};

struct package packs[1000];

void analizeLog(char *logFile, char *report);

int main(int argc, char **argv) {

 

    if (argc < 2) {
	printf("Usage:./pacman-analizer.o pacman.log\n");
	return 1;
    }


    analizeLog(argv[2], argv[4]);

    return 0;
}



char *nombrePaquete(char* line, int bytes){
    char *res = calloc(1, sizeof(char));
      int separation;
    for(int i =26; i<bytes; i++){
        if(line[i]==32){
            separation = i;
            break;
        }
    }
    for(int j=separation+1; j<bytes; j++){
        res = realloc(res,j-(separation-1)*sizeof(char));
        if(line[j]==32){
            break;
        }
        res[j-(separation+1)]=line[j];
    }
    return res;
}

char *fechaPaquete(char* line, int bytes){
    char *res = calloc(1, sizeof(char));
    for(int i =1; i<bytes; i++){
        res = realloc(res,i+1*sizeof(char));
        if(line[i]==93){
            break;
        }
        res[i-1]=line[i];
    }
    return res;
}


const char* categorie(char *line, int bytes){
    char *res = calloc(1, sizeof(char));
    for(int i =26; i<bytes; i++){
        res = realloc(res,i-24*sizeof(char));
        res[i-26]=line[i];
        if(line[i]==32){
            break;
        }  
    }

    if(res[0]==105 && res[1]==110 && res[2]==115){
        return "installation";
    }else if(res[0]==117 && res[1]==112 && res[2]==103){
        return "upgrade";
    }else if(res[0]==114 && res[1]==101 && res[2]==109){
        return "remove";
    }
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);
    char *c = (char *) calloc(1, sizeof(char));
    char *message = (char *) calloc(100000000, sizeof(char));
    char *line;
    int installed=0, upgraded=0, removed=0;
    int wr = open(report, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (wr < 0) {
        perror("Report file could not be created"); 
        exit(1); 
    }
        int file_descriptor = open(logFile, O_RDONLY);
    if (file_descriptor < 0) {
        perror("File could not be opened"); 
        return 0;
    }
    int count_bytes = 0, i=0, end,bytes = 0;
    while(1){
        line = (char *) calloc(0, sizeof(char));
        do
        {
            bytes++;
            line = realloc(line, bytes*sizeof(char));
            end = read(file_descriptor, c, 1);
            count_bytes++;
            message[count_bytes-1]=c[0];
            line[bytes-1]=c[0];

        } while (strcmp("\n",c)!=0);
        i++;
        if(line!=NULL){
            const char* aux = categorie(line, bytes);
            if(aux == "installation"){ 
                char * packageName =  nombrePaquete(line, bytes);
                char * packageInstallDate = fechaPaquete(line, bytes);
                strcpy(packs[installed].name,packageName);
                strcpy(packs[installed].installDate,packageInstallDate);
                strcpy(packs[installed].lastUpdate,"-");
                packs[installed].upgrades = 0;
                strcpy(packs[installed].removalDate,"-");
                installed++;
            }else if(aux == "upgrade"){ 
                char * packageName =  nombrePaquete(line, bytes);
                for(int i =0; i<1000; i++){
                    if(strcmp(packs[i].name,packageName)==0){
                        strcpy(packs[i].lastUpdate,fechaPaquete(line, bytes));
                        if(packs[i].upgrades==0){
                            upgraded++;
                        }
                        packs[i].upgrades++;
                        break;
                    }
                }
            }else if(aux == "remove"){ 
                char * packageName =  nombrePaquete(line, bytes);
                for(int i =0; i<1000; i++){
                    if(strcmp(packs[i].name,packageName)==0){
                        strcpy(packs[i].removalDate, fechaPaquete(line, bytes));
                        break;
                    }
                }
                removed++;
            }
        }
        bytes = 0;
        if(end==0){
            break;
        }
        free(line); 
    }

    if (close(file_descriptor) < 0)  
    { 
        perror("Log file could not be closed"); 
        exit(1); 
    }  



    write(wr, "Pacman Packages Report\n", strlen("Pacman Packages Report\n"));
    write(wr,"----------------------\n",strlen("----------------------\n"));
    write(wr, "Installed packages : ", strlen("Installed packages : "));
    char aux[20];
    sprintf(aux, "%d", installed);
    write(wr, aux, strlen(aux));
    write(wr, "\nUpgraded packages : ",strlen("\nUpgraded packages : "));
    sprintf(aux, "%d", upgraded);
    write(wr, aux, strlen(aux));
    write(wr, "\nRemoved packages : ",strlen("\nRemoved packages : "));
    sprintf(aux, "%d", removed);
    write(wr, aux, strlen(aux));
    write(wr, "\nCurrent installed : ",strlen("\nCurrent installed : "));
    sprintf(aux, "%d", (installed-removed));
    write(wr, aux, strlen(aux));

    //info
    write(wr, "\n\nList of packages\n", strlen("\n\nList of packages\n"));
    write(wr,"----------------------\n",strlen("----------------------\n"));

    for(int i = 0; i<1000;i++){
        if(strcmp(packs[i].name,"")!=0){
            write(wr, "- Package name         : ",strlen("- Package name         : "));
            write(wr,packs[i].name, strlen(packs[i].name));
            write(wr, "\n   - Install date      : ",strlen("\n   - Install date      : "));
            write(wr,packs[i].installDate, strlen(packs[i].installDate));
            write(wr, "\n   - Last update date  : ",strlen("\n   - Last update date  : "));
            write(wr,packs[i].lastUpdate, strlen(packs[i].lastUpdate));
            write(wr, "\n   - How many updates  : ",strlen("\n   - How many updates  : "));
            sprintf(aux, "%d", packs[i].upgrades);
            write(wr,aux, strlen(aux));
            write(wr, "\n   - Removal date      : ",strlen("\n   - Removal date      : "));
            write(wr,packs[i].removalDate, strlen(packs[i].removalDate));
            write(wr, "\n",strlen("\n"));
        }
    }

    if (close(wr) < 0)  
    { 
        perror("Report file could not be closed"); 
        exit(1); 
    } 

    printf("Report is generated at: [%s]\n", report);
}
