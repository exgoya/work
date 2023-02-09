sudo docker run\
    --name influxdb_goya_3\
    -p 8090:8086\
    --volume /home/goya/work/monitor/influxdb2:/var/lib/influxdb2\
    influxdb:2.0.7
