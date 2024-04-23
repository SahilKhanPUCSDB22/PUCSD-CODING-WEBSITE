drop table stud_test;
drop table coding_test;
drop table students ;
drop table colleges;
drop table interviewers;
drop table companies;

create table companies (
	unique_ID varchar(100) primary key,
	company_name varchar(100),
	company_location varchar(100),
	company_domain text);

create table colleges(
	unique_ID varchar(100) primary key,
       	college_name varchar(100),
	college_location varchar(100),
	college_domain text);

create table interviewers(
	unique_ID varchar(100) primary key,
       	interviewers_name varchar(100),
	interviewers_role varchar(100),
	interviewers_password varchar(50),
	company_id varchar(100) references companies(unique_ID));

create table students(
	unique_ID varchar(100) primary key,
	stud_name varchar(100),
	stud_add varchar(100),
	stud_stream varchar(100),
	stud_password varchar(50),
	stud_degree text,
	college_id varchar(100) references colleges(unique_ID));

create table coding_test(
	unique_ID varchar(100) primary key,
	test_name varchar(100),
	test_duration int,
	test_start_date int,
	test_end_date int,	
	interviewers_id varchar(100) references interviewers(unique_ID),
	questions text);

create table stud_test(
	unique_ID varchar(100) primary key,
	stud_id varchar(100) references students(unique_ID),
	test_id varchar(100) references coding_test(unique_ID),
       	status varchar(100),
	start_date int,
	end_date int,
	start_time int,
	end_time int,
	duration int,
	marks int);

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


update companies set company_name='bookface$0' WHERE unique_ID='companies$0';
update companies set company_name='chatsnap$0' WHERE unique_ID='companies$1';
update companies set company_name='chatsnap$0' WHERE unique_ID='companies$2';
update companies set company_name='bookface$0' WHERE unique_ID='companies$3';
update companies set company_name='wtps$0' WHERE unique_ID='companies$4';
update companies set company_name='bookface$0' WHERE unique_ID='companies$5';
update companies set company_name='wtps$0' WHERE unique_ID='companies$6';
update companies set company_name='bookface$0' WHERE unique_ID='companies$7';
update companies set company_name='gram$0' WHERE unique_ID='companies$8';
update companies set company_name='chatsnap$0' WHERE unique_ID='companies$9';


update companies set company_location='mumbai$0' WHERE unique_ID='companies$0';
update companies set company_location='banglore$0' WHERE unique_ID='companies$1';
update companies set company_location='banglore$0' WHERE unique_ID='companies$2';
update companies set company_location='banglore$0' WHERE unique_ID='companies$3';
update companies set company_location='hyd$0' WHERE unique_ID='companies$4';
update companies set company_location='banglore$0' WHERE unique_ID='companies$5';
update companies set company_location='hyd$0' WHERE unique_ID='companies$6';
update companies set company_location='kolkata$0' WHERE unique_ID='companies$7';
update companies set company_location='delhi$0' WHERE unique_ID='companies$8';
update companies set company_location='kolkata$0' WHERE unique_ID='companies$9';


update companies set company_domain='product$0' WHERE unique_ID='companies$0';
update companies set company_domain='product$0' WHERE unique_ID='companies$1';
update companies set company_domain='product$0' WHERE unique_ID='companies$2';
update companies set company_domain='product$0' WHERE unique_ID='companies$3';
update companies set company_domain='product$0' WHERE unique_ID='companies$4';
update companies set company_domain='service$0' WHERE unique_ID='companies$5';
update companies set company_domain='service$0' WHERE unique_ID='companies$6';
update companies set company_domain='consultancy$0' WHERE unique_ID='companies$7';
update companies set company_domain='hardware$0' WHERE unique_ID='companies$8';
update companies set company_domain='hardware$0' WHERE unique_ID='companies$9';




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


update colleges set college_name='tnu$0' WHERE unique_ID='colleges$0';
update colleges set college_name='hu$0' WHERE unique_ID='colleges$1';
update colleges set college_name='bu$0' WHERE unique_ID='colleges$2';
update colleges set college_name='hu$0' WHERE unique_ID='colleges$3';
update colleges set college_name='dlu$0' WHERE unique_ID='colleges$4';
update colleges set college_name='hu$0' WHERE unique_ID='colleges$5';
update colleges set college_name='ku$0' WHERE unique_ID='colleges$6';
update colleges set college_name='dlu$0' WHERE unique_ID='colleges$7';
update colleges set college_name='bu$0' WHERE unique_ID='colleges$8';
update colleges set college_name='ku$0' WHERE unique_ID='colleges$9';


update colleges set college_location='kashmir$0' WHERE unique_ID='colleges$0';
update colleges set college_location='kashmir$0' WHERE unique_ID='colleges$1';
update colleges set college_location='kashmir$0' WHERE unique_ID='colleges$2';
update colleges set college_location='delhi$0' WHERE unique_ID='colleges$3';
update colleges set college_location='delhi$0' WHERE unique_ID='colleges$4';
update colleges set college_location='kolkata$0' WHERE unique_ID='colleges$5';
update colleges set college_location='kolkata$0' WHERE unique_ID='colleges$6';
update colleges set college_location='kolkata$0' WHERE unique_ID='colleges$7';
update colleges set college_location='mumbai$0' WHERE unique_ID='colleges$8';
update colleges set college_location='lucknow$0' WHERE unique_ID='colleges$9';


update colleges set college_domain='product$0' WHERE unique_ID='colleges$0';
update colleges set college_domain='product$0' WHERE unique_ID='colleges$1';
update colleges set college_domain='product$0' WHERE unique_ID='colleges$2';
update colleges set college_domain='product$0' WHERE unique_ID='colleges$3';
update colleges set college_domain='service$0' WHERE unique_ID='colleges$4';
update colleges set college_domain='service$0' WHERE unique_ID='colleges$5';
update colleges set college_domain='service$0' WHERE unique_ID='colleges$6';
update colleges set college_domain='service$0' WHERE unique_ID='colleges$7';
update colleges set college_domain='service$0' WHERE unique_ID='colleges$8';
update colleges set college_domain='hardware$0' WHERE unique_ID='colleges$9';




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


update interviewers set interviewers_name='sahil$0' WHERE unique_ID='interviewers$0';
update interviewers set interviewers_name='snehal$0' WHERE unique_ID='interviewers$1';
update interviewers set interviewers_name='nikhil$0' WHERE unique_ID='interviewers$2';
update interviewers set interviewers_name='nikhil$0' WHERE unique_ID='interviewers$3';
update interviewers set interviewers_name='nikhil$0' WHERE unique_ID='interviewers$4';
update interviewers set interviewers_name='nikhil$0' WHERE unique_ID='interviewers$5';
update interviewers set interviewers_name='talha$0' WHERE unique_ID='interviewers$6';
update interviewers set interviewers_name='nandini$0' WHERE unique_ID='interviewers$7';
update interviewers set interviewers_name='nikhil$0' WHERE unique_ID='interviewers$8';
update interviewers set interviewers_name='nikhil$0' WHERE unique_ID='interviewers$9';


update interviewers set interviewers_role='P$0' WHERE unique_ID='interviewers$0';
update interviewers set interviewers_role='WM$0' WHERE unique_ID='interviewers$1';
update interviewers set interviewers_role='P$0' WHERE unique_ID='interviewers$2';
update interviewers set interviewers_role='VP$0' WHERE unique_ID='interviewers$3';
update interviewers set interviewers_role='CEO$0' WHERE unique_ID='interviewers$4';
update interviewers set interviewers_role='WM$0' WHERE unique_ID='interviewers$5';
update interviewers set interviewers_role='P$0' WHERE unique_ID='interviewers$6';
update interviewers set interviewers_role='P$0' WHERE unique_ID='interviewers$7';
update interviewers set interviewers_role='VP$0' WHERE unique_ID='interviewers$8';
update interviewers set interviewers_role='P$0' WHERE unique_ID='interviewers$9';


update interviewers set interviewers_password='String4&quot' WHERE unique_ID='interviewers$0';
update interviewers set interviewers_password='String1&quot' WHERE unique_ID='interviewers$1';
update interviewers set interviewers_password='String3&quot' WHERE unique_ID='interviewers$2';
update interviewers set interviewers_password='String2&quot' WHERE unique_ID='interviewers$3';
update interviewers set interviewers_password='String4&quot' WHERE unique_ID='interviewers$4';
update interviewers set interviewers_password='String4&quot' WHERE unique_ID='interviewers$5';
update interviewers set interviewers_password='String4&quot' WHERE unique_ID='interviewers$6';
update interviewers set interviewers_password='String4&quot' WHERE unique_ID='interviewers$7';
update interviewers set interviewers_password='String4&quot' WHERE unique_ID='interviewers$8';
update interviewers set interviewers_password='String4&quot' WHERE unique_ID='interviewers$9';


update interviewers set company_id='companies$8' WHERE unique_ID='interviewers$0';
update interviewers set company_id='companies$7' WHERE unique_ID='interviewers$1';
update interviewers set company_id='companies$2' WHERE unique_ID='interviewers$2';
update interviewers set company_id='companies$7' WHERE unique_ID='interviewers$3';
update interviewers set company_id='companies$2' WHERE unique_ID='interviewers$4';
update interviewers set company_id='companies$6' WHERE unique_ID='interviewers$5';
update interviewers set company_id='companies$7' WHERE unique_ID='interviewers$6';
update interviewers set company_id='companies$9' WHERE unique_ID='interviewers$7';
update interviewers set company_id='companies$9' WHERE unique_ID='interviewers$8';
update interviewers set company_id='companies$9' WHERE unique_ID='interviewers$9';




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


update students set stud_name='nikhil$0' WHERE unique_ID='students$0';
update students set stud_name='nikhil$0' WHERE unique_ID='students$1';
update students set stud_name='kartik$0' WHERE unique_ID='students$2';
update students set stud_name='kartik$0' WHERE unique_ID='students$3';
update students set stud_name='nandini$0' WHERE unique_ID='students$4';
update students set stud_name='nikhil$0' WHERE unique_ID='students$5';
update students set stud_name='nandini$0' WHERE unique_ID='students$6';
update students set stud_name='nandini$0' WHERE unique_ID='students$7';
update students set stud_name='talha$0' WHERE unique_ID='students$8';
update students set stud_name='nikhil$0' WHERE unique_ID='students$9';
update students set stud_name='sahil$0' WHERE unique_ID='students$10';
update students set stud_name='deepak$0' WHERE unique_ID='students$11';
update students set stud_name='snehal$0' WHERE unique_ID='students$12';
update students set stud_name='nandini$0' WHERE unique_ID='students$13';
update students set stud_name='nikhil$0' WHERE unique_ID='students$14';
update students set stud_name='talha$0' WHERE unique_ID='students$15';
update students set stud_name='snehal$0' WHERE unique_ID='students$16';
update students set stud_name='nikhil$0' WHERE unique_ID='students$17';
update students set stud_name='nandini$0' WHERE unique_ID='students$18';
update students set stud_name='kartik$0' WHERE unique_ID='students$19';
update students set stud_name='kartik$0' WHERE unique_ID='students$20';
update students set stud_name='nikhil$0' WHERE unique_ID='students$21';
update students set stud_name='nandini$0' WHERE unique_ID='students$22';
update students set stud_name='nandini$0' WHERE unique_ID='students$23';
update students set stud_name='talha$0' WHERE unique_ID='students$24';
update students set stud_name='nandini$0' WHERE unique_ID='students$25';
update students set stud_name='nandini$0' WHERE unique_ID='students$26';
update students set stud_name='nandini$0' WHERE unique_ID='students$27';
update students set stud_name='nandini$0' WHERE unique_ID='students$28';
update students set stud_name='nikhil$0' WHERE unique_ID='students$29';


update students set stud_add='kashmir$0' WHERE unique_ID='students$0';
update students set stud_add='kashmir$0' WHERE unique_ID='students$1';
update students set stud_add='kashmir$0' WHERE unique_ID='students$2';
update students set stud_add='kashmir$0' WHERE unique_ID='students$3';
update students set stud_add='kashmir$0' WHERE unique_ID='students$4';
update students set stud_add='kashmir$0' WHERE unique_ID='students$5';
update students set stud_add='kashmir$0' WHERE unique_ID='students$6';
update students set stud_add='kashmir$0' WHERE unique_ID='students$7';
update students set stud_add='kashmir$0' WHERE unique_ID='students$8';
update students set stud_add='kashmir$0' WHERE unique_ID='students$9';
update students set stud_add='kashmir$0' WHERE unique_ID='students$10';
update students set stud_add='kashmir$0' WHERE unique_ID='students$11';
update students set stud_add='kashmir$0' WHERE unique_ID='students$12';
update students set stud_add='kashmir$0' WHERE unique_ID='students$13';
update students set stud_add='kashmir$0' WHERE unique_ID='students$14';
update students set stud_add='kashmir$0' WHERE unique_ID='students$15';
update students set stud_add='kashmir$0' WHERE unique_ID='students$16';
update students set stud_add='kashmir$0' WHERE unique_ID='students$17';
update students set stud_add='kashmir$0' WHERE unique_ID='students$18';
update students set stud_add='kashmir$0' WHERE unique_ID='students$19';
update students set stud_add='kashmir$0' WHERE unique_ID='students$20';
update students set stud_add='kashmir$0' WHERE unique_ID='students$21';
update students set stud_add='delhi$0' WHERE unique_ID='students$22';
update students set stud_add='kolkata$0' WHERE unique_ID='students$23';
update students set stud_add='kolkata$0' WHERE unique_ID='students$24';
update students set stud_add='kolkata$0' WHERE unique_ID='students$25';
update students set stud_add='kolkata$0' WHERE unique_ID='students$26';
update students set stud_add='delhi$0' WHERE unique_ID='students$27';
update students set stud_add='kolkata$0' WHERE unique_ID='students$28';
update students set stud_add='delhi$0' WHERE unique_ID='students$29';


update students set stud_stream='stream$4' WHERE unique_ID='students$0';
update students set stud_stream='stream$4' WHERE unique_ID='students$1';
update students set stud_stream='stream$4' WHERE unique_ID='students$2';
update students set stud_stream='stream$4' WHERE unique_ID='students$3';
update students set stud_stream='stream$4' WHERE unique_ID='students$4';
update students set stud_stream='stream$4' WHERE unique_ID='students$5';
update students set stud_stream='stream$3' WHERE unique_ID='students$6';
update students set stud_stream='stream$4' WHERE unique_ID='students$7';
update students set stud_stream='stream$4' WHERE unique_ID='students$8';
update students set stud_stream='stream$2' WHERE unique_ID='students$9';
update students set stud_stream='stream$1' WHERE unique_ID='students$10';
update students set stud_stream='stream$4' WHERE unique_ID='students$11';
update students set stud_stream='stream$4' WHERE unique_ID='students$12';
update students set stud_stream='stream$2' WHERE unique_ID='students$13';
update students set stud_stream='stream$4' WHERE unique_ID='students$14';
update students set stud_stream='stream$3' WHERE unique_ID='students$15';
update students set stud_stream='stream$4' WHERE unique_ID='students$16';
update students set stud_stream='stream$3' WHERE unique_ID='students$17';
update students set stud_stream='stream$4' WHERE unique_ID='students$18';
update students set stud_stream='stream$4' WHERE unique_ID='students$19';
update students set stud_stream='stream$4' WHERE unique_ID='students$20';
update students set stud_stream='stream$4' WHERE unique_ID='students$21';
update students set stud_stream='stream$4' WHERE unique_ID='students$22';
update students set stud_stream='stream$3' WHERE unique_ID='students$23';
update students set stud_stream='stream$3' WHERE unique_ID='students$24';
update students set stud_stream='stream$4' WHERE unique_ID='students$25';
update students set stud_stream='stream$2' WHERE unique_ID='students$26';
update students set stud_stream='stream$3' WHERE unique_ID='students$27';
update students set stud_stream='stream$3' WHERE unique_ID='students$28';
update students set stud_stream='stream$3' WHERE unique_ID='students$29';


update students set stud_password='String2&quot' WHERE unique_ID='students$0';
update students set stud_password='String4&quot' WHERE unique_ID='students$1';
update students set stud_password='String4&quot' WHERE unique_ID='students$2';
update students set stud_password='String4&quot' WHERE unique_ID='students$3';
update students set stud_password='String4&quot' WHERE unique_ID='students$4';
update students set stud_password='String4&quot' WHERE unique_ID='students$5';
update students set stud_password='String4&quot' WHERE unique_ID='students$6';
update students set stud_password='String4&quot' WHERE unique_ID='students$7';
update students set stud_password='String4&quot' WHERE unique_ID='students$8';
update students set stud_password='String4&quot' WHERE unique_ID='students$9';
update students set stud_password='String4&quot' WHERE unique_ID='students$10';
update students set stud_password='String4&quot' WHERE unique_ID='students$11';
update students set stud_password='String4&quot' WHERE unique_ID='students$12';
update students set stud_password='String4&quot' WHERE unique_ID='students$13';
update students set stud_password='String4&quot' WHERE unique_ID='students$14';
update students set stud_password='String4&quot' WHERE unique_ID='students$15';
update students set stud_password='String2&quot' WHERE unique_ID='students$16';
update students set stud_password='String2&quot' WHERE unique_ID='students$17';
update students set stud_password='String4&quot' WHERE unique_ID='students$18';
update students set stud_password='String4&quot' WHERE unique_ID='students$19';
update students set stud_password='String4&quot' WHERE unique_ID='students$20';
update students set stud_password='String4&quot' WHERE unique_ID='students$21';
update students set stud_password='String4&quot' WHERE unique_ID='students$22';
update students set stud_password='String4&quot' WHERE unique_ID='students$23';
update students set stud_password='String0&quot' WHERE unique_ID='students$24';
update students set stud_password='String4&quot' WHERE unique_ID='students$25';
update students set stud_password='String4&quot' WHERE unique_ID='students$26';
update students set stud_password='String4&quot' WHERE unique_ID='students$27';
update students set stud_password='String4&quot' WHERE unique_ID='students$28';
update students set stud_password='String4&quot' WHERE unique_ID='students$29';


update students set stud_degree='MCA$0' WHERE unique_ID='students$0';
update students set stud_degree='MCA$0' WHERE unique_ID='students$1';
update students set stud_degree='MCA$0' WHERE unique_ID='students$2';
update students set stud_degree='MCA$0' WHERE unique_ID='students$3';
update students set stud_degree='MCA$0' WHERE unique_ID='students$4';
update students set stud_degree='MA$0' WHERE unique_ID='students$5';
update students set stud_degree='MCA$0' WHERE unique_ID='students$6';
update students set stud_degree='MCA$0' WHERE unique_ID='students$7';
update students set stud_degree='BSc$0' WHERE unique_ID='students$8';
update students set stud_degree='BCA$0' WHERE unique_ID='students$9';
update students set stud_degree='MCA$0' WHERE unique_ID='students$10';
update students set stud_degree='LLB$0' WHERE unique_ID='students$11';
update students set stud_degree='MCA$0' WHERE unique_ID='students$12';
update students set stud_degree='Btech$0' WHERE unique_ID='students$13';
update students set stud_degree='MCA$0' WHERE unique_ID='students$14';
update students set stud_degree='MCA$0' WHERE unique_ID='students$15';
update students set stud_degree='MCA$0' WHERE unique_ID='students$16';
update students set stud_degree='MCA$0' WHERE unique_ID='students$17';
update students set stud_degree='MCA$0' WHERE unique_ID='students$18';
update students set stud_degree='MCA$0' WHERE unique_ID='students$19';
update students set stud_degree='MCA$0' WHERE unique_ID='students$20';
update students set stud_degree='MCA$0' WHERE unique_ID='students$21';
update students set stud_degree='MCA$0' WHERE unique_ID='students$22';
update students set stud_degree='MCA$0' WHERE unique_ID='students$23';
update students set stud_degree='MCA$0' WHERE unique_ID='students$24';
update students set stud_degree='MCA$0' WHERE unique_ID='students$25';
update students set stud_degree='MCA$0' WHERE unique_ID='students$26';
update students set stud_degree='MCA$0' WHERE unique_ID='students$27';
update students set stud_degree='MCA$0' WHERE unique_ID='students$28';
update students set stud_degree='Mtech$0' WHERE unique_ID='students$29';


update students set college_id='colleges$9' WHERE unique_ID='students$0';
update students set college_id='colleges$9' WHERE unique_ID='students$1';
update students set college_id='colleges$9' WHERE unique_ID='students$2';
update students set college_id='colleges$9' WHERE unique_ID='students$3';
update students set college_id='colleges$9' WHERE unique_ID='students$4';
update students set college_id='colleges$9' WHERE unique_ID='students$5';
update students set college_id='colleges$9' WHERE unique_ID='students$6';
update students set college_id='colleges$9' WHERE unique_ID='students$7';
update students set college_id='colleges$9' WHERE unique_ID='students$8';
update students set college_id='colleges$9' WHERE unique_ID='students$9';
update students set college_id='colleges$9' WHERE unique_ID='students$10';
update students set college_id='colleges$9' WHERE unique_ID='students$11';
update students set college_id='colleges$9' WHERE unique_ID='students$12';
update students set college_id='colleges$9' WHERE unique_ID='students$13';
update students set college_id='colleges$9' WHERE unique_ID='students$14';
update students set college_id='colleges$9' WHERE unique_ID='students$15';
update students set college_id='colleges$9' WHERE unique_ID='students$16';
update students set college_id='colleges$9' WHERE unique_ID='students$17';
update students set college_id='colleges$9' WHERE unique_ID='students$18';
update students set college_id='colleges$9' WHERE unique_ID='students$19';
update students set college_id='colleges$9' WHERE unique_ID='students$20';
update students set college_id='colleges$9' WHERE unique_ID='students$21';
update students set college_id='colleges$9' WHERE unique_ID='students$22';
update students set college_id='colleges$8' WHERE unique_ID='students$23';
update students set college_id='colleges$8' WHERE unique_ID='students$24';
update students set college_id='colleges$8' WHERE unique_ID='students$25';
update students set college_id='colleges$7' WHERE unique_ID='students$26';
update students set college_id='colleges$8' WHERE unique_ID='students$27';
update students set college_id='colleges$9' WHERE unique_ID='students$28';
update students set college_id='colleges$3' WHERE unique_ID='students$29';




insert into coding_test values('coding_test$0');
insert into coding_test values('coding_test$1');
insert into coding_test values('coding_test$2');
insert into coding_test values('coding_test$3');
insert into coding_test values('coding_test$4');
insert into coding_test values('coding_test$5');
insert into coding_test values('coding_test$6');
insert into coding_test values('coding_test$7');
insert into coding_test values('coding_test$8');
insert into coding_test values('coding_test$9');


update coding_test set test_name='service$0' WHERE unique_ID='coding_test$0';
update coding_test set test_name='product$0' WHERE unique_ID='coding_test$1';
update coding_test set test_name='product$0' WHERE unique_ID='coding_test$2';
update coding_test set test_name='product$0' WHERE unique_ID='coding_test$3';
update coding_test set test_name='product$0' WHERE unique_ID='coding_test$4';
update coding_test set test_name='product$0' WHERE unique_ID='coding_test$5';
update coding_test set test_name='product$0' WHERE unique_ID='coding_test$6';
update coding_test set test_name='product$0' WHERE unique_ID='coding_test$7';
update coding_test set test_name='product$0' WHERE unique_ID='coding_test$8';
update coding_test set test_name='product$0' WHERE unique_ID='coding_test$9';


update coding_test set test_duration=63 WHERE unique_ID='coding_test$0';
update coding_test set test_duration=-5 WHERE unique_ID='coding_test$1';
update coding_test set test_duration=-8 WHERE unique_ID='coding_test$2';
update coding_test set test_duration=-10 WHERE unique_ID='coding_test$3';
update coding_test set test_duration=-12 WHERE unique_ID='coding_test$4';
update coding_test set test_duration=-14 WHERE unique_ID='coding_test$5';
update coding_test set test_duration=-15 WHERE unique_ID='coding_test$6';
update coding_test set test_duration=-18 WHERE unique_ID='coding_test$7';
update coding_test set test_duration=15 WHERE unique_ID='coding_test$8';
update coding_test set test_duration=14 WHERE unique_ID='coding_test$9';


update coding_test set test_start_date=63 WHERE unique_ID='coding_test$0';
update coding_test set test_start_date=62 WHERE unique_ID='coding_test$1';
update coding_test set test_start_date=63 WHERE unique_ID='coding_test$2';
update coding_test set test_start_date=49 WHERE unique_ID='coding_test$3';
update coding_test set test_start_date=63 WHERE unique_ID='coding_test$4';
update coding_test set test_start_date=63 WHERE unique_ID='coding_test$5';
update coding_test set test_start_date=63 WHERE unique_ID='coding_test$6';
update coding_test set test_start_date=63 WHERE unique_ID='coding_test$7';
update coding_test set test_start_date=63 WHERE unique_ID='coding_test$8';
update coding_test set test_start_date=63 WHERE unique_ID='coding_test$9';


update coding_test set test_end_date=63 WHERE unique_ID='coding_test$0';
update coding_test set test_end_date=63 WHERE unique_ID='coding_test$1';
update coding_test set test_end_date=63 WHERE unique_ID='coding_test$2';
update coding_test set test_end_date=63 WHERE unique_ID='coding_test$3';
update coding_test set test_end_date=58 WHERE unique_ID='coding_test$4';
update coding_test set test_end_date=63 WHERE unique_ID='coding_test$5';
update coding_test set test_end_date=62 WHERE unique_ID='coding_test$6';
update coding_test set test_end_date=63 WHERE unique_ID='coding_test$7';
update coding_test set test_end_date=63 WHERE unique_ID='coding_test$8';
update coding_test set test_end_date=63 WHERE unique_ID='coding_test$9';


update coding_test set interviewers_id='interviewers$9' WHERE unique_ID='coding_test$0';
update coding_test set interviewers_id='interviewers$9' WHERE unique_ID='coding_test$1';
update coding_test set interviewers_id='interviewers$9' WHERE unique_ID='coding_test$2';
update coding_test set interviewers_id='interviewers$8' WHERE unique_ID='coding_test$3';
update coding_test set interviewers_id='interviewers$7' WHERE unique_ID='coding_test$4';
update coding_test set interviewers_id='interviewers$6' WHERE unique_ID='coding_test$5';
update coding_test set interviewers_id='interviewers$5' WHERE unique_ID='coding_test$6';
update coding_test set interviewers_id='interviewers$4' WHERE unique_ID='coding_test$7';
update coding_test set interviewers_id='interviewers$3' WHERE unique_ID='coding_test$8';
update coding_test set interviewers_id='interviewers$3' WHERE unique_ID='coding_test$9';


update coding_test set questions='String4&quot' WHERE unique_ID='coding_test$0';
update coding_test set questions='String4&quot' WHERE unique_ID='coding_test$1';
update coding_test set questions='String4&quot' WHERE unique_ID='coding_test$2';
update coding_test set questions='String4&quot' WHERE unique_ID='coding_test$3';
update coding_test set questions='String4&quot' WHERE unique_ID='coding_test$4';
update coding_test set questions='String4&quot' WHERE unique_ID='coding_test$5';
update coding_test set questions='String4&quot' WHERE unique_ID='coding_test$6';
update coding_test set questions='String4&quot' WHERE unique_ID='coding_test$7';
update coding_test set questions='String2&quot' WHERE unique_ID='coding_test$8';
update coding_test set questions='String3&quot' WHERE unique_ID='coding_test$9';




insert into stud_test values('stud_test$0');
insert into stud_test values('stud_test$1');
insert into stud_test values('stud_test$2');
insert into stud_test values('stud_test$3');


update stud_test set stud_id='students$29' WHERE unique_ID='stud_test$0';
update stud_test set stud_id='students$29' WHERE unique_ID='stud_test$1';
update stud_test set stud_id='students$28' WHERE unique_ID='stud_test$2';
update stud_test set stud_id='students$27' WHERE unique_ID='stud_test$3';


update stud_test set test_id='coding_test$9' WHERE unique_ID='stud_test$0';
update stud_test set test_id='coding_test$8' WHERE unique_ID='stud_test$1';
update stud_test set test_id='coding_test$1' WHERE unique_ID='stud_test$2';
update stud_test set test_id='coding_test$3' WHERE unique_ID='stud_test$3';


update stud_test set status='completed$0' WHERE unique_ID='stud_test$0';
update stud_test set status='in_progress$0' WHERE unique_ID='stud_test$1';
update stud_test set status='completed$0' WHERE unique_ID='stud_test$2';
update stud_test set status='completed$0' WHERE unique_ID='stud_test$3';


update stud_test set start_date=38 WHERE unique_ID='stud_test$0';
update stud_test set start_date=63 WHERE unique_ID='stud_test$1';
update stud_test set start_date=63 WHERE unique_ID='stud_test$2';
update stud_test set start_date=63 WHERE unique_ID='stud_test$3';


update stud_test set end_date=59 WHERE unique_ID='stud_test$0';
update stud_test set end_date=40 WHERE unique_ID='stud_test$1';
update stud_test set end_date=63 WHERE unique_ID='stud_test$2';
update stud_test set end_date=63 WHERE unique_ID='stud_test$3';


update stud_test set start_time=63 WHERE unique_ID='stud_test$0';
update stud_test set start_time=63 WHERE unique_ID='stud_test$1';
update stud_test set start_time=63 WHERE unique_ID='stud_test$2';
update stud_test set start_time=-7 WHERE unique_ID='stud_test$3';


update stud_test set end_time=63 WHERE unique_ID='stud_test$0';
update stud_test set end_time=63 WHERE unique_ID='stud_test$1';
update stud_test set end_time=63 WHERE unique_ID='stud_test$2';
update stud_test set end_time=63 WHERE unique_ID='stud_test$3';


update stud_test set duration=63 WHERE unique_ID='stud_test$0';
update stud_test set duration=63 WHERE unique_ID='stud_test$1';
update stud_test set duration=63 WHERE unique_ID='stud_test$2';
update stud_test set duration=63 WHERE unique_ID='stud_test$3';


update stud_test set marks=62 WHERE unique_ID='stud_test$0';
update stud_test set marks=63 WHERE unique_ID='stud_test$1';
update stud_test set marks=63 WHERE unique_ID='stud_test$2';
update stud_test set marks=63 WHERE unique_ID='stud_test$3';



select * from companies;
select * from colleges;
select * from students;
select * from interviewers;
select * from coding_test;
select * from stud_test;




