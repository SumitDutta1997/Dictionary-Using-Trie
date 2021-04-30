// DICTIONARY using TRIE data structure

/*
implemented a dictionary which gives the meaning of the word
entered, and if the entered word is not present in the dictionary
this program will say that the word is not found, and then will
auto suggest few words already present in the dictionary which have
the same prefix as the entered word.
*/

#include<iostream>
#define ALPHABET_SIZE 26
using namespace std;

struct TrieNode {

    /*
        in our trie node we have an array named children whose size
        is 26 since we have made an assumption that our dictionary
        will have words made up of only small case letters. We have
        a bool variable isEndOfWord just to check if a particular node
        is end of a word. We also have a string for every node which
        has meaning of that word.
    */

    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
    string meaning;
    TrieNode() {
        isEndOfWord = false;
        meaning = "";
        for(int i=0 ; i<ALPHABET_SIZE ; i++)
            children[i] = NULL;
    }
};

void insert(TrieNode *root, string word, string meaning)
{
    /*
        This function inserts words and their meaning
    */

    if(word.length() == NULL)
        return;
    TrieNode *curr = root;
    for(int i=0 ; i<word.length() ; i++)
    {
        int index = word[i]-'a';
        if(curr->children[index] == NULL)
            curr->children[index] = new TrieNode();
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
    curr->meaning = meaning;
}

void traverse(TrieNode *root, char word[], int level)
{
    /*
        This function is used to traverse every node
        in lexicographically manner and print them.
    */

    if(root == NULL)
        return;
    if(root->isEndOfWord == true)
    {
        word[level] = '\0';
        cout << "The word \""<< word <<"\" has meaning \""<< root->meaning <<"\""<< endl;
    }
    for(int i=0 ; i<ALPHABET_SIZE ; i++)
    {
        if(root->children[i] != NULL)
        {
            word[level] = i + 'a';
            traverse(root->children[i], word, level+1);
        }
    }
}

bool isLastNode(TrieNode *root)
{
    /*
        this function checks whether a node
        has any node below it or not.
        If a node does not have any node below
        it then it is the last node and this
        function return true or if a particular
        node has node below it then it is not the
        last node this function return false.

    */

    for(int i=0 ; i<ALPHABET_SIZE ; i++)
        if(root->children[i] != NULL)
            return false;
    return true;
}

void autoCompleteWords(TrieNode *root, string word)
{
    /*
        this function prints suggestions (words
        present in the dictionary whose prefix is
        same as the query passed in the parameters)
        if the query is not a legit word.
    */

    if(root->isEndOfWord == true)
        cout << word << endl;

    if(isLastNode(root) == true)
        return;

    for(int i=0 ; i<ALPHABET_SIZE ; i++)
    {
        if(root->children[i] != NULL)
        {
            word.push_back(i+97);
            autoCompleteWords(root->children[i],word);
            word.pop_back();
        }
    }
}

int search(TrieNode *root, string word)
{
    /*
        this function searches for the word passed
        in the parameters and returns -1 if the word
        was found an returns 0 if the word is not present
        (not even the initial few characters) and returns 1
        if the query is not present but the dictionary has
        few words with the same prefix.
    */

    TrieNode *curr = root;

    for(int i=0 ; i<word.length() ; i++)
    {
        int index = word[i]-'a';
        if(curr->children[index] == NULL)
            return 0;
        curr = curr->children[index];
    }

    bool isWord = (curr->isEndOfWord == true);
    if(isWord==true)
    {
        cout << endl << "The word \""<< word << "\" was found with meaning \""<< curr->meaning << "\"" << endl << endl;
        return -1;
    }

    bool isLast = isLastNode(curr);
    if(isLast == false)
    {
        cout << endl << "The word \"" << word << "\" was not found in the dictionary" << endl;
        cout << endl << "Did you mean : " << endl;
        autoCompleteWords(curr,word);
        cout << endl;
        return 1;
    }
}

TrieNode *DeleteUtil(TrieNode *root, string word, int i)
{
    /*
        this function deletes a word from the
        dictionary. It assumes that a word already present
        is the dictionary is only passed as parameters.
    */

    if(root == NULL)
        return NULL;

    if(i == word.length())
    {
        root->isEndOfWord = false;
        if(isLastNode(root) == true)
        {
            delete(root);
            root = NULL;
        }
        return root;
    }

    int index = word[i] - 'a';
    root->children[index] = DeleteUtil(root->children[index], word, i+1);

    if(isLastNode(root) == true && root->isEndOfWord == false)
    {
        delete(root);
        root = NULL;
    }

    return root;
}

TrieNode *Delete(TrieNode *root, string word)
{
    root = DeleteUtil(root,word,0);
    cout << endl << "The word \"" << word << "\" has been successfully deleted" << endl;
}

int main()
{
    string dict[] = {"intersect","intersects","intervene","interstellar","cat","cut","geek","their","there","past","guru","gurus"};
    string meaning[] = {"to_meet_and_cross_at_one_or_more_points","plural_form_of_intersect","extend_or_occur_between_events",
    "existing_or_occurring_between_stars","a_small_animal_that_is_related_to_lions_and_tigers","divide_into_pieces_with_a_knife",
    "a_knowledgeable_and_obsessive_enthusiast","belonging_to_or_associated_with_the_people_or_things",
    "used_when_gesturing_to_indicate_the_place_or_position_intended","gone_by_in_time_and_no_longer_existing",
    "a_hindu_spiritual_teacher","plural_form_of_guru"};

    int n = sizeof(dict)/sizeof(dict[0]);

    TrieNode *root = new TrieNode();

    //checking our insert function
    for(int i=0 ; i<n ; i++)
        insert(root,dict[i],meaning[i]);

    int level=0;
    char str[45];
    string word;
    char ch;
    int choice,check;

    do {

        system("cls");
        cout << endl << "DICTIONARY!" << endl;
        cout << endl << "1. Print all the words present in the dictionary with its meaning.";
        cout << endl << "2. Search word.";
        cout << endl << "3. Delete word." << endl;
        cout << endl << "Enter your choice: ";

        cin >> choice;
        switch(choice)
        {
            case 1:
                    cout << endl << "Words in the dictionary are : " << endl << endl;
                    traverse(root, str, level);
                    cout << endl;
                    break;
            case 2:
                    cout << endl << "Enter Word: ";
                    cin >> word;
                    check = search(root, word);
                    //if(check == -1)
                        //return 0;
                    if(check == 0)
                        cout << endl << "The word \"" << word << "\" was not found in the dictionary" << endl << endl;
                    break;
            case 3:
                    cout << endl << "Enter Word: ";
                    cin >> word;
                    Delete(root, word);
                    cout << endl;
                    break;
        }
        cout << "Do you wish to continue: (enter 'y' or 'Y') ";
	    cin >> ch;
    } while(ch=='y' || ch=='Y');

    return 0;
}
