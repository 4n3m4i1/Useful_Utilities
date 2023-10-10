#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


#define PRINT_BIN_VALUE     (1 << 0)
#define PRINT_LEN           (0xF0)
#define PRINT_8             (1 << 4)
#define PRINT_16            (1 << 5)
#define PRINT_32            (1 << 6)
#define PRINT_64            (1 << 7)

union DispType {
    double fl;
    uint64_t ival;
};

void print_bin8(uint64_t val);
void print_bin16(uint64_t val);
void print_bin32(uint64_t val);
void print_bin64(uint64_t val);

double input;

void main(int argc, char **argv){
    uint16_t arg_w_val = 1;

    // Options for extended printing
    uint16_t print_options = 0;

    if(argc > 1){
        for(int n = 1; n < argc; ++n){
            if(argv[n][0] == '-'){
                switch(argv[n][1]){
                    case 'b':
                    case 'B':
                        arg_w_val += 1;
                        print_options |= PRINT_BIN_VALUE;
                    break;

                    case 'l':
                    case 'L':
                        if(n < (argc - 1)){
                            uint32_t shif = strtoul(argv[++n],NULL,10);
                            switch(shif){
                                case 8:
                                    print_options |= PRINT_8;
                                break;
                                case 16:
                                    print_options |= PRINT_16;
                                break;
                                case 32:
                                    print_options |= PRINT_32;
                                break;
                                case 64:
                                    print_options |= PRINT_64;
                                break;
                                default:
                                    printf("\nUnrecognized -L Argument!!\n");
                                    return;
                                break;
                            }
                            //printf("Len: %d\n",shif);
                            arg_w_val += 2;
                        } else {
                            printf("No -L argument provided!\n");
                        }
                    break;

                    case '-':
                        printf("Quick Converter Help\n");
                        printf("-b\t\tPrints Binary Output\n");
                        printf("-l {8,16,32,64}\tSpecifies Length of Output Data, Default: 32\n");
                        printf("Bye!\n");
                        return;
                    break;
                }
            }
        }
        
        if(!(print_options & PRINT_LEN)) print_options |= PRINT_32;

        
        char *strpt;

        input = strtod(argv[arg_w_val], &strpt);
        //input = strtod(innstr, &strpt);

        uint64_t in_int = (uint64_t)input;
        int64_t  in_inst = (int64_t)input;

        //printf("\nInput: %f\n", input);
        if(print_options & PRINT_64){
            printf("\nDouble Representation\tInt Representation\n");
            printf("LF: %lf\n\t\t\tD: ", input);
        } else {
            printf("\nFloat Representation\tInt Representation\n");
            printf("F: %f\n\t\t\tD: ", (float)input);
        }
        
        switch(print_options & PRINT_LEN){
            case PRINT_8:
                printf("%10d",(int8_t)in_inst);
            break;
            case PRINT_16:
                printf("%10d",(int16_t)in_inst);
            break;
            case PRINT_32:
                printf("%10ld",(int32_t)in_inst);
            break;
            case PRINT_64:
                printf("%10lld",in_inst);
            break;
        }
        printf("\n\t\t\tU: ");
        switch(print_options & PRINT_LEN){
            case PRINT_8:
                printf("%10u",(uint8_t)in_int);
            break;
            case PRINT_16:
                printf("%10u",(uint16_t)in_int);
            break;
            case PRINT_32:
                printf("%10lu",(uint32_t)in_int);
            break;
            case PRINT_64:
                printf("%10llu", in_int);
            break;
        }

        if(print_options & PRINT_64){
            uint64_t *aahh = (uint64_t *)&input;
            printf("\n\nFLOAT H: 0x%016llX\nINT   H: 0x%016llX\n\n", *aahh, in_int);
        } else {
            float ppp = (float)input;
            uint32_t *aahh = (uint32_t *)&ppp;
            printf("\nH: 0x%08X\t\tH: ", *aahh);
            switch(print_options & PRINT_LEN){
                case PRINT_8:
                    printf("      0x%02X",(uint8_t)in_int);
                break;
                case PRINT_16:
                    printf("    0x%04X",(uint16_t)in_int);
                break;
                case PRINT_32:
                    printf("0x%08lX",(uint32_t)in_int);
                break;
                case PRINT_64:
                    //printf("0x%16llX", in_int);
                    printf("0x%#018" PRIx64 "",in_int);
                break;
            }
            printf("\n\n");   
        }


        if(print_options & PRINT_BIN_VALUE){
            if(print_options & PRINT_64){
                printf("Double Binary\t");
                uint64_t *aahh = (uint64_t *)&input;
                print_bin64(*aahh);
            } else {
                float ppp = (float)input;
                uint64_t *aahh = (uint64_t *)&ppp;
                printf("Float Binary\t");
                print_bin32(*aahh);
            }
            
            printf("\nInt Binary\t");
            switch(print_options & PRINT_LEN){
            case PRINT_8:
                print_bin8(in_int);
            break;
            case PRINT_16:
                print_bin16(in_int);
            break;
            case PRINT_32:
                print_bin32(in_int);
            break;
            case PRINT_64:
                print_bin64(in_int);
            break;
        }
            printf("\n");
        }

    }
}

void print_bin8(uint64_t val){
    printf("0b");
    for(int n = 0; n < 8; n++){
        if(val & (1 << (7 - n))) printf("1");
        else printf("0");
    }
}

void print_bin16(uint64_t val){
    printf("0b");
    for(int n = 0; n < 16; n++){
        if(val & (1 << (15 - n))) printf("1");
        else printf("0");
    }
}

void print_bin32(uint64_t val){
    printf("0b");
    for(int n = 0; n < 32; n++){
        if(val & (1 << (31 - n))) printf("1");
        else printf("0");
    }
}

void print_bin64(uint64_t val){
    printf("0b");
    for(unsigned int n = 0; n < 64; n++){
        if(val & (1llu << (63 - n))) printf("1");
        else printf("0");
    }
}




