#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Trie structure
struct Trie
{	
    struct Trie *children[26];
    int count;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *crawl = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!crawl->children[index]) {
            crawl->children[index] = (struct Trie *)malloc(sizeof(struct Trie));
            for (int j = 0; j < 26; j++) {
                crawl->children[index]->children[j] = NULL;
            }
            crawl->children[index]->count = 0;
        }
        crawl = crawl->children[index];
    }
    crawl->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *crawl = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!crawl->children[index]) {
            return 0;
        }
        crawl = crawl->children[index];
    }
    return crawl->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (!pTrie) return;
    for (int i = 0; i < 26; i++) {
        deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *root = (struct Trie *)malloc(sizeof(struct Trie));
    if (root) {
        for (int i = 0; i < 26; i++) {
            root->children[i] = NULL;
        }
        root->count = 0;
    }
    return root;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file\n");
        exit(1);
    }
    int numWords = 0;
    char buffer[256];
    while (fscanf(file, "%s", buffer) != EOF) {
        pInWords[numWords] = strdup(buffer);
        numWords++;
    }
    fclose(file);
    return numWords;
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