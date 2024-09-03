import asyncio
import aiomysql
import time
import random
import string
from multiprocessing import Process

# Singlestore에 연결 설정
db_config = {
    'host': '192.168.0.7',  # Singlestore 호스트 주소
    'user': 'root',         # Singlestore 사용자 이름
    'password': 'test',     # Singlestore 비밀번호
    'db': 'test',           # 사용할 데이터베이스 이름
    'port': 3306            # Singlestore 포트 (기본값: 3306)
}

# 데이터 관련 설정
total_records = 20000000  # 삽입할 전체 레코드 수 (프로세스당)
batch_size = 10000  # 배치 크기
num_columns = 50  # 테이블에 생성할 컬럼 수
total_records_str = f"{total_records:,}"  # 쉼표로 구분된 숫자 형식의 문자열

def generate_random_string(string_length=10):
    """랜덤한 문자열을 생성합니다."""
    return ''.join(random.choices(string.ascii_uppercase, k=string_length))

def generate_batch_data(num_rows, num_columns):
    """각 배치에 대해 랜덤 데이터를 생성하여 반환합니다."""
    return [
        tuple(generate_random_string() for _ in range(num_columns))
        for _ in range(num_rows)
    ]

async def table_exists(cursor, table_name):
    """테이블이 존재하는지 확인합니다."""
    await cursor.execute(f"SHOW TABLES LIKE '{table_name}'")
    result = await cursor.fetchone()
    return result is not None

async def create_table(cursor, table_type, num_columns):
    """지정된 개수의 컬럼을 가진 테이블을 생성합니다."""
    table_name = "emp"
    if not await table_exists(cursor, table_name):
        columns = ", ".join([f"col{i} VARCHAR(100)" for i in range(1, num_columns + 1)])  # 지정된 개수의 컬럼 생성
        
        if table_type == 'rowstore':
            create_table_sql = f"""
            CREATE ROWSTORE TABLE {table_name} (
                id BIGINT AUTO_INCREMENT PRIMARY KEY,
                {columns}
            )
            """
        elif table_type == 'columnstore':
            create_table_sql = f"""
            CREATE TABLE {table_name} (
                id BIGINT AUTO_INCREMENT PRIMARY KEY,
                {columns}
                , sort key(id)
            )
            """
        elif table_type == 'temporary':
            create_table_sql = f"""
            CREATE TEMPORARY TABLE {table_name} (
                id BIGINT AUTO_INCREMENT PRIMARY KEY,
                {columns}
            )
            """
        else:
            raise ValueError("Invalid table type specified. Choose from 'rowstore', 'columnstore', or 'temporary'.")
        
        await cursor.execute(create_table_sql)
        print(f"{table_type.capitalize()} 테이블이 {num_columns}개의 컬럼과 함께 성공적으로 생성되었습니다.")

async def insert_batch(cursor, batch_data):
    """배치 데이터를 비동기적으로 데이터베이스에 삽입하고 commit 합니다."""
    placeholders = ", ".join(["%s"] * len(batch_data[0]))  # 컬럼 개수에 맞는 자리 표시자 생성
    insert_data_sql = f"""
    INSERT INTO emp ({', '.join([f'col{i}' for i in range(1, len(batch_data[0]) + 1)])})
    VALUES ({placeholders})
    """
    await cursor.executemany(insert_data_sql, batch_data)

async def run_process(table_type, num_columns):
    # 데이터베이스 연결 풀 생성
    pool = await aiomysql.create_pool(**db_config, maxsize=20)  # 연결 풀 크기 설정

    async with pool.acquire() as conn:
        async with conn.cursor() as cursor:
            # 테이블이 존재하지 않을 경우에만 생성
            await create_table(cursor, table_type, num_columns)
            
            # 데이터 삽입 시작 시간 기록
            start_time = time.time()

            # 전체 레코드 삽입
            for i in range(total_records // batch_size):
                batch_data = generate_batch_data(batch_size, num_columns)
                await insert_batch(cursor, batch_data)
                await conn.commit()  # 각 배치마다 한 번 커밋

            # 데이터 삽입 종료 시간 기록
            end_time = time.time()
            elapsed_time = end_time - start_time
            print(f"{total_records_str}건의 데이터가 프로세스에서 성공적으로 삽입되었습니다. 소요 시간: {elapsed_time:.2f}초")

    # 연결 풀 종료
    pool.close()
    await pool.wait_closed()

def start_process(table_type, num_columns):
    """프로세스에서 비동기 작업을 실행합니다."""
    asyncio.run(run_process(table_type, num_columns))

def start_processes(num_processes=3):
    """여러 프로세스를 시작하여 병렬로 작업을 수행합니다."""
    processes = []
    for _ in range(num_processes):
        p = Process(target=start_process, args=('columnstore', num_columns))
        p.start()
        processes.append(p)

    for p in processes:
        p.join()

if __name__ == "__main__":
    start_processes(num_processes=10)