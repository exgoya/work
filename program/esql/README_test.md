useradd -d /home/sgoya -s /bin/bash sgoya


active 종료 (glsnr --stop) -> standby failover
active 기동 (glsnr --start) -> failback
slave 종료  -> active failover
slave 기동 -> reconnect global connection

app

while(
transaction start
group 1 update
group 2 update
commit;
);

while{
if(runUpdate == 0){break;}
if(runUpdate == 1){continue;}
}
19068 -> retry

test schema

create table T1 (c1 number primary key, c2 number) sharding by hash(c1) at cluster wide;

select c1,c2 from t1 where c1 = :num for update
update t1 set c2=:cnum

cnum = cnum++

update t1 set c2=:cnum

commit;
