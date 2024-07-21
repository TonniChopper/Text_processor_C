# Text_processor_C
Text Processing Tool  This tool processes text input based on various options provided through command-line arguments. It supports removing digits and punctuation, replacing specific words or phrases, and formatting the output in a specified style.
## Command-Line Options

The program is controlled using the following command-line options:

- `-d`: Remove digits from the text.
- `-p`: Remove punctuation from the text.
- `-s`: Apply styled output formatting.
- `-r <string>`: Replace words with `<string>`, case-sensitive.
- `-R <string>`: Replace words with `<string>`, case-insensitive.

## Input Handling

You can provide text input to the program in two ways:

- **Standard Input**: You can enter text directly into the console. The program reads lines from standard input until two consecutive newline characters are encountered.

- **File Input**: You can also redirect text from a file into the program. Use input redirection to supply the contents of a file:

  ```
  ./text_processor [options] < input_file.txt
  ```
In both cases, the program will process the text according to the provided options and display the results on the standard output.
## Examples

### Remove Digits and Punctuation
```
./text_processor -d -p
```
This will remove all digits and punctuation from the input text.

### Replace Words with Case Sensitivity
```
./text_processor -r "replacement" prefix1 prefix2
```
This will replace occurrences of words starting with `prefix1` or `prefix2` with the word `"replacement"`, considering case sensitivity.

### Styled Output
```
./text_processor -s -r "replace" prefix1 prefix2
```
This will replace occurrences of words starting with `prefix1` or `prefix2` with the word `"replace"`, and display the output in a styled format.

### No Replacements, Just Formatting
```
./text_processor -s
```
This will format the input text according to the specified style without replacing any words.

## Functions

- `nacitavanie(char list[])`: Reads lines from standard input until two consecutive newline characters are encountered.
- `vypis_t(const char* text)`: Prints the given text to standard output.
- `remove_(int d, int p, char *text, char *vystup)`: Removes digits and/or punctuation from the text based on the flags provided.
- `find_and_replace(char *text, char *replace_string, char **prefixes, int num_prefixes, int case_sensitive, int argc)`: Finds and replaces words in the text according to the provided prefixes and replacement string.
- `print_output(const char *input_text, const char *replacement_text)`: Prints the text with replacements in a styled format.
