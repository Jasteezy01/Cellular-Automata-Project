/*
Jadon Olson
A1: 1D Cellular Automata

This program replicates a cellular automata system. It creates a rule set based on
a number provided by the user. The rule set number is then converted to binary and
is stored in an array. Using this "rule set array" the program will specify what
new value should be produced given a value and its neighbors. Then a starting
generation array of lenght 64 is made, with a single 1 at index 32. The program
then uses the rule set array to compute 49 following generations. All 50 generations
are displayed.
*/
#include <iostream>
#include <math.h>

    //This converts the rule set number to a binary number in the form
    //of an array.
    void convertRuleSetNumberToRuleSetArray(int nums, int ruleSetArr[8]){
        int j = 0;
        for(int i = 7; i >= 0; i--){
            if(nums < pow(2, i)){
                
                continue;
            }
            else{
                ruleSetArr[i] = 1;
                nums -= int(pow(2, i));
            }
        }
    }

    //This method displays the current generation
    //0's are spaces and 1's are #s
    void displayCurrentGeneration(int values[], int size){
        std::string ret = "";
        for(int i = 0; i < size; i++){
            if(values[i] == 0)
                ret += " ";
            else
                ret += "#";
        }
        std::cout << ret << std::endl;
    }

    //This method converts the provided binary number to a base ten integer
    int convertNeighborhoodToIndex(int left, int middle, int right){
        int ret = 0;
        if(right == 1)
            ret += 1;
        if(middle == 1)
            ret += 2;
        if(left == 1)
            ret += 4;

        return ret;
    }

    //This method computes the next generation
    void computeNextGeneration(int currentArr[], int nextArr[], int size, int ruleArr[]){
        //The 2 edge indexes dont have 2 neighbors so they are just passed
        nextArr[0] = currentArr[0];
        nextArr[size-1] = currentArr[size-1];

        //For each index in the current generation we need to pass its 2 neighbors to compute the next generation
        for(int i = 1; i < size-1; i++){
            int integer = convertNeighborhoodToIndex(currentArr[i-1], currentArr[i], currentArr[i+1]);
            nextArr[i] = ruleArr[integer];
        }
        //set the current array to the next generation
        for(int i = 0; i < size; i++)
            currentArr[i] = nextArr[i];
    }

//This is the main method
int main() {
    int ruleSetNum;
    int ruleSetArr[8]{};
    int generationArr[64]{};

    std::cout << "Enter a rule set number (0-255): " << std::endl; //Ask user for rule set number
    
    if(std::cin >> ruleSetNum && ruleSetNum >= 0 && ruleSetNum <= 255){
        convertRuleSetNumberToRuleSetArray(ruleSetNum, ruleSetArr); //create the rule set array
        
    }
    else {
        std::cout << "That's not a correct value. Program ending..." << std::endl; //If the value entered is not accepted program ends
        return 0;
    }
    generationArr[32] = 1;
    
    //Display the current generation and then compute the next generation
    for(int i = 0; i < 50; i++){
        displayCurrentGeneration(generationArr, 64);
        int nextGenArr[64]{};
        computeNextGeneration(generationArr, nextGenArr, 64, ruleSetArr);

    }
}