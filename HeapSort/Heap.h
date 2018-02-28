#pragma once

#include<stdio.h>
#include<stdlib.h>

#define HeapMaxSize 1000
typedef int HeapDataType;

typedef int(*Compare)(HeapDataType a, HeapDataType b);

typedef struct Heap {
	HeapDataType data[HeapMaxSize];
	size_t size;
	Compare cmp;
}Heap;

void HeapInit(Heap *heap);                                 //��ʼ����
 
void HeapInsert(Heap *heap, HeapDataType value);           //�����в���Ԫ��

int HeapRoot(Heap *heap,HeapDataType value);               //ȡ�Ѷ�Ԫ��

void HeapErase(Heap *heap);                                //ɾ���Ѷ�Ԫ��
 
int HeapEmpty(Heap *heap);                                 //�ж϶��Ƿ�Ϊ�նѣ���Ϊ�գ�����0�����򣺷���1

size_t HeapSize(Heap *heap);                               //ȡ�ѵĴ�С

void HeapDestroy(Heap* heap);                              //���ٶ�


void AdjustUp(Heap *heap, size_t heap_size, Compare cmp, size_t index);    //�ϸ�

void AdjustDown(Heap *heap, size_t heap_size, Compare cmp, size_t index);  //�³�

void HeapSort(HeapDataType array[], size_t size);            //������
