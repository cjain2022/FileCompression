#include<iostream>
#include<vector>
#include "BinaryTree.h"
#include "node.h"
using namespace std;

class PriorityQueue{
	vector< BinaryTreeNode<node>* > pq;
	public:
		int getSize(){
			return pq.size();
		}
		bool isEmpty(){
			return pq.size()==0;
		}
		BinaryTreeNode<node>* getMin(){
			if( isEmpty() ){
				return NULL;
			}else{
				return pq[0];
			}
		}
		void insert(BinaryTreeNode<node>*element){
			if(element==NULL){
				return;
			}
			pq.push_back(element);
			int childIndex=pq.size()-1;
			while(childIndex>0){
				int parentIndex=childIndex/2;
				if(pq[parentIndex]->data.chctr > pq[childIndex]->data.chctr){
					BinaryTreeNode<node>* temp=pq[parentIndex];
					pq[parentIndex]=pq[childIndex];
					pq[childIndex]=temp;
				}else{
					break;
				}
				childIndex=parentIndex;
			}
		}
		void removeMin(){
			if(isEmpty()){
				return;
			}
			pq[0]=pq[pq.size()-1];
			pq.pop_back();
			//Down Heapify
			int parentIndex=0;
			int leftChildIndex=2*parentIndex+1;
			int rightChildIndex=2*parentIndex+2;
			while(leftChildIndex<pq.size()){
				int minIndex=parentIndex;
				if(pq[minIndex]->data.chctr > pq[leftChildIndex]->data.chctr){
					minIndex=leftChildIndex;
				}
				if(rightChildIndex< pq.size()){
					if(pq[minIndex]->data.chctr >pq[rightChildIndex]->data.chctr){
						minIndex=rightChildIndex;
					}
				}
				if(minIndex==parentIndex){
					break;
				}
				BinaryTreeNode<node>* temp=pq[minIndex];
				pq[minIndex]=pq[parentIndex];
				pq[parentIndex]=temp;
				
				parentIndex=minIndex;
				leftChildIndex=2*parentIndex+1;
				rightChildIndex=2*parentIndex+2;
			}
		} 
};                                                                                                                                                                                                                                                                                                                                                                                                
