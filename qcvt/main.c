#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


#define PRINT_BIN_VALUE     (1 << 0)

union DispType {
    float fl;
    uint32_t ival;
};

void print_bin32(uint32_t val);

void main(int argc, char **argv){
/*
    printf("Argc = %2d\nInput: %s\n", argc, argv[1]);

    for(int n = 0; n < 10; n++){
        if(argv[1][n] && argv[1][n] != ' '){
            printf("%2X ", argv[1][n]);
        }
    }

    printf("\n");
*/
    union DispType dispval;

    uint16_t arg_w_val = 1;

    // Options for extended printing
    uint16_t print_options = 0;

    if(argc > 1){
        if(argc > 2 && argv[1][0] == '-'){
            arg_w_val = 2;
            // Check args
            if(argv[1][1] == 'b' || argv[1][1] == 'B'){
                print_options |= PRINT_BIN_VALUE;
            }
        }

        
        double input;
        char *strpt;

        input = strtod(argv[arg_w_val], &strpt);
        //input = strtod(innstr, &strpt);

        uint32_t in_int = (uint32_t)input;

        dispval.fl = (float)input;

        printf("\nInput: %f\n", input);
        printf("Float Representation\tInt Representation\n");
        printf("F: %f\t\tS: %8d\n", dispval.fl, (int32_t)in_int);
        printf("\t\t\tU: %8u\n", in_int);
        printf("H: 0x%08X\t\tH: 0x%08X\n\n", dispval.ival, in_int);


        if(print_options & PRINT_BIN_VALUE){
            printf("Float Binary\t");
            print_bin32(dispval.ival);
            printf("\nInt Binary\t");
            print_bin32(in_int);
            printf("\n");
        }

    }
}


void print_bin32(uint32_t val){
    printf("0b");
    for(int n = 0; n < 32; n++){
        if(val & (1 << (31 - n))) printf("1");
        else printf("0");
    }
}




