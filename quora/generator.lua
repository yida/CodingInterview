T = 10000
Q = 1000
N = 10000

T = 1000
Q = 500
N = 200

T = 10
Q = 5
N = 2

math.randomseed(os.time())
range = 1000000.0
print(T..' '..Q..' '..N)
-- Topics
for i = 1, T do
  id = i - 1
  x = math.random() * range;
  y = math.random() * range;
  print(id..' '..string.format('%.1f %.1f', x, y))
end
-- Questions
for i = 1, Q do
  topics = math.random(11) - 1
  io.write((i - 1)..' '..topics)
  unique_topic = {}
  topic_container = {}
  while (#topic_container < topics) do
    rand_id = math.random(T) - 1
    if not unique_topic[rand_id] then
      topic_container[#topic_container + 1] = rand_id
      unique_topic[rand_id] = 1;
    end
  end
  for i = 1, #topic_container do
    io.write(' '..topic_container[i])
  end
  io.write('\n')
end
-- Queries
for i = 1, N do
  query_type_id = math.random(2)
  if query_type_id == 1 then
    query_type = 't'
    query_num = math.random(math.min(10, T) - 1)
  else
    query_type = 'q'
    query_num = math.random(math.min(100, Q) - 1)
  end
  x = math.random() * range;
  y = math.random() * range;  
  print(query_type..' '..query_num..' '..string.format('%.1f %.1f', x, y));
end
