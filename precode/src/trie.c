#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"
#include "printing.h"
#include "list.h"

#define TRIE_RADIX 26
#define ASCII_TO_IDX(c) c - 97

struct node
{
    char *key;
    void *value;
    list_t *list_of_docs;
    node_t *children[TRIE_RADIX];
};

struct trie
{
    node_t *root;
};

static inline int isleaf(node_t *node)
{
    // A NULL node is not considered a leaf node
    if (node == NULL)
    {
        return 0;
    }

    for (int i = 0; i < TRIE_RADIX; i++)
    {
        if (node->children[i] != NULL)
        {
            return 0;
        }
    }

    return 1;
}

static node_t *node_create(char *key, void *value)
{
    node_t *node = (node_t *)calloc(1, sizeof(node_t));
    if (node == NULL)
    {
        goto error;
    }

    node->key = key;
    node->value = value;

    return node;

error:
    return NULL;
}

void node_destroy(node_t *node)
{
    free(node);
}

trie_t *trie_create()
{

    trie_t *t = (trie_t *)calloc(1, sizeof(trie_t));

    if (t == NULL)
    {
        goto error;
    }

    t->root = node_create(NULL, NULL);
    return t;

error:
    return NULL;
}

void _trie_destroy(node_t *node)
{
    if (isleaf(node))
    {
        node_destroy(node);
    }
    else
    {
        int i;
        for (i = 0; i < TRIE_RADIX; i++)
        {
            if (node->children[i] != NULL)
            {
                _trie_destroy(node->children[i]);
                node->children[i] = NULL;
            }
        }
        node_destroy(node);
    }

    return;
}

void trie_destroy(trie_t *trie)
{
    _trie_destroy(trie->root);
    free(trie);
    trie = NULL;
}

int trie_insert(trie_t *trie, char *key, void *value, int wordpos, char *next_word)
{
    node_t *iter = trie->root;
    // Only allow alphabet characters
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!isalpha(key[i]))
        {
            goto error;
        }
    }

    // Find the child indices
    for (int i = 0; key[i] != '\0'; i++)
    {
        // We only use lowercase letters (case insensitive)
        if (iter->children[ASCII_TO_IDX(tolower(key[i]))] == NULL)
        {
            iter->children[ASCII_TO_IDX(tolower(key[i]))] = node_create(NULL, NULL);
        }
        iter = iter->children[ASCII_TO_IDX(tolower(key[i]))];
    }
    iter->key = key;
    iter->value = value;
    word_posistion_t *word = malloc(sizeof(word_posistion_t));
    word->doc_name = value;
    word->pos = wordpos;
    word->word = key;
    word_posistion_t *nxt_wrd = malloc(sizeof(word_posistion_t));
    nxt_wrd->doc_name = value;
    nxt_wrd->pos = wordpos + 1;
    nxt_wrd->word = next_word;

    if (iter->list_of_docs == NULL)
    {
        iter->list_of_docs = list_create(compare_strings);
        list_addfirst(iter->list_of_docs, word);
    }
    else
    {
        list_addlast(iter->list_of_docs, word);
    }

    return 0;

error:
    return -1;
}

char *trie_find(trie_t *trie, char *key)
{
    // make iterator, check if the string posisition on the node is the same as in the key, if so go next node to check
    // if no node matches the word is not there
    // if all letters match the words is there
    node_t *iter = trie->root;
    for (int i = 0; key[i] != '\0'; i++)
    {
        iter = iter->children[ASCII_TO_IDX(tolower(key[i]))];
        if (iter == NULL)
        {
            return NULL;
        }
    }
    // dette er hentet fra forelesning^^ og under
    // under skjer det noe galt
    if (iter->key != NULL)
    {
        if (iter->list_of_docs != NULL)
        {
            return iter->list_of_docs;
        }
    }
    return NULL;
}

char *_trie_autocomplete(node_t *iter)
{
    for (int i = 0; i < TRIE_RADIX; i++)
    {
        if (iter->children[i] != NULL)
        {
            iter = iter->children[i];
            {
                if (iter->key != NULL)
                {
                    return iter->key;
                }
                else
                {
                    _trie_autocomplete(iter);
                }
            }
        }
    }
}
char *trie_autocomplete(trie_t *trie, char *input)
{
    node_t *iter = trie->root;

    for (int i = 0; input[i] != '\0'; i++)
    {
        iter = iter->children[ASCII_TO_IDX(tolower(input[i]))];
        if (iter == NULL)
        {
            return NULL;
        }
    }
    char *suggestion = _trie_autocomplete(iter);

    return suggestion;
}
