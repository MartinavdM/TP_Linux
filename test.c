#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
    FILE * LED[9];


    for(int index = 0; index < 9; index++)
    {
        char name[300];
        snprintf(name,300,"/sys/class/leds/fpga_led%d/brightness", index+1);
        printf("sprint reussi %d\n\r",index);
        LED[index] = fopen(name,"w");
        if(LED[index]==NULL)
        {
            printf("Erreur lors de l'ouverture d'un fichier");
            exit(1);
        }
    }


    for(int i = 0; i<9; i++)
    {
        if(i != 0)
        {
            printf("led %d OFF\r\n",(i-1));
            fprintf(LED[i-1],"0");
            fflush(LED[i-1]);
            fclose(LED[i-1]);
        }
        printf("led %d\n\r",i);
        fprintf(LED[i],"1");
        fflush(LED[i]);
        usleep(200000);
    }
    return 0;


}
