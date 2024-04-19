#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
typedef struct Trie
{	
    int count;
    struct Trie *children[26];
}Trie;

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int i, index, len = strlen(word);
    Trie *temp;

    if(pTrie == NULL){
        pTrie = createTrie();
    }

    temp = pTrie;

    for(i = 0; i < len; i++){
        if(!isalpha(word[i])){
            return NULL;
        }
        index = tolower(word[i]) - 'a';
        if(temp->children[index] == NULL){
            temp->children[index] = createTrie();
        }
        temp = temp->children[index];
    }
    temp->count++;
    return pTrie;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    Trie* temp = pTrie;
    int len = strlen(word);

    for(int i = 0; i < len; i++){
        int index = word[i] - 'a';
        if(temp->children[index] == NULL){
            return 0;
        }
        temp = temp->children[index];
    }
    return temp->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    int i;
    for(int i = 0; i < 26; i++){
        if(pTrie->children[i] != NULL){
            free(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    // int to traverse children
    int i;
    // allocate memory
    Trie *n  = malloc(sizeof(Trie));
    // set count to zero
    n->count = 0;

    // go through and set children to null
    for(i =0; i < 26; i++){
        n->children[i] = NULL;
    }

    return n;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    int n = 0;
    FILE* fp = fopen(filename, "r");
    if(fp == NULL){
        return -1;
    }

    for(int i = 0; i < n; i++){
        pInWords[i] = (char*)malloc(256 * sizeof(char));
        fscanf(fp, "%s", pInWords[i]);
    }
    fclose(fp);
    return n;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}