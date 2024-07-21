#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define MAX_LINE_LENGTH 1001

char *nacitavanie(char list[]){
    char line[MAX_LINE_LENGTH];
    int stop = 0;
    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        if (line[0] == '\n') {
            stop += 1;
        } else
            stop = 0;
        if (stop == 2)
            break;
        strcat(list,line);
//        for (int i = 0; i < strlen(list); ++i) {
//            if(list[i] == '\n' && list[i+1] == '\0'){
//                list[i] = '\0';
//            }
//        }
    }
    return list;
}
void vypis_t(const char* text){
    for (int i = 0; text[i]!='\0'; ++i) {
        printf("%c", text[i]);
    }
}

char *remove_(int d, int p, char *text,char *vystup){
    int count = 0;
    for (int i = 0; i < strlen(text); i++) {
            if (d && isdigit(text[i])) {
                continue;
            } else if (p && ispunct(text[i])) {
                continue;
            }
            vystup[count] = text[i];
            count++;
    }
    return vystup;
}

char *find_and_replace(char *text, char *replace_string, char **prefixes, int num_prefixes, int case_sensitive,int argc) {
    int j;
    char *word_start;
    int word_end, word_start_ind;
    char *prefix;
    int found_prefix;
    for (int i = 0; text[i] != '\0'; ++i) {
        if (!isalpha(text[i])) {
            continue;
        }
        word_start_ind = i;
        word_start = &text[i];
        int count = 0;
        if(num_prefixes==0){
            for (int l = i; isalpha(text[l]); ++l) {
                text[l] = replace_string[count];
                count++;
            }
            i += count;
            continue;
        }
        while (isalpha(text[word_start_ind])) {
            word_start_ind++;

        }
        word_end = word_start_ind;
        found_prefix = 0;
        if(num_prefixes>0) {
            for (j = 0; j < num_prefixes; j++) {
                prefix = prefixes[j];
                if (!case_sensitive) {
                    if (strncasecmp(word_start, prefix, strlen(prefix)) == 0) {
                        found_prefix = 1;
                        if (isalpha(text[i - 1]))
                            found_prefix = 0;
                        break;
                    }
                } else {
                    if (strncmp(word_start, prefix, strlen(prefix)) == 0) {
                        found_prefix = 1;
                        if (isalpha(text[i - 1]))
                            found_prefix = 0;
                        break;
                    }
                }
            }
        }
        if (found_prefix) {
            int count = 0;
            for (int l = i; l < word_end; ++l) {
                text[l] = replace_string[count];
                count++;
                if (count > strlen(replace_string)-1) {
                    text[l] = text[l];
                    break;
                }
            }
        }
    }
    return text;
}
void print_output(const char *input_text, const char *replacement_text) {
    char *input_copy = strdup(input_text);
    char *replacement_copy = strdup(replacement_text);


    char *sentence_delimiters = "\n";
    char *sentence = strtok(input_copy, sentence_delimiters);
    char *sentences[100];
    int sentence_count = 0;


    while (sentence != NULL) {
        sentences[sentence_count] = sentence;
        sentence = strtok(NULL, sentence_delimiters);
        sentence_count++;
    }


    char *word_delimiters = " ?._-=+,!:;*&^@#$%'()[]{}0123456789\t\n\0\"";
    char *word_delimiters_r = " ?.-_=+,!:;*&^@#$%'()[]{}0123456789\t\n\0\"";
    char *words[100];
    int word_sentence_numbers[100];
    int word_count = 0 , max_length = 0;

    for (int i = 0; i < sentence_count; i++) {
        char *word = strtok(sentences[i], word_delimiters);
        while (word != NULL) {
            words[word_count] = word;
            word_sentence_numbers[word_count] = i + 1;
            if (strlen(word) > max_length) {
                max_length = strlen(word);
            }
            word_count++;
            word = strtok(NULL, word_delimiters);
        }
    }

    char *replacement = strtok(replacement_copy, word_delimiters_r);
    char *replacements[100];
    int replacement_count = 0;

    while (replacement != NULL) {
        replacements[replacement_count++] = replacement;
        if (strlen(replacement) > max_length) {
            max_length = strlen(replacement);
        }
        replacement = strtok(NULL, word_delimiters_r);
    }

    for (int i = 0; i < word_count; i++) {
        printf("%-d. %-*s:%-*s\n", word_sentence_numbers[i], max_length, words[i], max_length, (i < replacement_count) ? replacements[i] : words[i]);
    }
    free(input_copy);
    free(replacement_copy);
}

int main (int argc, char *argv[]) {
    int option, remove_digits = 0, remove_punc = 0, style = 0, case_sensitive = 0, st_arg = 0, pocet_pref = 0;
    char list[1001] = {0}, *replacing_string, *prefixes[20];
    while ((option = getopt(argc, argv, ":dpsr:R:")) != -1) {
        switch (option) {
            case ':':
                opterr = 0;
                printf("E2");
                return 0;
            case '?' :
                opterr = 0;
                printf("E1");
                return 0;
            case 'd':
                remove_digits = 1;
                break;
            case 'p':
                remove_punc = 1;
                break;
            case 's':
                style = 1;
                break;
            case 'r':
                replacing_string = strdup(optarg);
                case_sensitive = 1;
                st_arg = optind;
                if(strlen(replacing_string) <= 0 || strlen(replacing_string) > 20){
                    printf("E3");
                    return 0;
                }
                break;
            case 'R' :
                replacing_string = strdup(optarg);
                case_sensitive = 0;
                st_arg = optind;
                if(strlen(replacing_string) <= 0 || strlen(replacing_string) > 20){
                    printf("E3");
                    return 0;
                }
                break;
            default:
                vypis_t(list);
                break;
        }
    }
    nacitavanie(list);
    char *processed_lines = malloc(sizeof(char) * strlen(list));
    char *new_processed_lines = malloc(sizeof(char) * strlen(list));
    remove_(remove_digits, remove_punc, list, processed_lines);
    new_processed_lines = strcpy(new_processed_lines, processed_lines);
    if (replacing_string != NULL) {
        int count = 0;
        for (int i = st_arg; i < argc; ++i) {
            prefixes[count] = argv[i];
            count++;
        }
        pocet_pref = argc - st_arg;
        char *new_text;
        if(remove_digits || remove_punc) {
            new_text = find_and_replace(new_processed_lines, replacing_string, prefixes, pocet_pref, case_sensitive, argc);
            if (style) {
                print_output(processed_lines, new_text);
            } else
                vypis_t(new_text);
        }
        else {
            new_text = find_and_replace(processed_lines, replacing_string, prefixes, pocet_pref, case_sensitive, argc);
            if (style) {
                print_output(list, new_text);
            } else
                vypis_t(new_text);
        }
    }else
        if (style) {
            print_output(processed_lines, processed_lines);
        } else
            vypis_t(processed_lines);
    free(processed_lines);
    free(new_processed_lines);
    free(replacing_string);
    return 0;
}
