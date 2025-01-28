#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <string>
#include <sstream>
#include <chrono>
#include <fstream>
#include <stdlib.h>

class MinHeap {
    public:
    std::vector<int> heap {0};  //heap index start with 1


    // insert value key into heap
    void insert(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    // extract the first element of heap
    int extract() {
        if (heap.size() <= 1) {
            std::cout << "Heap is empty" << std::endl;
            return 0;
        }
        int value = heap.at(1);
        heap.at(1) = heap.back();
        heap.pop_back();
        heapifyDown(1);
        return value;
    }

    // get the first content in heap
    int peek() {
        if (heap.size() <= 1) {
            std::cout << "Heap is empty" << std::endl;
            return 0;
        }
        return heap.at(1);
    }

    // function to heapify up the heap from currentIndex
    void heapifyUp(int currentIndex) {
        if ((currentIndex / 2) >= 1) {
            if (heap.at(currentIndex / 2) > heap.at(currentIndex)) {
                int temp = heap.at(currentIndex / 2);
                heap.at(currentIndex / 2) = heap.at(currentIndex);
                heap.at(currentIndex) = temp;
                heapifyUp(currentIndex / 2);
            }                                       
        }
    }

    // function to heapify down the heap from currentIndex
    void heapifyDown(int currentIndex) {
        int minIndex = currentIndex;
        if (currentIndex * 2 <= heap.size()-1)
            if (heap.at(currentIndex) > heap.at(currentIndex * 2))
                minIndex = currentIndex * 2;
        if (currentIndex * 2 + 1 <= heap.size()-1)
            if (heap.at(minIndex) > heap.at(currentIndex * 2 + 1))
                minIndex = currentIndex * 2 + 1;
        if (minIndex == currentIndex)
            return;
        int temp = heap.at(currentIndex);
        heap.at(currentIndex) = heap.at(minIndex);
        heap.at(minIndex) = temp;
        heapifyDown(minIndex);
    }

    // clear heap to empty
    void clearHeap() {
        heap.clear();
        heap.push_back(0);
    }

    // print heap content
    void printHeap() {
        for (int i = 1; i < heap.size(); i++)
            std::cout << heap.at(i) << " ";
        std::cout << std::endl;
    }

    // get the size of heap
    int size() {
        return heap.size() - 1;
    }
};

// perform empty heap test
void emptyHeapTest(MinHeap &h) {
    h.clearHeap();
    h.peek();
    h.extract();
}

// generate and store integer from [min, max) randomly
std::vector<int> generateVector(int min, int max) {
    std::vector<int> output;
    for (int i = min; i<max; i++)
        output.push_back(i);
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::shuffle(output.begin(), 
                output.end(), generator);     
    return output;
}

// perform heap insert test with each value appears twice
void heapInsertTest(MinHeap &h) {
    h.clearHeap();
    std::vector<int> insertValue1, insertValue2, insertValue3;
    insertValue1 = generateVector(-1000000, 1000000);
    insertValue2 = generateVector(-1000000, 1000000);
    for (auto i = insertValue1.begin(); i != insertValue1.end(); i++)
        h.insert(*i);
    for (auto i = insertValue2.begin(); i != insertValue2.end(); i++)
        h.insert(*i);       
    if (h.peek() != -1000000)
        std::cout << "Not correct " << h.peek() << std::endl;
    else
        std::cout << "Correct" << std::endl;
}

// perform heap insert and remove test with each value appears twice
void heapInsertAndRemoveTest(MinHeap &h) {
    h.clearHeap();
    std::vector<int> insertValue1, insertValue2;
    insertValue1 = generateVector(-1000000, 1000000);
    insertValue2 = generateVector(-1000000, 1000000);
    for (auto i = insertValue1.begin(); i != insertValue1.end(); i++)   
        h.insert(*i);
    for (auto i = insertValue2.begin(); i != insertValue2.end(); i++)
        h.insert(*i);
    for (int i = -1000000; i<1000000; i++) {
        if (h.extract() != i || h.extract() != i) {
            std::cout << "Not correct " << i << std::endl;
            return;
        }
    }        
    std::cout << "Correct" << std::endl;
}

// conduct heap test with n times
void conductHeapTest(int n) {
    MinHeap h;
    emptyHeapTest(h);
    for (int i = 0; i<n; i++)
        heapInsertTest(h);
    for (int i = 0; i<n; i++)
        heapInsertAndRemoveTest(h);
}

// perform heap sort with input
void heapSort(std::vector<int> &input) {
    MinHeap h;
    std::vector<int> output;

    for (int i = 0; i<input.size(); i++)
        h.insert(input.at(i));
    int heapSize = h.size();
    for (int i = 0; i<heapSize; i++)
        output.push_back(h.extract());
    input.swap(output);
}

// perform test with each value appears twice
void heapSortRandomArrayTest() {
    std::vector<int> inputValue1 = generateVector(-100, 100),
                    inputValue2 = generateVector(-100, 100);
    inputValue1.insert(inputValue1.end(), inputValue2.begin(), inputValue2.end());
    std::vector<int> finalVector = inputValue1;
    std::sort(finalVector.begin(), finalVector.end());
    heapSort(inputValue1);
    if (inputValue1 == finalVector)
        std::cout << "Correct" << std::endl;
    else
        std::cout << "Not correct" << std::endl;
}

// perform edge cases test
void heapSortEdgeCasesTest() {
    std::vector<int> emptyArray, identicalArray, negativeArray,
        sortedEmptyArray, sortedIdenticalArray, sortedNegativeArray;
    for (int i = 0; i<200; i++)
        identicalArray.push_back(1);
    negativeArray = generateVector(-200, 0);
    sortedEmptyArray = emptyArray;
    sortedIdenticalArray = identicalArray;
    sortedNegativeArray = negativeArray;
    heapSort(sortedEmptyArray);
    heapSort(sortedIdenticalArray);
    heapSort(sortedNegativeArray);
    std::sort(negativeArray.begin(), negativeArray.end());
    if (sortedEmptyArray == emptyArray &&
            sortedIdenticalArray == identicalArray && 
            sortedNegativeArray == negativeArray)
        std::cout << "Correct" << std::endl;
    else
        std::cout << "Not correct" << std::endl;
}

// count the time needed for heap sorting large array
void heapSortLargeArrayTest() {
    std::vector<int> largeArray = generateVector(-1000000, 1000000);
    auto start = std::chrono::high_resolution_clock::now();
    heapSort(largeArray);
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << 
    std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
    << std::endl;
}

// perform reverse order test
void heapSortReverseOrderTest() {
    std::vector<int> reverseArray, sortedArray;
    for (int i = 1000000; i>-1000001; i--)
        reverseArray.push_back(i);
    for (int i = -1000000; i<1000001; i++)
        sortedArray.push_back(i);
    heapSort(reverseArray);
    if (reverseArray == sortedArray)
        std::cout << "Correct" << std::endl;
    else
        std::cout << "Not correct" << std::endl;
}

// counduct heap sort test for n times
void conductHeapSortTest(int n) {
    for (int i = 0; i<n ; i++) {
        heapSortRandomArrayTest();
        heapSortEdgeCasesTest();
        heapSortLargeArrayTest();
        heapSortReverseOrderTest();
    }
}

// turn lines of number seperated by space to an array
void getLineInput(std::string input, std::vector<int> &v) {
    std::istringstream stream(input);
    int num;
    while (stream >> num) {
        v.push_back(num);
    }
}

// find kth min difference
void findKthMinDifference() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("myOutput.txt");
    std::string line;
    std::vector<int> inputInteger;
    MinHeap h;
    int k;
    while (std::getline(inputFile, line)) {
        inputInteger.clear();
        h.clearHeap();
        getLineInput(line, inputInteger);
        k = inputInteger.at(0);
        inputInteger.erase(inputInteger.begin());
        for (int i = 0; i<inputInteger.size(); i++)
            for (int j = i+1; j<inputInteger.size(); j++) 
                if (i != j)
                    h.insert(abs(inputInteger[i] - inputInteger[j]));
        for (int i = 0; i<k-1; i++)
            h.extract();
        outputFile << h.extract() << "\n";
    }
    inputFile.close();
    outputFile.close();
}

// compare if output is correct
bool compareOutput() {
    system("python3 exec.py input.txt output.txt");
    std::ifstream realOutput("output.txt");
    std::ifstream myOutput("myOutput.txt");
    std::vector<std::string> f1;
    std::vector<std::string> f2;

    std::string input;
    while(realOutput >> input) {
        f1.push_back(input);
        myOutput >> input;
        f2.push_back(input);
    } 
    return (f1 == f2);
}

// generate random integer array
std::vector<int> generateRandomIntegerVector(int intMin, int intMax) {
    std::vector<int> v;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> intDist(intMin, intMax);
    std::uniform_int_distribution<int> numDist(2, 100);
    int num = numDist(gen);
    std::uniform_int_distribution<int> kDist(1, num*(num-1)/2);
    v.push_back(kDist(gen));
    for (int i = 0; i<num; i++)
        v.push_back(intDist(gen));
    return v;
}

// write array to input.txt
void writeVectorToInput(std::vector<int> v) {
    std::ofstream outputFile("input.txt", std::ofstream::app);
    for (int i = 0; i < v.size()-1; i++)
        outputFile << v.at(i) << " ";
    outputFile << v.at(v.size()-1) << "\n";
    outputFile.close();
}

// conduct ramdom problem test on kth min difference
void problemRandomProblemTest(int n) {
    std::ofstream output("input.txt");
    output.close();
    for (int i = 0; i<n; i++)
        writeVectorToInput(generateRandomIntegerVector(-100, 100));
    std::vector<int> v = generateRandomIntegerVector(-100, 100);
    v.push_back(1000000);
    writeVectorToInput(v);
    v.clear();
    v = generateRandomIntegerVector(-100, 100);
    v.push_back(-1000000);
    writeVectorToInput(v);
    findKthMinDifference();
    std::cout << (compareOutput() ? "Correct" : "Not correct")
                << std::endl;
}

// conduct negative problem test on kth min difference
void problemNegativeTest(int n) {
    std::ofstream output("input.txt");
    output.close();
    for (int i = 0; i<n; i++)
        writeVectorToInput(generateRandomIntegerVector(-1000, 0));
    findKthMinDifference();
    std::cout << (compareOutput() ? "Correct" : "Not correct")
                << std::endl;
}

// conduct multilple same difference test on kth min difference
void problemMultipleSameDiffTest(int n) {
    std::ofstream output("input.txt");
    output.close();
    std::vector<int> v;
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int j = 0; j < n; j++) {
        std::uniform_int_distribution<int> intDist(-100, 100);
        std::uniform_int_distribution<int> identicalNumDist(0, 50);
        int identicalNum = identicalNumDist(gen);
        std::uniform_int_distribution<int> numDist(2, 99-identicalNum);
        int num = numDist(gen);
        std::uniform_int_distribution<int> kDist(1, num*(num-1)/2);
        v.push_back(kDist(gen));
        v.push_back(intDist(gen));
        int difference = intDist(gen);
        for (int i = 0; i<identicalNum; i++)
            v.push_back(v.at(i+1) + difference);
        for (int i = 0; i<num-identicalNum; i++)
            v.push_back(intDist(gen));
        writeVectorToInput(v);
        v.clear();
    }   
    findKthMinDifference();
    std::cout << (compareOutput() ? "Correct" : "Not correct")
                << std::endl;
}   

// conduct duplicate number test on kth min difference
void problemDuplicateNumberTest(int n) {
    std::ofstream output("input.txt");
    output.close();
    std::vector<int> v;
    for (int i = 0; i<n; i++) {
        v = generateRandomIntegerVector(-100, 100);
        v.insert(v.end(), v.begin()+1, v.end());
        writeVectorToInput(v);
    }
    findKthMinDifference();
    std::cout << (compareOutput() ? "Correct" : "Not correct")
                << std::endl;
}

// conduct test on kth min problem for n times
void conductProblemTest(int n, int size) {
    for (int i = 0; i < n; i++) {
        problemRandomProblemTest(size);
        problemNegativeTest(size);
        problemMultipleSameDiffTest(size);
        problemDuplicateNumberTest(size);
    }
}

// conduct test
int main() {
    conductHeapTest(5);
    conductHeapSortTest(10);
    conductProblemTest(10, 30);

    return 0;
}
