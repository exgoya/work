> Table
[T_PG_ADS_LTE_SESSION_INFO]
create table "T_PG_ADS_LTE_SESSION_INFO" ( 		
   "IDENTIFIER" VARCHAR(130),		
   "KEY_INDEX_P" VARCHAR(84) ,		
   "KEY_INDEX_S" VARCHAR(196) ,		
   "PAYLOAD" VARCHAR(1024) NOT NULL,		
   "OPEN_DATE" CHAR(8) ,		
   "OPEN_TIME" CHAR(6) ,		
   "UPDATE_TIME" DATE 		
)sharding by hash(IDENTIFIER);		

alter table "T_PG_ADS_LTE_SESSION_INFO" add constraint "T_PG_ADS_LTE_SESSION_INFO_PK" primary key("IDENTIFIER");		
create index "T_PG_ADS_LTE_SESSION_INFO_IDX01" on "T_PG_ADS_LTE_SESSION_INFO"("KEY_INDEX_P") ;		
create index "T_PG_ADS_LTE_SESSION_INFO_IDX02" on "T_PG_ADS_LTE_SESSION_INFO"("KEY_INDEX_S") ;		
create index "T_PG_ADS_LTE_SESSION_INFO_IDX03" on "T_PG_ADS_LTE_SESSION_INFO"("UPDATE_TIME") ;		


> Execute
# insert // thread 10, 전체 insert ( 10 * 1000 = 10,000 )
./SundbCbssPoc -c 10 -u i -m 1000
[4] : 3226 TPS 
[8] : 3234 TPS
...

# update
./SundbCbssPoc -c 10 -u u -m 1000
[7] : 3013 TPS 
[1] : 3004 TPS
...

# select
./SundbCbssPoc -c 10 -u s -m 1000
[2] : 13052 TPS 
[6] : 12886 TPS
...

# delete
./SundbCbssPoc -c 10 -u d -m 1000
[9] : 3196 TPS 
[4] : 3187 TPS

-> TPS 산정은 summary

> Compile(Makefile)
INC=-I. -I${GOLDILOCKS_HOME}/include -I/home/son2865/work/simple_bmt_cpp/include
->각 환경에 맞게 include path 설정
$> make clean;make all




