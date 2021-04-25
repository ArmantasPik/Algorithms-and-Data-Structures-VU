/*  
    Procesas: skaitytojas ateina į biblioteką ir paprašo pageidaujamos knygos, 
    bibliotekos darbuotojas randa pageidaujamą knygą ar informuoja skaitytoją, 
    kad tokios bibliotekoje nėra. Paieškos trukmė priklauso nuo saugyklos organizavimo būdo. 
    Biblioteka laikosi principo, kad skaitytojai neturi laukti eilėse, todėl priima tiek darbuotojų, kiek reikia. 
    Tikslas: patyrinėti: 1) kiek darbuotojų galima sutaupyti, jei vietoje nuoseklios paieškos nesutvarkytoje saugykloje būtų naudojama: 
    a) nuosekli paieška sutvarkytoje saugykloje, b) dvejetainė paieška; 
    2) kaip šie skaičiai kinta, augant bibliotekos fondams. 
    Pradiniai duomenys: skaitytojo atvykimo tikimybė (galima realizacija: generuojamas atsitiktinis skaičius ir tikrinama, ar jis tenkina tam tikrą sąlygą); 
    tikimybė, kad skaitytojo pageidaujama knyga bus bibliotekoje; bibliotekos knygos. 
    Pastabos: pageidaujamos knygos sugeneruojamos atsitiktinai pagal pradinius duomenis; 
    nuoseklios paieškos atvejais knygos saugomos vektoriuje ir paieškos trukmė yra lygi ieškant atliktų palyginimų skaičiui; 
    dvejetainės paieškos atveju knygos saugomos dvejetainiame paieškos medyje ir paieškos trukmė yra lygi teoriškai įvertintam operacijų skaičiui. 
*/

#include "header.h"

int main() 
{
    //Parameters
    int modelTime, numberOfBooks;
    float clientProbability, bookProbability;

    //Open and read data file
    FILE *inputFile;
    readFileAndValidate(inputFile, &modelTime, &numberOfBooks, &clientProbability, &bookProbability);

    //Print initial parameters
    printf("\n\nSimulation time: %d, Initial number of books: %d \n", modelTime, numberOfBooks);
    printf("Reader arrival probability: %.2f %%, Probability of book being the library: %.2f %% \n\n", clientProbability, bookProbability);

    //Initialize rand() function with current time as seed
    srand(time(0));

    //Program variables
    vector bookVectorNotArranged;
    vector bookVectorArranged;
    binarySearchTree *bookBST = createTree();
    int arranged1[numberOfBooks], arranged2[(int)1.5 * numberOfBooks], arranged3[2 * numberOfBooks];
    int notArranged1[numberOfBooks], notArranged2[(int)1.5 * numberOfBooks], notArranged3[2 * numberOfBooks];
    int maxLibrariansArranged, maxLibrariansNotArranged, maxLibrariansBST;

    //Initialize and fill both vectors and BST
    initializeAndFill(&bookVectorArranged, &bookVectorNotArranged, bookBST, numberOfBooks, arranged1, notArranged1);
	
    //Execute modelling functions
    maxLibrariansArranged = bookSearchModelInVector(bookVectorArranged, arranged1, modelTime, numberOfBooks, clientProbability, bookProbability);
    maxLibrariansNotArranged = bookSearchModelInVector(bookVectorNotArranged, arranged1, modelTime, numberOfBooks, clientProbability, bookProbability);
    maxLibrariansBST = bookSearchModelInBST(bookBST, arranged1, modelTime, numberOfBooks, clientProbability, bookProbability);

    //Clear vectors and BST
    VectorClear(&bookVectorArranged);
    VectorClear(&bookVectorNotArranged);
    deleteBST(bookBST -> root);

    //Print results
    printf("Simulating a model with initial number of books...\n");
    printf("Max number of librarians needed with arranged vector search: %d \n", maxLibrariansArranged);
    printf("Max number of librarians needed with non arranged vector search: %d\n", maxLibrariansNotArranged);
    printf("Max number of librarians needed with BST search: %d\n\n", maxLibrariansBST);

    //Initialize and fill both vectors and BST
    bookBST = createTree();
    initializeAndFill(&bookVectorArranged, &bookVectorNotArranged, bookBST, (numberOfBooks / 2 + numberOfBooks), arranged2, notArranged2);

    // traverseBST(bookBST -> root);
    // printf("\n");
    // printf("\nPrinted elements: ");
    // for(int i = 0; i < VectorSize(&bookVectorArranged); ++i)
    // {
    //     VAR *elem = (VAR*)VectorGet(&bookVectorArranged, i);
    //     printf("%d ", *elem);
    // }

    // printf("\n");
    // printf("\n");

    //Execute modelling functions
    maxLibrariansArranged = bookSearchModelInVector(bookVectorArranged, arranged2, modelTime, (numberOfBooks / 2 + numberOfBooks), clientProbability, bookProbability);
    maxLibrariansNotArranged = bookSearchModelInVector(bookVectorNotArranged, arranged2, modelTime, (numberOfBooks / 2 + numberOfBooks), clientProbability, bookProbability);
    maxLibrariansBST = bookSearchModelInBST(bookBST, arranged2, modelTime, (numberOfBooks / 2 + numberOfBooks), clientProbability, bookProbability);

    //Clear vectors and BST
    VectorClear(&bookVectorArranged);
    VectorClear(&bookVectorNotArranged);
    deleteBST(bookBST -> root);

    //Print results
    printf("Simulating a model with 50%% more books...\n");
    printf("Max number of librarians needed with arranged vector search: %d \n", maxLibrariansArranged);
    printf("Max number of librarians needed with non arranged vector search: %d\n", maxLibrariansNotArranged);
    printf("Max number of librarians needed with BST search: %d\n\n", maxLibrariansBST);

    //Initialize and fill both vectors and BST
    bookBST = createTree();
    initializeAndFill(&bookVectorArranged, &bookVectorNotArranged, bookBST, 2 * numberOfBooks, arranged3, notArranged3);
	
    //Execute modelling functions
    maxLibrariansArranged = bookSearchModelInVector(bookVectorArranged, arranged3, modelTime, 2 * numberOfBooks, clientProbability, bookProbability);
    maxLibrariansNotArranged = bookSearchModelInVector(bookVectorNotArranged, arranged3, modelTime, 2 * numberOfBooks, clientProbability, bookProbability);
    maxLibrariansBST = bookSearchModelInBST(bookBST, arranged3, modelTime, 2 * numberOfBooks, clientProbability, bookProbability);

    //Clear vectors and BST
    VectorClear(&bookVectorArranged);
    VectorClear(&bookVectorNotArranged);
    deleteBST(bookBST -> root);

    //Print results
    printf("Simulating a model with 100%% more books...\n");
    printf("Max number of librarians needed with arranged vector search: %d \n", maxLibrariansArranged);
    printf("Max number of librarians needed with non arranged vector search: %d\n", maxLibrariansNotArranged);
    printf("Max number of librarians needed with BST search: %d\n\n", maxLibrariansBST);

    //Compare results
    if(maxLibrariansArranged <= maxLibrariansNotArranged && maxLibrariansArranged <= maxLibrariansBST)
        printf("Based on results, searching for a book in an ARRANGED VECTOR is the most optimal\n");
    else if(maxLibrariansNotArranged <= maxLibrariansArranged && maxLibrariansNotArranged <= maxLibrariansBST)
        printf("Based on results, searching for a book in a NON ARRANGED VECTOR is the most optimal\n");
    else
        printf("Based on results, searching for a book in a BINARY SEARCH TREE is the most optimal\n");
    
    return 0;
}