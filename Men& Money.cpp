#include<iostream>
using namespace std;

class CNode {

public:
	int S1[6];
	int S2[6];
	int info;
	int boat;
	CNode* pNext;
};

class CStack {

public:
	CNode* pHead;
	CNode* pTail;

	CStack()
	{
		pHead = NULL;
		pTail = NULL;
	}

	~CStack()
	{
		CNode* pTrav = pHead;
		while (pTrav != NULL)
		{
			pHead = pHead->pNext;
			delete pTrav;
			pTrav = pHead;
		}
	}

	void Push(CNode* pnn)
	{
		if (pHead == NULL)
		{
			pHead = pnn;
			pTail = pnn;
			pTail->pNext = NULL;

		}
		else
		{
			pnn->pNext = pHead;
			pHead = pnn;
		}
	}

	CNode* Pop()
	{
		CNode* pTrav = pHead;
		if (pTrav == NULL)
		{
			return NULL;
		}
		else
		{
			pHead = pTrav->pNext;
			pTrav->pNext = NULL;
		}
		return pTrav;
	}

	int CheckBK(CNode* pnn)
	{
		int F = 1;
		int R = 0;
		CNode* pTemp = pHead;
		while (pTemp != NULL)
		{
			R = 0;
			for (int i = 0; i < 6; i++)
			{
				if (pnn->S1[i] == pTemp->S1[i])
				{
					R++;
					if (R == 6)
					{
						if (pTemp->boat == pnn->boat)
						{
							F = 0;
							break;
						}
					}
				}
			}
			pTemp = pTemp->pNext;
			if (F == 0)
			{
				return F;
			}
		}
		return F;
	}
};

class CList {

public:
	CNode* pHead;
	CNode* pTail;

	CList()
	{
		pHead = NULL;
		pTail = NULL;
	}

	~CList()
	{
		CNode* pTrav = pHead;
		while (pTrav != NULL)
		{
			pHead = pHead->pNext;
			pTrav = NULL;
			pTrav = pHead;
		}
	}

	void Attach(CNode* pnn)
	{
		if (pHead == NULL)
		{

			pHead = pnn;
			pTail = pnn;
		}
		else
		{
			pTail->pNext = pnn;
			pTail = pnn;
		}
	}


	void Remove(int v)
	{
		CNode* pTrav = pHead;
		CNode* pB = NULL;
		while (pTrav != NULL)
		{
			if (pTrav->info == v)
			{
				break;
			}
			pB = pTrav;
			pTrav = pTrav->pNext;
		}
		if (pB != NULL)
		{
			pB->pNext = pTrav->pNext;
			if (pTail == pTrav)
			{
				pTail = pB;
			}
		}
		else
		{
			pHead = pTrav->pNext;
		}

		delete pTrav;
	}

	
};

CNode* CreateInitState()
{
	CNode* pnn = new CNode;
	for (int i = 0; i < 6; i++)
	{
		pnn->S1[i] = 1;
		pnn->S2[i] = 0;
	}
	pnn->S1[1] = 8;
	pnn->S1[3] = 3;
	pnn->S1[5] = 5;
	pnn->pNext = NULL;
	pnn->boat = 1;
	return pnn;

}

int IsVisited(CNode* pnn, CList& Visit)
{
	
	CNode* pTrav = Visit.pHead;
	int F = 0;
	int R = 0;
	//Visit.pTail->pNext = NULL;
	//cout << "pTail = " << Visit.pTail->S1[0] << Visit.pTail->S1[1] << Visit.pTail->S1[2] << Visit.pTail->S1[3] << Visit.pTail->S1[4] << Visit.pTail->S1[5] << endl << endl;
	
	
	//pTrav = Visit.pHead;
	//while (pTrav != NULL)
	//{
		//cout << "Visited up:   " << pTrav->S1[0] << pTrav->S1[1] << pTrav->S1[2] << pTrav->S1[3] << pTrav->S1[4] << pTrav->S1[5] << " boat: "<<pTrav->boat << endl;
		//cout << "Visited down: " << pTrav->S2[0] << pTrav->S2[1] << pTrav->S2[2] << pTrav->S2[3] << pTrav->S2[4] << pTrav->S2[5] <<  endl << endl;
		//pTrav = pTrav->pNext;
	//}

	pTrav = Visit.pHead;
	//Visit.pTail->pNext = NULL;
	while (pTrav != NULL)
	{
		F = 0;
		for (int i = 0; i < 6; i++)
		{
			if (pTrav->S1[i] == pnn->S1[i])
			{
				F++;
				if (F == 6)
				{
					if (pTrav->boat == pnn->boat)
					{
						R = 1;
						break;
					}
				}
			}
		}
		pTrav = pTrav->pNext;
		if (R == 1)
		{
			return R;
			break;
		}
	}
	
	return R;
}

void ExpandChildren(CNode* pCurr, CStack& S, CList& Visit, int& C)
{
	int Result = 1;
	int Result2 = 1;
	C = 0;
	Visit.Attach(pCurr);
	//cout << "pCurr up:   " << pCurr->S1[0] << pCurr->S1[1] << pCurr->S1[2] << pCurr->S1[3] << pCurr->S1[4] << pCurr->S1[5] << endl;
	//cout << "pCurr down: " << pCurr->S2[0] << pCurr->S2[1] << pCurr->S2[2] << pCurr->S2[3] << pCurr->S2[4] << pCurr->S2[5]  << endl;
	//cout << "Boat: " << pCurr->boat << endl << endl;

	int a, b, c1, c2, c3, c4, c5, c6, c7 = 16, d00, d01, d10, d11, d20, d21, d30, d31, d40, d41, d50, d51, d60 = 0, d61 = 0, d70 = 1, d71 = 1;
	for (int k = 0; k < 6; k += 2)
	{
		if (k == 0)
		{
			a = 2; b = 4; c1 = 8; c2 = 5; c3 = 3; c4 = 8; c5 = 13; c6 = 11; c7 = 16;
			d00 = 1; d01 = 1; d10 = 0; d11 = 1; d20 = 1; d21 = 0;	    d30 = 0; d31 = 0; d40 = 0; d41 = 1; d50 = 1; d51 = 0;
		}
		if (k == 2)
		{
			a = 0; b = 4; c1 = 13; c2 = 8; c3 = 5; c4 = 3; c5 = 11; c6 = 8; c7 = 16;
			d00 = 1; d01 = 1; d10 = 1; d11 = 0; d20 = 0; d21 = 1;		d30 = 0; d31 = 0; d40 = 1; d41 = 0; d50 = 0; d51 = 1;
		}
		if (k == 4)
		{
			a = 0; b = 2; c1 = 11; c2 = 8; c3 = 3; c4 = 5; c5 = 8; c6 = 13; c7 = 16;
			d00 = 1; d01 = 1; d10 = 1; d11 = 0; d20 = 0; d21 = 1;		d30 = 0; d31 = 0; d40 = 0; d41 = 1; d50 = 1; d51 = 0;
		}

		if (pCurr->S1[k] == 1 && (pCurr->boat % 2) != 0)
		{
			for (int i = 0; i < 6; i++)
			{
				if (pCurr->S1[i] != 0)
				{
					CNode* pnn = new CNode;
					for (int r = 0; r < 6; r++)
					{
						pnn->S1[r] = pCurr->S1[r];
						pnn->S2[r] = pCurr->S2[r];
					}
					pnn->pNext = NULL;
					if (i == 1)
					{
						pnn->S1[i] = 0;
						pnn->S2[i] = 8;
					}
					else if (i == 3)
					{
						pnn->S1[i] = 0;
						pnn->S2[i] = 3;
					}
					else if (i == 5)
					{
						pnn->S1[i] = 0;
						pnn->S2[i] = 5;
					}
					else
					{
						pnn->S1[i] = 0;
						pnn->S2[i] = 1;
					}

						pnn->S1[k] = 0;
						pnn->S2[k] = 1;


					//cout << "if "<< k <<" is up1(pnn): " << i << " " << pnn->S1[0] << pnn->S1[1] << pnn->S1[2] << pnn->S1[3] << pnn->S1[4] << pnn->S1[5] << endl;
					//cout << "if "<< k <<" is up2(pnn): " << i << " " << pnn->S2[0] << pnn->S2[1] << pnn->S2[2] << pnn->S2[3] << pnn->S2[4] << pnn->S2[5] << endl << endl;

					if (!((pnn->S1[a] == d00 && pnn->S1[b] == d01 && (pnn->S1[1] + pnn->S1[3] + pnn->S1[5]) > c1) ||
						  (pnn->S1[a] == d10 && pnn->S1[b] == d11 && (pnn->S1[1] + pnn->S1[3] + pnn->S1[5]) > c2) ||
						  (pnn->S1[a] == d20 && pnn->S1[b] == d21 && (pnn->S1[1] + pnn->S1[3] + pnn->S1[5]) > c3) ||

						  (pnn->S2[a] == d30 && pnn->S2[b] == d31 && (pnn->S2[1] + pnn->S2[3] + pnn->S2[5]) > c4) ||
						  (pnn->S2[a] == d40 && pnn->S2[b] == d41 && (pnn->S2[1] + pnn->S2[3] + pnn->S2[5]) > c5) ||
						  (pnn->S2[a] == d50 && pnn->S2[b] == d51 && (pnn->S2[1] + pnn->S2[3] + pnn->S2[5]) > c6) ))
					{

						pnn->boat = 2;
						Result = IsVisited(pnn, Visit);
						if (Result == 0)
						{
							int E = S.CheckBK(pnn);
							if (E == 1)
							{
								
								S.Push(pnn);
								
								C++;
								//cout << "True " << k << " up" << endl << endl;
							}
						}

					}
				}
			}
			//cout << endl << "--------------------------------------------------------------------------------" << endl << endl;
		}

		//-------------------------------------------------------------------------------------------------------------------------------------------------\\

		else if(pCurr->S1[k] == 0 && (pCurr->boat % 2) == 0)
		{
			for (int i = 0; i < 6; i++)
			{
				if (pCurr->S1[i] == 0)
				{
					CNode* pnn = new CNode;
					for (int r = 0; r < 6; r++)
					{
						pnn->S1[r] = pCurr->S1[r];
						pnn->S2[r] = pCurr->S2[r];
					}
					pnn->pNext = NULL;
					if (i == 1)
					{
						pnn->S1[i] = 8;
						pnn->S2[i] = 0;
					}
					else if (i == 3)
					{
						pnn->S1[i] = 3;
						pnn->S2[i] = 0;
					}
					else if (i == 5)
					{
						pnn->S1[i] = 5;
						pnn->S2[i] = 0;
					}
					else
					{
						pnn->S1[i] = 1;
						pnn->S2[i] = 0;
					}

						pnn->S1[k] = 1;
						pnn->S2[k] = 0;

					//cout << "if else "<< k <<" is down1(pnn): " << i << " " << pnn->S1[0] << pnn->S1[1] << pnn->S1[2] << pnn->S1[3] << pnn->S1[4] << pnn->S1[5] << endl;
					//cout << "if else "<< k <<" is down2(pnn): " << i << " " << pnn->S2[0] << pnn->S2[1] << pnn->S2[2] << pnn->S2[3] << pnn->S2[4] << pnn->S2[5] << endl << endl;

					if (!((pnn->S2[a] == d00 && pnn->S2[b] == d01 && (pnn->S2[1] + pnn->S2[3] + pnn->S2[5]) > c1) ||
						  (pnn->S2[a] == d10 && pnn->S2[b] == d11 && (pnn->S2[1] + pnn->S2[3] + pnn->S2[5]) > c2) ||
						  (pnn->S2[a] == d20 && pnn->S2[b] == d21 && (pnn->S2[1] + pnn->S2[3] + pnn->S2[5]) > c3) ||

						  (pnn->S1[a] == d30 && pnn->S1[b] == d31 && (pnn->S1[1] + pnn->S1[3] + pnn->S1[5]) > c4) ||
						  (pnn->S1[a] == d40 && pnn->S1[b] == d41 && (pnn->S1[1] + pnn->S1[3] + pnn->S1[5]) > c5) ||
						  (pnn->S1[a] == d50 && pnn->S1[b] == d51 && (pnn->S1[1] + pnn->S1[3] + pnn->S1[5]) > c6) ))
					{

						pnn->boat = 1;
						Result = IsVisited(pnn, Visit);
						if (Result == 0)
						{
							int E = S.CheckBK(pnn);
							if (E == 1)
							{
								S.Push(pnn);
								
								C++;
								//cout << "True " << k << " down" << endl << endl;
							}
						}

					}

				}
			}
			//cout << endl << "--------------------------------------------------------------------------------" << endl << endl;

		}
		
	}
}

int Status(CNode* pnn)
{
	int F = 1;
	for (int i = 0; i < 6; i++)
	{
		if (pnn->S1[i] != 0)
		{
			F = 0;
			return F;
		}
	}
	return F;
}

void Display(CNode* pnn, int SN, CList& Final)
{
	CNode* pTrav = Final.pHead;
	while (pTrav != NULL)
	{
		if (Status(pTrav) == 1)
		{
			cout << "\n-------------------------------------------------------------------------------------------------------";
			cout << " Solution number (" << SN << ") S1: " << pTrav->S1[0] << pTrav->S1[1] << pTrav->S1[2] << pTrav->S1[3] << pTrav->S1[4] << pTrav->S1[5] << " boat: " << pTrav->boat << endl;
			cout << " Solution number (" << SN << ") S2: " << pTrav->S2[0] << pTrav->S2[1] << pTrav->S2[2] << pTrav->S2[3] << pTrav->S2[4] << pTrav->S2[5] << endl;
			cout << "-------------------------------------------------------------------------------------------------------\n";
		}
		else
		{
			cout << " S1: " << pTrav->S1[0] << pTrav->S1[1] << pTrav->S1[2] << pTrav->S1[3] << pTrav->S1[4] << pTrav->S1[5] << " boat: " << pTrav->boat << endl;
			cout << " S2: " << pTrav->S2[0] << pTrav->S2[1] << pTrav->S2[2] << pTrav->S2[3] << pTrav->S2[4] << pTrav->S2[5] << endl << endl;
		}
		pTrav = pTrav->pNext;
	}
}

void BackTrack(int& SN, CList& Final)
{
	CStack S;
	CList Visit;
	CNode* pnn = CreateInitState();
	
	int C = 0;
	Final.Attach(pnn);
	S.Push(pnn);
	int R = 0;
	
	while (S.pHead != NULL)
	{
		if (S.pHead != NULL)
		{
			//cout << " SPOP1 head: " << S.pHead->S1[0] << S.pHead->S1[1] << S.pHead->S1[2] << S.pHead->S1[3] << S.pHead->S1[4] << S.pHead->S1[5] << endl;
			//cout << " SPOP2 head: " << S.pHead->S2[0] << S.pHead->S2[1] << S.pHead->S2[2] << S.pHead->S2[3] << S.pHead->S2[4] << S.pHead->S2[5] << endl << endl;

		}

		CNode* pCurr = S.Pop();
		
		if (S.pHead != NULL)
		{
			//cout << " SPOP1 after head: " << S.pHead->S1[0] << S.pHead->S1[1] << S.pHead->S1[2] << S.pHead->S1[3] << S.pHead->S1[4] << S.pHead->S1[5] << endl;
			//cout << " SPOP2 after head: " << S.pHead->S2[0] << S.pHead->S2[1] << S.pHead->S2[2] << S.pHead->S2[3] << S.pHead->S2[4] << S.pHead->S2[5] << endl << endl;

		}

		ExpandChildren(pCurr, S, Visit, C);
		
		if (C > 0)
		{
			Final.Attach(pCurr);
		}

		if (Status(pCurr) == 1)
		{
			SN++;
		}

		if (S.pHead == NULL)
		{
			Display(pCurr, SN, Final);
		}
	}
}



void main()
{
	int SN = 0;
	CList Final;
	BackTrack(SN,Final);

	cout << "\n-------------------------------------------------------------------------------------------------------Number of solutions (" << SN <<")";
	cout << "\n\n";
	system("pause");
}

