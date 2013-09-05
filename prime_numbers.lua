output = io.open('buffer', 'w')

function generate_prime(primes, largest)
  local test_number = primes[#primes] + 1
  
  while test_number <= largest do
    local counter = 1
    local divided = false 
    while counter <= #primes do
      if primes[counter] > math.sqrt(largest) then
        break;
      end
      if test_number % primes[counter] == 0 then
        divided = true
        break;
      end
      counter = counter + 1
    end
    if not divided then
      print(test_number)
      output:write(test_number..',')
      primes[#primes + 1] = test_number
    end
    test_number = test_number + 1
  end
  return primes
end

filename = arg[1]
input = io.open(filename, 'r')
number = input:read("*number")

primes = {2}
output:write('2,')
while number do
  primes = generate_prime(primes, number)
--  for i = 1, #primes - 1 do
--    io.write(primes[i]..',')
--  end
--  print(primes[#primes])
  number = input:read("*number")
end
