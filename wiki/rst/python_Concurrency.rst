[[PageOutline(1-5,Table of Contents, floated)]]

{{{ #!div style=“background: #ffd; border: 3px ridge; width :300px”

’‘’Python’’’

{{{ #!python def hello(): return “world” }}}

}}}
---

== 파이썬 동시성 프로그래밍 ==
[https://www.inflearn.com/course/%ED%8C%8C%EC%9D%B4%EC%8D%AC-%EB%8F%99%EC%8B%9C%EC%84%B1-%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D/dashboard
파이썬 동시성 프로그래밍 : 데이터 수집부터 웹 개발까지 (feat. FastAPI)]

[https://github.com/amamov/teaching-async-python 강의코드]

== 개요 ==

-  동시성 (Concurrentcy) 프로그래밍
-  클라이언트와 서버간 통신
-  시스템 디스크 파일 읽기/쓰기
-  데이터베이스 쿼리 작업
-  API 사용
-  병렬성 (Parallelism) 프로그래밍
-  비디오, 오디오 또는 이미지 처리
-  컴퓨터 비전 ( Computer Vision : 컴퓨터 공학의 한 분야로 컴퓨터에게
   시각(vision) 데이터 처리 능력을 부여하는 기술 )
-  머신러닝 ( 데이터를 통해 학습한 후 정보를 바탕으로 결정을 내리기 위해
   학습한 내용을 적용하는 알고리즘 )
-  딥러닝 ( 딥 러닝은 머신 러닝의 하위 개념. 둘 다 광범위한 인공 지능의
   카테고리에 속하지만 인간과 가장 유사한 인공 지능을 구동하는 것 )

== 0. 환경 (venv) ==

{{{ % python –version Python 3.9.6 % python -m venv venv % source
venv/bin/activate (venv) exgoya@exgoya-MacBook-Pro teaching-async-python
% (venv) exgoya@exgoya-MacBook-Pro teaching-async-python % deactivate
exgoya@exgoya-MacBook-Pro teaching-async-python % }}}

== 1. 코루틴과 비동기 함수 ==
[https://docs.python.org/ko/3.9/library/asyncio-task.html]

=== 1.1 바운드와 블로킹 === ==== CPU Bound ==== 프로세스 진행 속도가 CPU
속도에 의해 제한됨을 의미한다. {{{ #!python def cpu_bound_func(number:
int): total = 1 arrange = range(1, number + 1) for i in arrange: for j
in arrange: for k in arrange: total *= i* j \* k

::

   return total

if **name** == “\ **main**\ ”: result = cpu_bound_func(50) print(result)
}}} ==== I/O Bound ==== 프로세스가 진행되는 속도가 I/O 하위 시스템의
속도에 의해 제한됨을 의미한다. {{{ #!python def io_bound_func():
print(“값을 입력해주세요.”) input_value = input() return
int(input_value) + 100

if **name** == “\ **main**\ ”: result = io_bound_func() print(result)
}}}

==== Network i/o bound ==== {{{ #!python import requests

def io_bound_func(): result = requests.get(“https://google.com”) return
result

if **name** == “\ **main**\ ”: for i in range(10): result =
io_bound_func() print(result) }}}

==== Blocking & Non-Blocking ==== - Blocking : A 함수가 B 함수를 호출 할
때, B 함수가 자신의 작업이 종료되기 전까지 A 함수에게 제어권을 돌려주지
않는 것 - Non-blocking : A 함수가 B 함수를 호출 할 때, B 함수가 제어권을
바로 A 함수에게 넘겨주면서, A 함수가 다른 일을 할 수 있도록 하는 것

=== 1.2 동기와 비동기 === - Synchronous : A 함수가 B 함수를 호출 할 때,
B 함수의 결과를 A 함수가 처리하는 것 - Asynchronous : A 함수가 B 함수를
호출 할 때, B 함수의 결과를 B 함수가 처리하는 것 ==== 동기(Sync) ====
{{{ #!python import time

def delivery(name, mealtime): print(f”{name}에게 배달 완료!“)
time.sleep(mealtime) print(f”{name} 식사 완료, {mealtime}시간 소요…“)
print(f”{name} 그릇 수거 완료”)

def main(): delivery(“A”, 5) delivery(“B”, 3) delivery(“C”, 4)

if **name** == “\ **main**\ ”: start = time.time() print(main()) # None
end = time.time() print(end - start) }}}

{{{ #!sh % python 02-1-sync.py A에게 배달 완료! A 식사 완료, 5시간 소요…
A 그릇 수거 완료 B에게 배달 완료! B 식사 완료, 3시간 소요… B 그릇 수거
완료 C에게 배달 완료! C 식사 완료, 4시간 소요… C 그릇 수거 완료 None
12.004334926605225 }}}

==== 비동기(Async) ====

{{{ #!python import time import asyncio

async def delivery(name, mealtime): print(f”{name}에게 배달 완료!“)
await asyncio.sleep(mealtime) print(f”{name} 식사 완료, {mealtime}시간
소요…“) print(f”{name} 그릇 수거 완료”) return mealtime

async def main():

::

   result = await asyncio.gather(
       delivery("A", 5),
       delivery("B", 3),
       delivery("C", 4),
   )

   print(result)

if **name** == “\ **main**\ ”: start = time.time() asyncio.run(main())
end = time.time() print(end - start) }}}

{{{ #!sh % python 02-2-async.py A에게 배달 완료! B에게 배달 완료! C에게
배달 완료! B 식사 완료, 3시간 소요… B 그릇 수거 완료 C 식사 완료, 4시간
소요… C 그릇 수거 완료 A 식사 완료, 5시간 소요… A 그릇 수거 완료 [5, 3,
4] 5.002339124679565 }}}

=== 1.3 Coroutine ( 코루틴 ) === 코루틴은 서브루틴의 더 일반화된
형태입니다. 서브루틴은 한 지점에서 진입하고 다른 지점에서 탈출합니다.
코루틴은 여러 다른 지점에서 진입하고, 탈출하고, 재개할 수 있습니다.
이것들은 async def 문으로 구현할 수 있습니다.

-  루틴 : 코드의 흐름
-  메인루틴 : 프로그램 메인 코드 흐름
-  서브루틴 : 하나의 지점에서 진입 (call) 다른 지점에서 탈출 (return) (
   함수, 메소드 )

\|||||\| ============> \|\| \||메인루틴||대기||메인루틴 \|\|
\||서브루틴|\|

-  코루틴 : 여러 다른 지점에서 진입, 탈출, 재개 ( 동시성 코딩 방법 )

\|||||||||||\| ========================> \|\|
\||메인루틴||대기||메인루틴||대기||메인루틴||대기 \|\|
\||코루틴||대기||코루틴||대기||코루틴

{{{ #!div style=“background: #ffd; border: 3px ridge;”

’‘’Corotine’’’

코루틴 함수 : 다른 지점에서 진입, 탈출, 재개 가능 1. 코루틴을 async def
문법으로 만듭니다 2. 최상위 코루틴은 asyncio.run()으로 실행하고 3. 종속
코루틴은 await를 붙여 실행합니다 코루틴 함수 예시 (async def) {{{
#!python async def delivery(name, mealtime): print(f”{name}에게 배달
완료!“) await asyncio.sleep(mealtime) print(f”{name} 식사 완료,
{mealtime}시간 소요…“) print(f”{name} 그릇 수거 완료”) return mealtime
}}} 메인 루틴 : asyncio.gather 를 사용하여 코루틴 함수들을 동시에 수행
{{{ #!python async def main():

::

   result = await asyncio.gather(
       delivery("A", 5),
       delivery("B", 3),
       delivery("C", 4),
   )

   print(result)

if **name** == “\ **main**\ ”: start = time.time() asyncio.run(main())
end = time.time() print(end - start) }}} 결과 {{{ #!sh % python
02-2-async.py A에게 배달 완료! B에게 배달 완료! C에게 배달 완료! B 식사
완료, 3시간 소요… B 그릇 수거 완료 C 식사 완료, 4시간 소요… C 그릇 수거
완료 A 식사 완료, 5시간 소요… A 그릇 수거 완료 [5, 3, 4]
5.002339124679565 }}} }}}

==== Awaitables (어웨이터블) ====

await 표현식에서 사용될 수 있는 객체 {{{ #!python async def main():

::

   await delivery("A", 5),
   await delivery("B", 3),
   await delivery("C", 4),

}}} {{{ #!sh % python 02-2-async.py A에게 배달 완료! A 식사 완료, 5시간
소요… A 그릇 수거 완료 B에게 배달 완료! B 식사 완료, 3시간 소요… B 그릇
수거 완료 C에게 배달 완료! C 식사 완료, 4시간 소요… C 그릇 수거 완료
12.006020069122314 }}}

==== Task ==== 태스크는 코루틴을 동시에 예약하는 데 사용됩니다.

{{{ #!python async def main():

::

   task1 = asyncio.create_task(delivery("A", 5))
   task2 = asyncio.create_task(delivery("B", 3))
   task3 = asyncio.create_task(delivery("C", 4))

   await task1
   await task2
   await task3

}}} {{{ #!sh % python 02-2-async.py A에게 배달 완료! B에게 배달 완료!
C에게 배달 완료! B 식사 완료, 3시간 소요… B 그릇 수거 완료 C 식사 완료,
4시간 소요… C 그릇 수거 완료 A 식사 완료, 5시간 소요… A 그릇 수거 완료
5.002243757247925 }}}

==== Future ==== Future는 비동기 연산의 최종 결과를 나타내는 특별한
저수준 어웨이터블 객체입니다.

=== 1.4 코루틴 테스트 ===

일반 {{{ #!python import requests import time

def fetcher(session, url): with session.get(url) as response: return
response.text

def main(): urls = [“https://naver.com”, “https://google.com”,
“https://instagram.com”] \* 10

::

   with requests.Session() as session:
       result = [fetcher(session, url) for url in urls]
       print(result)

if **name** == “\ **main**\ ”: start = time.time() main() end =
time.time() print(end - start) # 12 }}} 동시성 (aiohttp) {{{ #!python
import aiohttp import time import asyncio

async def fetcher(session, url): async with session.get(url) as
response: return await response.text()

async def main(): urls = [“https://naver.com”, “https://google.com”,
“https://instagram.com”] \* 10

::

   async with aiohttp.ClientSession() as session:
       result = await asyncio.gather(*[fetcher(session, url) for url in urls])
       print(result)

if **name** == “\ **main**\ ”: start = time.time() asyncio.run(main())
end = time.time() print(end - start) # 4.8

}}}

-  수행시간 - 일반: 16s, 동시성: 6s

== 2. 멀티 스레딩 와 멀티 프로세스 ==

=== 2.1 동시성 (Concurrentcy) vs 병렬성 (Parallelism) ===
\||동시성||병렬성|\| \||동시에 실행되는 것 같이 보이는 것||동시에 여러
작업이 처리되는 것|\| \||싱글 코어에서 멀티 쓰레드(Multi thread)를 동작
시키는 방식||멀티 코어에서 멀티 쓰레드(Multi thread)를 동작시키는
방식|\| \||한번에 많은 것을 처리||한번에 많은 일을 처리|\| \||논리적인
개념||물리적인 개념|\| ==== 그림1 ==== [[Image(scp.png)]] ==== 그림2
==== [[Image(con.png)]] ==== 그림3 ==== [[Image(concoffee.png)]]

=== 2.2 Multi Thread ===

==== GIL (Global interpreter lock ) ====

GIL은 Global Interpreter Lock의 약어로, 여러 개의 스레드가 파이썬
바이트코드를 한번에 하나만 사용할 수 있게 락을 거는 것을 의미한다. 쉽게
말해서 하나의 스레드만 파이썬 인터프리터를 제어할 수 있도록 하는
뮤텍스라고 보면 된다. 아래와 같은 특징이 있다. - thread context switch에
따른 비용 발생 - network,disk i/o bound 에서 유용하게 사용할 수 있지만
Cpu i/o bound 상황에서는 이점이 없음 ==== 그림4 ====
[[Image(gil.png,500px)]]

Multi Thread sample code {{{ #!python
#https://docs.python.org/3.7/library/concurrent.futures.html#concurrent.futures.ThreadPoolExecutor
import requests import time import os import threading from
concurrent.futures import ThreadPoolExecutor

def fetcher(params): session = params[0] url = params[1]
print(f”{os.getpid()} process \| {threading.get_ident()} url : {url}“)
with session.get(url) as response: return response.text

def main(): urls = [“https://google.com”, “https://apple.com”] \* 3

::

   executor = ThreadPoolExecutor(max_workers=3)

   with requests.Session() as session:

       params = [(session, url) for url in urls]
       results = list(executor.map(fetcher, params))
       #print(results)

if **name** == “\ **main**\ ”: start = time.time() main() end =
time.time() print(end - start) # 6.8

}}}

max_workers=1 {{{ #!sh % python 03-3-io-multi-threading.py
/Users/exgoya/git/teaching-async-python/venv/lib/python3.9/site-packages/urllib3/**init**.py:34:
NotOpenSSLWarning: urllib3 v2.0 only supports OpenSSL 1.1.1+, currently
the ‘ssl’ module is compiled with ‘LibreSSL 2.8.3’. See:
https://github.com/urllib3/urllib3/issues/3020 warnings.warn( 20677
process \| 123145424990208 url : https://google.com 20677 process \|
123145424990208 url : https://apple.com 20677 process \| 123145424990208
url : https://google.com 20677 process \| 123145424990208 url :
https://apple.com 20677 process \| 123145424990208 url :
https://google.com 20677 process \| 123145424990208 url :
https://apple.com 1.5145001411437988 }}}

max_workers=3 {{{ #!sh % python 03-3-io-multi-threading.py
/Users/exgoya/git/teaching-async-python/venv/lib/python3.9/site-packages/urllib3/**init**.py:34:
NotOpenSSLWarning: urllib3 v2.0 only supports OpenSSL 1.1.1+, currently
the ‘ssl’ module is compiled with ‘LibreSSL 2.8.3’. See:
https://github.com/urllib3/urllib3/issues/3020 warnings.warn( 20704
process \| 123145319292928 url : https://google.com 20704 process \|
123145336082432 url : https://apple.com 20704 process \| 123145352871936
url : https://google.com 20704 process \| 123145336082432 url :
https://apple.com 20704 process \| 123145336082432 url :
https://google.com 20704 process \| 123145319292928 url :
https://apple.com 0.7527620792388916 }}}

=== 2.3 Multi Process ===

새로운 복제 프로세스를 생성해 사용하는 방법

-  cpu bound 코드에서 이점을 가져갈 수 있음 (물리적인 Cpu core 여유가
   있어야함)
-  추가적인 메모리 필요 ( 프로세스 복제, 프로세스간 독립적인 메모리 사용
   )

!ThreadPoolExecutor -> !ProcessPoolExecutor {{{ #!python import time
import os import threading import sys from concurrent.futures import
ProcessPoolExecutor #from concurrent.futures import ThreadPoolExecutor

sys.set_int_max_str_digits(1000000) nums = [30] \* 100

def cpu_bound_func(num): print(f”{os.getpid()} process \|
{threading.get_ident()} thread, {num}“) numbers = range(1, num) total =
1 for i in numbers: for j in numbers: for k in numbers: total *= i* j \*
k return total

def main(): #executor = ProcessPoolExecutor(max_workers=10) executor =
ProcessPoolExecutor(max_workers=10) results =
list(executor.map(cpu_bound_func, nums)) print(results)

if **name** == “\ **main**\ ”: start = time.time() main() end =
time.time() print(end - start) # 22

}}}

== 3. 동시성 프로그래밍으로 데이터 수집 ==

=== 3.1 개요 ===

[https://beautiful-soup-4.readthedocs.io/en/latest/ Beautiful-soup] :
파이썬 Html & xml parser

[https://developers.google.com/search/docs/crawling-indexing/robots/intro?hl=ko
Google Robots.txt Guide] : Google Robots.txt 가이드
[https://www.google.com/robots.txt robots.txt]

=== 3.2 책정보 Scraping ===

-  코루틴 함수를 사용해 페이지별 책정보를 동시에 요청

{{{ #!python from bs4 import BeautifulSoup import aiohttp import asyncio

https://www.crummy.com/software/BeautifulSoup/bs4/doc/
======================================================

pip install beautifulsoup4
==========================

““” 웹 크롤링 : 검색 엔진의 구축 등을 위하여 특정한 방법으로 웹 페이지를
수집하는 프로그램 웹 스크래핑 : 웹에서 데이터를 수집하는 프로그램 ““”

async def fetch(session, url, i): print(i + 1) async with
session.get(url) as response: html = await response.text() soup =
BeautifulSoup(html, “html.parser”) cont_thumb = soup.find_all(“div”,
“cont_thumb”) for cont in cont_thumb: title = cont.find(“p”,
“txt_thumb”) if title is not None: print(title.text)

async def main(): BASE_URL =
“https://bjpublic.tistory.com/category/%EC%A0%84%EC%B2%B4%20%EC%B6%9C%EA%B0%84%20%EB%8F%84%EC%84%9C”
urls = [f”{BASE_URL}?page={i}” for i in range(1, 10)] async with
aiohttp.ClientSession() as session: await
asyncio.gather(\*[fetch(session, url, i) for i, url in enumerate(urls)])

if **name** == “\ **main**\ ”: asyncio.run(main()) }}}

=== 3.3 고양이 사진 Download ( naver api ) ===

{{{ #!python import os import aiohttp import asyncio from config import
get_secret import aiofiles

pip install aiofiles==0.7.0
===========================

async def img_downloader(session, img): img_name =
img.split(“/”)[-1].split(“?”)[0]

::

   try:
       os.mkdir("./images")
   except FileExistsError:
       pass

   async with session.get(img) as response:
       if response.status == 200:
           async with aiofiles.open(f"./images/{img_name}", mode="wb") as file:
               img_data = await response.read()
               await file.write(img_data)

async def fetch(session, url, i): print(i + 1) headers = {
“X-Naver-Client-Id”: get_secret(“NAVER_API_ID”),
“X-Naver-Client-Secret”: get_secret(“NAVER_API_SECRET”), } async with
session.get(url, headers=headers) as response: result = await
response.json() items = result[“items”] images = [item[“link”] for item
in items] await asyncio.gather(\*[img_downloader(session, img) for img
in images])

async def main(): BASE_URL = “https://openapi.naver.com/v1/search/image”
keyword = “cat” urls =
[f”{BASE_URL}?query={keyword}&display=20&start={1+ i*20}” for i in
range(10)] async with aiohttp.ClientSession() as session: await
asyncio.gather(\*[fetch(session, url, i) for i, url in enumerate(urls)])

if **name** == “\ **main**\ ”: asyncio.run(main())

}}} config.py {{{ #!python import json from pathlib import Path from
typing import Optional

BASE_DIR = Path(**file**).resolve().parent

def get_secret( key: str, default_value: Optional[str] = None,
json_path: str = str(BASE_DIR / “secrets.json”), ): with open(json_path)
as f: secrets = json.loads(f.read()) try: return secrets[key] except
KeyError: if default_value: return default_value raise
EnvironmentError(f”Set the {key} environment variable.”) }}}
secrets.json {{{ #!sh { “NAVER_API_ID”:“Tjs4go68m2N\__DwxmuPU”,
“NAVER_API_SECRET”:“eq6pnHsUuX” } }}}

== 4. 빅데이터 관리의 핵심 기술 MongoDB 이해와 구축 ==

=== 4.1 Create Mongodb in Cloud === https://www.mongodb.com/ [[BR]]
https://www.mongodb.com/try/download/shell

=== 4.2 ODM & ORM === ODM (Object-Document Mapper) : NoSQL에서 Document
Database를 지원하기 위해 데이터를 변환하는 프로그래밍 기법 - 구현체 :
odmantic, beanie

ORM (Object-Relational Mapper)
   데이터베이스와 객체 지향 프로그래밍 언어 간의 호환되지 않는 데이터를
   변환하는 프로그래밍 기법

== 5. 실전 프로젝트 : 콜렉터 ( FastAPI ) ==

=== 5.1 FastAPI === https://fastapi.tiangolo.com/ko/

FastAPI는 현대적이고, 빠르며(고성능), 파이썬 표준 타입 힌트에 기초한
Python3.6+의 API를 빌드하기 위한 웹 프레임워크입니다.

==== ASGI (Asynchronous Server Gateway Interface) ====

https://asgi.readthedocs.io/en/latest/introduction.html

-  WSGI (Web Server Gateway Interface) : 웹서버 인터페이스 (동기)
-  ASGI (Asynchronous Server Gateway Interface) : 비동기 웹서버
   인터페이스 ==== 그림5 ==== [[Image(wsgi.png)]] ==== 그림6 ====
   [[Image(asgi.png)]]

https://jellybeanz.medium.com/cgi-wsgi-asgi-%EB%9E%80-cgi-wsgi-asgi-bc0ba75fa5cd
==== uvicorn ==== https://www.uvicorn.org/

Python용 ASGI 웹 서버

== 6. 결과물 ==

[raw-attachment:mydog-main.zip:wiki:goya/python mydog-main.zip]

/search {{{ #!python @app.get(“/search”, response_class=HTMLResponse)
async def search(request: Request, q: str):

::

   # 1. 쿼리에서 검색어 추출
   keyword = q
   # (예외처리)
   #  - 검색어가 없다면 사용자에게 검색을 요구 return
   if not keyword:
       context = {"request": request, "title": title}
       print("debug -- no keyword")
       return templates.TemplateResponse(
           "./index.html",
           context
       )
   #  - 해당 검색어에 대해 수집된 데이터가 이미 DB에 존재한다면 해당 데이터를 사용자에게 보여준다. return
   if await mongodb.engine.find_one(BookModel, BookModel.keyword == keyword):
       print("exist keyword data")
       books = await mongodb.engine.find(BookModel, BookModel.keyword == keyword)
       return templates.TemplateResponse("./index.html", {"request": request, "title": title, "books": books},)

   # 2. 데이터 수집기로 해당 검색어에 대해 데이터를 수집한다.
   naver_book_scraper = NaverBookScraper()
   books = await naver_book_scraper.search(keyword, 10)
   book_models = []
   for book in books:
       book_model = BookModel(
           keyword=keyword,
           publisher=book["publisher"],
           discount=book["discount"],
           image=book["image"],
       )
       book_models.append(book_model)
   # 3. DB에 수집된 데이터를 저장한다.
   await mongodb.engine.save_all(book_models)

   #  - 수집된 각각의 데이터에 대해서 DB에 들어갈 모델 인스턴스를 찍는다.
   #  - 각 모델 인스턴스를 DB에 저장한다.
   return templates.TemplateResponse(
       "./index.html",
       {"request": request, "title": title, "books": books},
   )

}}}

Mongodb Object {{{ #!python from odmantic import AIOEngine from
motor.motor_asyncio import AsyncIOMotorClient

from app.config import MONGO_DB_NAME, MONGO_URL

class MongoDB: def **init**\ (self): self.client = None self.engine =
None

::

   def connect(self):
       self.client = AsyncIOMotorClient(MONGO_URL)
       self.engine = AIOEngine(client=self.client, database=MONGO_DB_NAME)

       print("db와 성공적으로 연결이 완료되었습니다.")

   def close(self):
       self.client.close()

mongodb = MongoDB()

}}}

Book model {{{ #!python from odmantic import Model

class BookModel(Model): keyword: str publisher: str discount: int image:
str

::

   class Config:
       collection = "books"

}}}

Book template {{{ #!python {% include “header.html” %}

::

     <center>
       <form id="search_form" action="/search">
         <input
           type="search"
           placeholder="keyword"
           id="search_input"
           name="q"
         />
         <button type="submit">검색</button>
       </form>
     </center>
   <main>
     {% if books %}
     <!--  -->
     <center>
       <h3 style="color: gray">{{books|length}}개 데이터 수집..</h3>
     </center>
     <section>
       {% for book in books %}
       <div>
         <img src="{{book.image}}" width="150px" height="200px" />
         <p>
           {% if book.publisher|length > 10 %}
           <!--  -->
           {{book.publisher[:10]}}...
           <!--  -->
           {% else %} {{book.publisher}} {% endif %}
         </p>
         <p>{{book.discount}} 원</p>
       </div>
       {% endfor %}
     </section>

     <hr />

     <!--  -->
     {% else %}
     <center><h3 style="color: gray">Please Input Keyword (반려동물 관련서적을 검색할 수 있습니다)</h3></center>
     {% endif %}
   </main>
   {% include "footer.html" %}

}}}

== 7. 강의코드.zip == 강의코드 :
[raw-attachment:teaching-async-python-main.zip:wiki:goya/python
teaching-async-python-main.zip]
