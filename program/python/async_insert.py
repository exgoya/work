import asyncio
import aiomysql
import random
import string
import time

# Singlestore에 연결 설정
db_config = {
    'host': '192.168.0.7',  # Singlestore 호스트 주소
    'user': 'root',         # Singlestore 사용자 이름
    'password': 'test',     # Singlestore 비밀번호
    'db': 'test',           # 사용할 데이터베이스 이름
    'port': 3306            # Singlestore 포트 (기본값: 3306)
}

def generate_random_data():
    """랜덤한 직원 데이터를 생성합니다."""
    name = ''.join(random.choices(string.ascii_letters, k=10))
    age = random.randint(20, 65)
    hire_date = f"202{random.randint(0, 3)}-{random.randint(1, 12):02d}-{random.randint(1, 28):02d}"
    department = random.choice(['Engineering', 'Marketing', 'HR', 'Finance', 'Sales'])
    return (name, age, hire_date, department)

async def insert_batch(pool, batch_data):
    """배치 데이터를 비동기적으로 데이터베이스에 삽입하고 commit 합니다."""
    async with pool.acquire() as conn:
        async with conn.cursor() as cursor:
            insert_data_sql = "INSERT INTO emp (name, age, hire_date, department) VALUES (%s, %s, %s, %s)"
            await cursor.executemany(insert_data_sql, batch_data)
            await conn.commit()  # 각 배치마다 commit

async def create_table(cursor, table_type):
    """사용자가 지정한 테이블 유형에 따라 테이블을 생성합니다."""
    await cursor.execute("DROP TABLE IF EXISTS emp")
    
    if table_type == 'rowstore':
        create_table_sql = """
        CREATE ROWSTORE TABLE emp (
            id BIGINT AUTO_INCREMENT PRIMARY KEY,
            name VARCHAR(100) NOT NULL,
            age INT NOT NULL,
            hire_date DATE,
            department TEXT
        )
        """
    elif table_type == 'columnstore':
        create_table_sql = """
        CREATE TABLE emp (
            id BIGINT AUTO_INCREMENT PRIMARY KEY,
            name VARCHAR(100) NOT NULL,
            age INT NOT NULL,
            hire_date DATE,
            department TEXT
           -- ,SORT KEY(name)
        ) 
        """
    elif table_type == 'temporary':
        create_table_sql = """
        CREATE TEMPORARY TABLE emp (
            id BIGINT AUTO_INCREMENT PRIMARY KEY,
            name VARCHAR(100) NOT NULL,
            age INT NOT NULL,
            hire_date DATE,
            department TEXT
        )
        """
    else:
        raise ValueError("Invalid table type specified. Choose from 'rowstore', 'columnstore', or 'temporary'.")
    
    await cursor.execute(create_table_sql)
    print(f"{table_type.capitalize()} 테이블이 성공적으로 생성되었습니다.")

async def main(table_type):
    # 데이터베이스 연결 풀 생성
    pool = await aiomysql.create_pool(**db_config)

    async with pool.acquire() as conn:
        async with conn.cursor() as cursor:
            # 선택된 테이블 유형으로 테이블 생성
            await create_table(cursor, table_type)
            
            # 기존 데이터 삭제 (초기화)
            await cursor.execute("DELETE FROM emp")
            print("기존 데이터가 삭제되었습니다.")

    # 데이터 삽입 시작 시간 기록
    start_time = time.time()

    # 10,000,000건의 무작위 데이터 생성 및 삽입
    batch_size = 1000  # 배치 크기
    total_records = 1000000
    batches = [ [generate_random_data() for _ in range(batch_size)] for _ in range(total_records // batch_size) ]

    # 코루틴을 통해 비동기적으로 데이터 삽입 및 각 배치마다 commit
    tasks = [insert_batch(pool, batch) for batch in batches]
    await asyncio.gather(*tasks)

    # 데이터 삽입 종료 시간 기록
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"10,000,000건의 데이터가 성공적으로 삽입되었습니다. 소요 시간: {elapsed_time:.2f}초")

    # 연결 풀 종료
    pool.close()
    await pool.wait_closed()

if __name__ == "__main__":
    # 'rowstore', 'columnstore', 'temporary' 중 선택하여 사용
    table_type = 'columnstore'
    asyncio.run(main(table_type))