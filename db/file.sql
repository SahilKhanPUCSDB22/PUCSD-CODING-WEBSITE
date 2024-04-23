drop table sfiles;
drop table ifiles;

create table ifiles 
(
fname varchar(1024) primary key,
ftype varchar(100),
fsize int,
owner int references interviewers(interviewers_id),
filedata text
);

create table sfiles 
(
fname varchar(1024) primary key,
ftype varchar(100),
fsize int,
owner int references students(stud_id),
filedata text
);
