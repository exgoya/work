LOAD DATA INFILE "/root/tpch/data/sf1/lineitem.tbl"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE lineitem
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

LOAD DATA INFILE "/root/tpch/data/sf1/customer.tbl"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE customer
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

LOAD DATA INFILE "/root/tpch/data/sf1/nation.tbl"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE nation
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

LOAD DATA INFILE "/root/tpch/data/sf1/orders.tbl"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE orders
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

LOAD DATA INFILE "/root/tpch/data/sf1/part.tbl"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE part
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

LOAD DATA INFILE "/root/tpch/data/sf1/partsupp.tbl"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE partsupp
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

LOAD DATA INFILE "/root/tpch/data/sf1/region.tbl"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE region
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

LOAD DATA INFILE "/root/tpch/data/sf1/supplier.tbl"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE supplier
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';
