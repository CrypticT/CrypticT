#include <string.h>
#include <ctype.h>
#include "index.h"
#include "map.h"
#include "printing.h"
#include "trie.h"
#include "list.h"

list_t *list_of_documents;
size_t doc_arr = 1000;

/*
 * Implement your index here.
 */
typedef struct index index_t;
typedef struct documents documents_t;
struct documents
{
    char **array;
    char *doc_name;
    unsigned int *amount_of_words;
};

struct index
{
    trie_t *index;
};

struct node
{
    node_t *node;
};
/*
 * Struct to hold a single search result.
 * Implement this to work with the search result functions.
 */

struct search_result
{
    list_t *query_list;
    list_t *res_list;
    char **document;
    int *pos;
    char *word;
    list_iter_t *res_next;
    list_iter_t *content_next;
    list_t *occurences;
};

// Compare to ints
static inline int cmp_ints(void *a, void *b)
{
    return *((int *)a) - *((int *)b);
}

// Compares two strings without case-sensitivity
static inline int cmp_strs(void *a, void *b)
{
    return strcasecmp((const char *)a, (const char *)b);
}

index_t *index_create()
{

    trie_t *idx = trie_create();
    list_of_documents = list_create(compare_strings);
    return idx;
}

void destroy_res(search_result_t *res)
{
    list_destroy(res->res_list);
    list_destroyiter(res->res_next);
    list_destroyiter(res->content_next);
    list_destroyiter(res->occurences);
    free(res);   
}
void destroy_list_of_docs(list_t *list)
{
    list_iter_t *iter = list_createiter(list);
    word_posistion_t *word;
    while(list_hasnext(iter))
    {
        word = list_next(iter);
        free(word);
    }
    list_destroy(list);
    free(iter);
}
void index_destroy(index_t *index)
{
    trie_destroy(index);
    destroy_list_of_docs(list_of_documents);
}

void index_add_document(index_t *idx, char *document_name, list_t *words)
{
    list_iter_t *iter = list_createiter(words);
    list_iter_t *next_word;
    int txtsize = 0;
    int wordpos = 0;
    int word_check = 0;
    documents_t *document = malloc(sizeof(document));
    document->doc_name = document_name;
    document->amount_of_words = 0;
    document->array = calloc(doc_arr, sizeof(char *));
    while (list_hasnext(iter) != 0)
    {
        char *elem = list_next(iter);
        int count = 0;
        next_word = iter;
        char *next_elem = list_next(next_word);
        for(int i = 0; next_elem[i] != '\0'; i++)
        {
            if(!isalpha(next_elem[i]))
            {
                i = 0;
                next_elem = NULL;
                next_elem = list_next(next_word);
                if(!list_hasnext(next_word))
                {
                    next_elem = NULL;
                    break;
                }
            }
            count++;
        }
        
        if (txtsize > doc_arr)
        {
            doc_arr *= 2;
            document->array = realloc(document->array, doc_arr * sizeof(char *));
        }
        document->array[txtsize] = elem;
        txtsize++;
        char *key = elem;
        for (int i = 0; key[i] != '\0'; i++)
        {
            if (isalpha(key[i]))
            {
                word_check++;
            }
            else
            {
                break;
            }
        }
        void *value = document_name;
        trie_insert(idx, key, value, wordpos, next_elem);
        if (word_check > 0)
        {
            wordpos++;
            document->amount_of_words++;
        }
        // iter has elem on its node, so now i have to add this element on to a node for the TRIE
    }
    list_addlast(list_of_documents, document);
}



search_result_t *index_find(index_t *idx, char *query)
{
    char *word;

    size_t amount_of_docs = 2;
    size_t amount_of_pos = 10;
    //splits words separeted by a space
    word = strtok(query, " ");
    while(word != NULL)
    {
        word = strtok(NULL, " ");
    }
    list_t *list = trie_find(idx, query);
    documents_t *doc;
    if(list != NULL)
    {
        search_result_t *res = malloc(sizeof(search_result_t));
        res->res_list = list;
        res->res_next = list_createiter(res->res_list);
        res->content_next = list_createiter(list_of_documents);
        res->occurences = list_createiter(res->res_list);
        return res;
    }
    return NULL;
    
    
}


char *autocomplete(index_t *idx, char *input, size_t size)
{
    char *suggestion;
    if (size > 3)
    {
        suggestion = trie_autocomplete(idx, input);
    }
    if (suggestion != NULL)
    {
        return suggestion;
    }
    return NULL;
}

char **result_get_content(search_result_t *res)
{
    // make an array to know what doc u have been on previously
    if(res == NULL)
    {
        return NULL;
    }
    word_posistion_t *occurence;
    documents_t *doc;
    if (list_hasnext(res->content_next))
    {
        list_iter_t *iter = list_createiter(res->res_list);
        doc = list_next(res->content_next);
        while(list_hasnext(iter))
        {
            occurence = list_next(iter);
            if(doc->doc_name == occurence->doc_name)
            {
                res->document = doc->doc_name;
                return doc->array;
            }
        }        
    }
    destroy_res(res);

    return NULL;
  
}

int result_get_content_length(search_result_t *res)
{
    if(res == NULL)
    {
        return NULL;
    }
    list_iter_t *iter = list_createiter(list_of_documents);
    documents_t *elem;
    while (list_hasnext(iter))
    {
        elem = list_next(iter);
        if (elem->doc_name == res->document)
        {
            return elem->amount_of_words;
        }
    }
    return NULL;
}

search_hit_t *result_next(search_result_t *res)
{
    if(res == NULL)
    {
        return NULL;
    }
    search_hit_t *hit = malloc(sizeof(search_hit_t));
    word_posistion_t *search_result;
    if (list_hasnext(res->res_next))
    {
        search_result = list_next(res->res_next);
        //problem if multiple docs
        if(res->document != search_result->doc_name)
        {
            return NULL;
        }
        hit->location = search_result->pos;
        int length = 0;
        while (search_result->word[length] != '\0')
        {
            length++;
        }
        hit->len = length;
        return hit;
    }
    return NULL;
}
