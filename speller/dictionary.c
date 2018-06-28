/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

/**
 * Converts a alphabetic character or apostrophy into an number 
 * 
 */
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
void makeNULL(trie *trav){
    
    trav-> is_word = false;
    for(int i = 0; i < 27; i++){
        
            trav->next[i] = NULL;
        
    }
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bool checkNULL(trie *trav){
    
    int counter = 0; 
    for(int i = 0; i < 27; i++){
        if (trav->next[i] == NULL){
            counter++;
        }
    }
    if (counter == 27){
        return true;
    } else {
        return false; 
    }
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
int convert(char letter){
    char wordspace[53] = "abcdefghijklmnopqrstuvwxyz'ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    for (int i = 0; i < 53; i++){
        if (letter == wordspace[i]){
            return i % 27;
        }
    }
    return -1; 
}

/**
 * Returns true if word is in dictionary else false.
 */
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
bool check(const char *word)
{
    int index = 0;
    trie * test = root;
    while(true){
        
        int place = convert(word[index]);
        
        //check at the end of the word
        if(word[index] == '\0'){
            if(test -> is_word == true){
                //printf("word found!!");
                return true;
            } else {
                //printf("not a word homie \n");
                return false;
            }
            
        }
        
        if(test->next[place] == NULL){
            //the path has not been traveled; word does not exist
            //printf("the path has not been traveled; word DNE\n"); 
            return false;
        } else {
            test = test-> next[place];
            index++;
        }
    }
    
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bool load(const char *dictionary)
{
    //creat the root node of the structure and get the address
    root= malloc(sizeof(trie));
    if (root == NULL) {return false;}
    makeNULL(root);
    
    //open the dictionary for reading
    
    FILE *dptr = fopen(dictionary, "r");
    if(dptr == NULL){return false;}
    
    //create a word buffer that can hold the longest word
    char buffer[LENGTH + 2];
    
    while(fgets(buffer, 47, dptr) != NULL){
        
        //enter the word via the algorithm 
        trie *trav = root;
        int index = 0; 
        while(true){
            int place = convert(buffer[index]);
            
            if(buffer[index] != '\n'){
                if(trav->next[place] == NULL){
                    trav->next[place] = malloc(sizeof(trie));
                    if(trav->next[place] == NULL) {return false;}
                    makeNULL(trav->next[place]);
                    trav = trav->next[place];
                    index++;
                } else {
                    //just go down the trail 
                    trav = trav->next[place];
                    index++;
                }
            } else {
                //EOF in buffer
                trav->is_word = true;
                break;
            }
        }
        
        
    }
    fclose(dptr);
    
    return true;
    
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
unsigned int size(void)
{
    
    return count(root);
    
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bool unload(void)
{
    
    return erase(root);
    
    
}

bool erase(trie *trav){
    
    
    //base case: if they are all null you can just free the entire structure
    if (checkNULL(trav) == true){
        free (trav);
    } 
    //recursive case: 
    else {
        for(int i = 0; i < 27; i++ ){
            if (trav->next[i] != NULL){
                erase(trav->next[i]);
            }
        }
        free(trav);
    }
    return true;
}

unsigned int count(trie *root){
    
    //base case: if they are all null, check the main lobby and return the anser
    if (checkNULL(root) == true){
        if(root->is_word == true){
            return 1;
        } else{
            return 0;
        }
    
    } else { //recursive case: go down all the paths that are avaliable
        unsigned int counter = 0;
        for(int i = 0; i < 27; i++){
            if(root->next[i] != NULL){
                counter = counter + count(root->next[i]);
                
                }
            }    
        
        if(root->is_word == true){
                    counter++;
        }
        return counter; 
    }
}

