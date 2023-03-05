import asyncio
from time import time
marr = []

async def fac():
    while(len(marr) > 0):
        res = marr.pop(0)
        print(res)
        await asyncio.sleep(1)

def dataadd(size):
    for i in range(size):
        marr.append(i)
        
async def main():
    # Schedule three calls *concurrently*:
    begin = time()
    L = await asyncio.gather( 
                             fac(),
                             fac(),
                             fac(),
                             fac(),
                             fac(),
                             fac(),
                             )
    print(L)
    end=time()
    print('실행 시간: {0:.3f}초'.format(end - begin))

dataadd(10)
asyncio.run(main())