#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *out;

void print_to_out(char s[]){
    fprintf(out, "%s\n", s);
}

int main()
{
    char ch, file_name[25];
    FILE *fp;
    

    printf("Enter name of a file you wish to compile to C\n");
    gets(file_name);

    fp = fopen(file_name, "r"); // read mode

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }


    out = fopen("out/output.c", "w");

    print_to_out("#include <stdio.h>");
    print_to_out("#include <stdlib.h>");
    print_to_out("int main(){");
    print_to_out("u_int8_t memory[255] = {};");
    print_to_out("u_int8_t pointer = 0;");
    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
        switch(ch) {
            case '[':
                print_to_out("while (memory[pointer] != 0) {");
                break;
            case ']':
                print_to_out("}");
                break;
            case '+':
                print_to_out("memory[pointer]++;");
                break;
            case '-':
                print_to_out("memory[pointer]--;");
                break;
            case '<':
                print_to_out("pointer--;");
                break;
            case '>':
                print_to_out("pointer++;");
                break;
            case '.':
                print_to_out("printf(\"%c\", memory[pointer]);");
                break;
            case ',':
                print_to_out("memory[pointer] = getchar();");
                break;
            default:
                break;
        }
    }
    print_to_out("}");

    fclose(fp);
    fclose(out);
    return 0;
}
