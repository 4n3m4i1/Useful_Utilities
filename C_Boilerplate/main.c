#include <stdio.h>
#include <inttypes.h>

/*
    Arguments/Parameters

    // Filename
    -n  Default {main.c}
                {any}

    // Return type
    -r  Default {void, v}
                {int, i}
                {float, f}
                {double, d}

    // Argument field filled?
    -a  Default   {yes, y}
                    {no, n}

    // Included Headers
    -i
*/
#define NAME_OPT    'n'
#define RETURN_OPT  'r'
#define ARGS_OPT    'a'
#define INCLUDE_OPT 'i'

enum RETURN_BREAK_STATE {
    STATE_OK,
    STATE_BAD_FLAG,
    STATE_MISSING_ARG
};

uint32_t hasher(char *tohash);
enum FLAG_IDXS {
    NAME_IDX,
    RETURN_TYPE_IDX,
    ARGS_FIELD_IDX,
    HEADERS_IDX
};

#define NUM_ARG_FLAGS       4
#define NUM_ARG_VARIANTS    4
uint32_t flag_hashes[NUM_ARG_FLAGS][NUM_ARG_VARIANTS];


int next_state_update(int idx, int max){
    int retval = STATE_OK;
    if(idx + 1 >= max){
        retval = STATE_MISSING_ARG;
    }
    return retval;
}

char dfl_filename[] = "main.c";
char void_return_str[] = "";
char alt_return_str[] = "return retval;";
char full_main_str[] = "main(int argc, char **argv){";

char null_string[1] = "\0";

char void_str[] = "void";
char int_str[] = "int";
char float_str[] = "float";
char double_str[] = "double";

char dfl_include[] = "#include <stdio.h>\n#include <inttypes.h>";
char include_prefix[] = "#include ";
char stdio_hdr[] = "<stdio.h>";

void main(int argc, char **argv){
//    for(int n = 0; n < NUM_ARG_FLAGS; ++n){
//        for(int m = 0; m < NUM_ARG_VARIANTS; ++m){
//            flag_hashes[n][m] = hasher()
//        }
//    }
    int retval = STATE_OK;

    char *fname = dfl_filename;
    int num_includes = 2;
    char *include_string = dfl_include;
    char *main_str = full_main_str;
    char *ret_type_str = void_str;

    for(int n = 1; n < argc; ++n){
        if(argv[n][0] == '-'){
            if(STATE_OK == (retval = next_state_update(n, argc))){
                switch(argv[n][1]){
                    case NAME_OPT:
                        fname = argv[++n];
                    break;
                    case RETURN_OPT:

                    break;
                    case ARGS_OPT:

                    break;
                    case INCLUDE_OPT:{

                        break;
                    }
                    default:
                        printf("Unknown Argument: %s\r\n", argv[n]);
                        retval = STATE_BAD_FLAG;
                    break;
                }            
            } else {
                printf("Error on Argument Parse!\r\n");
                break;
            }
        }
    }

    if(retval == STATE_OK){
        FILE *fp;
        fp = fopen(fname, "w");

        fprintf(fp, "%s\n\n\n", include_string);
        fprintf(fp, "%s %s\n", ret_type_str, main_str);
        fprintf(fp, "\n\n\n\n%s\n}", (ret_type_str == void_str) ? "\0" : ret_type_str);

        fclose(fp);
    }

}



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