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

void print_bin8(uint64_t val, uint8_t radix);
void print_bin16(uint64_t val, uint8_t radix);
void print_bin32(uint64_t val, uint8_t radix);
void print_bin64(uint64_t val, uint8_t radix);

double input;

uint8_t int_len = 0;
uint8_t frac_len;

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

                    case 'f':
                    case 'F':
                        if(n < (argc - 2)){
                            int_len = (uint8_t)strtoul(argv[++n], NULL, 10);
                            frac_len = (uint8_t)strtoul(argv[++n], NULL, 10);

                            switch(int_len){
                                case 8:
                                break;
                                case 16:
                                break;
                                case 32:
                                break;
                                case 64:
                                break;
                                default:
                                    printf("Nonstandard Int Length!\n");
                                    return;
                                break;
                            }

                            if(frac_len >= int_len){
                                printf("Fractional Length Greater Than Integer Length!\n");
                                return;
                            }

                            arg_w_val += 3;
                        } else {
                            printf("Incorrect Fixed Point I.F Format Entered!\n");
                            return;
                        }

                    break;

                    case '-':
                        printf("Quick Converter Help\n");
                        printf("-b\t\tPrints Binary Output\n");
                        printf("-l {8,16,32,64}\tSpecifies Length of Output Data, Default: 32\n");
                        printf("-f {TypeLen} {Frac Bits}\tFixed Point Radix Converter\n");
                        printf("Bye!\n");
                        return;
                    break;
                }
            }
        }
        
        if(!(print_options & PRINT_LEN)) print_options |= PRINT_32;

        // fixed point overrides print option of length
        if(int_len){
            print_options &= ~(PRINT_LEN);
            switch(int_len){
                case 8:
                    print_options |= PRINT_8;
                case 16:
                    print_options |= PRINT_16;
                break;
                case 32:
                    print_options |= PRINT_32;
                break;
                case 64:
                    print_options |= PRINT_64;
                break;
            }
        }
        
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
                print_bin64(*aahh, 0);
            } else {
                float ppp = (float)input;
                uint64_t *aahh = (uint64_t *)&ppp;
                printf("Float Binary\t");
                print_bin32(*aahh, 0);
            }
            
            printf("\nInt Binary\t");
            switch(print_options & PRINT_LEN){
            case PRINT_8:
                print_bin8(in_int, int_len);
            break;
            case PRINT_16:
                print_bin16(in_int, int_len);
            break;
            case PRINT_32:
                print_bin32(in_int, int_len);
            break;
            case PRINT_64:
                print_bin64(in_int, int_len);
            break;
        }
            printf("\n");
        }

        if(int_len){
            printf("\nQ%u.%u Fixed Point:\n", int_len, frac_len);
            uint64_t radix = (1u << frac_len);
            //double input_mag = (input < 0) ? input * -1.0 : input;
            //if((input_mag - (double)in_inst) < 0) printf("F:\t%.14lf\n", input / (double)radix);
            //else {
                in_int = (int64_t)(((double)radix) * input);

                uint8_t hasfrac = 0;

                if(input - (double)in_inst){
                    printf("HasFrac\n");
                    hasfrac = 1;
                } else {
                    printf("NoFrac\n");
                }
                
                switch(print_options & PRINT_LEN){
                    case PRINT_8: {
                        int8_t fl_cvt_back = (int8_t)in_inst;
                        if(hasfrac){
                            printf("F:          %.14lf\n", ((double)fl_cvt_back / (double)radix));
                            printf("S: %10d\n", (int8_t)(input * (double)radix));
                            printf("H:        0x%02X",(uint8_t)(input * (double)radix));
                        } else {
                            printf("F:          %.14lf\n", (input / (double)radix));
                            printf("S: %10d\n", fl_cvt_back);
                            printf("H:        0x%02X",(uint8_t)in_inst);
                        }
                    }
                    break;
                    case PRINT_16: {
                        int16_t fl_cvt_back = (int16_t)in_inst;
                        if(hasfrac){
                            printf("F:          %.14lf\n", ((double)fl_cvt_back / (double)radix));
                            printf("S: %10d\n", (int16_t)(input * (double)radix));
                            printf("H:     0x%04X", (uint16_t)(input * (double)radix));
                        } else {
                            printf("F:          %.14lf\n", (input / (double)radix));
                            printf("S: %10d\n", fl_cvt_back);
                            printf("H:     0x%04X",(uint16_t)in_inst);
                        }
                        
                    }
                    break;
                    case PRINT_32: {
                        int32_t fl_cvt_back = (int32_t)in_inst;
                        if(hasfrac){
                            printf("F:          %.14lf\n", ((double)fl_cvt_back / (double)radix));
                            printf("S: %10ld\n", (int32_t)(input * (double)radix));
                            printf("H: 0x%08lX",(uint32_t)(input * (double)radix));
                        } else {
                            printf("F:          %.14lf\n", (input / (double)radix));
                            printf("S: %10ld\n", fl_cvt_back);
                            printf("H: 0x%08lX",(uint32_t)in_inst);
                        }
                        
                    }
                    break;
                    case PRINT_64: {
                        if(hasfrac){
                            printf("F:          %.14lf\n", ((double)in_inst / (double)radix));
                            printf("S: %10lld\n", (int64_t)(input * (double)radix));
                            printf("H: 0x%#018" PRIx64 "", (uint64_t)(input * (double)radix));
                        } else {
                            printf("F:          %.14lf\n", (input / (double)radix));
                            printf("S: %10lld\n", in_inst);
                            printf("H: 0x%#018" PRIx64 "",in_int);
                        }
                        
                    }
                    break;
                }
                printf("\n\n");
            //}
        }

    }
}

void print_bin8(uint64_t val, uint8_t radix){
    printf("0b");
    for(int n = 0; n < 8; n++){
        if(radix && ((n - 1) == radix)) printf(".");
        if(val & (1 << (7 - n))) printf("1");
        else printf("0");
    }
}

void print_bin16(uint64_t val, uint8_t radix){
    printf("0b");
    for(int n = 0; n < 16; n++){
        if(radix && ((n - 1) == radix)) printf(".");
        if(val & (1 << (15 - n))) printf("1");
        else printf("0");
    }
}

void print_bin32(uint64_t val, uint8_t radix){
    printf("0b");
    for(int n = 0; n < 32; n++){
        if(radix && ((n - 1) == radix)) printf(".");
        if(val & (1 << (31 - n))) printf("1");
        else printf("0");
    }
}

void print_bin64(uint64_t val, uint8_t radix){
    printf("0b");
    for(unsigned int n = 0; n < 64; n++){
        if(radix && ((n - 1) == radix)) printf(".");
        if(val & (1llu << (63 - n))) printf("1");
        else printf("0");
    }
}




