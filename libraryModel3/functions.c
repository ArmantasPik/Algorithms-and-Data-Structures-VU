#include "header.h"

//Function to read data file and validate the data
void readFileAndValidate(FILE *inputFile, int *modelTime, int *numberOfBooks, float *clientProbability, float *bookProbability)
{
    char fileName[maxChar];

    //Open file and check if exists
    do
    {
        printf("\nEnter data file name: ");
        scanf("%[^\n]s", fileName);
        inputFile = fopen(fileName, "r");

        if(inputFile == NULL)
        {
            printf("Error! Could not open data file. Try again.\n");
            while(getchar() != '\n'); 
        }

    } while (inputFile == NULL);
    
    //read data
    for(int i = 0; i < 4; i++)
    {
        if(i == 0)
            fscanf(inputFile, "%d", modelTime);

        if(i == 1)
            fscanf(inputFile, "%f", clientProbability);

        if(i == 2)
            fscanf(inputFile, "%f", bookProbability);

        if(i == 3)
            fscanf(inputFile, "%d", numberOfBooks);

        if(i < 3)
            while(fgetc(inputFile) != '\n');
    }

    //close file
    fclose(inputFile);

    //Validate all data and edge cases
    if(*modelTime <= 0)
    {
        printf("Model test time should be positive");
        exit(1);
    }

    if(*clientProbability <= 0)
    {
        printf("Client probability to enter should be positive");
        exit(1);
    }
    else if(*clientProbability >= 100)
    {
        printf("Client probability to enter should be less than 100");
        exit(1);
    }

    if(*bookProbability <= 0)
    {
        printf("Book probability should be positive");
        exit(1);
    }
    else if(*bookProbability >= 100)
    {
        printf("Book probability should be less than 100");
        exit(1);
    }

    if(*numberOfBooks <= 0)
    {
        printf("Number of books should be positive");
        exit(1);
    }
    else if(*numberOfBooks > maxBookSize)
    {
        printf("Number of books is too big");
        exit(1);
    }

    return;
}

//Function to initialize book vectors and book BST. In addition, initialize them with values
void initializeAndFill(vector *bookVectorArranged, vector *bookVectorNotArranged, binarySearchTree *bookBST, int numberOfBooks, int arranged[], int notArranged[])
{
    //Get random index for a book number
    for(int i = 0; i < numberOfBooks; i++)
        arranged[i] = rand() % ((i + 2) * 6) ;

    //Check for same book numbers in indexes, if found, generate different index. In addition, initialize non arranged array with same book indexes
    for(int i = 0; i < numberOfBooks; i++)
    {
        for(int j = 0; j < numberOfBooks; j++)
        {
            if(arranged[i] == arranged[j] && i != j)
            {
                arranged[i] = rand() % ((j + 2) * 7);
                continue;
            }
        }

        notArranged[i] = arranged[i];
    }

    //Sort arranged array
    qsort(arranged, numberOfBooks, sizeof(int), cmpfunction);

    //Shuffle non arranged array
    shuffle(notArranged, numberOfBooks);

    //Store books by arranged and non arranged order in vectors
    VectorInit(bookVectorArranged);
    VectorInit(bookVectorNotArranged);

    for(int i = 0; i < numberOfBooks; i++)
    {
        VectorPushBack(bookVectorArranged, &arranged[i]);
        VectorPushBack(bookVectorNotArranged, &notArranged[i]);
    }

    //Store books in binary search tree
    for(int i = 0; i < numberOfBooks; i++)
    {
        insert(bookBST, notArranged[i]);
    }

    return;
}

//Function to model the simulation for searching books in vector and return the maximum needed librarians for the job
int bookSearchModelInVector(vector bookVector, int bookArray[], int modelTime, int numberOfBooks, float clientProbability, float bookProbability)
{
    //Model variables
    int currentTime = 0;
    int maxLibrarians = 0;
    int activeClients = 0;
    int searchedBook;
    int clientTimes[maxActiveClients];

    // printf("\nPrinted elements: ");
    // for(int i = 0; i < VectorSize(&bookVector); ++i)
    // {
    //     VAR *elem = (VAR*)VectorGet(&bookVector, i);
    //     printf("%d ", *elem);
    // }

    //Modelling loop for arranged book vector
    while(currentTime < modelTime)
    {
        currentTime++;

        //Check for clients whose books have been finished being searched
        for(int i = 0; i < activeClients; i++)
        {
            if(clientTimes[i] < currentTime)
            {
                for(int j = i; j < activeClients - 1; j++)
                {
                    clientTimes[j] = clientTimes[j + 1];
                    activeClients--;
                }
            }
        }

        //Get new library client
        if((rand() % 100) < clientProbability)
        {
            if(activeClients == maxActiveClients)
            {
                printf("Max number of active clients reached \n");
                continue;
            }
        
            activeClients++;

            if(activeClients > maxLibrarians)
                maxLibrarians = activeClients;

            //Check if book is in library
            if((rand() % 100) < bookProbability)
            {
                //Generate random index for the book in the library
                searchedBook = bookArray[rand() % numberOfBooks];

                //Search for it in the vector of books and determine time taken
                for(int i = 0; i < numberOfBooks; i++)
                {
                    if(searchedBook == *(VectorGet(&bookVector, i)))
                    {
                        clientTimes[activeClients - 1] = currentTime + i + 1;
                        break;
                    }

                    if(i == numberOfBooks - 1)
                        clientTimes[activeClients - 1] = currentTime + i + 1; 
                }
            }
            else
            {
                //If book is not in the library the search will take the maximum amount of time, that means equivelant to the amount of books in the vector
                clientTimes[activeClients - 1] = currentTime + numberOfBooks;
            }
        }
    }
    
    return maxLibrarians;
}

//Function to model the simulation for searching books in a BST and return the maximum needed librarians for the job
int bookSearchModelInBST(binarySearchTree *bookBST, int bookArray[], int modelTime, int numberOfBooks, float clientProbability, float bookProbability)
{
    //Model variables
    int currentTime = 0;
    int maxLibrarians = 0;
    int activeClients = 0;
    int searchedBook;
    int clientTimes[maxActiveClients];
    int searchCounter = 0;

    //Modelling loop for searching books in a binary search tree
    while(currentTime < modelTime)
    {
        currentTime++;

        //Check for clients whose books have been finished being searched
        for(int i = 0; i < activeClients; i++)
        {
            if(clientTimes[i] < currentTime)
            {
                for(int j = i; j < activeClients - 1; j++)
                {
                    clientTimes[j] = clientTimes[j + 1];
                    activeClients--;
                }
            }
        }

        //Get new client
        if((rand() % 100) < clientProbability)
        {
            if(activeClients == maxActiveClients)
            {
                printf("Max number of active clients reached \n");
                continue;
            }
        
            activeClients++;

            if(activeClients > maxLibrarians)
                maxLibrarians = activeClients;

            //Check if book is in library
            if((rand() % 100) < bookProbability)
            {
                //Generate random index for the book in the library
                searchedBook = bookArray[rand() % numberOfBooks];
                
                //Search for it in the binary search tree and determine time taken
                BSTnode *currentNode = bookBST->root;
                searchCounter = 0;

                while(currentNode != NULL)
                {
                    searchCounter++;

                    if(currentNode -> data == searchedBook)
                        break;
                    else if(searchedBook < currentNode -> data)
                        currentNode = currentNode -> left;
                    else    
                        currentNode = currentNode -> right;
                }

                clientTimes[activeClients - 1] = currentTime + searchCounter;
            }
            else
            {
                //If the book is not in the library then the search will take the maximum amount of time for a BST tree O(log(n))
                BSTnode *currentNode = bookBST->root;
                searchCounter = 0;

                while(currentNode != NULL)
                {
                    searchCounter++;

                    if(currentNode -> data == -1)
                        break;
                    else if(-1 < currentNode -> data)
                        currentNode = currentNode -> left;
                    else    
                        currentNode = currentNode -> right;
                }

                clientTimes[activeClients - 1] = currentTime + searchCounter;
            }
        }
    }

    return maxLibrarians;
}

//Function to shuffle an array, mainly used to shuffle array given to non arranged vector of books
void shuffle(int *array, int n)
{
    if (n > 1) 
    {
        int i;
        for (i = 0; i < n - 1; i++) 
        {
          int j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }

    return;
}

//Function to compare two integers, for q-sort
int cmpfunction(const void * a, const void * b) 
{
   return ( *(int*)a - *(int*)b );
}