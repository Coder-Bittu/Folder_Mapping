#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <windows.h>


void SizeToString(unsigned long long size,char * string){
	
	if(size>(1024*1024*1024)){
		sprintf(string,"%.2lf GB" , ((double)size/(1024*1024*1024)));
	}else if(size>(1024*1024)){
		sprintf(string,"%.2lf MB" , ((double)size/(1024*1024)));
	}else if(size>(1024)){
		sprintf(string,"%.2lf KB" , ((double)size/(1024)));
	}else if(size>(1024*1024*1024)){
		sprintf(string,"%llu B" , (size));
	}
	
	
}


unsigned long long ListDir(char dir[260] , int * FolderCount , int * FileCount){
	
	unsigned long long size = 0;
	
	int File = 0;
	int Folder = 0;
	
	char PATH[2048];
	HANDLE fhnd;
	WIN32_FIND_DATA fileinfo;
	
	sprintf(PATH,"%s\\*.*",dir);
	
	fhnd = FindFirstFile(PATH,&fileinfo);
	
	do {
		
		
		
		sprintf(PATH,"%s\\%s",dir,fileinfo.cFileName);
		
		if(strcmp(fileinfo.cFileName,".")!=0 && strcmp(fileinfo.cFileName,"..")!=0){
		
			if(GetFileAttributes(PATH)==16){
				std::cout << fileinfo.cFileName << std::endl;
				size += ListDir(PATH,FolderCount,FileCount);
				++Folder;
			}else{
				std::cout <<"   "<< fileinfo.cFileName << std::endl;
				size += (fileinfo.nFileSizeHigh * (MAXDWORD+1)) + fileinfo.nFileSizeLow;
				++File;
			}
		
		}
	
	}while(FindNextFile(fhnd,&fileinfo));
	
	FindClose(fhnd);
	
	*FileCount = *FileCount + File;
	*FolderCount = *FolderCount + Folder;
	
	return size;
}





int main(){
	
	
	int Folder = 0;
	int File = 0;
	
	char SizeString[30]={0};
	unsigned long long size = 0;
	
	char dir[]="E:";
	
	size = ListDir(dir,&Folder,&File);
	
	SizeToString(size,SizeString);
	
	
	std::cout << "\n\n\nScanning finished for\n"<<dir<<"\n\n"<<std::endl;
	std::cout << SizeString << std::endl;
	std::cout << "File count: "<<File << std::endl;
	std::cout << "Folder Count: " << Folder << std::endl;

	return 0;	
}
