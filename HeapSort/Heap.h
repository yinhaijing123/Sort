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

void HeapInit(Heap *heap);                                 //初始化堆
 
void HeapInsert(Heap *heap, HeapDataType value);           //给堆中插入元素

int HeapRoot(Heap *heap,HeapDataType value);               //取堆顶元素

void HeapErase(Heap *heap);                                //删掉堆顶元素
 
int HeapEmpty(Heap *heap);                                 //判断堆是否为空堆，若为空：返回0；否则：返回1

size_t HeapSize(Heap *heap);                               //取堆的大小

void HeapDestroy(Heap* heap);                              //销毁堆


void AdjustUp(Heap *heap, size_t heap_size, Compare cmp, size_t index);    //上浮

void AdjustDown(Heap *heap, size_t heap_size, Compare cmp, size_t index);  //下沉

void HeapSort(HeapDataType array[], size_t size);            //堆排序
