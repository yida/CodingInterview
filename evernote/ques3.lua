N = 10

print(N)

function print_big_int(number)
  if number < 0 then 
    print('negative') 
    io.write('-')
    number = - number;
  end
  num = number 
  div = num
  mod = 0
--  io.write('big:\n')
  num_array = {}
  while div > 0 do
--    print(div, mod)
    mod = math.fmod(div, 10)
    num_array[#num_array + 1] = mod
    div = math.floor(div / 10)
  end

  for i = #num_array, 1, -1 do
    io.write(num_array[i])
  end
  io.write('\n')
end

product = 1;
for i = 1, N do
  sign = math.random(2)
  num = math.random(50)
  if sign == 2 then
    num = - num
  end
  print(num)
  product = product * num 
--  print(product)
end
--print_big_int(product)
