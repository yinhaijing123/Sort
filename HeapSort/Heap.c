#include"Heap.h"

int Less(HeapDataType a, HeapDataType b)
{
	return a < b;
}

int More(HeapDataType a, HeapDataType b)
{
	return a > b;
}

void Swap(HeapDataType * a, HeapDataType *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void AdjustUp(Heap *heap, size_t heap_size, Compare cmp, size_t index)
{
	if (
		heap == NULL)
	{
		return;
	}
	//1.先找到当前节点对应的父节点
	//2.比较父节点与子节点的关系，\
		如若子节点比父节点小(设该堆为最小堆)，则父子节点进行交换,\
     将当前父节点作为新的子节点，重新找新的父节点;\
	    如若子节点比父节点大，则结束调整
	//3.当子节点为0时，则结束循环
	size_t child = index;
	size_t parent = (child - 1) / 2;

	while (child > 0)
	{
		if (cmp(heap->data[child], heap->data[parent]))
		{
			Swap(&heap->data[child], &heap->data[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}

	}
}


void AdjustDown(Heap *heap, size_t heap_size, Compare cmp, size_t index)
{
	if (heap == NULL)
	{
		return;
	}
	/*1.设定父节点为初始位置，找到对应的子节点
	  2.判断左右子树的关系，若右子树的值小于左子树的值，child=child+1;
	  2.比较当前的父节点和子节点值的大小，
		若父节点比子节点的值大，则父子节点值进行交换
	  将当前子节点赋给父节点，形成新的父节点，并获得子节点
		若父节点比字节点的值小，则结束调整
	  3.当子节点的下标大于堆的大小，则结束循环。
	*/
	size_t parent = index;
	size_t child = 2 * parent + 1;


	while (child <= heap->size - 1)
	{
		if ((child + 1) > heap->size - 1)                     //该树最后节点为某根节点的左节点
		{
			if (cmp(heap->data[child], heap->data[parent]))
			{
				Swap(&heap->data[child], &heap->data[parent]);
			}
			break;
		}
		if (cmp(heap->data[child + 1], heap->data[child]))
		{
			child = child + 1;
		}
		if (cmp(heap->data[child], heap->data[parent]))
		{
			Swap(&heap->data[child], &heap->data[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapInit(Heap *heap)
{
	if (heap == NULL)
	{
		return;
	}
	heap->size = 0;
	heap->cmp = Less;            //初始为最小堆
}

void HeapInsert(Heap *heap, HeapDataType value)
{
	if (heap == NULL)                          //非法输入
	{
		return;
	}
	if (heap->size >= HeapMaxSize)             //堆已满
	{
		return;
	}
	//1.向尾部插入value,并将size+1；
	heap->data[heap->size++] = value;

	//2.重新调整，使该堆满足堆的性质(上浮调整)\
	  (若传参数Less,则该堆表示最小堆;传More,则该堆表示最大堆)
	AdjustUp(heap, heap->size, Less, heap->size - 1);
}

int HeapRoot(Heap *heap, HeapDataType* value)
{
	if (heap == NULL || heap->size == 0)
	{
		return 0;
	}
	*value = heap->data[0];
	return 1;
}

void HeapErase(Heap *heap)
{
	if (heap == NULL)
	{
		return;
	}

	if (heap->size == 0)             //堆为空
	{
		return;
	}
	if (heap->size == 1)
	{
		heap->size--;
		return;
	}
	//1.将堆顶元素与堆尾元素交换,删除堆尾元素
	Swap(&heap->data[0], &heap->data[heap->size - 1]);
	heap->size--;
	//2.重新调整，使该堆满足堆的性质(下沉调整)
	if (heap->size > 1)
	{
		AdjustDown(heap, heap->size, Less, 0);
	}
}

int HeapEmpty(Heap *heap)
{
	if (heap == NULL || heap->size > 0)
	{
		return 0;
	}
	return  1;
}

size_t HeapSize(Heap *heap)
{
	if (heap == NULL || heap->size == 0)
	{
		return 0;
	}
	return heap->size;
}

void HeapDestroy(Heap* heap)
{
	if (heap == NULL)
	{
		return;
	}
	heap->size = 0;
}

void HeapSort(HeapDataType array[], size_t size)
{
	//1.遍历数组，插入堆
	//2.取堆顶元素，存入数组，并删除堆顶元素
	if (array == NULL)
	{
		return;
	}
	size_t i = 0;
	Heap heap;
	HeapInit(&heap);
	for (i = 0; i < size; i++)
	{
		HeapInsert(&heap, array[i]);
	}
	i = 0;
	while (heap.size)
	{
		int value = 0;
		int ret = HeapRoot(&heap, &value);
		array[i++] = value;
		HeapErase(&heap);
	}
}
/****************************************************************************
							 以下为测试代码
*****************************************************************************/

#define TEST_HEADER printf("=======================%s========================\n",__FUNCTION__)

void HeapPrint(Heap *heap, char *msg)
{
	if (heap == NULL)
	{
		return;
	}
	size_t i = 0;
	printf("%s\n", msg);
	for (i = 0; i < heap->size; i++)
	{
		printf("[下标:%d][元素:%d]\t", i, heap->data[i]);
	}
	printf("\n");
}

void TestHeapInsert()
{
	TEST_HEADER;
	Heap heap;
	HeapInit(&heap);

	HeapInsert(&heap, 5);
	HeapInsert(&heap, 8);
	HeapInsert(&heap, 3);
	HeapInsert(&heap, 2);
	HeapInsert(&heap, 1);
	HeapPrint(&heap, "向堆中插入5个数据");
}

void TestHeapRoot()
{
	TEST_HEADER;
	Heap heap;
	HeapInit(&heap);

	HeapDataType value = 0;
	HeapInsert(&heap, 9);
	HeapInsert(&heap, 18);
	HeapInsert(&heap, 3);
	HeapInsert(&heap, 36);
	HeapInsert(&heap, 58);
	HeapPrint(&heap, "向堆中插入5个数据");
	int ret = HeapRoot(&heap, &value);
	printf("expect ret is 1，actual ret is %d\n", ret);
	printf("expect value is 3，actual value is %d\n", value);
}

void TestHeapErase()
{
	TEST_HEADER;
	Heap heap;
	HeapInit(&heap);

	HeapInsert(&heap, 5);
	HeapInsert(&heap, 8);
	HeapInsert(&heap, 3);
	HeapInsert(&heap, 2);
	HeapInsert(&heap, 1);
	HeapPrint(&heap, "向堆中插入5个元素");

	HeapErase(&heap);
	HeapPrint(&heap, "删除堆顶元素");

	HeapErase(&heap);
	HeapPrint(&heap, "删除堆顶元素");
	HeapErase(&heap);
	HeapPrint(&heap, "删除堆顶元素");
	HeapErase(&heap);
	HeapPrint(&heap, "删除堆顶元素");
	HeapErase(&heap);
	HeapPrint(&heap, "删除堆顶元素");
}

void TestHeapEmpty()
{
	TEST_HEADER;
	Heap heap;
	HeapInit(&heap);

	int ret = HeapEmpty(&heap);
	printf("expect ret is 1,actual ret is %d\n", ret);

	HeapInsert(&heap, 3);
	HeapInsert(&heap, 2);
	HeapInsert(&heap, 1);
	HeapPrint(&heap, "向堆中插入3个元素");

	ret = HeapEmpty(&heap);
	printf("expect ret is 0,actual ret is %d\n", ret);
}

void TestSort()
{
	TEST_HEADER;
	int array[5] = { 8,5,9,6,3 };
	int i = 0;
	HeapSort(array, 5);
	for (i = 0; i < 5; i++)
	{
		printf("%d\t", array[i]);
	}
	printf("\n");
}
int main()
{
	//TestHeapInsert();
	//TestHeapRoot();
	//TestHeapErase();
	//TestHeapEmpty();
	TestSort();

	system("pause");
	return 0;
}
