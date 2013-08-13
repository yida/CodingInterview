debug = true 
debug = false

filename = arg[1]

input_file = io.open(filename, 'r')
T = input_file:read('*number')
Q = input_file:read('*number')
N = input_file:read('*number')
Topic = {}
for i = 1, T do
  id = input_file:read('*number')
  x = input_file:read('*number')
  y = input_file:read('*number')
--  print(id, x, y)
  Topic[i] = {}
  Topic[i].id = id;
  Topic[i].x = x;
  Topic[i].y = y;
  Topic[i].questions = {}
end
--print('topics '..#Topic)
--for i = 1, T do
--  print(Topic[i].id, Topic[i].x, Topic[i].y)
--end

--print('question ');
Questions = {}
for i = 1, Q do
  id = input_file:read('*number')
  t_num = input_file:read('*number')
  Questions[i] = {}
  Questions[i].id = id
  Questions[i].topics = {}
  for j = 1, t_num do
    t_id = input_file:read('*number') 
    if not Topic[t_id + 1].questions then Topic[t_id + 1].questions = {} end
    Topic[t_id + 1].questions[#Topic[t_id + 1].questions + 1] = id
  end
end
--for i = 1, T do
--  for j = 1, #Topic[i].questions do
--    io.write(Topic[i].questions[j]..' ')
--  end
--  io.write('\n')
--end

function merge_sort(topic, p, r, k)
  if r > p then
    local first_half = merge_sort(topic, p, k, math.floor((p + k)/2))
    local second_half = merge_sort(topic, k + 1, r, math.floor((k + 1 + r)/2))
    first_idx = 1;
    second_idx = 1;
    local merge = {}
    while (first_idx <= #first_half and second_idx <= #second_half) do
      if math.abs(first_half[first_idx].distance - second_half[second_idx].distance) <= 0.001 then
        if first_half[first_idx].id > second_half[second_idx].id then
          merge[#merge + 1] = first_half[first_idx]
          first_idx = first_idx + 1
        else
          merge[#merge + 1] = second_half[second_idx]
          second_idx = second_idx + 1
        end
      elseif first_half[first_idx].distance < second_half[second_idx].distance then
          merge[#merge + 1] = first_half[first_idx]
          first_idx = first_idx + 1
      else
          merge[#merge + 1] = second_half[second_idx]
          second_idx = second_idx + 1
      end
    end
    while (first_idx <= #first_half) do
      merge[#merge + 1] = first_half[first_idx]
      first_idx = first_idx + 1
    end
    while (second_idx <= #second_half) do
      merge[#merge + 1] = second_half[second_idx]
      second_idx = second_idx + 1
    end
    return merge
  else
    return {topic[k]}
  end
end


function topic_query(num, x, y) 
  for i = 1, #Topic do
    Topic[i].distance = math.sqrt((Topic[i].x - x)^2 + (Topic[i].y -y)^2);
  end

  Topic = merge_sort(Topic, 1, #Topic, math.floor((1 + #Topic) / 2))
  for i = 1, math.min(num, #Topic) do
    if debug then
      io.write(Topic[i].id..':'..Topic[i].distance..'\n')
    else
      io.write(Topic[i].id..' ')
    end
  end
  io.write('\n')

end

function question_query(num, x, y)
  for i = 1, #Topic do
    Topic[i].distance = math.sqrt((Topic[i].x - x)^2 + (Topic[i].y - y)^2);
  end

  Topic = merge_sort(Topic, 1, #Topic, math.floor((1 + #Topic) / 2))
  ques_unique = {}  
  topic_idx = 1
  while (topic_idx <= #Topic and #ques_unique <= num) do
    for i = 1, #Topic[topic_idx].questions do
      ques_id = Topic[topic_idx].questions[i]
      if not ques_unique[tostring(ques_id)] then
        ques_unique[tostring(ques_id)] = Questions[ques_id + 1]
        ques_unique[tostring(ques_id)].distance = Topic[topic_idx].distance
      end
    end
    topic_idx = topic_idx + 1
  end
  ques = {}
  for k, v in pairs(ques_unique) do
--    print(k, v)
    ques[#ques + 1] = v
  end

--  for i = 1, #ques do
--    print(ques[i].id, ques[i].distance)
--  end

  ques = merge_sort(ques, 1, #ques, math.floor((1 + #ques) / 2))
--  print(#ques, num)
  for i = 1, math.min(num, #ques) do
--  for i = 1, #ques do
    if debug then
      io.write(ques[i].id..':'..ques[i].distance..'\n')
    else
      io.write(ques[i].id..' ')
    end
  end
  io.write('\n')
end

for i = 1, N do
  qtype = input_file:read(2)
  max_num = input_file:read('*number')
  goal_x = input_file:read('*number')
  goal_y = input_file:read('*number')
--  print(qtype, max_num, goal_x, goal_y)
  if qtype:find('t') then
--    print('topic query')
    topic_query(max_num, goal_x, goal_y)
  elseif qtype:find('q') then
--    print('question query')
    question_query(max_num, goal_x, goal_y)
  end
end
