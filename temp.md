
##### cacheTable.cpp   
通用的队列，可以使用在接收队列，处理队列，缓冲，消息队列等等...

节点
```
struct queueNode {
	//common
	int iSt;			//保存socket
	char cIPBuffer[16];		//保存远端IP地址
	int iIPLength;		//远端IP地址长度
	char CPortBuffer[6];		//保存远端端口
	int iPortLength;		//远端端口长度

	//mq
	char cOperate;		//进行操作

	//common
	char cNodeBuffer[128];	//操作buffer
	int iNodeBufferLength;	//操作buffer长度
};
```
包含一些基本信息

队列
总是从队首生成，队尾消费
```
class queueTable {
private:
  //队列中的节点数组
	struct queueNode m_QueueNode[QUEUELENGTH];
  //队列最大长度
  int m_TotalNum;			
  //队列长度
  int m_NodeNum;			
  //完善队列操作数组
	int m_ClearArray;			

  //判断队列是否为满
	bool fullQueue();					
  //判断队列是否为空
	bool emptyQueue();					

public:   
  //构造函数
	CQueueTable(int iNodeNum);						
	~CQueueTable();
  //插入节点到队列
	void insertQueueNode(queueNode *pQueueNode);
  //根据操作符来查询节点个数			
	int scanQueueNodeNum(char cOperate);					
  //根据索引获取节点
	void getQueueNode(int iIndex, queueNode *pQueueNode *pQueueNode);
  //维护队列，保证队列中没有空节点
  void defendQueue(int iIndex)				
  //在队尾获取消费节点
	void getTailNode(queueNode *pQueueNode);				
  //在队首插入消费节点
	void istHeadNode(queueNode *pQueueNode);				
  //获取完善队列操作数组
	int *getArray();							
  //重置完善队列操作数组
	void resetArray();							
};
```
