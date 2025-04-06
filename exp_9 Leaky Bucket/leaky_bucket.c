#include<stdio.h>

int main(){

    int bucket_size,outgoing_rate,inputs;
    int incomming_packet;
    int store;

    printf("Enter Bucket Size,outgoing Rate,number of inputs : ");
    scanf("%d%d%d",&bucket_size,&outgoing_rate,&inputs);


    while (inputs != 0){
        printf("Enter Incomming packet size : ");

        scanf("%d",&incomming_packet);

        if (incomming_packet <= (bucket_size - store)){
            store += incomming_packet;

            printf("Before outgoing buv")
        }
    }
    
}