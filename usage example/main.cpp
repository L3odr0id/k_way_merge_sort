#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <algorithm>

using namespace std;

const int k = 4;

struct Clock
{
    Clock (){
        start_time = chrono::high_resolution_clock::now();
    }

    float get_info(){
         chrono::duration<float> seconds = chrono::high_resolution_clock::now() - start_time;
         return seconds.count();
    }
    chrono::high_resolution_clock::time_point start_time;
};

unsigned int counter = 0;

void KWayMerge(vector<int> &numArr, vector<int> &helperArr, int kPartitions, int low, int high){
    int totalSize = high - low + 1;
    int sizePartitions = max(totalSize / kPartitions, 1);
    int sizeLastPartition = totalSize - sizePartitions * (kPartitions - 1);

    if (totalSize < kPartitions)
    {
        KWayMerge(numArr,helperArr,totalSize, low, high);
        return;
    }
    vector<int> indices(kPartitions);

    int count = low;
    int min;
    int minPosition;
    int currentPart;

    while (count <= high){
        min = numeric_limits<int>::max();
        minPosition = 0;
        currentPart = low;
        for (int i = 0; i < kPartitions; i++){
            if (i == kPartitions - 1 && indices[i] == sizeLastPartition){
                break;
            }

            if (indices[i] == sizePartitions && i != kPartitions - 1){
                currentPart += sizePartitions;
                continue;
            }
            counter++;
            if (helperArr[currentPart + indices[i]] < min){
                min = helperArr[currentPart + (indices[i])];
                minPosition = i;
            }
            currentPart += sizePartitions;
        }
        numArr[count++] = min;
        indices[minPosition]++;
    }

    for (int i = low; i <= high; i++){
        //counter++;
        helperArr[i] = numArr[i];
    }
}

void KWayMergeSort(vector<int> &numArr, vector<int> &helperArr, int kPartitions, int startPart, int endPart){
    int totalSize = endPart - startPart + 1;
    int sizePartitions = max(totalSize / kPartitions, 1);
    int sizeEndPartition = totalSize - (sizePartitions * (kPartitions - 1));

    if (sizePartitions > 1){
        for (int i = 0; i < kPartitions; i++){
            int newEndPart;
            if (i == kPartitions - 1){
                newEndPart = i * sizePartitions + startPart + sizeEndPartition - 1;
            }
            else{
                newEndPart = i * sizePartitions + startPart + sizePartitions - 1;
            }
            KWayMergeSort(numArr,helperArr,kPartitions, i * sizePartitions + startPart, newEndPart);
        }
    }
    else{
        if (sizeEndPartition > 1){
            KWayMergeSort(numArr,helperArr,kPartitions, endPart - sizeEndPartition, endPart);
        }
    }

    KWayMerge(numArr,helperArr,kPartitions, startPart, endPart);
}

void sort(vector<int> &numArr, vector<int> &helperArr, int kPartitions){
    counter = 0;
    helperArr = vector<int>(numArr.size());
    for (int i = 0; i < numArr.size(); i++)
    {
        helperArr[i] = numArr[i];
    }
    KWayMergeSort(numArr,helperArr,kPartitions, 0, numArr.size() - 1);
}

void fill_arr(vector<int> &arr, long int size){
    for (unsigned int var = 0; var < size; ++var)
        arr.at(var) = rand();
}

void fill_arr_keyboard(vector<int> &arr, int size){
    for (int var = 0; var < size; ++var)
        cin>>arr[var];
}

void show_arr(vector<int> arr, long int size){
    for (int i = 0;i < size; ++i)
        cout<<arr[i]<<" ";
    cout<<endl;
}

double log(double a, double b)
{
    return log(b) / log(a);
}

void ShowRes(vector<int> &numArr){
    Clock timer; vector<int> helperArr;  const unsigned int N = numArr.size(); const double analitical = N*log(k,N);
    sort(numArr,helperArr,k);
    //counter = (int)analitical-N/7;
    float timeRes = timer.get_info();
    cout<<"| "<<setw(10)<<N<<" | "<<setw(10)<<fixed<<setprecision(5)<<timeRes<<" | "<<setw(10)<<counter<<" | "<<setprecision(2)<<setw(10)<<analitical<<" | "<<setw(10)<<counter*1.0/analitical<<" |"<<endl;
}

vector<int> do_research_best(vector<int>& numArr, vector<int>& helperArr){
    sort(numArr,helperArr,k);
    return numArr;
}

vector<int> do_research_middle( vector<int>& numArr, vector<int>&){
    return numArr;
}

vector<int> do_research_worst(vector<int>& numArr, vector<int>& helperArr){
    sort(numArr,helperArr,k);
    reverse(numArr.begin(), numArr.end());
    return numArr;
}

void research(vector<int> action(vector<int>&, vector<int>&)){
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"|   size          time          T(e)         T(a)      T(e)/T(a) |"<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
    for (unsigned int i = 10000;i<=50000;i+=10000){
        vector<int> numArr(i); vector<int> helperArr;
        fill_arr(numArr,i);
        numArr = action(numArr, helperArr);
        ShowRes(numArr);
    }
    cout<<"------------------------------------------------------------------"<<endl;
}

int main()
{
    cout<<"Enter 1 for test."<<endl<<"Enter 2 for research."<<endl;
    string cmd;cin>>cmd; vector<int> helperArr;
    if (cmd == "1"){
        vector<int> numArr(8);
        fill_arr_keyboard(numArr,8);
        sort(numArr,helperArr,k);
        cout<<"Sorted array: "<<endl;
        show_arr(numArr,8);
    }
    if (cmd == "2"){
        cout<<"4-way Merge Sort"<<endl;
        cout<<"For best case:"<<endl;
        research(do_research_best);
        cout<<"For random case:"<<endl;
        research(do_research_middle);
        cout<<"For worst case:"<<endl;
        research(do_research_worst);
    }
    return 0;
}
