/**
 * pa4/dictionary.c
 *
 * The dictionary linked list interface.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

struct dict_entry *new_entry(const char *word, const char *definition)
{
    struct dict_entry *x = (struct dict_entry*)malloc(sizeof(struct dict_entry));
    strcpy(x->word,word);
    int p = strlen(definition);
    x->definition = calloc((p+1), sizeof(char));
    strcpy(x->definition,definition);
    return x;
}

void free_entry(struct dict_entry *entry)
{
    free(entry);
}

void dict_insert_sorted(struct dictionary *dict, struct dict_entry *entry)
{
    char *eword = entry->word;

    if(dict->list == NULL){
        dict->list = entry;
        dict->size += 1;
        return;
    }
    struct dict_entry *curr = dict->list;
    char *cword = curr->word;

    if(strcmp(eword,cword) < 0){
        dict->list = entry;
        dict->size += 1;
        entry->next = curr;
        return;
    }
    struct dict_entry *prev = curr;
    while (curr != NULL ) {
        prev = curr;

        curr = curr->next;
        cword = curr->word;
        if(curr == NULL){
            break;
        }

        if(strcmp(eword,cword) > 0){
            continue;
        }else{
            entry->next = curr;
            prev->next = entry;
            dict->size += 1;
            return;
        }
    }
    prev->next = entry;
    entry->next = NULL;
    dict->size += 1;
}

void dict_remove_word(struct dictionary *dict, const char *word)
{
   struct dict_entry *x = dict->list;
   struct dict_entry *temp = dict->list;

   if (temp != NULL && strcmp(temp->word , word)==0) {
        x = temp->next; 
        free(temp);
        dict->size -= 1;
        return;
   }

   while (x != NULL){
        temp = x;
        x = x->next;
        if(x != NULL && strcmp(x->word ,word)==0){
            temp->next = x->next;
            dict->size -= 1;
            free(x);
            return;
        }
   } 
    
   if(temp == NULL){
       return;
   }
    printf("Cannot find \"%s\" in dictionary.\n", word);
   return;

}

struct dict_entry *dict_lookup(struct dictionary *dict, const char *word)
{
   struct dict_entry *x = dict->list;

   while (x != NULL)
    {
       
        if(strcmp(x->word , word)==0){
            return x;
        }
       x = x->next;
    }

    return NULL;
}

void free_dictionary(struct dictionary *dict)
{
   struct dict_entry *tmp;
   struct dict_entry *x = dict->list;
   if(x == NULL){
       return;
   }
   while (x != NULL)
    {
       tmp = x;
       x = x->next;
       free(tmp);
    }
    free(dict);
}

void print_dictionary(struct dictionary *dict)
{
    struct dict_entry *x = dict->list;
    while (x != NULL) {
        printf(" %s ", x->word);
        x = x->next;
    }
}

void print_word_list(struct dictionary *dict)
{
    struct dict_entry *x = dict->list;
    while (x != NULL) {
        printf(" %s ", x->word);
        x = x->next;
    }
}

void print_word(struct dict_entry *entry)
{
    printf("%s\n", entry->word);
    printf("  %s\n", entry->definition);
    
}

struct dictionary *load_dictionary(const char *filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    struct dictionary *dict;
    if (!(dict = malloc(sizeof(*dict)))) {
        perror("malloc");
        return NULL;
    }

    dict->size = 0;
    dict->list = NULL;

    if (!filename) {
        return dict;
    }

    if (!(fp = fopen(filename, "r"))) {
        perror("fopen");
        return NULL;
    }

    while ((nread = getline(&line, &len, fp)) != -1) {
        char *word = strtok(line, ":");
        char *definition = strtok(NULL, "\n");
        while (*definition == ' ')
            definition++;
        struct dict_entry *entry = new_entry(word, definition);
        dict_insert_sorted(dict, entry);
    }
    free(line);

    return dict;
}
