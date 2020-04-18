#include<iostream>
#include<unordered_map>
#include"MinPriorityQueue.h"
#include<string>
#include<math.h>
#include<fstream>
using namespace std;
string readFile(string path=""){
	//Function to readFIle and extract all data in a string 
	string data;
	if(path==""){
		//FOR TESTING 
		data="aabbccdd";
	}else{
		string line;
		ifstream myfile(path);
		while(getline(myfile,line)){
			data=data+line;
		}
		myfile.close();
	}
	return data;
}
int* CountVectorizer(string data){
	//The function returns the count of all the 255 characters
	int* counts=new int[255];
	for(int i=0;i<255;i++){
		counts[i]=0;
	}
	for(int i=0;i<data.size();i++){
		counts[int(data[i])]++;
	}
	return counts;
}
void storeEncoder(unordered_map<char,string>& encoder){
	//store the hash map in a file for future use 
	//Also Store the encoded file 
	return;
}
char bit2byte(string byteStr){
	// To Convert The a binary string of size 8 into a Byte
	//My Attempt==NOT WORKING Properly 
	if(byteStr.size()<=8){
		while(byteStr.size()<=8){
			byteStr="0"+byteStr;
		}
	}
	cout<<"The Byte String i s"<<byteStr<<endl;
	int sum=0;
	for(int i=0;i<8;i++){
		int p=7-i;
		if(byteStr[i]=='1'){
			sum+=pow(2,p);
		}
	}
	return sum;
}
void fileEncoder(string data, unordered_map<char,string>&encoder){
	//The Function encodes the complete document according to created hash map
	//After Encoding into 0 and 1 it splits the binary string into size of 8
	//Then it will call bit2byste function for creating the data in bytes => To store in a file
	string binStr="";
	for(int i=0;i<data.size();i++){
		if(encoder.count(data[i])>0){
			binStr=binStr+encoder[data[i]];
			//cout<<encoder[data[i]]<<" "<<data[i]<<endl;
		}
	}
	// To Splits the string in size of 8 
	while(binStr.size()>8){
		string byteStr=binStr.substr(0,8);
		binStr=binStr.substr(8);
	}
}
void pathFinder(BinaryTreeNode<node>*root,unordered_map<char,string> &encoder,string s=""){
	// This Function returns the root to leaf path for all characters present in document
	if(root==NULL){
		return;
	}
	if(root->left==NULL && root->right==NULL){
		node ndata=root->data;
		cout<<"We reached :  "<<ndata.ch <<"Path: "<<s<<endl;
		encoder[ndata.ch]=s;
		return;
	}
	pathFinder(root->left,encoder,s+"0");
	pathFinder(root->right,encoder,s+"1");
}
void fileCompressor(string path=""){
	//This Function is where the Huffman code begins its execution 
	string data=readFile(path);
	int* counts=CountVectorizer(data);
	PriorityQueue minPQ;
	for(int i=0;i<255;i++){
		if(counts[i]==0){
			continue;
		}
		node ndata=node(char(i+'a'),counts[i]);
		BinaryTreeNode<node>*temp=new BinaryTreeNode<node>(ndata);
		minPQ.insert(temp);
	}
	while(minPQ.getSize()>1){
		BinaryTreeNode<node>*n1=minPQ.getMin();
		minPQ.removeMin();
		BinaryTreeNode<node>*n2=minPQ.getMin();
		minPQ.removeMin();
		int csum=n1->data.chctr+n2->data.chctr;
		node ndata=node('#',csum);
		BinaryTreeNode<node>*internal_node=new BinaryTreeNode<node>(ndata);
		internal_node->left=n1;
		internal_node->right=n2;
		minPQ.insert(internal_node);
	}
	BinaryTreeNode<node>*root=minPQ.getMin();
	minPQ.removeMin();
	if(minPQ.isEmpty()){
		cout<<"Tree Creation Succesful"<<endl;
	}
	unordered_map<char,string>encoder;
	pathFinder(root,encoder);
	storeEncoder(encoder);
	fileEncoder(data,encoder);
}
int main(){
	fileCompressor();
	//cout<<bit2binary("1100001");
	return 0;
}
