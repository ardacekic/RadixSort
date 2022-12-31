#include "the2.h"
#include <cmath>

int countingsort(int* arr, int arraySize, int groupSize,int groupSizebfore,int div,bool ascending,long&  numberOfIterations){
	int grup_power =  pow(10,groupSize);
	int power_divide = pow(10,div*groupSizebfore);
	
	int *counter;
	counter = new int[grup_power];

	int *final;
	final = new int[arraySize];

		for(int i=0; i<grup_power;i++){
			counter[i] =0;
		}

		for(int i = 0; i<arraySize;i++){
			counter[(arr[i]/power_divide)%(grup_power)]++;
			numberOfIterations++;
		}

		if(ascending){
			for(int i = 1;i<grup_power;i++){
				counter[i] = counter[i] + counter[i-1];
				numberOfIterations++;
			}
		}else{
			for(int i = grup_power-2;i>=0;i--){
				counter[i] = counter[i] + counter[i+1];
				numberOfIterations++;
			}
		}

		for(int i=arraySize-1; i>=0;i--){
			numberOfIterations++;
			final[counter[(arr[i]/power_divide)%grup_power]-1] = arr[i];
			counter[(arr[i]/power_divide)%grup_power]--;
		}

		for(int n=0; n<arraySize; n++){ //copy the back
			numberOfIterations++;
			arr[n] = final[n];
		}

		
	delete [] counter;
	delete [] final;
	return numberOfIterations;
}

void calculategroups(int* group_size,int groupSize,int maxDigitLength,int loop_count){
		int i =0;
		int counted = 0;
		for(i =0; i<loop_count-1;i++){
			group_size[i]=groupSize;
			counted++;
		}
		if(maxDigitLength%groupSize != 0)
			group_size[loop_count-1]=maxDigitLength-counted*groupSize;
		else
			group_size[loop_count-1]=groupSize;
}

long multiDigitRadixSort(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength){
    long numberOfIterations = 0;
	int *group_size;
	int loop_cnt =(int)ceil((double)maxDigitLength/(double)groupSize);
	group_size = new int[loop_cnt + 1];
	calculategroups(group_size,groupSize,maxDigitLength,loop_cnt); //must calculate grupsize for each iter
	for(int div=0;div<(int)ceil((double)maxDigitLength/(double)groupSize);div++){
			countingsort(arr, arraySize, group_size[div],group_size[div-1],div,ascending,numberOfIterations);	
	}
	delete [] group_size;	
    return numberOfIterations;
}