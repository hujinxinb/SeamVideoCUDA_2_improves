#include"ZbitVideoMergeAlg.h"
#include <string>
#define CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 
#include<array>
using namespace std;
//C++通常在字符串中最后一个字符的后面存储一个字符'\0'，可以用来计算字符数组的长度
//str[i]=str[i]-'a'+'A';小写变大写   比如str[i]='3' str[i]-'0'就是数字3


//我们用递归的时候，可以把一些需要的东西作为递归函数参数，或者返回值来用
//要么用递归，要么用迭代，迭代的时候我们可以留意是从前往后还是从后往前
//用空间换时间，新建一个vector保存偶数再把它插到原来的vector后面，很多时候都要新建一个数据类型来保存一些东西，会在算法上简化很多
//递归的时候，有些需要一直保存的变量需要去外部定义，
//注意可以紧接在递归语句后加几句话处理


//int a=9/4等于2，如果要返回3的话我们可以dim3 grid((src1.cols + block.x - 1) / block.x, (src1.rows + block.y - 1) / block.y);这种用于cuda编程里设定好块的情况下再设定每块里有多少线程

//（一道不错的leetcode）Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
//https://www.nowcoder.com/practice/bd73f6b52fdc421d91b14f9c909f9104?tpId=46&tqId=29040&tPage=1&rp=1&ru=/ta/leetcode&qru=/ta/leetcode/question-ranking
//动态规划一般用于可以将大问题分割成小问题，并且可以通过小问题的解来解决大问题，常见于子字符串，而且一般是new一个length+1的数组，然后计算到dp[0]或dp[n],每次计算dp[i]又用一次从i到n-1或0到i的遍历
//很多时候都要新建一个数据类型来保存一些东西，会在算法上简化很多



//int array[3][5];
//
//int(*ch)[5] = array; //正确，两者指向的类型相同，此相当于(int (*ch)[5] = &array[0];)
//int **ch = array; //这个不正确，因为前者是指向整型指针的指针，后者是指向整型数组的指针，类型不同，在做函数参数也要注意。


//string a=s.substr(0,5);       //获得字符串s中 从第0位开始的长度为5的字符串//默认时的长度为从开始位置到尾


//快慢指针找到链表中间节点
//ListNode* slow = head;
//ListNode* fast = head;
//while (fast->next != null&&fast->next->next != null){
//	fast = fast->next->next;
//	slow = slow->next;
//}
//这时slow就是中间节点




//atoi(x.c_str());将string型的x转成int型   
//int a = 99;  char c[3] = "";  _itoa_s(a, c, 3, 10);这是将int型转char *

//string s;cin>>s;或者string str(s.size(),'*');

//vector<int> a; vector<int> temp; temp=a; vector<int> temp2(b,e);创建一个容器，这个容器保存了位于[b,e)中迭代器所指示元素的一个复件

//students.erase(students.begin()+i);注意这个要是在循环里面，那判断条件要是while(i!=students.size())，因为每次erase会修改students.size()

//insert和erase，可以c.insert(d,b,e);或c.erase(b,e);这里b,e都是迭代器


//for (auto it = bottom.begin(); it != bottom.end(); it++)
//	ret.push_back(*it);
//等价于ret.insert(ret.end(), bottom.begin(), bottom.end());


//sort(numbers.begin(), numbers.end()); // 排序，取数组中间那个数
//int middle = numbers[numbers.size() / 2];


//bool compare(const Student& x, const Student& y)
//{
//	return x.name < y.name;
//}
//
//sort(student.begin(),student.end(),compare);


//根据中序遍历算法生成中序双向链表
//void convertHelper(TreeNode* cur, TreeNode*& pre)
//{
//	if (cur == nullptr) return;
//
//	convertHelper(cur->left, pre);
//
//	cur->left = pre;
//	if (pre) pre->right = cur;
//	pre = cur;
//
//	convertHelper(cur->right, pre);
//}


//回溯就是在递归后加一句把递归前的一些已改变量给退回
//class Solution {
//public:
//	vector<vector<int> > buffer;
//	vector<int> tmp;

//	vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
//		if (root == NULL)
//			return buffer;
//		tmp.push_back(root->val);
//		if ((expectNumber - root->val) == 0 && root->left == NULL && root->right == NULL)
//		{
//			buffer.push_back(tmp);
//		}
//		FindPath(root->left, expectNumber - root->val);
//		FindPath(root->right, expectNumber - root->val);
//
//		tmp.pop_back();
//		return buffer;
//	}
//};





//“student.a am I”。后来才意识到，这家伙原来把句子单词的顺序翻转了，正确的句子应该是“I am a student.”
//class Solution {
//public:
//	string ReverseSentence(string str) {
//		string res = "", tmp = "";
//		for (unsigned int i = 0; i < str.size(); ++i){
//			if (str[i] == ' ') res = " " + tmp + res, tmp = "";
//			else tmp += str[i];
//		}
//		if (tmp.size()) res = tmp + res;
//		return res;
//	}
//};




//输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。


/*对vector容器内的数据进行排序，按照 将a和b转为string后
若 a＋b<b+a  a排在在前 的规则排序,
如 2 21 因为 212 < 221 所以 排序后为 21 2
to_string() 可以将int 转化为string
*/ 

//class Solution {
//public:
//	static bool cmp(int a, int b){
//		string A = "";
//		string B = "";
//		A += to_string(a);
//		A += to_string(b);
//		B += to_string(b);
//		B += to_string(a);
//
//		return A<B;
//	}
//	string PrintMinNumber(vector<int> numbers) {
//		string  answer = "";
//		sort(numbers.begin(), numbers.end(), cmp);
//		for (int i = 0; i<numbers.size(); i++){
//			answer += to_string(numbers[i]);
//		}
//		return answer;
//	}
//};



//在.h的class定义里申明int* m_flags;   在.cpp里实现	int m_total = nubmers->length(); m_flags = new int[m_total]; 这种写法是常规写法，用于不知道具体数量的数组


//*p=*q不是两指针相等而是两个指针指向的内容相等。一个地址只能放一个指针，所以不论让有多少个指针相等，都只是让这些指针指向了同一个“变量”，所以有时要用memcpy而不能用指针等于
//程序秒退在最后加句getchar();
//()的优先级高于*，所以float *g()表示一个函数，它的返回类型为指向浮点数的指针，又如fp是一个函数指针，(*fp)()可以调用这个函数
//char cmd[128];gets(cmd); char c;c=getchar();
//注意c里的sleep()函数

//基类Base里virtual void print(){ cout << "Base"; }；派生类Derived里void print(){ cout << "Derived"; }；主函数Base *point = new Derived();point->print();最后显示的是Derived。如果不加virtual显示的是Base
// virtual void setWTA_K(int wta_k) = 0; 纯虚函数后面加=0，即表示一个虚拟函数只是提供了一个可被子类型改写的接口。但是，它本身并不能通过虚拟机制被调用。这就是纯虚拟函数
//包含（或继承）一个或多个纯虚拟函数的类被编译器识别为抽象基类。试图创建一个抽象基类的独立类对象会导致编译时刻错误。
// Query 声明了纯虚拟函数
// 所以, 程序员不能创建独立的 Query 类对象
// ok: NameQuery 中的 Query 子对象
//Query *pq = new NameQuery("Nostromo");
// 错误: new 表达式分配 Query 对象
//Query *pq2 = new Query;
//抽象基类只能作为子对象出现在后续的派生类中。





//只要是.h里写了的方法，.cpp里必须要实现，否则用起来会报错


//int calendar[13][31];  int (*monthp)[31]; monthp=calendar;

//calendar[month][day]=0即是*(*(calendar+month)+day)=0

//char *r;strcpy(r,s);strcat(r,t);是错的，要char *r;r=malloc(strlen(s)+strlen(t)+1);strcpy(r,s);strcat(r,t);




//
//int main()
//{
//	//batchProcess();
//
//	FILE* pFileOut = fopen("stitch.yuv", "w+");
//
//	ZBIT_VM_init();
//
//	Video_Merge_Handler ptemp = NULL;//这里Video_Merge_Handler是define为了void *
//	ptemp = ZBIT_VM_create();//可以把ZbitVideoMerge *赋给void *，void *能保存下来，如果要再用的时候，把void *强制转换成ZbitVideoMerge *就可以了。就是说如int *可以直接赋给void *，void *再变int *要强制转换
//	if (NULL == ptemp)
//	{
//		printf("func[%s] LIne[%d] create failed ! \r\n", __FUNCTIONW__, __LINE__);
//		return -1;
//	}
//
//	PZBIT_VM_CONFIG inputCfg = new zbit_vm_cfg;//PZBIT_VM_CONFIG是被typedef成了一个结构体指针，我们用new 结构体名的方式就能给它内存，然后切记要给它里面要用的变量赋初值如下
//
//	inputCfg->m_iInputVideoHeight = 720;
//	inputCfg->m_iInputVideoWidth = 1280;
//	inputCfg->m_iVideoFrameRate = 25;
//
//	ZBIT_VM_setConfig(ptemp, inputCfg);
//
//
//#if 0
//	ZbitVideoMerge zb(1);
//
//	PZBIT_VM_CONFIG inputCfg = new zbit_vm_cfg;
//	inputCfg->m_iInputVideoHeight = 720;
//	inputCfg->m_iInputVideoWidth = 1280;
//	inputCfg->m_iVideoFrameRate = 25;
//
//	zb.SetConfig(inputCfg);
//#endif
//
//	FILE* pFileIn1 = fopen("result.yuv", "rb+");
//	FILE* pFileIn2 = fopen("result1.yuv", "rb+");
//
//
//	//下面这几行代码可以求出yuv视频的帧数放在all里
//	fseek(pFileIn1, 0L, SEEK_END);
//	long size = ftell(pFileIn1);
//	int all = size / (1280 * 720 * 1.5);
//	rewind(pFileIn1);
//
//	int bufLen = 1280 * 720 * 3 / 2;
//	unsigned char* pYuvBuf1 = new unsigned char[bufLen];
//	unsigned char* pYuvBuf2 = new unsigned char[bufLen];
//	unsigned char* pYuvBuf3 = new unsigned char[4000 * 1080 * 3 / 2];
//
//
//	fread(pYuvBuf1, bufLen*sizeof(unsigned char), 1, pFileIn1);
//	fread(pYuvBuf2, bufLen*sizeof(unsigned char), 1, pFileIn2);
//
//
//
//	PZBIT_VM_FRAMEINFO IN frameA = new zbit_vm_frameinfo;
//
//	frameA->ptrY = pYuvBuf1;
//	frameA->ptrU = pYuvBuf1 + 1280 * 720;
//	frameA->ptrV = pYuvBuf1 + 1280 * 720 + 1280 * 720 / 4;
//
//
//	PZBIT_VM_FRAMEINFO IN frameB = new zbit_vm_frameinfo;
//
//	frameB->ptrY = pYuvBuf2;
//	frameB->ptrU = pYuvBuf2 + 1280 * 720;
//	frameB->ptrV = pYuvBuf2 + 1280 * 720 + 1280 * 720 / 4;
//
//	PZBIT_VM_FRAMEINFO IN frameOUT = new zbit_vm_frameinfo;
//
//
//	frameOUT->ptrY = pYuvBuf3;		//其实这里pYuvBuf3只是个 new unsigned char[4000*1080*3/2];里面内容是空的，但需要这样先赋给frameOUT->ptrY等，
//	//否则后面memcpy(framOUT->ptrY, yuvImg.data, MergeFrameSize);会出错，,memcpy这个函数前两都是指针，第三个是长度，将二指针开始的该长度字节的数据给一指针开始的该长度
//	frameOUT->ptrU = pYuvBuf3 + 4000 * 1080;
//	frameOUT->ptrV = pYuvBuf3 + 4000 * 1080 + 4000 * 1080 / 4;
//
//	ZBIT_VM_algProcess(ptemp, frameA, frameB, NULL, NULL, 2, frameOUT);
//
//	//zb.VideoProcess(frameA, frameB, NULL, NULL, 2, frameOUT);
//
//
//	for (int a = 0; a < 10; a++)
//	{
//	
//		for (int i = 0; i < all; i++)
//		{
//			int start1 = clock();
//
//			fread(pYuvBuf1, bufLen*sizeof(unsigned char), 1, pFileIn1);//fread函数第一个参数是指针，可以是char *，第二个是读取的字节数，第三个是要读多少个第二参数，第四个是fopen返回的文件指针
//			//，这次fread后文件指针就会停在这不会回到文件开头（这点很好）
//			fread(pYuvBuf2, bufLen*sizeof(unsigned char), 1, pFileIn2);
//
//
//
//			frameA->ptrY = pYuvBuf1;
//			frameA->ptrU = pYuvBuf1 + 1280 * 720;
//			frameA->ptrV = pYuvBuf1 + 1280 * 720 + 1280 * 720 / 4;
//
//
//			frameB->ptrY = pYuvBuf2;
//			frameB->ptrU = pYuvBuf2 + 1280 * 720;
//			frameB->ptrV = pYuvBuf2 + 1280 * 720 + 1280 * 720 / 4;
//
//			//zb.VideoProcess(frameA, frameB, NULL, NULL, 2, frameOUT);
//
//			ZBIT_VM_algProcess(ptemp, frameA, frameB, NULL, NULL, 2, frameOUT);
//
//
//
//
//			fwrite(frameOUT->ptrY, frameOUT->m_iWidth * frameOUT->m_iHeight, 1, pFileOut);
//			fwrite(frameOUT->ptrU, frameOUT->m_iWidth * frameOUT->m_iHeight / 4, 1, pFileOut);
//			fwrite(frameOUT->ptrV, frameOUT->m_iWidth * frameOUT->m_iHeight / 4, 1, pFileOut);
//
//			//memcpy(pYuvBufs, yuvImg.data, bufLens*sizeof(unsigned char));
//
//			int start2 = clock();
//			cout << "total: " << start2 - start1 << "width: " << frameOUT->m_iWidth << "height:" << frameOUT->m_iHeight << endl;
//
//		}
//
//		rewind(pFileIn1);
//		rewind(pFileIn2);
//	}
//
//	delete[] pYuvBuf1;
//	delete[] pYuvBuf2;
//	delete[] pYuvBuf3;
//	delete[] frameA;
//	delete[] frameB;
//	delete[] frameOUT;
//	ZBIT_VM_delete(ptemp);
//
//
//	fclose(pFileIn1);
//	fclose(pFileIn2);
//	fclose(pFileOut);
//
//	return 1;
//}
//
//




int main()
{
	//batchProcess();

	//FILE* pFileOut = fopen("stitch.yuv", "w+");

	ZBIT_VM_init();

	Video_Merge_Handler ptemp = NULL;//这里Video_Merge_Handler是define为了void *
	ptemp = ZBIT_VM_create();//可以把ZbitVideoMerge *赋给void *，void *能保存下来，如果要再用的时候，把void *强制转换成ZbitVideoMerge *就可以了。就是说如int *可以直接赋给void *，void *再变int *要强制转换
	if (NULL == ptemp)
	{
		printf("func[%s] LIne[%d] create failed ! \r\n", __FUNCTIONW__, __LINE__);
		return -1;
	}

	zbit_vm_cfg cfg = { 1280, 720, 1, 25 };

	PZBIT_VM_CONFIG inputCfg = &cfg ;

	ZBIT_VM_setConfig(ptemp, inputCfg);

	FILE* pFileIn1 = fopen("result.yuv", "rb+");
	FILE* pFileIn2 = fopen("result1.yuv", "rb+");


	//下面这几行代码可以求出yuv视频的帧数放在all里
	fseek(pFileIn1, 0L, SEEK_END);
	long size = ftell(pFileIn1);
	int all = size / (1280 * 720 * 1.5);
	rewind(pFileIn1);

	const int bufLen = 1280*720*3/2;
	const int bufLenMax = 2500 * 720 * 3 / 2;
	

	//下面这几行必须采用堆分配，经过测试栈分配不了1280*720*3/2这么大的空间，很简单，写个char c[1280*720*3/2]就运行不了
	unsigned char* pYuvBuf1 = new unsigned char[bufLen];
	unsigned char* pYuvBuf2 = new unsigned char[bufLen];
	unsigned char* pYuvBuf3 = new unsigned char[3000 * 720 * 3 / 2];


	fread(pYuvBuf1, bufLen*sizeof(unsigned char), 1, pFileIn1);
	fread(pYuvBuf2, bufLen*sizeof(unsigned char), 1, pFileIn2);




	zbit_vm_frameinfo framea = { pYuvBuf1, pYuvBuf1 + 1280 * 720, pYuvBuf1 + 1280 * 720 + 1280 * 720 / 4 };

	PZBIT_VM_FRAMEINFO IN frameA = &framea;

	//frameA->ptrY = pYuvBuf1;
	//frameA->ptrU = pYuvBuf1 + 1280 * 720;
	//frameA->ptrV = pYuvBuf1 + 1280 * 720 + 1280 * 720 / 4;


	zbit_vm_frameinfo frameb = { pYuvBuf2, pYuvBuf2 + 1280 * 720, pYuvBuf2 + 1280 * 720 + 1280 * 720 / 4 };

	PZBIT_VM_FRAMEINFO IN frameB = &frameb;

	//frameB->ptrY = pYuvBuf2;
	//frameB->ptrU = pYuvBuf2 + 1280 * 720;
	//frameB->ptrV = pYuvBuf2 + 1280 * 720 + 1280 * 720 / 4;

	zbit_vm_frameinfo frameout = { pYuvBuf3, pYuvBuf3 + 3000 * 720, pYuvBuf3 + 3000 * 720 + 3000 * 720 / 4 };

	PZBIT_VM_FRAMEINFO IN frameOUT = &frameout;


	//frameOUT->ptrY = pYuvBuf3;		//其实这里pYuvBuf3只是个 new unsigned char[4000*1080*3/2];里面内容是空的，但需要这样先赋给frameOUT->ptrY等，
	////否则后面memcpy(framOUT->ptrY, yuvImg.data, MergeFrameSize);会出错，,memcpy这个函数前两都是指针，第三个是长度，将二指针开始的该长度字节的数据给一指针开始的该长度
	//frameOUT->ptrU = pYuvBuf3 + 4000 * 1080;
	//frameOUT->ptrV = pYuvBuf3 + 4000 * 1080 + 4000 * 1080 / 4;

	ZBIT_VM_algProcess(ptemp, frameA, frameB, NULL, NULL, 2, frameOUT);

	//zb.VideoProcess(frameA, frameB, NULL, NULL, 2, frameOUT);


	


		for (int i = 0; i < all; i++)
		{
			int start1 = clock();

			fread(pYuvBuf1, bufLen*sizeof(unsigned char), 1, pFileIn1);//fread函数第一个参数是指针，可以是char *，第二个是读取的字节数，第三个是要读多少个第二参数，第四个是fopen返回的文件指针
			//，这次fread后文件指针就会停在这不会回到文件开头（这点很好）
			fread(pYuvBuf2, bufLen*sizeof(unsigned char), 1, pFileIn2);



			frameA->ptrY = pYuvBuf1;
			frameA->ptrU = pYuvBuf1 + 1280 * 720;
			frameA->ptrV = pYuvBuf1 + 1280 * 720 + 1280 * 720 / 4;


			frameB->ptrY = pYuvBuf2;
			frameB->ptrU = pYuvBuf2 + 1280 * 720;
			frameB->ptrV = pYuvBuf2 + 1280 * 720 + 1280 * 720 / 4;

	

			ZBIT_VM_algProcess(ptemp, frameA, frameB, NULL, NULL, 2, frameOUT);

			/*fwrite(frameOUT->ptrY, frameOUT->m_iWidth * frameOUT->m_iHeight, 1, pFileOut);
			fwrite(frameOUT->ptrU, frameOUT->m_iWidth * frameOUT->m_iHeight / 4, 1, pFileOut);
			fwrite(frameOUT->ptrV, frameOUT->m_iWidth * frameOUT->m_iHeight / 4, 1, pFileOut);*/

			//memcpy(pYuvBufs, yuvImg.data, bufLens*sizeof(unsigned char));

			int start2 = clock();
			cout << "total: " << start2 - start1 << "width: " << frameOUT->m_iWidth << "height:" << frameOUT->m_iHeight << endl;

		}

		rewind(pFileIn1);
		rewind(pFileIn2);


	delete[] pYuvBuf1;
	delete[] pYuvBuf2;
	delete[] pYuvBuf3;
	ZBIT_VM_delete(ptemp);

	fclose(pFileIn1);
	fclose(pFileIn2);
	//fclose(pFileOut);

	return 1;
}


