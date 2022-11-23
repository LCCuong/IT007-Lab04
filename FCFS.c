/*######################################
# University of Information Technology #
# IT007 Operating System               #
# <Le Chi Cuong>, <21520012>           #
# File: FCFS.c			       #
######################################*/
#include<stdio.h>

void main(){
	int pn[10];
	//thêm mảng index để quản lí thứ tự các process
	int arr[10], bur[10], star[10], finish[10], tat[10], wt[10], index[10], i, n;
	int totwt=0, tottat=0;
	
	//Nhập số lượngng process
	printf("Enter the number of processes:");
	scanf("%d",&n);
	
	/*
	Nhập các thông tin của các process bao processgồm:
	+ Tên process thứ i lưu ở pn[i]
	+ Arrival time của process thứ i lưu ở arr[i]
	+ Burst Time của process thứ i lưu ở bur[i]
	*/
	for(i=0;i<n;i++) {
		printf("Enter the Process Name, Arrival Time & Burst Time:");
		scanf("%d%d%d",&pn[i],&arr[i],&bur[i]);
		index[i] = i;
	}
	
	//sắp xếp lại các tiến trình theo thứ tự Arrival time tăng dần (chỉ sắp xếp mảng index)
	for (i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if (arr[index[i]] > arr[index[j]])
			{
				int temp = index[i];
				index[i] = index[j];
				index[j] = temp;
			}
	
	/*
	 tính toán thời gian process bắt đầu được thực thi (start),
	 thời gian chờ của process (wait), thời gian hoàn thành của
	 process (finish) và thời gian quay vòng (tat)
	*/
	for(i=0;i<n;i++) {
		int ind = index[i];
		if(i==0) {
			star[ind]=arr[ind]; //nếu là tiến trình đến đầu tiên thì start = arr
			wt[ind]=star[ind]-arr[ind];
			finish[ind]=star[ind]+bur[ind];
			tat[ind]=finish[ind]-arr[ind];
		} else{
			/*
			 kể từ tiến trình đến thứ 2 trở đi thì start[index[i]] = max(arr[index[i]], finish[index[i-1]])
			*/ 
			if (arr[ind] > finish[index[i-1]])
				star[ind]=arr[ind];
			else star[ind]=finish[index[i-1]];
			
			wt[ind]=star[ind]-arr[ind];
			finish[ind]=star[ind]+bur[ind];
			tat[ind]=finish[ind]-arr[ind];
		}
	}
	printf("\nPName\tArrtime\tBurtime\tStart\tTAT\tFinish");
	for(i=0;i<n;i++) {
		int ind = index[i];
		printf("\n%d\t%d\t%d\t%d\t%d\t%d",pn[ind],arr[ind],bur[ind],star[ind],tat[ind],finish[ind]);
		totwt+=wt[ind];
		tottat+=tat[ind];
	}
	printf("\nAverage waiting time = %f", (totwt*1.0/n));
	printf("\nAverage turnaround time = %f", (tottat*1.0/n));
	printf("\n");
}
