mysql connection

{{{ wait_timeout : connection sleep timeout Max_used_connections : 최대
시도 되었던 연결 값 Connections : Mysql 서버에서 연결 시도한 횟수
Aborted_clients : Client가 비정상적으로 종료된 횟수 Aborted_connects :
연결 실패 횟수

Threads_cached : Thread Cache의 Thread 수 Threads_connected : 현재
연결된 Thread 수 Threads_created : 접속을 위해 생성된 Thread 수
Threads_running : Sleeping 되어 있지 않은 Thread 수 }}}

status {{{ MariaDB [(none)]> show global variables like ‘wait_timeout%’;
+—————+——-+ \| Variable_name \| Value \| +—————+——-+ \| wait_timeout \|
30 \| +—————+——-+ 1 row in set (0.002 sec)

MariaDB [(none)]> show status like ‘%connection%’; +———————————–+——–+ \|
Variable_name \| Value \| +———————————–+——–+ \| Connection_errors_accept
\| 0 \| \| Connection_errors_internal \| 0 \| \|
Connection_errors_max_connections \| 0 \| \|
Connection_errors_peer_address \| 0 \| \| Connection_errors_select \| 0
\| \| Connection_errors_tcpwrap \| 0 \| \| Connections \| 552303 \| \|
Max_used_connections \| 625 \| \| Slave_connections \| 0 \|
+———————————–+——–+

MariaDB [(none)]> show status like ‘Aborted%’; +——————+——–+ \|
Variable_name \| Value \| +——————+——–+ \| Aborted_clients \| 509069 \|
\| Aborted_connects \| 0 \| +——————+——–+ 2 rows in set (0.001 sec)

MariaDB [(none)]> show status like ‘threads%’; +——————-+——-+ \|
Variable_name \| Value \| +——————-+——-+ \| Threads_cached \| 22 \| \|
Threads_connected \| 193 \| \| Threads_created \| 1360 \| \|
Threads_running \| 1 \| +——————-+——-+ 4 rows in set (0.001 sec)

MariaDB [(none)]> show global variables like ‘wait_timeout%’;
+—————+——-+ \| Variable_name \| Value \| +—————+——-+ \| wait_timeout \|
30 \| +—————+——-+ 1 row in set (0.002 sec)

MariaDB [(none)]> show variables like ‘wait_timeout%’; +—————+——-+ \|
Variable_name \| Value \| +—————+——-+ \| wait_timeout \| 30 \|
+—————+——-+ 1 row in set (0.002 sec) }}}

set {{{ MariaDB [(none)]> set GLOBAL max_connections = 100000; }}}
