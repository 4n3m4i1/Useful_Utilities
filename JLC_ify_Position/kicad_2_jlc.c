/*
    Kicad 7 BOM and Position -> JLC PCBA Files
    This just changes the headers and some other things

    Standard non grouped BOM only!!
*/
#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>

#define TMP_LEN     512

const char jlc_pos_hdr[] = "\"Designator\",\"Val\",\"Package\",\"Mid X\",\"Mid Y\",\"Rotation\",\"Layer\"\n";
const char jlc_bom_hdr[] = "\"Designator\",\"Qty\",\"Value\",\"Footprint\",\"LCSC Part Number\"\n";

#define ARG_CHAR    '-'
#define DELIMITER   ','
// magic hashed numbers
#define ARG_pos     0x000031B2
#define ARG_POS     0x000023D2
#define ARG_p       0x00000070
#define ARG_P       0x00000050

#define ARG_bom     0x00002F4C
#define ARG_BOM     0x0000216C
#define ARG_b       0x00000062
#define ARG_B       0x00000042

uint32_t hasher(char *tohash){                      // Returns unique 32 bit hash per input string
    uint32_t t_sum = 0;
    uint32_t scalar = 1;

    for(int n = 0; n < 24; n++){
        if((tohash[n] < 0x7b && tohash[n] > 0x40) || (tohash[n] < 0x3A && tohash[n] > 0x2F)){   // Generate hash from valid chars
            t_sum += scalar * (uint32_t)tohash[n];
            scalar *= 10;
        }
        if(!tohash[n + 1]){                         // Break loop if next char is terminator
            break;
        }
    }

    return t_sum;
}

void skip_col(FILE *fp){
    if(fp){
        char a = getc(fp);
        if(a == '"'){           // Skip "" fields that have , in them
            int chk = 1;
            while((((a = getc(fp)) != (int)DELIMITER) && a != EOF) || chk){
                if(a == '"') chk = 0;
            }
        } else {
            while(((a = getc(fp)) != (int)DELIMITER) && a != EOF);
        }
    }
}

int extract_and_append_filename(char *dst, char *src, char *append){
    int retval = 0;
    if(dst && src){
        int n;
        for(n = 0; src[n] != '.'; ++n) dst[n] = src[n];
        for(int m = 0; append[m]; ++m) dst[n + m] = append[m];
        retval = 1;
    }
    return retval;
}

int diy_readline(FILE *fp, char *retstr, int *rlen){
    int retval = -1;
    if(fp && retstr && rlen){
        int n;
    }
}

void zero_tmp(char *tmp){
    if(tmp){
        for(int n = 0; n < TMP_LEN; ++n) tmp[n] = 0x00;
    }
}

void main(int argc, char **argv){
    char tmp[TMP_LEN] = {0x00};

    char pos_msg[] = "_JLC_pos_fmt.csv";
    char bom_msg[] = "_JLC_BOM_fmt.csv";

    FILE    *fp;
    FILE    *opfp;

    if(argc > 1){
        for(int n = 1; n < argc; ++n){
            zero_tmp(tmp);
            switch(hasher(argv[n])){
                case ARG_pos:
                case ARG_POS:
                case ARG_p:
                case ARG_P:
                    if(n < argc && argv[n + 1][0] != ARG_CHAR){
                        fp = fopen(argv[++n], "r");
                        if(fp){
                            extract_and_append_filename(tmp, argv[n], pos_msg);
                            printf("Creating %s\n", tmp);
                            opfp = fopen(tmp, "w");
                            fprintf(opfp, "%s", jlc_pos_hdr);

                            fgets(tmp, TMP_LEN, fp);
                            while(fgets(tmp, TMP_LEN, fp)) fputs(tmp, opfp);

                            fclose(opfp);
                            fclose(fp);
                        } else {
                            printf("Position File: %s Not Found!\n", argv[n]);
                            return;    
                        }
                    } else {
                        printf("Position Filename Not Provided!\n");
                        return;
                    }
                break;

                case ARG_bom:
                case ARG_BOM:
                case ARG_b:
                case ARG_B:
                    if(n < argc && argv[n + 1][0] != ARG_CHAR){
                        fp = fopen(argv[++n], "r");
                        if(fp){
                            extract_and_append_filename(tmp, argv[n], bom_msg);
                            printf("Creating %s\n", tmp);
                            opfp = fopen(tmp, "w");
                            fprintf(opfp, "%s", jlc_bom_hdr);

                            fgets(tmp, TMP_LEN, fp);
                            skip_col(fp); // skip #
                            //skip_col(fp); // skip Designator
                            while(fgets(tmp, TMP_LEN, fp)){
                                fputs(tmp, opfp);
                                skip_col(fp);
                                //skip_col(fp);
                            }

                            fclose(opfp);
                            fclose(fp);
                        } else {
                            printf("Position File: %s Not Found!\n", argv[n]);
                            return;    
                        }
                    } else {
                        printf("BOM Filename Not Provided!\n");
                        return;
                    }
                break;

                default:
                    printf("Unrecognized Parameter:\n\t%s\n", argv[n]);
                    return;
                break;
            }
        }
    } else {
        printf("No Arguments Provided! :(\n");
    }
}


