sh init.sh

./sktperf g1n1 $1    1 1000 20000 &
./sktperf g2n1 $1 1001 2000 20000 &
./sktperf g3n1 $1 2001 3000 20000 &
