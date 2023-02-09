sh init.sh

./sktperf $1     1 15000 300000 g1n1 g1n2 &
./sktperf $1 15001 30000 300000 g2n1 g2n2 &
