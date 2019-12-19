#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main() {
    std::cout << "size_t size:" << sizeof(size_t) << std::endl;
    unsigned char* pic1 = (unsigned char*)malloc(0x100000);
    // unsigned char* pic2 = (unsigned char*)malloc(0x2000);

    printf("pic1 = %p\n", pic1);
    // printf("pic2 = %p\n", pic2);
    printf("pic1 pre 16:\n");
    for (int i = 0; i < 16; i++) {
        printf("%0x ", *(pic1 - 16 + 15 - i));
    }
    // printf("\npic2 pre 16:\n");
    // for (int i = 0; i < 16; i++)
    // {
    //         printf("%0x ", *(pic2 - 16 + 15 - i));
    // }

    //        printf("pic2 = %p\n", pic2);

    for (int i = 0; i < 0x100000; i++) {
        *(pic1 + i) = i & 0xFF;
    } 
     printf("\npic1 after 16:\n");

    for (int i = 0; i < 16; i++) {
        printf("%0x ", *(pic1 + 0x100000 + 15 - i));
    }
        // for (int i = 0x1000; i < 0x1008; i++) {
        //     *(pic1 + i) = 0xff;
        // }
         //*(pic1 + 0x1009) = 1;
    //     for (int i = 0x1010; i < 0x1050; i++) {
    //         *(pic1 + i) = i & 0xFF;
    //     }

  
    printf("\n1111111111\n");
    // printf("pic = %d\n", pic1[0x1010]);

    free(pic1);
    printf("pic1 = %p\n", pic1);

    printf("\npic1 pre 16:\n");
    for (int i = 0; i < 16; i++) {
        printf("%0x ", *(pic1 - 16 + 15 - i));
    }
    printf("\npic1 after 16:\n");

    for (int i = 0; i < 16; i++) {
        printf("%0x ", *(pic1 + 0x100000 + 15 - i));
    }
    printf("\n222222222\n");
    //        free(pic2);

    printf("3333333333\n");
    return 0;
}