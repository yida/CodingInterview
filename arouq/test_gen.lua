
filename = "test2.txt"
file = io.open(filename, 'w');

topicNum = 3;
questionNum = 6;
queryNum = 2;
file:write(topicNum..' '..questionNum..' '..queryNum);



file:close();
