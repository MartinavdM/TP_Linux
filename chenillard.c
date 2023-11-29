#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_LEDS 9

int main(void)
{
    FILE * LED[NUM_LEDS];

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
    while(1)
    { 
        for(int i = 0; i<NUM_LEDS; i++)
        {
            if(i != 0)
            {
                printf("led %d OFF\r\n",(i-1));
                fprintf(LED[i-1],"0");
                fflush(LED[i-1]);
            }
            else
            {
                printf("last led OFF\r\n");
                fprintf(LED[NUM_LEDS-1],"0");
                fflush(LED[NUM_LEDS-1]);
            }
            printf("led %d\n\r",i);
            fprintf(LED[i],"1");
            fflush(LED[i]);
            usleep(50000);
        }
    }
    return 0;

}