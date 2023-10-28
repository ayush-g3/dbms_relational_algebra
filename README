symbols used for different RA operators 
sigma : $[condition] 
project : #[attributes comma separated] 
rename : %[new attribute names comma separated] 
union : + 
intersection : ^ 
set difference : - 
theta join : *[condition] 
left outer join : ~*[condition] 
right outer join : *~[condition] 
cross product : @ 
division : / 
 

in join condition the attribute name of the table on left should be on left and for right also. 
 

use && for AND, || for OR, ! for NOT 
comparators in conditions can be  
=, !=(for both strings and numbers) <,>,<=,>=(for numbers only) 
in conditions attribute and literal values are case insensitive  
table names are also case insensitive 
for saving the result use <- 
give the string/character literals within double quotes and they are case sensitive 
 

Sample tables are given as Book1, Book2 etc in database directory. 
Note that there should not be any blank lines anywhere in csv files 
 

SAMPLE COMMANDS 
command = "temp <- $[Age=21](#[Name, Age]($[Roll_No=1](Book1)))"; 
command = "$[Age=21](#[Name, Age]($[Roll_No=1](Book1)))"; 
command="#[Age, Roll_No, Name]($[(Age=19 && Name=\"Ayush Gangwar\") || Roll_No=3](Book1))"; 
command = "%[roll2, name2, age2](Book1)"; 
command = "Book1 + Book3"; 
command = "Book1 ^ Book3"; 
command = "Book1 - Book3"; 
command = "Book1 *[Roll_No = Student_Id] Book6"; 
command = "Book1 ~*[Roll_No = Student_Id] Book6"; 
command = "Book6 *~[Roll_No = Student_Id] Book1"; 
command = "Book1 @ Book2"; 
command = "Book4 / Book5"; 
 

 

Some other queries are in sample_commands.txt 