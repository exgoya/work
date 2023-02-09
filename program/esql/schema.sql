
connect test test;
drop sequence if exists seq1;
commit;
create sequence seq1;

drop table if exists test;
commit;

create table test (c1 number primary key, c2 number) sharding by hash(c1) at cluster wide;

insert into test values(seq1.nextval,seq1.nextval);
insert into test select seq1.nextval, seq1.nextval from test;

commit;

insert into test select seq1.nextval, seq1.nextval from test;
insert into test select seq1.nextval, seq1.nextval from test;
insert into test select seq1.nextval, seq1.nextval from test;
insert into test select seq1.nextval, seq1.nextval from test;
insert into test select seq1.nextval, seq1.nextval from test;
insert into test select seq1.nextval, seq1.nextval from test;
insert into test select seq1.nextval, seq1.nextval from test;
insert into test select seq1.nextval, seq1.nextval from test;
insert into test select seq1.nextval, seq1.nextval from test;
insert into test select seq1.nextval, seq1.nextval from test;
commit;

select cluster_group_name, count(*) from test group by cluster_group_name;

select c1 from test@g1 order by c1 limit 10;
select c1 from test@g2 order by c1 limit 10;
