#include <vector>
#include <limits>
using namespace std;

class KWayMerge{
    void doKWayMerge(vector<int> &numArr, vector<int> &helperArr, int kPartitions, int low, int high);
    void KWayMergeSort(vector<int> &numArr, vector<int> &helperArr, int kPartitions, int startPart, int endPart);
public:
    void sort(vector<int> &numArr, vector<int> &helperArr, int kPartitions);
};

void KWayMerge::doKWayMerge(vector<int> &numArr, vector<int> &helperArr, int kPartitions, int low, int high){
    int totalSize = high - low + 1;
    int sizePartitions = max(totalSize / kPartitions, 1);
    int sizeLastPartition = totalSize - sizePartitions * (kPartitions - 1);

    if (totalSize < kPartitions)
    {
        doKWayMerge(numArr,helperArr,totalSize, low, high);
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
            if (helperArr[currentPart + indices[i]] < min){
                min = helperArr[currentPart + (indices[i])];
                minPosition = i;
            }
            currentPart += sizePartitions;
        }
        numArr[count++] = min;
        indices[minPosition]++;
    }

    for (size_t i = low; i <= high; i++){
        //counter++;
        helperArr[i] = numArr[i];
    }
}

void KWayMerge::KWayMergeSort(vector<int> &numArr, vector<int> &helperArr, int kPartitions, int startPart, int endPart){
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

    doKWayMerge(numArr,helperArr,kPartitions, startPart, endPart);
}

void KWayMerge::sort(vector<int> &numArr, vector<int> &helperArr, int kPartitions){
    helperArr = vector<int>(numArr.size());
    for (size_t i = 0; i < numArr.size(); i++){
        helperArr[i] = numArr[i];
    }
    KWayMergeSort(numArr,helperArr,kPartitions, 0, numArr.size() - 1);
}


