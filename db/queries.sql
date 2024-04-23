drop table stud_test;
drop table coding_test;
drop table students ;
drop table colleges;
drop table interviewers;
drop table companies;

create table companies (
	unique_ID varchar,
	company_id int unique, 
	company_name varchar(100),
	company_location varchar(100),
	company_domain text);

create table colleges(
	unique_ID varchar,
	college_id int unique,
       	college_name varchar(100),
	college_location varchar(100),
	college_domain text);

create table interviewers(
	unique_ID varchar,
	interviewers_id int unique,
       	interviewers_fname varchar(100),
	interviewers_lname varchar(100),
	interviewers_role varchar(100),
	interviewers_password varchar(10),
	company_id int references companies(company_id));

create table students(
	unique_ID varchar,
	stud_id int unique, 
	stud_fname varchar(100),
	stud_lname varchar(100),
	stud_add varchar(100),
	stud_stream varchar(100),
	stud_password varchar(10),
	stud_degree text,
	college_id int references colleges(college_id));

create table coding_test(
	unique_ID varchar,
	test_id int unique,
	test_name varchar(100),
	test_duration int,
	test_start_date int,
	test_end_date int,	
	interviewers_id int references interviewers(interviewers_id),
	questions text);

create table stud_test(
	unique_ID varchar,
	stud_id int references students(stud_id),
	test_id int references coding_test(test_id) ,
       	status varchar(100),
	start_date int,
	end_date int,
	start_time int,
	end_time int,
	duration int,
	marks int);







insert into pass1 values('pass1$0');




insert into pass3 values('pass3$0');


insert into pass4 values('pass4$0');


insert into pass5 values('pass5$0');
insert into pass5 values('pass5$1');


insert into pass6 values('pass6$0');
insert into pass6 values('pass6$1');




insert into lucknow values('lucknow$0');


insert into pune values('pune$0');


insert into hyd values('hyd$0');


insert into banglore values('banglore$0');


insert into mumbai values('mumbai$0');


insert into kolkata values('kolkata$0');


insert into delhi values('delhi$0');


insert into kashmir values('kashmir$0');




insert into ct values('ct$0');


insert into wtps values('wtps$0');


insert into bookface values('bookface$0');


insert into gram values('gram$0');


insert into chatsnap values('chatsnap$0');


insert into bell values('bell$0');


insert into ph values('ph$0');


insert into xinul values('xinul$0');


insert into bsdorg values('bsdorg$0');


insert into sungsam values('sungsam$0');




insert into sppu values('sppu$0');


insert into mu values('mu$0');


insert into dlu values('dlu$0');


insert into bu values('bu$0');


insert into ku values('ku$0');


insert into hu values('hu$0');


insert into tnu values('tnu$0');


insert into fc values('fc$0');


insert into au values('au$0');


insert into pucsd values('pucsd$0');




insert into HR values('HR$0');


insert into CR values('CR$0');


insert into SDE values('SDE$0');


insert into QA values('QA$0');


insert into WM values('WM$0');


insert into CEO values('CEO$0');


insert into VP values('VP$0');


insert into P values('P$0');




insert into software values('software$0');


insert into hardware values('hardware$0');


insert into consultancy values('consultancy$0');


insert into service values('service$0');


insert into product values('product$0');




insert into msc values('msc$0');


insert into mcs values('mcs$0');


insert into mtech values('mtech$0');


insert into bsc values('bsc$0');


insert into bcs values('bcs$0');


insert into btech values('btech$0');


insert into bchs values('bchs$0');




insert into deepak values('deepak$0');


insert into kartik values('kartik$0');


insert into bhushan values('bhushan$0');


insert into snehal values('snehal$0');


insert into saurabh values('saurabh$0');


insert into sahil values('sahil$0');




insert into science values('science$0');


insert into technology values('technology$0');


insert into research values('research$0');


insert into engineering values('engineering$0');


insert into support values('support$0');




insert into submitted values('submitted$0');


insert into incomplete values('incomplete$0');


insert into timeout values('timeout$0');




insert into shukla values('shukla$0');


insert into khan values('khan$0');


insert into tripathi values('tripathi$0');


insert into kulkarni values('kulkarni$0');


insert into shelke values('shelke$0');


insert into jagdale values('jagdale$0');




















insert into q46845 values('q46845$0');
insert into q46845 values('q46845$1');
insert into q46845 values('q46845$2');
insert into q46845 values('q46845$3');




insert into test values('test$0');
insert into test values('test$1');
insert into test values('test$2');
insert into test values('test$3');
insert into test values('test$4');


insert into companies values('companies$0');
insert into companies values('companies$1');
insert into companies values('companies$2');
insert into companies values('companies$3');
insert into companies values('companies$4');
insert into companies values('companies$5');
insert into companies values('companies$6');
insert into companies values('companies$7');
insert into companies values('companies$8');
insert into companies values('companies$9');


update companies set company_id=49 WHERE unique_ID='companies$0';
update companies set company_id=56 WHERE unique_ID='companies$1';
update companies set company_id=48 WHERE unique_ID='companies$2';
update companies set company_id=60 WHERE unique_ID='companies$3';
update companies set company_id=1 WHERE unique_ID='companies$4';
update companies set company_id=32 WHERE unique_ID='companies$5';
update companies set company_id=50 WHERE unique_ID='companies$6';
update companies set company_id=54 WHERE unique_ID='companies$7';
update companies set company_id=40 WHERE unique_ID='companies$8';
update companies set company_id=16 WHERE unique_ID='companies$9';


update companies set company_name='xinul' WHERE unique_ID='companies$0';
update companies set company_name='bsdorg' WHERE unique_ID='companies$1';
update companies set company_name='ph' WHERE unique_ID='companies$2';
update companies set company_name='wtps' WHERE unique_ID='companies$3';
update companies set company_name='sungsam' WHERE unique_ID='companies$4';
update companies set company_name='bell' WHERE unique_ID='companies$5';
update companies set company_name='ct' WHERE unique_ID='companies$6';
update companies set company_name='gram' WHERE unique_ID='companies$7';
update companies set company_name='chatsnap' WHERE unique_ID='companies$8';
update companies set company_name='bookface' WHERE unique_ID='companies$9';


update companies set company_location='kashmir' WHERE unique_ID='companies$0';
update companies set company_location='pune' WHERE unique_ID='companies$1';
update companies set company_location='kashmir' WHERE unique_ID='companies$2';
update companies set company_location='kolkata' WHERE unique_ID='companies$3';
update companies set company_location='mumbai' WHERE unique_ID='companies$4';
update companies set company_location='kashmir' WHERE unique_ID='companies$5';
update companies set company_location='hyd' WHERE unique_ID='companies$6';
update companies set company_location='kolkata' WHERE unique_ID='companies$7';
update companies set company_location='kolkata' WHERE unique_ID='companies$8';
update companies set company_location='banglore' WHERE unique_ID='companies$9';


update companies set company_domain='product' WHERE unique_ID='companies$0';
update companies set company_domain='product' WHERE unique_ID='companies$1';
update companies set company_domain='product' WHERE unique_ID='companies$2';
update companies set company_domain='consultancy' WHERE unique_ID='companies$3';
update companies set company_domain='service' WHERE unique_ID='companies$4';
update companies set company_domain='product' WHERE unique_ID='companies$5';
update companies set company_domain='consultancy' WHERE unique_ID='companies$6';
update companies set company_domain='consultancy' WHERE unique_ID='companies$7';
update companies set company_domain='hardware' WHERE unique_ID='companies$8';
update companies set company_domain='product' WHERE unique_ID='companies$9';


insert into colleges values('colleges$0');
insert into colleges values('colleges$1');
insert into colleges values('colleges$2');
insert into colleges values('colleges$3');
insert into colleges values('colleges$4');
insert into colleges values('colleges$5');
insert into colleges values('colleges$6');
insert into colleges values('colleges$7');
insert into colleges values('colleges$8');
insert into colleges values('colleges$9');


update colleges set college_id=63 WHERE unique_ID='colleges$0';
update colleges set college_id=52 WHERE unique_ID='colleges$1';
update colleges set college_id=56 WHERE unique_ID='colleges$2';
update colleges set college_id=57 WHERE unique_ID='colleges$3';
update colleges set college_id=48 WHERE unique_ID='colleges$4';
update colleges set college_id=61 WHERE unique_ID='colleges$5';
update colleges set college_id=32 WHERE unique_ID='colleges$6';
update colleges set college_id=40 WHERE unique_ID='colleges$7';
update colleges set college_id=59 WHERE unique_ID='colleges$8';
update colleges set college_id=60 WHERE unique_ID='colleges$9';


update colleges set college_name='fc' WHERE unique_ID='colleges$0';
update colleges set college_name='dlu' WHERE unique_ID='colleges$1';
update colleges set college_name='mu' WHERE unique_ID='colleges$2';
update colleges set college_name='sppu' WHERE unique_ID='colleges$3';
update colleges set college_name='hu' WHERE unique_ID='colleges$4';
update colleges set college_name='pucsd' WHERE unique_ID='colleges$5';
update colleges set college_name='tnu' WHERE unique_ID='colleges$6';
update colleges set college_name='au' WHERE unique_ID='colleges$7';
update colleges set college_name='ku' WHERE unique_ID='colleges$8';
update colleges set college_name='bu' WHERE unique_ID='colleges$9';


update colleges set college_location='kolkata' WHERE unique_ID='colleges$0';
update colleges set college_location='mumbai' WHERE unique_ID='colleges$1';
update colleges set college_location='hyd' WHERE unique_ID='colleges$2';
update colleges set college_location='mumbai' WHERE unique_ID='colleges$3';
update colleges set college_location='delhi' WHERE unique_ID='colleges$4';
update colleges set college_location='lucknow' WHERE unique_ID='colleges$5';
update colleges set college_location='pune' WHERE unique_ID='colleges$6';
update colleges set college_location='kolkata' WHERE unique_ID='colleges$7';
update colleges set college_location='kolkata' WHERE unique_ID='colleges$8';
update colleges set college_location='kolkata' WHERE unique_ID='colleges$9';


update colleges set college_domain='hardware' WHERE unique_ID='colleges$0';
update colleges set college_domain='hardware' WHERE unique_ID='colleges$1';
update colleges set college_domain='service' WHERE unique_ID='colleges$2';
update colleges set college_domain='consultancy' WHERE unique_ID='colleges$3';
update colleges set college_domain='service' WHERE unique_ID='colleges$4';
update colleges set college_domain='software' WHERE unique_ID='colleges$5';
update colleges set college_domain='software' WHERE unique_ID='colleges$6';
update colleges set college_domain='software' WHERE unique_ID='colleges$7';
update colleges set college_domain='product' WHERE unique_ID='colleges$8';
update colleges set college_domain='service' WHERE unique_ID='colleges$9';


insert into interviewers values('interviewers$0');
insert into interviewers values('interviewers$1');
insert into interviewers values('interviewers$2');
insert into interviewers values('interviewers$3');
insert into interviewers values('interviewers$4');
insert into interviewers values('interviewers$5');
insert into interviewers values('interviewers$6');
insert into interviewers values('interviewers$7');
insert into interviewers values('interviewers$8');
insert into interviewers values('interviewers$9');


update interviewers set interviewers_id=62 WHERE unique_ID='interviewers$0';
update interviewers set interviewers_id=60 WHERE unique_ID='interviewers$1';
update interviewers set interviewers_id=63 WHERE unique_ID='interviewers$2';
update interviewers set interviewers_id=57 WHERE unique_ID='interviewers$3';
update interviewers set interviewers_id=48 WHERE unique_ID='interviewers$4';
update interviewers set interviewers_id=61 WHERE unique_ID='interviewers$5';
update interviewers set interviewers_id=37 WHERE unique_ID='interviewers$6';
update interviewers set interviewers_id=44 WHERE unique_ID='interviewers$7';
update interviewers set interviewers_id=56 WHERE unique_ID='interviewers$8';
update interviewers set interviewers_id=47 WHERE unique_ID='interviewers$9';


update interviewers set interviewers_fname='bhushan' WHERE unique_ID='interviewers$0';
update interviewers set interviewers_fname='saurabh' WHERE unique_ID='interviewers$1';
update interviewers set interviewers_fname='saurabh' WHERE unique_ID='interviewers$2';
update interviewers set interviewers_fname='kartik' WHERE unique_ID='interviewers$3';
update interviewers set interviewers_fname='snehal' WHERE unique_ID='interviewers$4';
update interviewers set interviewers_fname='saurabh' WHERE unique_ID='interviewers$5';
update interviewers set interviewers_fname='deepak' WHERE unique_ID='interviewers$6';
update interviewers set interviewers_fname='saurabh' WHERE unique_ID='interviewers$7';
update interviewers set interviewers_fname='saurabh' WHERE unique_ID='interviewers$8';
update interviewers set interviewers_fname='sahil' WHERE unique_ID='interviewers$9';


update interviewers set interviewers_lname='shukla' WHERE unique_ID='interviewers$0';
update interviewers set interviewers_lname='jagdale' WHERE unique_ID='interviewers$1';
update interviewers set interviewers_lname='jagdale' WHERE unique_ID='interviewers$2';
update interviewers set interviewers_lname='jagdale' WHERE unique_ID='interviewers$3';
update interviewers set interviewers_lname='jagdale' WHERE unique_ID='interviewers$4';
update interviewers set interviewers_lname='shelke' WHERE unique_ID='interviewers$5';
update interviewers set interviewers_lname='shelke' WHERE unique_ID='interviewers$6';
update interviewers set interviewers_lname='shelke' WHERE unique_ID='interviewers$7';
update interviewers set interviewers_lname='khan' WHERE unique_ID='interviewers$8';
update interviewers set interviewers_lname='jagdale' WHERE unique_ID='interviewers$9';


update interviewers set interviewers_role='VP' WHERE unique_ID='interviewers$0';
update interviewers set interviewers_role='VP' WHERE unique_ID='interviewers$1';
update interviewers set interviewers_role='VP' WHERE unique_ID='interviewers$2';
update interviewers set interviewers_role='P' WHERE unique_ID='interviewers$3';
update interviewers set interviewers_role='VP' WHERE unique_ID='interviewers$4';
update interviewers set interviewers_role='VP' WHERE unique_ID='interviewers$5';
update interviewers set interviewers_role='VP' WHERE unique_ID='interviewers$6';
update interviewers set interviewers_role='WM' WHERE unique_ID='interviewers$7';
update interviewers set interviewers_role='CR' WHERE unique_ID='interviewers$8';
update interviewers set interviewers_role='VP' WHERE unique_ID='interviewers$9';


update interviewers set interviewers_password='pass4' WHERE unique_ID='interviewers$0';
update interviewers set interviewers_password='pass1' WHERE unique_ID='interviewers$1';
update interviewers set interviewers_password='pass3' WHERE unique_ID='interviewers$2';
update interviewers set interviewers_password='pass5' WHERE unique_ID='interviewers$3';
update interviewers set interviewers_password='pass1' WHERE unique_ID='interviewers$4';
update interviewers set interviewers_password='pass6' WHERE unique_ID='interviewers$5';
update interviewers set interviewers_password='pass4' WHERE unique_ID='interviewers$6';
update interviewers set interviewers_password='pass3' WHERE unique_ID='interviewers$7';
update interviewers set interviewers_password='pass3' WHERE unique_ID='interviewers$8';
update interviewers set interviewers_password='pass5' WHERE unique_ID='interviewers$9';


update interviewers set company_id=54 WHERE unique_ID='interviewers$0';
update interviewers set company_id=50 WHERE unique_ID='interviewers$1';
update interviewers set company_id=32 WHERE unique_ID='interviewers$2';
update interviewers set company_id=1 WHERE unique_ID='interviewers$3';
update interviewers set company_id=60 WHERE unique_ID='interviewers$4';
update interviewers set company_id=48 WHERE unique_ID='interviewers$5';
update interviewers set company_id=54 WHERE unique_ID='interviewers$6';
update interviewers set company_id=56 WHERE unique_ID='interviewers$7';
update interviewers set company_id=49 WHERE unique_ID='interviewers$8';
update interviewers set company_id=60 WHERE unique_ID='interviewers$9';


insert into students values('students$0');
insert into students values('students$1');
insert into students values('students$2');
insert into students values('students$3');
insert into students values('students$4');
insert into students values('students$5');
insert into students values('students$6');
insert into students values('students$7');
insert into students values('students$8');
insert into students values('students$9');
insert into students values('students$10');
insert into students values('students$11');
insert into students values('students$12');
insert into students values('students$13');
insert into students values('students$14');
insert into students values('students$15');
insert into students values('students$16');
insert into students values('students$17');
insert into students values('students$18');
insert into students values('students$19');
insert into students values('students$20');
insert into students values('students$21');
insert into students values('students$22');
insert into students values('students$23');
insert into students values('students$24');
insert into students values('students$25');
insert into students values('students$26');
insert into students values('students$27');
insert into students values('students$28');
insert into students values('students$29');


update students set stud_id=20 WHERE unique_ID='students$0';
update students set stud_id=41 WHERE unique_ID='students$1';
update students set stud_id=50 WHERE unique_ID='students$2';
update students set stud_id=14 WHERE unique_ID='students$3';
update students set stud_id=51 WHERE unique_ID='students$4';
update students set stud_id=63 WHERE unique_ID='students$5';
update students set stud_id=59 WHERE unique_ID='students$6';
update students set stud_id=26 WHERE unique_ID='students$7';
update students set stud_id=28 WHERE unique_ID='students$8';
update students set stud_id=5 WHERE unique_ID='students$9';
update students set stud_id=29 WHERE unique_ID='students$10';
update students set stud_id=24 WHERE unique_ID='students$11';
update students set stud_id=61 WHERE unique_ID='students$12';
update students set stud_id=16 WHERE unique_ID='students$13';
update students set stud_id=62 WHERE unique_ID='students$14';
update students set stud_id=58 WHERE unique_ID='students$15';
update students set stud_id=8 WHERE unique_ID='students$16';
update students set stud_id=2 WHERE unique_ID='students$17';
update students set stud_id=44 WHERE unique_ID='students$18';
update students set stud_id=55 WHERE unique_ID='students$19';
update students set stud_id=52 WHERE unique_ID='students$20';
update students set stud_id=32 WHERE unique_ID='students$21';
update students set stud_id=47 WHERE unique_ID='students$22';
update students set stud_id=1 WHERE unique_ID='students$23';
update students set stud_id=60 WHERE unique_ID='students$24';
update students set stud_id=10 WHERE unique_ID='students$25';
update students set stud_id=56 WHERE unique_ID='students$26';
update students set stud_id=54 WHERE unique_ID='students$27';
update students set stud_id=48 WHERE unique_ID='students$28';
update students set stud_id=4 WHERE unique_ID='students$29';


update students set stud_fname='sahil' WHERE unique_ID='students$0';
update students set stud_fname='sahil' WHERE unique_ID='students$1';
update students set stud_fname='deepak' WHERE unique_ID='students$2';
update students set stud_fname='sahil' WHERE unique_ID='students$3';
update students set stud_fname='saurabh' WHERE unique_ID='students$4';
update students set stud_fname='sahil' WHERE unique_ID='students$5';
update students set stud_fname='sahil' WHERE unique_ID='students$6';
update students set stud_fname='sahil' WHERE unique_ID='students$7';
update students set stud_fname='deepak' WHERE unique_ID='students$8';
update students set stud_fname='saurabh' WHERE unique_ID='students$9';
update students set stud_fname='bhushan' WHERE unique_ID='students$10';
update students set stud_fname='saurabh' WHERE unique_ID='students$11';
update students set stud_fname='sahil' WHERE unique_ID='students$12';
update students set stud_fname='sahil' WHERE unique_ID='students$13';
update students set stud_fname='sahil' WHERE unique_ID='students$14';
update students set stud_fname='saurabh' WHERE unique_ID='students$15';
update students set stud_fname='bhushan' WHERE unique_ID='students$16';
update students set stud_fname='saurabh' WHERE unique_ID='students$17';
update students set stud_fname='sahil' WHERE unique_ID='students$18';
update students set stud_fname='sahil' WHERE unique_ID='students$19';
update students set stud_fname='saurabh' WHERE unique_ID='students$20';
update students set stud_fname='bhushan' WHERE unique_ID='students$21';
update students set stud_fname='sahil' WHERE unique_ID='students$22';
update students set stud_fname='sahil' WHERE unique_ID='students$23';
update students set stud_fname='bhushan' WHERE unique_ID='students$24';
update students set stud_fname='sahil' WHERE unique_ID='students$25';
update students set stud_fname='sahil' WHERE unique_ID='students$26';
update students set stud_fname='bhushan' WHERE unique_ID='students$27';
update students set stud_fname='saurabh' WHERE unique_ID='students$28';
update students set stud_fname='sahil' WHERE unique_ID='students$29';


update students set stud_lname='jagdale' WHERE unique_ID='students$0';
update students set stud_lname='kulkarni' WHERE unique_ID='students$1';
update students set stud_lname='tripathi' WHERE unique_ID='students$2';
update students set stud_lname='jagdale' WHERE unique_ID='students$3';
update students set stud_lname='jagdale' WHERE unique_ID='students$4';
update students set stud_lname='tripathi' WHERE unique_ID='students$5';
update students set stud_lname='kulkarni' WHERE unique_ID='students$6';
update students set stud_lname='jagdale' WHERE unique_ID='students$7';
update students set stud_lname='khan' WHERE unique_ID='students$8';
update students set stud_lname='jagdale' WHERE unique_ID='students$9';
update students set stud_lname='kulkarni' WHERE unique_ID='students$10';
update students set stud_lname='jagdale' WHERE unique_ID='students$11';
update students set stud_lname='kulkarni' WHERE unique_ID='students$12';
update students set stud_lname='jagdale' WHERE unique_ID='students$13';
update students set stud_lname='tripathi' WHERE unique_ID='students$14';
update students set stud_lname='khan' WHERE unique_ID='students$15';
update students set stud_lname='jagdale' WHERE unique_ID='students$16';
update students set stud_lname='jagdale' WHERE unique_ID='students$17';
update students set stud_lname='tripathi' WHERE unique_ID='students$18';
update students set stud_lname='jagdale' WHERE unique_ID='students$19';
update students set stud_lname='tripathi' WHERE unique_ID='students$20';
update students set stud_lname='tripathi' WHERE unique_ID='students$21';
update students set stud_lname='tripathi' WHERE unique_ID='students$22';
update students set stud_lname='kulkarni' WHERE unique_ID='students$23';
update students set stud_lname='jagdale' WHERE unique_ID='students$24';
update students set stud_lname='jagdale' WHERE unique_ID='students$25';
update students set stud_lname='jagdale' WHERE unique_ID='students$26';
update students set stud_lname='tripathi' WHERE unique_ID='students$27';
update students set stud_lname='shelke' WHERE unique_ID='students$28';
update students set stud_lname='jagdale' WHERE unique_ID='students$29';


update students set stud_add='kashmir' WHERE unique_ID='students$0';
update students set stud_add='kashmir' WHERE unique_ID='students$1';
update students set stud_add='lucknow' WHERE unique_ID='students$2';
update students set stud_add='kashmir' WHERE unique_ID='students$3';
update students set stud_add='kashmir' WHERE unique_ID='students$4';
update students set stud_add='mumbai' WHERE unique_ID='students$5';
update students set stud_add='kashmir' WHERE unique_ID='students$6';
update students set stud_add='kashmir' WHERE unique_ID='students$7';
update students set stud_add='mumbai' WHERE unique_ID='students$8';
update students set stud_add='kashmir' WHERE unique_ID='students$9';
update students set stud_add='delhi' WHERE unique_ID='students$10';
update students set stud_add='delhi' WHERE unique_ID='students$11';
update students set stud_add='kashmir' WHERE unique_ID='students$12';
update students set stud_add='kashmir' WHERE unique_ID='students$13';
update students set stud_add='kashmir' WHERE unique_ID='students$14';
update students set stud_add='delhi' WHERE unique_ID='students$15';
update students set stud_add='kashmir' WHERE unique_ID='students$16';
update students set stud_add='delhi' WHERE unique_ID='students$17';
update students set stud_add='hyd' WHERE unique_ID='students$18';
update students set stud_add='kashmir' WHERE unique_ID='students$19';
update students set stud_add='kashmir' WHERE unique_ID='students$20';
update students set stud_add='kashmir' WHERE unique_ID='students$21';
update students set stud_add='delhi' WHERE unique_ID='students$22';
update students set stud_add='kashmir' WHERE unique_ID='students$23';
update students set stud_add='kashmir' WHERE unique_ID='students$24';
update students set stud_add='delhi' WHERE unique_ID='students$25';
update students set stud_add='mumbai' WHERE unique_ID='students$26';
update students set stud_add='banglore' WHERE unique_ID='students$27';
update students set stud_add='delhi' WHERE unique_ID='students$28';
update students set stud_add='kashmir' WHERE unique_ID='students$29';


update students set stud_stream='support' WHERE unique_ID='students$0';
update students set stud_stream='research' WHERE unique_ID='students$1';
update students set stud_stream='support' WHERE unique_ID='students$2';
update students set stud_stream='engineering' WHERE unique_ID='students$3';
update students set stud_stream='support' WHERE unique_ID='students$4';
update students set stud_stream='support' WHERE unique_ID='students$5';
update students set stud_stream='support' WHERE unique_ID='students$6';
update students set stud_stream='support' WHERE unique_ID='students$7';
update students set stud_stream='support' WHERE unique_ID='students$8';
update students set stud_stream='engineering' WHERE unique_ID='students$9';
update students set stud_stream='engineering' WHERE unique_ID='students$10';
update students set stud_stream='engineering' WHERE unique_ID='students$11';
update students set stud_stream='support' WHERE unique_ID='students$12';
update students set stud_stream='support' WHERE unique_ID='students$13';
update students set stud_stream='support' WHERE unique_ID='students$14';
update students set stud_stream='support' WHERE unique_ID='students$15';
update students set stud_stream='engineering' WHERE unique_ID='students$16';
update students set stud_stream='support' WHERE unique_ID='students$17';
update students set stud_stream='support' WHERE unique_ID='students$18';
update students set stud_stream='support' WHERE unique_ID='students$19';
update students set stud_stream='engineering' WHERE unique_ID='students$20';
update students set stud_stream='support' WHERE unique_ID='students$21';
update students set stud_stream='technology' WHERE unique_ID='students$22';
update students set stud_stream='support' WHERE unique_ID='students$23';
update students set stud_stream='support' WHERE unique_ID='students$24';
update students set stud_stream='research' WHERE unique_ID='students$25';
update students set stud_stream='research' WHERE unique_ID='students$26';
update students set stud_stream='support' WHERE unique_ID='students$27';
update students set stud_stream='engineering' WHERE unique_ID='students$28';
update students set stud_stream='support' WHERE unique_ID='students$29';


update students set stud_password='pass1' WHERE unique_ID='students$0';
update students set stud_password='pass6' WHERE unique_ID='students$1';
update students set stud_password='pass5' WHERE unique_ID='students$2';
update students set stud_password='pass1' WHERE unique_ID='students$3';
update students set stud_password='pass4' WHERE unique_ID='students$4';
update students set stud_password='pass4' WHERE unique_ID='students$5';
update students set stud_password='pass3' WHERE unique_ID='students$6';
update students set stud_password='pass3' WHERE unique_ID='students$7';
update students set stud_password='pass1' WHERE unique_ID='students$8';
update students set stud_password='pass3' WHERE unique_ID='students$9';
update students set stud_password='pass3' WHERE unique_ID='students$10';
update students set stud_password='pass1' WHERE unique_ID='students$11';
update students set stud_password='pass1' WHERE unique_ID='students$12';
update students set stud_password='pass1' WHERE unique_ID='students$13';
update students set stud_password='pass5' WHERE unique_ID='students$14';
update students set stud_password='pass6' WHERE unique_ID='students$15';
update students set stud_password='pass1' WHERE unique_ID='students$16';
update students set stud_password='pass1' WHERE unique_ID='students$17';
update students set stud_password='pass5' WHERE unique_ID='students$18';
update students set stud_password='pass4' WHERE unique_ID='students$19';
update students set stud_password='pass1' WHERE unique_ID='students$20';
update students set stud_password='pass4' WHERE unique_ID='students$21';
update students set stud_password='pass6' WHERE unique_ID='students$22';
update students set stud_password='pass1' WHERE unique_ID='students$23';
update students set stud_password='pass3' WHERE unique_ID='students$24';
update students set stud_password='pass5' WHERE unique_ID='students$25';
update students set stud_password='pass4' WHERE unique_ID='students$26';
update students set stud_password='pass1' WHERE unique_ID='students$27';
update students set stud_password='pass1' WHERE unique_ID='students$28';
update students set stud_password='pass3' WHERE unique_ID='students$29';


update students set stud_degree='msc' WHERE unique_ID='students$0';
update students set stud_degree='bcs' WHERE unique_ID='students$1';
update students set stud_degree='bchs' WHERE unique_ID='students$2';
update students set stud_degree='bsc' WHERE unique_ID='students$3';
update students set stud_degree='bcs' WHERE unique_ID='students$4';
update students set stud_degree='bchs' WHERE unique_ID='students$5';
update students set stud_degree='bchs' WHERE unique_ID='students$6';
update students set stud_degree='bcs' WHERE unique_ID='students$7';
update students set stud_degree='bchs' WHERE unique_ID='students$8';
update students set stud_degree='bchs' WHERE unique_ID='students$9';
update students set stud_degree='bchs' WHERE unique_ID='students$10';
update students set stud_degree='bchs' WHERE unique_ID='students$11';
update students set stud_degree='bchs' WHERE unique_ID='students$12';
update students set stud_degree='bsc' WHERE unique_ID='students$13';
update students set stud_degree='msc' WHERE unique_ID='students$14';
update students set stud_degree='bcs' WHERE unique_ID='students$15';
update students set stud_degree='bsc' WHERE unique_ID='students$16';
update students set stud_degree='mtech' WHERE unique_ID='students$17';
update students set stud_degree='bchs' WHERE unique_ID='students$18';
update students set stud_degree='bcs' WHERE unique_ID='students$19';
update students set stud_degree='bchs' WHERE unique_ID='students$20';
update students set stud_degree='bchs' WHERE unique_ID='students$21';
update students set stud_degree='bcs' WHERE unique_ID='students$22';
update students set stud_degree='bsc' WHERE unique_ID='students$23';
update students set stud_degree='bchs' WHERE unique_ID='students$24';
update students set stud_degree='bcs' WHERE unique_ID='students$25';
update students set stud_degree='bchs' WHERE unique_ID='students$26';
update students set stud_degree='bcs' WHERE unique_ID='students$27';
update students set stud_degree='bchs' WHERE unique_ID='students$28';
update students set stud_degree='bsc' WHERE unique_ID='students$29';


update students set college_id=60 WHERE unique_ID='students$0';
update students set college_id=60 WHERE unique_ID='students$1';
update students set college_id=60 WHERE unique_ID='students$2';
update students set college_id=60 WHERE unique_ID='students$3';
update students set college_id=60 WHERE unique_ID='students$4';
update students set college_id=60 WHERE unique_ID='students$5';
update students set college_id=60 WHERE unique_ID='students$6';
update students set college_id=60 WHERE unique_ID='students$7';
update students set college_id=60 WHERE unique_ID='students$8';
update students set college_id=60 WHERE unique_ID='students$9';
update students set college_id=60 WHERE unique_ID='students$10';
update students set college_id=60 WHERE unique_ID='students$11';
update students set college_id=60 WHERE unique_ID='students$12';
update students set college_id=60 WHERE unique_ID='students$13';
update students set college_id=59 WHERE unique_ID='students$14';
update students set college_id=59 WHERE unique_ID='students$15';
update students set college_id=59 WHERE unique_ID='students$16';
update students set college_id=40 WHERE unique_ID='students$17';
update students set college_id=32 WHERE unique_ID='students$18';
update students set college_id=61 WHERE unique_ID='students$19';
update students set college_id=61 WHERE unique_ID='students$20';
update students set college_id=61 WHERE unique_ID='students$21';
update students set college_id=48 WHERE unique_ID='students$22';
update students set college_id=48 WHERE unique_ID='students$23';
update students set college_id=57 WHERE unique_ID='students$24';
update students set college_id=60 WHERE unique_ID='students$25';
update students set college_id=56 WHERE unique_ID='students$26';
update students set college_id=57 WHERE unique_ID='students$27';
update students set college_id=57 WHERE unique_ID='students$28';
update students set college_id=59 WHERE unique_ID='students$29';


insert into coding_test values('coding_test$0');
insert into coding_test values('coding_test$1');
insert into coding_test values('coding_test$2');
insert into coding_test values('coding_test$3');
insert into coding_test values('coding_test$4');


update coding_test set test_id=9 WHERE unique_ID='coding_test$0';
update coding_test set test_id=8 WHERE unique_ID='coding_test$1';
update coding_test set test_id=6 WHERE unique_ID='coding_test$2';
update coding_test set test_id=5 WHERE unique_ID='coding_test$3';
update coding_test set test_id=34 WHERE unique_ID='coding_test$4';


update coding_test set test_name='test' WHERE unique_ID='coding_test$0';
update coding_test set test_name='test' WHERE unique_ID='coding_test$1';
update coding_test set test_name='test' WHERE unique_ID='coding_test$2';
update coding_test set test_name='test' WHERE unique_ID='coding_test$3';
update coding_test set test_name='test' WHERE unique_ID='coding_test$4';


update coding_test set test_duration=63 WHERE unique_ID='coding_test$0';
update coding_test set test_duration=1 WHERE unique_ID='coding_test$1';
update coding_test set test_duration=60 WHERE unique_ID='coding_test$2';
update coding_test set test_duration=62 WHERE unique_ID='coding_test$3';
update coding_test set test_duration=63 WHERE unique_ID='coding_test$4';


update coding_test set test_start_date=61 WHERE unique_ID='coding_test$0';
update coding_test set test_start_date=63 WHERE unique_ID='coding_test$1';
update coding_test set test_start_date=63 WHERE unique_ID='coding_test$2';
update coding_test set test_start_date=63 WHERE unique_ID='coding_test$3';
update coding_test set test_start_date=62 WHERE unique_ID='coding_test$4';


update coding_test set test_end_date=63 WHERE unique_ID='coding_test$0';
update coding_test set test_end_date=63 WHERE unique_ID='coding_test$1';
update coding_test set test_end_date=63 WHERE unique_ID='coding_test$2';
update coding_test set test_end_date=63 WHERE unique_ID='coding_test$3';
update coding_test set test_end_date=63 WHERE unique_ID='coding_test$4';


update coding_test set interviewers_id=63 WHERE unique_ID='coding_test$0';
update coding_test set interviewers_id=62 WHERE unique_ID='coding_test$1';
update coding_test set interviewers_id=63 WHERE unique_ID='coding_test$2';
update coding_test set interviewers_id=63 WHERE unique_ID='coding_test$3';
update coding_test set interviewers_id=63 WHERE unique_ID='coding_test$4';


update coding_test set questions='q46845' WHERE unique_ID='coding_test$0';
update coding_test set questions='q46845' WHERE unique_ID='coding_test$1';
update coding_test set questions='q46845' WHERE unique_ID='coding_test$2';
update coding_test set questions='q46845' WHERE unique_ID='coding_test$3';
update coding_test set questions='q46845' WHERE unique_ID='coding_test$4';


insert into stud_test values('stud_test$0');
insert into stud_test values('stud_test$1');
insert into stud_test values('stud_test$2');
insert into stud_test values('stud_test$3');
insert into stud_test values('stud_test$4');
insert into stud_test values('stud_test$5');
insert into stud_test values('stud_test$6');
insert into stud_test values('stud_test$7');
insert into stud_test values('stud_test$8');
insert into stud_test values('stud_test$9');
insert into stud_test values('stud_test$10');
insert into stud_test values('stud_test$11');
insert into stud_test values('stud_test$12');
insert into stud_test values('stud_test$13');
insert into stud_test values('stud_test$14');


update stud_test set stud_id=16 WHERE unique_ID='stud_test$0';
update stud_test set stud_id=61 WHERE unique_ID='stud_test$1';
update stud_test set stud_id=24 WHERE unique_ID='stud_test$2';
update stud_test set stud_id=29 WHERE unique_ID='stud_test$3';
update stud_test set stud_id=4 WHERE unique_ID='stud_test$4';
update stud_test set stud_id=1 WHERE unique_ID='stud_test$5';
update stud_test set stud_id=5 WHERE unique_ID='stud_test$6';
update stud_test set stud_id=28 WHERE unique_ID='stud_test$7';
update stud_test set stud_id=61 WHERE unique_ID='stud_test$8';
update stud_test set stud_id=24 WHERE unique_ID='stud_test$9';
update stud_test set stud_id=29 WHERE unique_ID='stud_test$10';
update stud_test set stud_id=54 WHERE unique_ID='stud_test$11';
update stud_test set stud_id=5 WHERE unique_ID='stud_test$12';
update stud_test set stud_id=10 WHERE unique_ID='stud_test$13';
update stud_test set stud_id=4 WHERE unique_ID='stud_test$14';


update stud_test set test_id=5 WHERE unique_ID='stud_test$0';
update stud_test set test_id=5 WHERE unique_ID='stud_test$1';
update stud_test set test_id=5 WHERE unique_ID='stud_test$2';
update stud_test set test_id=5 WHERE unique_ID='stud_test$3';
update stud_test set test_id=6 WHERE unique_ID='stud_test$4';
update stud_test set test_id=6 WHERE unique_ID='stud_test$5';
update stud_test set test_id=6 WHERE unique_ID='stud_test$6';
update stud_test set test_id=6 WHERE unique_ID='stud_test$7';
update stud_test set test_id=34 WHERE unique_ID='stud_test$8';
update stud_test set test_id=34 WHERE unique_ID='stud_test$9';
update stud_test set test_id=34 WHERE unique_ID='stud_test$10';
update stud_test set test_id=8 WHERE unique_ID='stud_test$11';
update stud_test set test_id=8 WHERE unique_ID='stud_test$12';
update stud_test set test_id=9 WHERE unique_ID='stud_test$13';
update stud_test set test_id=5 WHERE unique_ID='stud_test$14';


update stud_test set status='submitted' WHERE unique_ID='stud_test$0';
update stud_test set status='timeout' WHERE unique_ID='stud_test$1';
update stud_test set status='timeout' WHERE unique_ID='stud_test$2';
update stud_test set status='timeout' WHERE unique_ID='stud_test$3';
update stud_test set status='submitted' WHERE unique_ID='stud_test$4';
update stud_test set status='incomplete' WHERE unique_ID='stud_test$5';
update stud_test set status='submitted' WHERE unique_ID='stud_test$6';
update stud_test set status='timeout' WHERE unique_ID='stud_test$7';
update stud_test set status='timeout' WHERE unique_ID='stud_test$8';
update stud_test set status='timeout' WHERE unique_ID='stud_test$9';
update stud_test set status='timeout' WHERE unique_ID='stud_test$10';
update stud_test set status='incomplete' WHERE unique_ID='stud_test$11';
update stud_test set status='timeout' WHERE unique_ID='stud_test$12';
update stud_test set status='incomplete' WHERE unique_ID='stud_test$13';
update stud_test set status='timeout' WHERE unique_ID='stud_test$14';


update stud_test set start_date=63 WHERE unique_ID='stud_test$0';
update stud_test set start_date=63 WHERE unique_ID='stud_test$1';
update stud_test set start_date=63 WHERE unique_ID='stud_test$2';
update stud_test set start_date=62 WHERE unique_ID='stud_test$3';
update stud_test set start_date=62 WHERE unique_ID='stud_test$4';
update stud_test set start_date=62 WHERE unique_ID='stud_test$5';
update stud_test set start_date=63 WHERE unique_ID='stud_test$6';
update stud_test set start_date=62 WHERE unique_ID='stud_test$7';
update stud_test set start_date=63 WHERE unique_ID='stud_test$8';
update stud_test set start_date=63 WHERE unique_ID='stud_test$9';
update stud_test set start_date=63 WHERE unique_ID='stud_test$10';
update stud_test set start_date=62 WHERE unique_ID='stud_test$11';
update stud_test set start_date=63 WHERE unique_ID='stud_test$12';
update stud_test set start_date=62 WHERE unique_ID='stud_test$13';
update stud_test set start_date=57 WHERE unique_ID='stud_test$14';


update stud_test set end_date=63 WHERE unique_ID='stud_test$0';
update stud_test set end_date=63 WHERE unique_ID='stud_test$1';
update stud_test set end_date=63 WHERE unique_ID='stud_test$2';
update stud_test set end_date=63 WHERE unique_ID='stud_test$3';
update stud_test set end_date=62 WHERE unique_ID='stud_test$4';
update stud_test set end_date=62 WHERE unique_ID='stud_test$5';
update stud_test set end_date=63 WHERE unique_ID='stud_test$6';
update stud_test set end_date=62 WHERE unique_ID='stud_test$7';
update stud_test set end_date=61 WHERE unique_ID='stud_test$8';
update stud_test set end_date=61 WHERE unique_ID='stud_test$9';
update stud_test set end_date=62 WHERE unique_ID='stud_test$10';
update stud_test set end_date=62 WHERE unique_ID='stud_test$11';
update stud_test set end_date=62 WHERE unique_ID='stud_test$12';
update stud_test set end_date=63 WHERE unique_ID='stud_test$13';
update stud_test set end_date=60 WHERE unique_ID='stud_test$14';


update stud_test set start_time=32 WHERE unique_ID='stud_test$0';
update stud_test set start_time=45 WHERE unique_ID='stud_test$1';
update stud_test set start_time=28 WHERE unique_ID='stud_test$2';
update stud_test set start_time=36 WHERE unique_ID='stud_test$3';
update stud_test set start_time=24 WHERE unique_ID='stud_test$4';
update stud_test set start_time=24 WHERE unique_ID='stud_test$5';
update stud_test set start_time=56 WHERE unique_ID='stud_test$6';
update stud_test set start_time=32 WHERE unique_ID='stud_test$7';
update stud_test set start_time=44 WHERE unique_ID='stud_test$8';
update stud_test set start_time=30 WHERE unique_ID='stud_test$9';
update stud_test set start_time=31 WHERE unique_ID='stud_test$10';
update stud_test set start_time=44 WHERE unique_ID='stud_test$11';
update stud_test set start_time=31 WHERE unique_ID='stud_test$12';
update stud_test set start_time=32 WHERE unique_ID='stud_test$13';
update stud_test set start_time=22 WHERE unique_ID='stud_test$14';


update stud_test set end_time=33 WHERE unique_ID='stud_test$0';
update stud_test set end_time=60 WHERE unique_ID='stud_test$1';
update stud_test set end_time=34 WHERE unique_ID='stud_test$2';
update stud_test set end_time=63 WHERE unique_ID='stud_test$3';
update stud_test set end_time=40 WHERE unique_ID='stud_test$4';
update stud_test set end_time=33 WHERE unique_ID='stud_test$5';
update stud_test set end_time=57 WHERE unique_ID='stud_test$6';
update stud_test set end_time=34 WHERE unique_ID='stud_test$7';
update stud_test set end_time=62 WHERE unique_ID='stud_test$8';
update stud_test set end_time=32 WHERE unique_ID='stud_test$9';
update stud_test set end_time=32 WHERE unique_ID='stud_test$10';
update stud_test set end_time=45 WHERE unique_ID='stud_test$11';
update stud_test set end_time=32 WHERE unique_ID='stud_test$12';
update stud_test set end_time=33 WHERE unique_ID='stud_test$13';
update stud_test set end_time=40 WHERE unique_ID='stud_test$14';


update stud_test set duration=1 WHERE unique_ID='stud_test$0';
update stud_test set duration=15 WHERE unique_ID='stud_test$1';
update stud_test set duration=6 WHERE unique_ID='stud_test$2';
update stud_test set duration=27 WHERE unique_ID='stud_test$3';
update stud_test set duration=16 WHERE unique_ID='stud_test$4';
update stud_test set duration=9 WHERE unique_ID='stud_test$5';
update stud_test set duration=1 WHERE unique_ID='stud_test$6';
update stud_test set duration=2 WHERE unique_ID='stud_test$7';
update stud_test set duration=18 WHERE unique_ID='stud_test$8';
update stud_test set duration=2 WHERE unique_ID='stud_test$9';
update stud_test set duration=1 WHERE unique_ID='stud_test$10';
update stud_test set duration=1 WHERE unique_ID='stud_test$11';
update stud_test set duration=1 WHERE unique_ID='stud_test$12';
update stud_test set duration=1 WHERE unique_ID='stud_test$13';
update stud_test set duration=18 WHERE unique_ID='stud_test$14';


update stud_test set marks=63 WHERE unique_ID='stud_test$0';
update stud_test set marks=63 WHERE unique_ID='stud_test$1';
update stud_test set marks=63 WHERE unique_ID='stud_test$2';
update stud_test set marks=62 WHERE unique_ID='stud_test$3';
update stud_test set marks=63 WHERE unique_ID='stud_test$4';
update stud_test set marks=60 WHERE unique_ID='stud_test$5';
update stud_test set marks=63 WHERE unique_ID='stud_test$6';
update stud_test set marks=60 WHERE unique_ID='stud_test$7';
update stud_test set marks=62 WHERE unique_ID='stud_test$8';
update stud_test set marks=63 WHERE unique_ID='stud_test$9';
update stud_test set marks=63 WHERE unique_ID='stud_test$10';
update stud_test set marks=63 WHERE unique_ID='stud_test$11';
update stud_test set marks=62 WHERE unique_ID='stud_test$12';
update stud_test set marks=63 WHERE unique_ID='stud_test$13';
update stud_test set marks=63 WHERE unique_ID='stud_test$14';



alter table companies add constraint pk1 PRIMARY KEY (company_id);
alter table colleges add constraint pk2 PRIMARY KEY (college_id);
alter table interviewers add constraint pk3 PRIMARY KEY (interviewers_id);
alter table students add constraint pk4 PRIMARY KEY (stud_id);
alter table coding_test add constraint pk5 PRIMARY KEY (test_id);
alter table stud_test add constraint pk6 PRIMARY KEY (stud_id,test_id);

alter table companies drop column unique_ID;
alter table colleges drop column unique_ID;
alter table interviewers drop column unique_ID;
alter table students drop column unique_ID;
alter table coding_test drop column unique_ID;
alter table stud_test drop column unique_ID;
