primes = {1}

test_number = 2;
while #primes <= 1000 do
  local counter = 2
  local divided = false
  while not divided and counter <= #primes do
    if test_number % primes[counter] == 0 then
      divided = true
    end
    counter = counter + 1
  end
  if not divided then
    primes[#primes + 1] = test_number
  end
  test_number = test_number + 1
end

sum = 0
for counter = 2, #primes do
  sum = sum + primes[counter]
end
print(sum)
