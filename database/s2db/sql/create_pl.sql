CREATE OR REPLACE PIPELINE tpch_10_lineitem
    AS LOAD DATA FS "/root/tpch/data/sf10/lineitem.tbl*"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE lineitem
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

CREATE OR REPLACE PIPELINE tpch_10_customer
    AS LOAD DATA FS "/root/tpch/data/sf10/customer.tbl*"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE customer
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

CREATE OR REPLACE PIPELINE tpch_10_nation
    AS LOAD DATA FS "/root/tpch/data/sf10/nation.tbl*"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE nation
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

CREATE OR REPLACE PIPELINE tpch_10_orders
    AS LOAD DATA FS "/root/tpch/data/sf10/orders.tbl*"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE orders
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

CREATE OR REPLACE PIPELINE tpch_10_part
    AS LOAD DATA FS "/root/tpch/data/sf10/part.tbl*"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE part
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

CREATE OR REPLACE PIPELINE tpch_10_partsupp
    AS LOAD DATA FS "/root/tpch/data/sf10/partsupp.tbl*"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE partsupp
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

CREATE OR REPLACE PIPELINE tpch_10_region
    AS LOAD DATA FS "/root/tpch/data/sf10/region.tbl*"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE region
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';

CREATE OR REPLACE PIPELINE tpch_10_supplier
    AS LOAD DATA FS "/root/tpch/data/sf10/supplier.tbl*"
    SKIP DUPLICATE KEY ERRORS
    INTO TABLE supplier
    FIELDS TERMINATED BY '|'
    LINES TERMINATED BY '|\n';
