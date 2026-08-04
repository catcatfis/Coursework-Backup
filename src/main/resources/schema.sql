-- 创建数据库
CREATE DATABASE IF NOT EXISTS oilcost DEFAULT CHARACTER SET utf8mb4;
USE oilcost;

-- 单位代码表
CREATE TABLE IF NOT EXISTS department (
    dpid VARCHAR(10) PRIMARY KEY COMMENT '单位代码',
    dname VARCHAR(6) NOT NULL UNIQUE
) COMMENT '单位代码表';

-- 油水井表
CREATE TABLE IF NOT EXISTS oil_water (
    owid CHAR(4) PRIMARY KEY,
    owname CHAR(2) NOT NULL CHECK (owname IN ('油井', '水井')),
    dpid CHAR(9) NOT NULL,
    CONSTRAINT fk_ow_dpid FOREIGN KEY (dpid) REFERENCES department(dpid)
) COMMENT '油水井表';

-- 施工单位表
CREATE TABLE IF NOT EXISTS Constructio (
    cname VARCHAR(20) PRIMARY KEY
) COMMENT '施工单位表';

-- 物码表
CREATE TABLE IF NOT EXISTS item (
    itemid CHAR(5) PRIMARY KEY,
    itemname CHAR(3) NOT NULL UNIQUE,
    unit CHAR(1) NOT NULL,
    uprice INT COMMENT '单价'
) COMMENT '物码表';

-- 作业表
CREATE TABLE IF NOT EXISTS task (
    tid CHAR(9) PRIMARY KEY,
    dpid CHAR(10) NOT NULL,
    owid CHAR(4) NOT NULL,
    budgetamount FLOAT NOT NULL CHECK (budgetamount >= 0),
    budgeter VARCHAR(10),
    budgetdate DATE,
    startdate DATE,
    enddate DATE,
    cname VARCHAR(20),
    ConstructionContent VARCHAR(10) NOT NULL,
    materialcost FLOAT CHECK (materialcost >= 0),
    laborcost FLOAT CHECK (laborcost >= 0),
    Equipmentcost FLOAT CHECK (Equipmentcost >= 0),
    othercost FLOAT CHECK (othercost >= 0),
    Settlementamount FLOAT CHECK (Settlementamount >= 0),
    Settlementer VARCHAR(10),
    Settlementdate DATE,
    Amountcredited FLOAT CHECK (Amountcredited >= 0),
    Amountcrediter VARCHAR(10),
    Amountcreditedate DATE,
    CONSTRAINT fk_task_dpid FOREIGN KEY (dpid) REFERENCES department(dpid),
    CONSTRAINT fk_task_owid FOREIGN KEY (owid) REFERENCES oil_water(owid),
    CONSTRAINT fk_task_cname FOREIGN KEY (cname) REFERENCES Constructio(cname)
) COMMENT '作业表';

-- 材料消耗表
CREATE TABLE IF NOT EXISTS materialconsumption (
    tid CHAR(9) NOT NULL,
    itemid CHAR(5) NOT NULL,
    quantity INT NOT NULL,
    price FLOAT NOT NULL,
    PRIMARY KEY (tid, itemid),
    CONSTRAINT fk_mc_tid FOREIGN KEY (tid) REFERENCES task(tid),
    CONSTRAINT fk_mc_itemid FOREIGN KEY (itemid) REFERENCES item(itemid)
) COMMENT '材料消耗表';

-- 插入初始数据
INSERT INTO department VALUES
    ('1122','采油厂'),
    ('112201','采油一矿'),
    ('112202','采油二矿'),
    ('112201001','采一矿一队'),
    ('112201002','采一矿二队'),
    ('112201003','采一矿三队'),
    ('112202001','采二矿一队'),
    ('112202002','采二矿二队');

INSERT INTO oil_water VALUES
    ('y001', '油井', '112201001'),
    ('y002', '油井', '112201001'),
    ('y003', '油井', '112201002'),
    ('s001', '水井', '112201002'),
    ('y004', '油井', '112201003'),
    ('s002', '水井', '112202001'),
    ('s003', '水井', '112202001'),
    ('y005', '油井', '112202002');

INSERT INTO Constructio VALUES
    ('作业公司作业一队'),
    ('作业公司作业二队'),
    ('作业公司作业三队');

INSERT INTO item VALUES
    ('wm001', '材料一', '吨', 10),
    ('wm002', '材料二', '米', 10),
    ('wm003', '材料三', '桶', 10),
    ('wm004', '材料四', '袋', 10);

INSERT INTO task VALUES
    ('zy2018001', '112201001', 'y001', 10000.00, '张三', '2018-05-01', '2018-05-04', '2018-05-25', '作业公司作业一队', '堵漏', 7000.00, 2500.00, 1000.00, 1400.00, 11900.00, '李四', '2018-05-26', 11900.00, '王五', '2018-05-28'),
    ('zy2018002', '112201002', 'y003', 11000.00, '张三', '2018-05-01', '2018-05-04', '2018-05-23', '作业公司作业二队', '检泵', 6000.00, 1500.00, 1000.00, 2400.00, 10900.00, '李四', '2018-05-26', 10900.00, '王五', '2018-05-28'),
    ('zy2018003', '112201002', 's001', 10500.00, '张三', '2018-05-01', '2018-05-06', '2018-05-23', '作业公司作业二队', '调剖', 6500.00, 2000.00, 500.00, 1400.00, 10400.00, '李四', '2018-05-26', 10400.00, '王五', '2018-05-28'),
    ('zy2018004', '112202001', 's002', 12000.00, '张三', '2018-05-01', '2018-05-04', '2018-05-24', '作业公司作业三队', '解堵', 6000.00, 2000.00, 1000.00, 1600.00, 10600.00, '李四', '2018-05-26', 10600.00, '赵六', '2018-05-28'),
    ('zy2018005', '112202002', 'y005', 12000.00, '张三', '2018-05-01', '2018-05-04', '2018-05-28', '作业公司作业三队', '防砂', 7000.00, 1000.00, 2000.00, 1300.00, 11300.00, '李四', '2018-06-01', NULL, NULL, NULL);

INSERT INTO materialconsumption VALUES
    ('zy2018001', 'wm001', 200, 2000.00),
    ('zy2018001', 'wm002', 200, 2000.00),
    ('zy2018001', 'wm003', 200, 2000.00),
    ('zy2018001', 'wm004', 100, 1000.00),
    ('zy2018002', 'wm001', 200, 2000.00),
    ('zy2018002', 'wm002', 200, 2000.00),
    ('zy2018002', 'wm003', 200, 2000.00),
    ('zy2018003', 'wm001', 200, 2000.00),
    ('zy2018003', 'wm002', 200, 2000.00),
    ('zy2018003', 'wm003', 250, 2500.00),
    ('zy2018004', 'wm001', 200, 2000.00),
    ('zy2018004', 'wm002', 200, 2000.00),
    ('zy2018004', 'wm004', 200, 2000.00),
    ('zy2018005', 'wm001', 200, 2000.00),
    ('zy2018005', 'wm002', 200, 2000.00),
    ('zy2018005', 'wm004', 300, 3000.00);
