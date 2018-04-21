#include <stdio.h>
#include <unistd.h>
#include "COSObjectFactory.h"
#include "CThread.h"
#include "osenum.h"

void *TestThread(void *arg)
{
    int i = *(int *)arg;
    while(i < 10000)
    {
        printf(" %d ", i);
        i = i + 2;
        //sleep(1);
    }
    return NULL;
}

int main()
{
    int A = 0;
    int B = 1;
    char p[100];
    COSObjectFactory::GetVersion(p, 100);
    printf("%s\n", p);
    CThread *pThr1 = COSObjectFactory::CreateThread(TestThread, (void *)&A, 0, OS_POLICY_OTHER);
    //pThr1->WaitForQuit(NULL);
    delete pThr1;
    CThread *pThr2 = COSObjectFactory::CreateThread(TestThread, (void *)&B, 0, OS_POLICY_OTHER);
      pThr1->WaitForQuit(NULL);
    delete pThr2;

    printf("hello world\n");
    return 0;
}
