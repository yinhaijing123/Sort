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
	//1.���ҵ���ǰ�ڵ��Ӧ�ĸ��ڵ�
	//2.�Ƚϸ��ڵ����ӽڵ�Ĺ�ϵ��\
		�����ӽڵ�ȸ��ڵ�С(��ö�Ϊ��С��)�����ӽڵ���н���,\
     ����ǰ���ڵ���Ϊ�µ��ӽڵ㣬�������µĸ��ڵ�;\
	    �����ӽڵ�ȸ��ڵ�����������
	//3.���ӽڵ�Ϊ0ʱ�������ѭ��
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
	/*1.�趨���ڵ�Ϊ��ʼλ�ã��ҵ���Ӧ���ӽڵ�
	  2.�ж����������Ĺ�ϵ������������ֵС����������ֵ��child=child+1;
	  2.�Ƚϵ�ǰ�ĸ��ڵ���ӽڵ�ֵ�Ĵ�С��
		�����ڵ���ӽڵ��ֵ�����ӽڵ�ֵ���н���
	  ����ǰ�ӽڵ㸳�����ڵ㣬�γ��µĸ��ڵ㣬������ӽڵ�
		�����ڵ���ֽڵ��ֵС�����������
	  3.���ӽڵ���±���ڶѵĴ�С�������ѭ����
	*/
	size_t parent = index;
	size_t child = 2 * parent + 1;


	while (child <= heap->size - 1)
	{
		if ((child + 1) > heap->size - 1)                     //�������ڵ�Ϊĳ���ڵ����ڵ�
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
	heap->cmp = Less;            //��ʼΪ��С��
}

void HeapInsert(Heap *heap, HeapDataType value)
{
	if (heap == NULL)                          //�Ƿ�����
	{
		return;
	}
	if (heap->size >= HeapMaxSize)             //������
	{
		return;
	}
	//1.��β������value,����size+1��
	heap->data[heap->size++] = value;

	//2.���µ�����ʹ�ö�����ѵ�����(�ϸ�����)\
	  (��������Less,��öѱ�ʾ��С��;��More,��öѱ�ʾ����)
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

	if (heap->size == 0)             //��Ϊ��
	{
		return;
	}
	if (heap->size == 1)
	{
		heap->size--;
		return;
	}
	//1.���Ѷ�Ԫ�����βԪ�ؽ���,ɾ����βԪ��
	Swap(&heap->data[0], &heap->data[heap->size - 1]);
	heap->size--;
	//2.���µ�����ʹ�ö�����ѵ�����(�³�����)
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
	//1.�������飬�����
	//2.ȡ�Ѷ�Ԫ�أ��������飬��ɾ���Ѷ�Ԫ��
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
							 ����Ϊ���Դ���
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
		printf("[�±�:%d][Ԫ��:%d]\t", i, heap->data[i]);
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
	HeapPrint(&heap, "����в���5������");
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
	HeapPrint(&heap, "����в���5������");
	int ret = HeapRoot(&heap, &value);
	printf("expect ret is 1��actual ret is %d\n", ret);
	printf("expect value is 3��actual value is %d\n", value);
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
	HeapPrint(&heap, "����в���5��Ԫ��");

	HeapErase(&heap);
	HeapPrint(&heap, "ɾ���Ѷ�Ԫ��");

	HeapErase(&heap);
	HeapPrint(&heap, "ɾ���Ѷ�Ԫ��");
	HeapErase(&heap);
	HeapPrint(&heap, "ɾ���Ѷ�Ԫ��");
	HeapErase(&heap);
	HeapPrint(&heap, "ɾ���Ѷ�Ԫ��");
	HeapErase(&heap);
	HeapPrint(&heap, "ɾ���Ѷ�Ԫ��");
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
	HeapPrint(&heap, "����в���3��Ԫ��");

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
