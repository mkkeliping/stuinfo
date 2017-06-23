/* 学校表，包括全国各大高校*/
use STU;
create table School(
SchoolCode VARCHAR(15) primary key,/*学校编号*/
SchoolName varchar(30) not null,#学校名称，汉字不能超过15个
SchoolBorn date,#学校创办日期
SchoolAdr varchar(40),#学校地址
SchoolHead  varchar(10)#校长名
)character set = utf8;

insert into School values('0001','河北地质大学','1996-6-2','石家庄','李军');

/* 学院表，包括一个学校中的所有学院*/
create table College(
collegeCode VARCHAR(15) primary key,/*学院编号*/
collegeName varchar(30) not null,#学院名称，汉字不能超过15个
collegeHead  varchar(10),#院长名
SchoolCode VARCHAR(15),
FOREIGN KEY (SchoolCode) REFERENCES School(SchoolCode)
)character set = utf8;

insert into College values('0001','信息工程学院','李明','0001');
/* 专业表，包括每个院的各个专业*/
create table Major(
MajorCode VARCHAR(15) primary key,/*专业编号*/
MajorName varchar(20) not null,#专业名称，汉字不能超过15个
MajorHead  varchar(10),#专业指导老师
collCode VARCHAR(15),#学院编号
FOREIGN KEY (collCode) REFERENCES College(collegeCode)#外键，被参照表是College，被参照列是collegeCode
)character set = utf8;
insert into Major values('0001','软件工程','李明','0001');
/* 学生信息表，包括每个专业的各个学生信息*/
create table Student(
stuID VARCHAR(15) primary key,/*学号*/
stuName varchar(10) not null,#学生名称
stuSex  char(4) check(stuSex in('男','女')),#学生性别
stuBorn date,#学生出生日期年-月-日
stuPolSta varchar(8),#政治面貌
stuAdr varchar(30),#籍贯
stutel char(11),#学生电话
stumajor VARCHAR(15),#学生所属系号
sstatus smallint,
foreign key (stumajor) references Major(MajorCode)#外键，被参照表是Major，被参照列是MajorCode
)character set = utf8;


insert into Student values('1111','小名','男','1996-6-2','团员','河北','1111','0001',2);
insert into Student values('1112','小花','男','1996-6-3','团员','河北','1112','0001',2);

create table Course(
Cno VARCHAR(15) primary key,/*学号*/
Cname varchar(20)#学生名称
)character set = utf8;

insert into Course values('1','软件工程');
insert into Course values('2','离散数学');
insert into Course values('3','高等代数');
insert into Course values('4','大学英语');



create table SC(
stuID VARCHAR(15),#学号
Cno VARCHAR(15),#课程号
Grade smallint,#成绩
scstatus smallint,
primary key(stuID,Cno),#主码两个
foreign key (stuID)references Student(stuID),#学号是外码，参照表是Student
foreign key (Cno)references Course(Cno)#课程号是外码，参照表是Course
)character set = utf8 ;

create view view1#视图
as
select Student.stuID,Student.stuName,Student.stuSex,Student.stumajor,SC.Cno,SC.Grade
from SC,Student
where SC.stuID=Student.stuID;
