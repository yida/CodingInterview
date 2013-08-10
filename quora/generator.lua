T = 10000
Q = 1000
N = 10000

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
  for i = 1, topics do
    io.write(' '..math.random(T + 1) - 1)
  end
  io.write('\n')
end
-- Queries
for i = 1, N do
  query_type_id = math.random(2)
  if query_type_id == 1 then
    query_type = 't'
    query_num = math.random(math.min(10, T) + 1) - 1
  else
    query_type = 'q'
    query_num = math.random(math.min(100, Q) + 1) - 1
  end
  x = math.random() * range;
  y = math.random() * range;  
  print(query_type..' '..query_num..' '..string.format('%.1f %.1f', x, y));
end
