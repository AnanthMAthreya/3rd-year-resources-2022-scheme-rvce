#include<stdio.h>

unsigned fields[10];

unsigned short checksum(){
    int i;
    int sum=0;
    printf("Enter IP header information in 16 bit words\n");

    for(i=0; i<10;i++){
        // printf("Field %d\n", i+1);
        scanf("%x", &fields[i]);
        sum = sum + (unsigned short) fields[i];
        while (sum>>16)
            sum = (sum & 0xFFFF) + (sum >> 16);
    }

    sum =~ sum;

    return (unsigned short)sum;
}

int main(){
    unsigned short result1, result2;

    //Sender
    result1 = checksum();
    printf("\nComputer Checksum at sender: %x\n", result1);
    //Receiver
    result2 = checksum();
    printf("\nComputerd Checksum at receiver: %x\n", result2);

    if (result2 == 0x0000)
        printf("No error");
    else
        printf("Error in Data received");
    
    return 0;
}