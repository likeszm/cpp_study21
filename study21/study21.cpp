/*
* CPP学习记录21：内存管理基础
* 
* 知识点：
* 1、不同程序的内存一般是相互独立的（内存修改器除外）
* 2、同一程序的内存被分为四个区域：栈区、堆区、数据区、代码区
* 3、栈区：存放临时变量，一般是函数调用产生的变量
* 4、堆区：这个区域很大，由程序员自由支配
* 5、数据区：全局变量、常量、静态变量都存放于此
* 6、代码区：就是存放程序代码的区域，只读
* 7、一定要小心内存泄漏问题！！！
* 8、使用C的malloc时要利用memset来初始化，然后使用free释放
* 9、C++的new会调用对象的构造函数，也就是说new自带初始化能力，而且delete也能自动调用析构函数!
* 10、delete [] p; 这个括号不要忘了
*/

#include <iostream>

#include <stdio.h>
#include <malloc.h>


#define TEST_MODE 0
//TEST_MODE：   0：不测试 1：测试栈区 2：测试数据区 3：三区比较 
//				4：堆栈区别 5：C内存分配实例 6：CPP内存分配实例

#if TEST_MODE == 3

int var_7 = 10;

#endif // TEST_MODE == 3

void C_memory(void);
void CPP_memory(void);

class Test_class
{
public:
	Test_class()
	{
		std::cout << "创建对象成功!" << std::endl;
	}
	~Test_class()
	{
		std::cout << "销毁对象成功!" << std::endl;
	}

};


int main()
{

#if TEST_MODE == 1			//栈区测试

	//运行发现地址逐渐变小，说明局部变量存储在栈区
	int var_1 = 0;
	double var_2 = 0.1;
	short var_3 = '0';

	std::wcout << "Var\tSize\tAddr" << std::endl;
	std::wcout << "var1:\t" << sizeof(var_1) << "\t" << &var_1 << std::endl;
	std::wcout << "var2:\t" << sizeof(var_2) << "\t" << &var_2 << std::endl;
	std::wcout << "var3:\t" << sizeof(var_3) << "\t" << &var_3 << std::endl;

#elif TEST_MODE == 2		//数据区测试
	
	//运行发现地址逐渐增大，说明静态变量存储在数据区
	static int var_4 = 0;
	static double var_5 = 0.1;
	static short var_6 = '0';

	std::wcout << "Var\tSize\tAddr" << std::endl;
	std::wcout << "var4:\t" << sizeof(var_4) << "\t" << &var_4 << std::endl;
	std::wcout << "var5:\t" << sizeof(var_5) << "\t" << &var_5 << std::endl;
	std::wcout << "var6:\t" << sizeof(var_6) << "\t" << &var_6 << std::endl;

#elif TEST_MODE == 3		//栈区、数据区、堆区比较

	//可以发现，内存地址不连续了，明显被分块了

	int var_8 = 0;
	int* p_var_9 = new int;
	*p_var_9 = 99;
	std::wcout << "*p_var_9 = " << *p_var_9 << std::endl;

	std::wcout << "全局变量地址: " << &var_7 << std::endl;
	std::wcout << "局部变量地址: " << &var_8 << std::endl;
	std::wcout << "申请内存的变量地址: " << p_var_9 << std::endl;

#elif TEST_MODE == 4		//堆栈的区别

	#if 0

//会造成栈溢出，运行出错
	int array[1024][9999] = { 0 };

	#else

//正常运行，说明堆的空间足够大
	int *p_array = new int[1024 * 9999];

	std::wcout << "p_array = " << p_array << std::endl;

	delete[] p_array;

	p_array = NULL;

	#endif

#elif TEST_MODE == 5	//C内存使用范例

	C_memory();

#elif TEST_MODE == 6	//C++内存使用范例

	CPP_memory();

#endif 

	return 0;
}


void C_memory(void)
{
	int len = 0, * p_data = NULL, i = 0;

	printf("memory length = ");

	scanf_s("%d", &len);

	p_data = (int*)malloc(len * sizeof(int));
	if (p_data == NULL)
	{
		printf("memory distrbution failed!\n");
		exit(0);
	}
	else
	{
		printf("memory distrbution successed!\n");
	}

	memset(p_data, 0, len * sizeof(int));	//初始化

	for ( i = 0; i < len; i++)
	{
		printf("data [%d] = %d \n", i, p_data[i]);
	}

	for (i = 0; i < len; i++)
	{
		p_data[i] = i;
	}

	for (i = 0; i < len; i++)
	{
		printf("data [%d] = %d \n", i, p_data[i]);
	}

	free(p_data);
	p_data = NULL;

	return;
}

void CPP_memory(void)
{
#if 0

	Test_class obj1;

	//在这里打断点，以及在函数结束调用出打断点观察控制台输出
	//可以看出，先运行到本函数的结尾的}之后再运行析构函数
	int temp = 0;


#else

	Test_class* p = new Test_class();
	
	int x = 0;
	
	delete p;

	//在delete的前面和后面打断点，可以发现delete会自动调用析构函数

#endif

}
