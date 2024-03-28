#include<iostream>
#include<fstream>
#include<math.h>
#include<iomanip>
using namespace std;

const int sample=8;
const int feature=2;
const int kCentroid = 3;
struct Sample{
	float x[feature];
};

//---------------------------------
Sample centroids[kCentroid];
Sample trainingSamples[sample];
//---------------------------------
// load data from file
//this code writed by Duong Quang Trjnh
void nhap(){
	ifstream ip("training_set.txt");//dia chi file training dataset
	for(int i=0;i<sample;i++)
		for(int j = 0; j < feature; j++)
			ip>>trainingSamples[i].x[j];
	ip.close();
}
//ham tinh khoang cach
float distanceBetwenTwoSample(Sample a, Sample b){
	float sum=0;
	for(int i=0; i<feature; i++)
		sum+=pow(a.x[i]-b.x[i],2);
	return sqrt(sum);
}
//kiem tra cap nhat centroids
bool checkCentroids(Sample centroidA[], Sample centroidB[]){
	for(int i=0; i<kCentroid; i++)
		for(int j=0; j<feature; j++)
			if(centroidA[i].x[j] != centroidB[i].x[j])
				return false;
	return true;
}
//kmean
void kmeans(Sample samples[]){
	Sample centroidsTemp[kCentroid];
	float distance[sample][kCentroid];
	bool minArray[sample][kCentroid];
	do{
		//calcutate distance array
		for(int i=0; i<sample; i++)	for(int j=0; j<kCentroid; j++) distance[i][j]= distanceBetwenTwoSample(trainingSamples[i], centroids[j]);
		//coppy centroid to compare
		for(int i=0; i<kCentroid; i++)	for(int j = 0; j < feature; j++) centroidsTemp[i].x[j] = centroids[i].x[j];
		//min array with full false
		for (int i = 0; i < sample; i++) for (int j = 0; j < kCentroid; j++) minArray[i][j] = false;
		//calcutate min array
		for(int i=0; i<sample; i++){
			float min= distance[i][0];
			int finger=0;
			for(int j=1; j<kCentroid; j++)
				if(distance[i][j] < min){
					min = distance[i][j];
					finger=j;
				}
			minArray[i][finger] = true;
		}
		//clear centroids back to 0
		for(int i=0; i<kCentroid; i++) for(int j=0; j<feature; j++) centroids[i].x[j] = 0;
		//update centroid
		for(int j=0; j<kCentroid; j++){
			int count=0;
			for(int i=0; i<sample; i++)
				if(minArray[i][j]){
					for(int i1=0; i1<feature; i1++)
						centroids[j].x[i1]+=trainingSamples[i].x[i1];
					count+=1;
				}
			for(int i=0; i<feature; i++)
				centroids[j].x[i]/=count;
		}
	}while(!checkCentroids(centroidsTemp, centroids));
}
main(){
	nhap();
	centroids[0] = trainingSamples[0];
	centroids[1] = trainingSamples[3];
	centroids[2] = trainingSamples[6];
	
	kmeans(trainingSamples);
	
	for(int i=0; i<kCentroid; i++){
		for(int j=0; j<feature; j++)
			cout<<fixed<<setw(10)<<centroids[i].x[j];
		cout<<endl;
	}
}
