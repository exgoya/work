create cluster group g1 cluster member g1n1 host '192.168.0.133' port 10101;
create cluster group g2 cluster member g2n1 host '192.168.0.135' port 10101;
create cluster group g3 cluster member g3n1 host '192.168.0.137' port 10101;

alter cluster group g1 add cluster member g1n2 host '192.168.0.134' port 10101;
alter cluster group g2 add cluster member g2n2 host '192.168.0.136' port 10101;
alter cluster group g3 add cluster member g3n2 host '192.168.0.138' port 10101;

-- hash
drop table test;
create table test (id int, cnt int, name varchar(10)) sharding by hash(id);
create index idx_test on test(id);
commit;

-- range
drop table test;
create table test (id int, cnt int, name varchar(10))
sharding by range(id)
  shard s1 values less than (1001)      at cluster group g1,
  shard s2 values less than (2001)      at cluster group g2,
  shard s3 values less than (MAXVALUE)  at cluster group g3;
create index idx_test on test(id);
commit;

select cluster_member_name, count(*) from test group by cluster_member_name;
